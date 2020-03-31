// This demo driver is based on the Program 39.1 KansaLaplace2D.m from
// the book "Meshfree Approximation Methods with MATLAB, Gregory
// E. Fasshauer", World Scientific Publishing, 2007

// Include general/common includes, utilities and initialisation
#include "../../../../../src/general/common_includes.h"
#include "../../../../../src/general/utilities.h"
#include "../../../../../src/general/initialise.h"

// Matrices
#include "../../../../../src/matrices/cc_matrix.h"

// Nodes
#include "../../../../../src/data_structures/cc_node.h"

// We need to inherent from a mesh free problem
#include "../../../../../src/problem/ac_mesh_free_problem.h"

// The class to solve linear systems using numerical recipes
#include "../../../../../src/linear_solvers/cc_lu_solver_numerical_recipes.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../../../src/matrices/cc_matrix_armadillo.h"

// The class to solve linear systems using Armadillo's type matrices
#include "../../../../../src/linear_solvers/cc_solver_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

#ifdef CHAPCHOM_USES_VTK
#include "../../../../../src/vtk/cc_chapchom2vtk.h"
#endif // #ifdef CHAPCHOM_USES_VTK

using namespace chapchom;

// f function
template<class VEC_TYPE>
const Real Lu(VEC_TYPE &x)
{
 return -1.25*M_PI*M_PI*sin(M_PI*x(0))*cos(M_PI*x(1)/2.0);
}

// u exact solution
template<class VEC_TYPE>
const Real u_exact(VEC_TYPE &x)
{
 return sin(M_PI*x(0))*cos(M_PI*x(1)/2.0);
}

// Radial function
const Real psi(const Real r, const Real epsilon)
{
 return std::exp(-((r*epsilon)*(r*epsilon)));
}

// Laplacian psi
const Real Lpsi(const Real r, const Real epsilon)
{
 const Real er2 = (epsilon*r)*(epsilon*r);
 return 4*epsilon*epsilon*std::exp(-er2)*(er2-1);
}

#if 0
template<class MAT_TYPE, class VEC_TYPE>
void compute_distance_matrix(MAT_TYPE &data_sites, MAT_TYPE &centers,
                             MAT_TYPE &distance_matrix)
{
 // Get the number of "vector points" on "data_sites"
 // Get the number of "vector points" on "centers"
 const unsigned n_vector_points_data_sites = data_sites.n_columns();
 const unsigned n_vector_points_centers = centers.n_columns();
 
 // The dimension of input vector points must be the same, otherwise
 // there is an error
 const unsigned dimension = data_sites.n_rows();
 const unsigned tmp_dimension = centers.n_rows();
 
 if (dimension != tmp_dimension)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The dimensions of the data sites vector and the\n"
                 << "centers vector are different\n"
                 << "dim(data_site):" << dimension
                 << "\ndim(centers):" << tmp_dimension
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Loop over all the data points in the first matrix
 for (unsigned m = 0; m < n_vector_points_data_sites; m++)
  {
   // Loop over all the data points in the second matrix
   for (unsigned n = 0; n < n_vector_points_centers; n++)
    {
     VEC_TYPE distance(dimension);
     //distance.allocate_memory();
     // Loop over the elements of both vectors
     for (unsigned k = 0; k < dimension; k++)
      {
       distance(k) = data_sites(k, m) - centers(k, n);
      }
     distance_matrix(m,n)=distance.norm_2();
    }
  }
 
}
#endif // #if 0

template<class MAT_TYPE, class VEC_TYPE>
void generate_interpolation_matrix_and_rhs_vector(std::vector<CCNode<Real> *> &nodes_pt,
                                                  std::vector<CCNode<Real> *> &centers_pt,
                                                  MAT_TYPE &interpolation_matrix,
                                                  VEC_TYPE &rhs_vector)
{
 // Get the number of nodes and centers
 const unsigned n_nodes = nodes_pt.size();
 const unsigned n_centers = centers_pt.size();
 
 // Get the dimension of the nodes and centers
 const unsigned dimension = nodes_pt[0]->dimension();
 const unsigned tmp_dimension = centers_pt[0]->dimension();
 
 if (dimension != tmp_dimension)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The dimension of the nodes and the centers\n"
                 << "is different\n"
                 << "dim(nodes):" << dimension
                 << "\ndim(centers):" << tmp_dimension
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Loop over all nodes
 for (unsigned m = 0; m < n_nodes; m++)
  {
   // Loop over all centers
   for (unsigned n = 0; n < n_centers; n++)
    {
     VEC_TYPE distance(dimension);
     // Loop over the elements of both, the node and the center
     for (unsigned k = 0; k < dimension; k++)
      {
       distance(k) = nodes_pt[m]->get_position(k) - centers_pt[n]->get_position(k);
      }
     Real r = distance.norm_2();
     interpolation_matrix(m,n) = Lpsi(r, epsilon);
     //interpolation_matrix(m, n) = psi(r, epsilon);
    }
   
   VEC_TYPE tmp_v(dimension);
   for (unsigned k = 0; k < dimension; k++)
    {
     tmp_v(k) = nodes_pt[m]->get_position(k);
    }
   
   // --------------------------------------------------------------
   // Evaluate the function f() at the nodes positions 
   // --------------------------------------------------------------
   rhs_vector(m) = Lu<VEC_TYPE >(tmp_v);
   
  }
 
}

// =================================================================
// =================================================================
// =================================================================
/// This class inherits from the ACMeshFreeProblem class and
/// approximates a solution to the PDE
///
/// \Delta^2 \mathbf{u} = f(\mathbf{x})
///
/// where f(\mathbf{x}) = -1.25*M_PI*M_PI*sin(M_PI*x(0))*cos(M_PI*x(1)/2.0)
///
/// and Dirichlet boundary conditions
///
/// u(\mathbf{x}) = sin(M_PI*x(0)), when \mathbf{x} \in \Gamma_{1}
/// u(\mathbf{x}) = 0,              when \mathbf{x} \in \Gamma_{2}
///
/// where \Gamma_{1} = \{ \mathbf{x}: 0 \leq x(0) \leq 1, x(1) = 0 \} and
/// where \Gamma_{2} = \partial \Omega \Gamma_{1}
///
// =================================================================
// =================================================================
// =================================================================
 class CCMeshFreeLaplacianProblem : public virtual ACMeshFreeProblem
 {
 
 public:
 
  /// Constructor
  CCMeshFreeLaplacianProblem(std::ostringstream &output_filename,
                             std::ostringstream &output_filename_error)
   : ACMeshFreeProblem()
  {
   Output_file.open((output_filename.str()).c_str());
   Output_error_file.open((output_filename_error.str()).c_str());
  }
  
  /// Destructor
  ~CCMeshFreeLaplacianProblem()
  {
   Output_file.close();
   Output_error_file.close();
  }
  
  // Set initial conditions (empty)
  void set_initial_conditions() { }
  
  // Set boundary conditions
  void set_boundary_conditions()
  {
   // Get the number of boundary nodes
   const unsigned n_bnd_nodes = n_boundary_nodes();
   // Loop over the boundary nodes and assign boundary conditions
   for (unsigned i = 0; i < n_bnd_nodes; i++)
    {
     CCBoundaryNode<Real> *bnd_node_pt = Boundary_nodes_pt[i];
     // Check whether the node live on boundary 1 or boundary 2
     const unsigned bnd_id = 1;
     if (bnd_node_pt->is_on_boundary(bnd_id))
      {
       // Get node position
       const Real x = bnd_node_pt->get_position(0);
       const Real u_value = sin(M_PI*x);
       bnd_node_pt->set_variable(u_value, 0);
       bnd_node_pt->pin_u(0);
      }
     else
      {
       bnd_node_pt->set_variable(0, 0);
       bnd_node_pt->pin_u(0);
      }
     
    }
   
  }
  
  // Complete problem setup (set boundary conditions)
  void complete_problem_setup()
  {
   set_boundary_conditions();
  }
  
  // Document the solution
  void document_solution()
  {
   // Initial problem configuration
   Output_file << time() << "\t" << u(0) << std::endl;
   output_error();
  }
  
  // Output error
  void output_error()
  {
   // Compute the error 
   const Real t = this->time();
   const Real u_analytical = 1.0/(1.0+t);
   const Real error = std::fabs(u(0)-u_analytical);
   Output_error_file << time() << "\t" << error << std::endl;
  }
  
 protected:
  
  // The output file
  std::ofstream Output_file;
  // The error output file
  std::ofstream Output_error_file;
  
 }; // class CCMeshFreeLaplacianProblem

struct Args {
 argparse::ArgValue<Real> epsilon;
};

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{ 
 // Instantiate parser
 Args args;
 auto parser = argparse::ArgumentParser(argv[0], "Distance Matrix");
 
 // Add arguments  
 parser.add_argument<Real>(args.epsilon, "--epsilon")
  .help("Epsilon for phi")
  .default_value("9.0");
 
 // Parse the input arguments
 parser.parse_args(argc, argv);
 
 // --------------------------------------------------------------
 // RBF parameters
 // --------------------------------------------------------------
 // The value for epsilon
 //const Real epsilon = 21.1;
 //const Real epsilon = 9.0;
 Real epsilon = args.epsilon;
 
 // ----------------------------------------------------------------
 // Prepare the output file name
 // ----------------------------------------------------------------
 std::ostringstream output_solution_filename;
 output_solution_filename << "RESLT/soln.dat";
 //output_solution_filename.precision(8);
 
 // ----------------------------------------------------------------
 // Prepare the output error file name
 // ----------------------------------------------------------------
 std::ostringstream output_error_filename;
 output_error_filename << "RESLT/soln_error.dat";
 //output_error_filename.precision(8);
 
 // Create an instance of the problem
 CCMeshFreeLaplacianProblem problem(output_solution_filename, output_error_filename);
 
 // --------------------------------------------------------------
 // Domain specification
 // --------------------------------------------------------------
 // TODO: Create a DOMAIN (mesh?) type class
 // Create the nodes
 problem.create_nodes();
 
 // Set boundary conditions
 problem.complete_problem_setup();
 
#ifdef CHAPCHOM_PANIC_MODE
 // Output initial state of the nodes
 std::ostringstream output_nodes_filename;
 output_nodes_filename << "RESLT/nodes.dat";
 std::ostringstream output_boundary_nodes_filename;
 output_boundary_nodes_filename << "RESLT/boundary_nodes.dat";

 problem.output_nodes_information(output_nodes_filename);
 problem.output_boundary_nodes_information(output_boundary_nodes_filename);
#endif // #ifdef CHAPCHOM_PANIC_MODE
 
 // --------------------------------------------------------------
 // Set the problem and solve it
 // --------------------------------------------------------------
 
 // -------------------------------------------------------------- 
 // Create the interpolation matrix
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> interpolation_matrix(n_nodes, n_nodes);
#else
 CCMatrix<Real> interpolation_matrix(n_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // --------------------------------------------------------------
 // Create the right-hand side vector
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> rhs(n_nodes);
#else 
 CCVector<Real> rhs(n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // --------------------------------------------------------------
 // Generate the interpolation matrix and the right-hand side vector
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 generate_interpolation_matrix_and_rhs_vector<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> >(nodes_pt, nodes_pt, interpolation_matrix, rhs);
#else
 generate_interpolation_matrix_and_rhs_vector<CCMatrix<Real>, CCVector<Real> >(nodes_pt, nodes_pt, interpolation_matrix, rhs);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // The solution vector (with the respective number of rows) stores
 // the coefficients for the interpolant polynomials
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> sol(n_nodes);
#else
 CCVector<Real> sol(n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // --------------------------------------------------------------
 // Solve
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
  // Create an Armadillo linear solver
  CCSolverArmadillo<Real> linear_solver;
#else
 // Create a linear solver
 CCLUSolverNumericalRecipes<Real> linear_solver;
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 //std::cerr << "Distance matrix" << std::endl;
 //distance_matrix.print();
 //interpolation_matrix.print();
 
 // --------------------------------------------------------------
 // Solve the system of equations
 // --------------------------------------------------------------
 //linear_solver.solve(distance_matrix, rhs, sol);
 linear_solver.solve(interpolation_matrix, rhs, sol);
 //std::cerr << "Solution vector" << std::endl;
 //sol.print();
 
 //std::cerr << "Nodes positions and values" << std::endl;
 /*
 // Show results
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i]->print(true);
  }
 */
 
 // --------------------------------------------------------------
 // --------------------------------------------------------------
 // EVALUATION STAGE
 // --------------------------------------------------------------
 // --------------------------------------------------------------
 std::cerr << "\nEVALUATION\n" << std::endl;
 
 // --------------------------------------------------------------
 // Evaluate (compute error RMSE)
 // --------------------------------------------------------------
 const unsigned n_evaluation_points_per_dimension = pow(dim+1, degree+1);
 const unsigned n_evaluation_nodes = pow(n_evaluation_points_per_dimension, dim);
 // Distance between a pair of nodes
 const Real h_test = L / (Real)(n_evaluation_points_per_dimension - 1);
 
 // A vector of evaluation nodes
 std::vector<CCNode<Real> *> evaluation_nodes_pt(n_evaluation_nodes);
 // Create evaluation nodes
 for (unsigned long i = 0; i < n_evaluation_nodes; i++)
  {
   evaluation_nodes_pt[i] = new CCNode<Real>(dim, n_variables, n_history_values);
  } 
 
 // Assign positions
 unsigned long kk = 0;
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
   const Real position_i = i*h_test;
   for (unsigned j = 0; j < n_evaluation_points_per_dimension; j++)
    {
     const Real position_j = j*h_test;
     evaluation_nodes_pt[kk]->set_position(position_i, 0);
     evaluation_nodes_pt[kk]->set_position(position_j, 1);
     kk++;
    }
  }
 
 // Compute approximated solution at new positions
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> evaluation_nodes_position(dim, n_evaluation_nodes);
#else
 CCMatrix<Real> evaluation_nodes_position(dim, n_evaluation_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 //evaluation_nodes_position.allocate_memory();
 // --------------------------------------------------------------
 // Assign positions
 // --------------------------------------------------------------
 for (unsigned long i = 0; i < n_evaluation_nodes; i++)
  {
   evaluation_nodes_position(0, i) = evaluation_nodes_pt[i]->get_position(0);
   evaluation_nodes_position(1, i) = evaluation_nodes_pt[i]->get_position(1);
  }
 
 // Compute distance matrix with new positions
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> evaluation_distance_matrix(n_evaluation_nodes, n_nodes);
#else
 CCMatrix<Real> evaluation_distance_matrix(n_evaluation_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the distance matrix using the evaluation nodes position
 // and the original nodes positions
 // --------------------------------------------------------------
 //evaluation_distance_matrix.allocate_memory();
#ifdef CHAPCHOM_USES_ARMADILLO
 compute_distance_matrix<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> >(evaluation_nodes_position, nodes_position, evaluation_distance_matrix);
#else
 compute_distance_matrix<CCMatrix<Real>, CCVector<Real> >(evaluation_nodes_position, nodes_position, evaluation_distance_matrix);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 //approx_distance_matrix.print();
 
 // --------------------------------------------------------------
 // Create the interpolation matrix for evaluation nodes
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> interpolation_evaluation_matrix(n_evaluation_nodes, n_nodes);
#else
 CCMatrix<Real> interpolation_evaluation_matrix(n_evaluation_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the interpolation matrix using the RBF psi
 // --------------------------------------------------------------
 //interpolation_evaluation_matrix.allocate_memory();
#ifdef CHAPCHOM_USES_ARMADILLO
 psi<CCMatrixArmadillo<Real> >(evaluation_distance_matrix, interpolation_evaluation_matrix, epsilon);
#else
 psi<CCMatrix<Real> >(evaluation_distance_matrix, interpolation_evaluation_matrix, epsilon);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // Approximated solution
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> approx_sol(n_evaluation_nodes);
#else
 CCVector<Real> approx_sol(n_evaluation_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // Approximate solution at given points
 multiply_matrix_times_vector(interpolation_evaluation_matrix, sol, approx_sol);
 
 // --------------------------------------------------------------
 // Assign solution to nodes
 // --------------------------------------------------------------
 for (unsigned long i = 0; i < n_evaluation_nodes; i++)
  {
   evaluation_nodes_pt[i]->set_variable(approx_sol(i), 0);
  }
 
 // Move the positions of the nodes and the results into two CCData<T>
 // vectors
 std::vector<CCData<Real> > positions;
 std::vector<CCData<Real> > values;
 for (unsigned long i = 0; i < n_evaluation_nodes; i++)
  {
   positions.push_back(evaluation_nodes_pt[i]->x());
   values.push_back(evaluation_nodes_pt[i]->u());
  }
 
 // Output to file
 std::ostringstream output_filename;
 output_filename
  << "./RESLT/soln" << "_" << std::setfill('0') << "0";
 
 CCChapchom2VTK::get_instance().output_position_and_attribute_datas(positions, values, output_filename);
 
 /*
 // --------------------------------------------------------------
 // Output data for plotting
 // --------------------------------------------------------------
 std::ofstream output_file("RESLT/output.dat");
 // Output the number of data/points
 output_file << n_evaluation_points << std::endl;
 output_file << n_evaluation_points_per_dimension << std::endl;
 for (unsigned i = 0; i < n_evaluation_points; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     output_file << approx_solution_position(k, i) << " ";
    }
   output_file << approx_sol(i) << std::endl;
  }
 
 // Close output file
 output_file.close();
 */
 // --------------------------------------------------------------
 // Get real solution at given points and get the error 
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> real_sol(n_evaluation_nodes);
#else 
 CCVector<Real> real_sol(n_evaluation_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 //real_sol.allocate_memory();
 for (unsigned i = 0; i < n_evaluation_nodes; i++)
  {
#ifdef CHAPCHOM_USES_ARMADILLO
   CCVectorArmadillo<Real> tmp_v(dim);
#else
   CCVector<Real> tmp_v(dim);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   //tmp_v.allocate_memory();
   for (unsigned j = 0; j < dim; j++)
    {
     tmp_v(j) = evaluation_nodes_position(j, i);
    }
   // ------------------------
   // Evaluation at approx_solution_position
   real_sol(i) = u_exact(tmp_v);
  }
 /*
   {
   // Move the positions of the nodes and the results into two CCData<T>
   // vectors
   std::vector<CCData<Real> > solution_values;
   for (unsigned long i = 0; i < n_evaluation_nodes; i++)
   {
   CCData<Real> u(1);
   u(0) = real_sol(i);
   solution_values.push_back(u);
   DEB(real_sol(i));
   }
   // Output to file
   std::ostringstream output_sol_filename;
   output_sol_filename
   << "./RESLT/soln_real" << "_" << std::setfill('0') << "0";
  
   CCChapchom2VTK::get_instance().output_position_and_attribute_datas(positions, solution_values, output_sol_filename);
   }
 */
 // --------------------------------------------------------------
 // Compute error
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> error(n_evaluation_nodes);
#else
 CCVector<Real> error(n_evaluation_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 //error.allocate_memory();
 std::cerr << "ERRORS" << std::endl;
 for (unsigned i = 0; i < n_evaluation_nodes; i++)
  {
   //error(i) = real_sol(i) - 0.0;
   error(i) = real_sol(i) - approx_sol(i);
   //std::cerr << i << ": " << std::fabs(error(i)) << std::endl;
   //std::cerr << i << ": " << real_sol(i) << ":" << approx_sol(i) << std::endl;
  }
 
 // Move the error into a vector
 std::vector<CCData<Real> > error_to_plot;
 for (unsigned long i = 0; i < n_evaluation_nodes; i++)
  {
   CCData<Real> data(1);
   data(0) = error(i);
   error_to_plot.push_back(data);
  }
 
 // Output to file
 std::ostringstream error_filename;
 error_filename
  << "./RESLT/errorn" << "_" << std::setfill('0') << "0";

 CCChapchom2VTK::get_instance().output_position_and_attribute_datas(positions, error_to_plot, error_filename);
 
 const Real rms_error = error.norm_2() / sqrt(n_evaluation_nodes);
 
 // --------------------------------------------------------------
 // Output error
 // --------------------------------------------------------------
 std::ofstream error_file("RESLT/error.dat");
 for (unsigned i = 0; i < n_evaluation_nodes; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     error_file << evaluation_nodes_position(k, i) << " ";
    }
   error_file << error(i) << std::endl;
  }
 
 // Close error file
 error_file.close();
 
 // --------------------------------------------------------------
 // Summary
 // --------------------------------------------------------------
 std::cerr << std::endl;
 std::cerr << "Polynomial degree: " << degree << std::endl;
 std::cerr << "N. nodes per dimension: " << n_nodes_per_dim << std::endl;
 std::cerr << "N. total nodes: " << n_nodes << std::endl;
 
 std::cerr << "RBF[Epsilon]: " << epsilon << std::endl;
 
 std::cerr << "N. nodes per dimension (evaluation): " << n_evaluation_points_per_dimension << std::endl;
 std::cerr << "N. total nodes (evaluation): " << n_evaluation_nodes << std::endl;
 
 std::cerr << "RMS-error: " << rms_error << std::endl;
 
 // ==============================================================
 // ==============================================================
 
 // --------------------------------------------------------------
 // Delete nodes storage
 // --------------------------------------------------------------
 for (unsigned i = 0; i < n_nodes; i++)
  {
   delete nodes_pt[i];
  }
 
 return 0;
 
}


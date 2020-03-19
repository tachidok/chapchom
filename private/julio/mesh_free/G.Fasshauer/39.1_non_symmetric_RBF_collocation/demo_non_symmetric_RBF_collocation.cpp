// This demo driver is based on the Program 39.1 KansaLaplace2D.m from
// the book "Meshfree Approximation Methods with MATLAB, Gregory
// E. Fasshauer", World Scientific Publishing, 2007

// Include general/common includes, utilities and initialisation
#include "../../../../../src/general/common_includes.h"
#include "../../../../../src/general/utilities.h"
#include "../../../../../src/general/initialise.h"

// Matrices
#include "../../../../../src/matrices/cc_matrix.h"
#include "../../../../../src/data_structures/cc_node.h"

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
 // Initialise chapchom
 initialise_chapchom();

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
 
 // --------------------------------------------------------------
 // Domain specification
 // --------------------------------------------------------------
 // TODO: Create a DOMAIN (mesh?) type class
 
 // Dimension of the problem
 const unsigned dim = 2;
 
 // Specify the one-dimensional lenght of the domain
 const unsigned L = 1.0;
 
 // --------------------------------------------------------------
 // Create and give position to nodes
 // --------------------------------------------------------------
 // Nodes per dimension
 const unsigned n_nodes_per_dim = pow(2, 4);
 // The number of nodes
 const unsigned n_nodes = pow(n_nodes_per_dim, dim);
 // Distance between a pair of nodes
 const Real h = L / (Real)(n_nodes_per_dim - 1);
 // A vector of nodes
 std::vector<CCNode<Real> *> nodes_pt(n_nodes);
 
 // Number of variables stored in each node
 const unsigned n_variables = 1;
 
 // Create nodes
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i] = new CCNode<Real>(dim, n_variables);
  }
 
 // Assign positions
 unsigned kk = 0;
 for (unsigned i = 0; i < n_nodes_per_dim; i++)
  {
   const Real position_i = i*h;
   for (unsigned j = 0; j < n_nodes_per_dim; j++)
    {
     const Real position_j = j*h;
     nodes_pt[kk]->set_position(position_i, 0);
     nodes_pt[kk]->set_position(position_j, 1);
     kk++;
    }
  }
 
 // Create boundary nodes
 const unsigned n_nodes_per_boundary = n_nodes_per_dim;
 // Create total number of boundary nodes
 const unsigned n_boundary_nodes = (n_nodes_per_dim * 4) - 4;
 // A vector of boundary nodes
 std::vector<CCBoundaryNode<Real> *> boundary_nodes_pt(n_boundary_nodes);
 // The IDs for the boundaries
 const unsigned boundary_1_id = 1;
 const unsigned boundary_2_id = 2;
 
 // Create the boundary nodes
 for (unsigned i = 0; i < n_boundary_nodes; i++)
  {
   if (i < n_nodes_per_boundary)
    {
     boundary_nodes_pt[i] = new CCBoundaryNode<Real>(boundary_1_id, dim, n_variables);
    }
   else
    {
     boundary_nodes_pt[i] = new CCBoundaryNode<Real>(boundary_2_id, dim, n_variables);
    }
  }
 
 // We have two boundaries and two nodes lying on both boundaries
 boundary_nodes_pt[0]->add_to_boundary(boundary_2_id);
 boundary_nodes_pt[n_nodes_per_boundary-1]->add_to_boundary(boundary_2_id);
 
 // Assign positions
 kk = 0;
 for (unsigned i = 0; i < n_nodes_per_dim; i++)
  {
   const Real position_i = i*h;
   // (x, 0)
   boundary_nodes_pt[i]->set_position(position_i, 0);
   boundary_nodes_pt[i]->set_position(0, 1);
   // (x, 1)
   boundary_nodes_pt[i+n_nodes_per_dim]->set_position(position_i, 0);
   boundary_nodes_pt[i+n_nodes_per_dim]->set_position(1, 1);
   // (1, y)
   boundary_nodes_pt[i+n_nodes_per_dim*2]->set_position(1, 0);
   boundary_nodes_pt[i+n_nodes_per_dim*2]->set_position(position_i, 1);
   // (0, y)
   boundary_nodes_pt[i+n_nodes_per_dim*3]->set_position(0, 0);
   boundary_nodes_pt[i+n_nodes_per_dim*3]->set_position(position_i, 1);
   
  }
 
 // --------------------------------------------------------------
 // Output supporting nodes
 // --------------------------------------------------------------
 std::ofstream nodes_file("RESLT/nodes.dat");
 
 // Assign positions
 for (unsigned long i = 0; i < n_nodes; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     const Real r = rand();
     const Real position = static_cast<Real>(r / RAND_MAX) * L;
     // Generate position and assign it
     //const Real position = x[k];
     nodes_pt[i]->set_position(position, k);
     //x[k]+=h;
     nodes_file << position;
     if (k + 1 < dim)
      {
       nodes_file << " ";
      }
    }
   nodes_file << std::endl;
  }
 
 // Close support nodes file
 nodes_file.close();
 
 // --------------------------------------------------------------
 // Set initial conditions
 // --------------------------------------------------------------
 /*
 for (unsigned i = 0; i < n_nodes; i++)
 {
 for (unsigned j = 0; j < n_variables; j++)
 {
 const Real u = 0.0;
 nodes_pt[i]->set_variable(u, j);
 }
 }
 */
 
 // --------------------------------------------------------------
 // Set boundary conditions
 // --------------------------------------------------------------
 /*
 // Move the first and the last node to the boundary of the domain
 nodes_pt[0]->set_position(0.0, 0);
 nodes_pt[0]->set_variable(0.0, 0);
 nodes_pt[n_nodes-1]->set_position(1.0, 0);
 nodes_pt[n_nodes-1]->set_variable(1.0, 0);
 */
 
 // --------------------------------------------------------------
 // Set the problem and solve it
 // --------------------------------------------------------------
 
 // TODO: The distance matrix may be formed while we loop over the
 // nodes to extract their position
 
 // --------------------------------------------------------------
 // Loop over the nodes and extract their position and store them in a
 // matrix
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> nodes_position(dim, n_nodes);
#else
 CCMatrix<Real> nodes_position(dim, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // Each column stores the vector position of a node
 //nodes_position.allocate_memory();
 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned j = 0; j < dim; j++)
    {
     nodes_position(j, i) = nodes_pt[i]->get_position(j);
    }
  }
  
 // -------------------------------------------------------------- 
 // Create the distance matrix
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> distance_matrix(n_nodes, n_nodes);
#else
 CCMatrix<Real> distance_matrix(n_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the distance matrix using the nodes position centers
 // shifted by the same nodes position
 // --------------------------------------------------------------
 //distance_matrix.allocate_memory();
#ifdef CHAPCHOM_USES_ARMADILLO
 compute_distance_matrix<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> >(nodes_position, nodes_position, distance_matrix);
#else
 compute_distance_matrix<CCMatrix<Real>, CCVector<Real> >(nodes_position, nodes_position, distance_matrix);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // -------------------------------------------------------------- 
 // Create the interpolation matrix (the one that applies the RBF)
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCMatrixArmadillo<Real> interpolation_matrix(n_nodes, n_nodes);
#else
 CCMatrix<Real> interpolation_matrix(n_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the interpolation matrix using the RBF PSI
 // --------------------------------------------------------------

 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned j = 0; j < n_nodes; j++)
    {
     Real r = distance_matrix(i, j);
     interpolation_matrix(i, j) = Lpsi(r, epsilon);
     interpolation_matrix(i, j) = psi(r, epsilon);
    }
   
  }
 
 // --------------------------------------------------------------
 // Set right-hand side
 // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
 CCVectorArmadillo<Real> rhs(n_nodes);
#else 
 CCVector<Real> rhs(n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO 
 //rhs.allocate_memory();
 for (unsigned i = 0; i < n_nodes; i++)
  {
#ifdef CHAPCHOM_USES_ARMADILLO
   CCVectorArmadillo<Real> tmp_v(dim);
#else
   CCVector<Real> tmp_v(dim);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   //tmp_v.allocate_memory();
   for (unsigned j = 0; j < dim; j++)
    {
     tmp_v(j) = nodes_pt[i]->get_position(j);
    }
   // --------------------------------------------------------------
   // Evaluate the function f at the centers positions
   // --------------------------------------------------------------
#ifdef CHAPCHOM_USES_ARMADILLO
   rhs(i) = Lu<CCVectorArmadillo<Real> >(tmp_v);
#else
   rhs(i) = Lu<CCVector<Real> >(tmp_v);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
  }
 
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
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}


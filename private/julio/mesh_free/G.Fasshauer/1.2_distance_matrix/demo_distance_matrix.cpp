// This demo driver is based on the Program 1.2 DistanceMatrixFit.m
// from the book "Meshfree Approximation Methods with MATLAB, Gregory
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

#ifdef SCICELLXX_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../../../src/matrices/cc_matrix_armadillo.h"

// The class to solve linear systems using Armadillo's type matrices
#include "../../../../../src/linear_solvers/cc_solver_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILLO

using namespace chapchom;

// This fucntion has it maximum value at the center, depending on the
// dimension s. At the boundaries it is zero.
template<class VEC_TYPE>
const Real test_function(VEC_TYPE &x, const unsigned s)
{
 Real prod=1.0;
 for (unsigned i = 0; i < s; i++)
  {
   prod*=x(i)*(1.0-x(i));
  }
 return pow(4, s)*prod;
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
   throw SciCellxxLibError(error_message.str(),
                          SCICELLXX_CURRENT_FUNCTION,
                          SCICELLXX_EXCEPTION_LOCATION);
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
 argparse::ArgValue<unsigned> dimension;
 argparse::ArgValue<unsigned> degree;
 argparse::ArgValue<unsigned> n_evaluation_points_per_dimension;
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
 parser.add_argument<unsigned>(args.dimension, "--dim")
  .help("Dimension")
  .default_value("2")
  .choices({"1", "2", "3"});
 
 parser.add_argument<unsigned>(args.degree, "--degree")
  .help("Degree")
  .default_value("3")
  .choices({"1", "2", "3"});
 
 parser.add_argument<unsigned>(args.n_evaluation_points_per_dimension, "--n_evaluation_points_per_dimension")
  .help("Number of evaluation points per dimension")
  .default_value("1000");
 
 // Parse the input arguments
 parser.parse_args(argc, argv);
 
 // --------------------------------------------------------------
 // Domain specification
 // --------------------------------------------------------------
 // TODO: Create a DOMAIN (mesh?) type class
 
 // Dimension of the problem
 unsigned dim = args.dimension; // (if you change the dimension then
                                // also change
                                // 'n_evaluation_points_per_dimension')
 
 // Interpolant degree
 unsigned degree = args.degree;
 
 // Specify the one-dimensional lenght of the domain
 const unsigned L = 1.0;
 
 // --------------------------------------------------------------
 // Create and give position to nodes
 // --------------------------------------------------------------
 // Nodes per dimension
 const unsigned n_nodes_per_dim = pow(2, degree+1);
 // The number of nodes
 const unsigned n_nodes = pow(n_nodes_per_dim, dim);
 // A vector of nodes
 std::vector<CCNode<Real> *> nodes_pt(n_nodes);
 
 // Number of variables stored in the node
 const unsigned n_variables = 1;
 // Number of history values
 const unsigned n_history_values = 1;
 
 // Distance between a pair of nodes
 const Real h = L / (Real)(n_nodes_per_dim - 1);
 std::vector<Real> x(dim, 0.0);
 // Create the nodes
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i] = new CCNode<Real>(dim, n_variables, n_history_values);
  }

 // --------------------------------------------------------------
 // Output supporting nodes
 // --------------------------------------------------------------
 std::ofstream nodes_file("RESLT/nodes.dat");
 
 // Assign positions
 for (unsigned i = 0; i < n_nodes; i++)
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
 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned j = 0; j < n_variables; j++)
    {
     const Real u = 0.0;
     nodes_pt[i]->set_variable(u, j);
    }
  }
 
 // --------------------------------------------------------------
 // Set boundary conditions
 // --------------------------------------------------------------
 
 // Move the first and the last node to the boundary of the domain
 //nodes_pt[0]->set_position(0.0, 0);
 //nodes_pt[0]->set_variable(0.0, 0);
 //nodes_pt[n_nodes-1]->set_position(1.0, 0);
 //nodes_pt[n_nodes-1]->set_variable(1.0, 0);
 
 // --------------------------------------------------------------
 // Set the problem and solve it
 // --------------------------------------------------------------
 
 // TODO: The distance matrix may be formed while we loop over the
 // nodes to extract their position
 
 // --------------------------------------------------------------
 // Loop over the nodes and extract their position and store them in a
 // matrix
 // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
 CCMatrixArmadillo<Real> nodes_position(dim, n_nodes);
#else
 CCMatrix<Real> nodes_position(dim, n_nodes);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
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
#ifdef SCICELLXX_USES_ARMADILLO
  CCMatrixArmadillo<Real> distance_matrix(n_nodes, n_nodes);
#else
 CCMatrix<Real> distance_matrix(n_nodes, n_nodes);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the distance matrix using the nodes position centers
 // shifted by the same nodes position
 // --------------------------------------------------------------
 //distance_matrix.allocate_memory();
#ifdef SCICELLXX_USES_ARMADILLO
 compute_distance_matrix<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> >(nodes_position, nodes_position, distance_matrix);
#else
 compute_distance_matrix<CCMatrix<Real>, CCVector<Real> >(nodes_position, nodes_position, distance_matrix);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 
 // --------------------------------------------------------------
 // Set right-hand side
 // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
 CCVectorArmadillo<Real> rhs(n_nodes);
#else 
 CCVector<Real> rhs(n_nodes);
#endif // #ifdef SCICELLXX_USES_ARMADILLO 
 //rhs.allocate_memory();
 for (unsigned i = 0; i < n_nodes; i++)
  {
#ifdef SCICELLXX_USES_ARMADILLO
   CCVectorArmadillo<Real> tmp_v(dim);
#else
   CCVector<Real> tmp_v(dim);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
   //tmp_v.allocate_memory();
   for (unsigned j = 0; j < dim; j++)
    {
     tmp_v(j) = nodes_pt[i]->get_position(j);
    }
   // --------------------------------------------------------------
   // Evaluate the KNOWN function at the centers positions
   // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
   rhs(i) = test_function<CCVectorArmadillo<Real> >(tmp_v, dim);
#else
   rhs(i) = test_function<CCVector<Real> >(tmp_v, dim);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
  }
 
 // The solution vector (with the respective number of rows) stores
 // the coefficients for the interpolant polynomials
#ifdef SCICELLXX_USES_ARMADILLO
 CCVectorArmadillo<Real> sol(n_nodes);
#else
 CCVector<Real> sol(n_nodes);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 
 // --------------------------------------------------------------
 // Solve
 // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
  // Create an Armadillo linear solver
  CCSolverArmadillo<Real> linear_solver;
#else
 // Create a linear solver
 CCLUSolverNumericalRecipes<Real> linear_solver;
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 
 std::cerr << "Distance matrix" << std::endl;
 //distance_matrix.print();
 
 // --------------------------------------------------------------
 // Solve the system of equations
 // --------------------------------------------------------------
 linear_solver.solve(distance_matrix, rhs, sol);
 std::cerr << "Solution vector" << std::endl;
 //sol.print();

 std::cerr << "Nodes positions and values" << std::endl;
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
 unsigned n_evaluation_points_per_dimension = args.n_evaluation_points_per_dimension;
 const unsigned n_data_in_evaluation_points = pow(n_evaluation_points_per_dimension, dim);
 // Distance between a pair of nodes
 const Real h_test = L / (Real)(n_evaluation_points_per_dimension - 1);
 
 // Compute approximated solution at new positions
#ifdef SCICELLXX_USES_ARMADILLO
 CCMatrixArmadillo<Real> approx_solution_position(dim, n_evaluation_points_per_dimension);
#else
 CCMatrix<Real> approx_solution_position(dim, n_evaluation_points_per_dimension);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 //approx_solution_position.allocate_memory();
 // --------------------------------------------------------------
 // Assign positions
 // --------------------------------------------------------------
 std::vector<Real> x_eval(dim, 0.0);
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     const Real r = rand();
     const Real position = static_cast<Real>(r / RAND_MAX) * L;
     // Generate position and assign it
     //const Real position = x_eval[k];
     approx_solution_position(k, i) = position;
     //x_eval[k]+=h_test;
    }
  }
 
 // Compute distance matrix with new positions
#ifdef SCICELLXX_USES_ARMADILLO
 CCMatrixArmadillo<Real> approx_distance_matrix(n_evaluation_points_per_dimension, n_nodes);
#else
 CCMatrix<Real> approx_distance_matrix(n_evaluation_points_per_dimension, n_nodes);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 // --------------------------------------------------------------
 // Generate the distance matrix using the nodes position centers
 // shifted by the new positions
 // --------------------------------------------------------------
 //approx_distance_matrix.allocate_memory();
#ifdef SCICELLXX_USES_ARMADILLO
 compute_distance_matrix<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> >(approx_solution_position, nodes_position, approx_distance_matrix);
#else
 compute_distance_matrix<CCMatrix<Real>, CCVector<Real> >(approx_solution_position, nodes_position, approx_distance_matrix);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 //approx_distance_matrix.print();
 
 // Approximated solution
#ifdef SCICELLXX_USES_ARMADILLO
 CCVectorArmadillo<Real> approx_sol(n_evaluation_points_per_dimension);
#else
 CCVector<Real> approx_sol(n_evaluation_points_per_dimension);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 // Approximate solutin at given points
 multiply_matrix_times_vector(approx_distance_matrix, sol, approx_sol);
 
 // --------------------------------------------------------------
 // Output data for plotting
 // --------------------------------------------------------------
 std::ofstream output_file("RESLT/output.dat");
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     output_file << approx_solution_position(k, i) << " ";
    }
   output_file << approx_sol(i) << std::endl;
  }
 
 // Close output file
 output_file.close();
 
 // --------------------------------------------------------------
 // Get real solution at given points and get the error 
 // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
 CCVectorArmadillo<Real> real_sol(n_evaluation_points_per_dimension);
#else 
 CCVector<Real> real_sol(n_evaluation_points_per_dimension);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 //real_sol.allocate_memory();
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
#ifdef SCICELLXX_USES_ARMADILLO
   CCVectorArmadillo<Real> tmp_v(dim);
#else
   CCVector<Real> tmp_v(dim);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
   //tmp_v.allocate_memory();
   for (unsigned j = 0; j < dim; j++)
    {
     tmp_v(j) = approx_solution_position(j, i);
    }
   // ------------------------
   // Evaluation at approx_solution_position
   real_sol(i) = test_function(tmp_v, dim);
  }
 
 // --------------------------------------------------------------
 // Compute error
 // --------------------------------------------------------------
#ifdef SCICELLXX_USES_ARMADILLO
 CCVectorArmadillo<Real> error(n_evaluation_points_per_dimension);
#else
 CCVector<Real> error(n_evaluation_points_per_dimension);
#endif // #ifdef SCICELLXX_USES_ARMADILLO
 //error.allocate_memory();
 std::cerr << "ERRORS" << std::endl;
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
   error(i) = real_sol(i) - approx_sol(i);
   //std::cerr << i << ": " << std::fabs(error(i)) << std::endl;
   //std::cerr << i << ": " << real_sol(i) << ":" << approx_sol(i) << std::endl;
  }
 
 const Real rms_error = error.norm_2() / sqrt(n_data_in_evaluation_points);
 
 // --------------------------------------------------------------
 // Output error
 // --------------------------------------------------------------
 std::ofstream error_file("RESLT/error.dat");
 for (unsigned i = 0; i < n_evaluation_points_per_dimension; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     error_file << approx_solution_position(k, i) << " ";
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


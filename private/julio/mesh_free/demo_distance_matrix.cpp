// This demo driver is based on the Program 1.2 DistanceMatrixFit.m
// from the book "Meshfree Approximation Methods with MATLAB, Gregory
// E. Fasshauer", World Scientific Publishing, 2007

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// Matrices
#include "../../../src/matrices/cc_matrix.h"
#include "../../../src/data_structures/cc_node.h"

// The class to solve linear systems using numerical recipes
#include "../../../src/linear_solvers/cc_lu_solver_numerical_recipes.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"

// The class to solve linear systems using Armadillo's type matrices
#include "../../../src/linear_solvers/cc_solver_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

using namespace chapchom;

const Real test_function(CCVector<Real> &x, const unsigned s)
{
 Real prod=1.0;
 for (unsigned i = 0; i < s; i++)
  {
   prod*=x(i)*(1.0-x(i));
  }
 return pow(4, s)*prod;
}

template<class T>
void compute_distance_matrix(CCMatrix<T> &data_sites, CCMatrix<T> &centers,
                             CCMatrix<T> &distance_matrix)
{
 // Get the number of "vector points" on "data_sites"
 // Get the number of "vector points" on "centers"
 const unsigned n_vector_points_data_sites = data_sites.n_columns();
 const unsigned n_vector_points_centers = centers.n_columns();

 // The dimension MUST be the same for both input data, otherwise
 // there is an error
 const unsigned dimension = data_sites.n_rows();
 
 // Loop over all the data points in the first matrix
 for (unsigned m = 0; m < n_vector_points_data_sites; m++)
  {
   // Loop over all the data points in the second matrix
   for (unsigned n = 0; n < n_vector_points_centers; n++)
    {
     CCVector<T> distance(dimension);
     distance.allocate_memory();
     // Loop over the elements of both vectors
     for (unsigned k = 0; k < dimension; k++)
      {
       distance(k) = data_sites(k, m) - centers(k, n);
      }
     distance_matrix(m,n)=distance.norm_2();
    }
  }
 
}

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
 
 // --------------------------------------------------------------
 // Domain specification
 // --------------------------------------------------------------
 // TODO: Create a DOMAIN (mesh?) type class
 
 // Dimension of the problem
 const unsigned dim = 1;
 
 // Specify the lenght of the domain
 const unsigned L = 1.0;
 
 // --------------------------------------------------------------
 // Create and give position to nodes
 // --------------------------------------------------------------
 // Nodes per dimension
 const unsigned n_nodes_per_dim = 10;
 // The number of nodes
 const unsigned n_nodes = pow(n_nodes_per_dim, dim);
 // A vector of nodes
 std::vector<CCNode<Real> *> nodes_pt(n_nodes);
 
 // Number of variables stored in the node
 const unsigned n_variables = 1;
 // Number of history values
 const unsigned n_history_values = 1;
 
 const Real h = L / (Real)(n_nodes_per_dim - 1);
 std::vector<Real> x(dim, 0.0);
 // Create the nodes
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i] = new CCNode<Real>(dim, n_variables, n_history_values);
  }
 
 // Assign positions
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i] = new CCNode<Real>(dim, n_variables, n_history_values);
   for (unsigned k = 0; k < dim; k++)
    {
     //const Real r = rand();
     //const Real position = static_cast<Real>(r / RAND_MAX);
     const Real position = x[k];
     nodes_pt[i]->set_position(position, k);
     x[k]+=h;
    }
  }
 
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
 nodes_pt[0]->set_position(0.0, 0);
 nodes_pt[0]->set_variable(0.0, 0);
 nodes_pt[n_nodes-1]->set_position(1.0, 0);
 nodes_pt[n_nodes-1]->set_variable(1.0, 0);
 
 // --------------------------------------------------------------
 // Set the problem and solve it
 // --------------------------------------------------------------
 // Create the distance matrix
 
 // TODO: The distance matrix may be formed while we loop over the
 // nodes to extract their position
 
 // Loop over the nodes and extract their position and store them in a
 // matrix
#ifdef CHAPCHOM_USES_ARMADILLO
 CCArmadilloMatrix<Real> nodes_position(dim, n_nodes);
#else
 CCMatrix<Real> nodes_position(dim, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 nodes_position.allocate_memory();
 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned j = 0; j < dim; j++)
    {
     nodes_position(j, i) = nodes_pt[i]->get_position(j);
    }
  }
 
 // Store the distance matrix
#ifdef CHAPCHOM_USES_ARMADILLO
 CCArmadilloMatrix<Real> distance_matrix(n_nodes, n_nodes);
#else
 CCMatrix<Real> distance_matrix(n_nodes, n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 distance_matrix.allocate_memory();
 compute_distance_matrix(nodes_position, nodes_position, distance_matrix);
 
 // Set right-hand side
#ifdef CHAPCHOM_USES_ARMADILLO
 CCArmadilloVectror<Real> rhs(n_nodes);
#else 
 CCVector<Real> rhs(n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 rhs.allocate_memory();
 for (unsigned i = 0; i < n_nodes; i++)
  {
#ifdef CHAPCHOM_USES_ARMADILLO
   CCArmadilloVector<Real> tmp_v(dim);
#else
   CCVector<Real> tmp_v(dim);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   tmp_v.allocate_memory();
   for (unsigned j = 0; j < dim; j++)
    {
     tmp_v(j) = nodes_pt[i]->get_position(j);
    }
   // Evaluate the KNOWN function at the centers 
   rhs(i) = test_function(tmp_v, dim);
  }
 
 // The solution vector (with the respective number of rows)
#ifdef CHAPCHOM_USES_ARMADILLO
 CCArmadilloVector<Real> sol(n_nodes);
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

 std::cerr << "Distance matrix" << std::endl;
 distance_matrix.print();
 
 // Solve the system of equations
 linear_solver.solve(distance_matrix, rhs, sol);
 sol.print();
 
 // Evaluate (compute error RMSE)
#ifdef CHAPCHOM_USES_ARMADILLO
 CCArmadilloMatrix<Real> test_position(dim, n_nodes * n_nodes);
#else
 CCMatrix<Real> test_position(dim, n_nodes * n_nodes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 for (unsigned i = 0; i < n_nodes * n_nodes; i++)
  {
   const Real r = rand();
   const Real position = static_cast<Real>(r / RAND_MAX);
   test_position(0, i) = position; 
  }
 
 // Evaluation at test position
 
 
 // Show results
 for (unsigned i = 0; i < n_nodes; i++)
  {
   std::cerr << "["<< i<< "]:";
   for (unsigned j = 0; j < dim; j++)
    {
     std::cerr << " " << nodes_pt[i]->get_position(j);
    }
   std::cerr << std::endl;
  }
 
 // Delete nodes storage
 for (unsigned i = 0; i < n_nodes; i++)
  {
   delete nodes_pt[i];
  }
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}


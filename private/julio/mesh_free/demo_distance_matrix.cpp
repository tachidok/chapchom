// This demo driver is based on the Program 1.2 DistanceMatrixFit.m
// from the book "Meshfree Approximation Methods with MATLAB, Gregory
// E. Fasshauer", World Scientific Publishing, 2007

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// Matrices
#include "../../../src/matrices/cc_matrix.h"
#include "../../../src/nodes/cc_node.h"

// The class to solve linear systems using numerical recipes
#include "../../../src/linear_solvers/cc_lu_solver_numerical_recipes.h"

using namespace chapchom;

const double test_function(CCVector<double> &x, const unsigned s)
{
 double prod=1.0;
 for (unsigned i = 0; i < s; i++)
  {
   prod*=x(i)*(1.0-x(i));
  }
 return pow(4, s)*prod;
}

template<class T>
void compute_distance_matrix(CCVector<T> &data_sites, CCVector<T> &centers,
                             CCMatrix<T> &distance_matrix)
{
 const unsigned n_rows = data_sites.size();
 const unsigned n_columns = centers.size();
 for (unsigned i = 0; i < n_rows; i++)
  {
   for (unsigned j = 0; j < n_columns; j++)
    {
     const T dsi = data_sites(i);
     const T cj = centers(j);
     distance_matrix(i,j)=(dsi-cj)*(dsi-cj);
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
 // Specify the domain
 std::vector<double> domain(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   domain[i]=1.0;
  }
 
 // --------------------------------------------------------------
 // Create and give position to nodes
 // --------------------------------------------------------------
 // The number of nodes
 const unsigned n_nodes = 100;
 // A vector of nodes
 std::vector<CCNode<double> *> nodes_pt(n_nodes);
 
 // Number of variables stored in the node
 const unsigned n_variables = 1;
 // Number of history values
 const unsigned n_history_values = 1;
 
 // Create the nodes and assign position
 for (unsigned i = 0; i < n_nodes; i++)
  {
   nodes_pt[i] = new CCNode<double>(dim, n_variables, n_history_values);
   for (unsigned k = 0; k < dim; k++)
    {
     const double position = static_cast<double>(rand() / RAND_MAX);
     nodes_pt[i]->set_position(position, k);
    }
  }
 
 // --------------------------------------------------------------
 // Set initial conditions
 // --------------------------------------------------------------
 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned j = 0; j < n_variables; j++)
    {
     const double u = 0.0;
     nodes_pt[i]->set_variable(u, j);
    }
  }
 
 // --------------------------------------------------------------
 // Set boundary conditions
 // --------------------------------------------------------------
 
 // Move the first and the last node to the boundary of the domain
 nodes_pt[0]->set_position(0.0, 0);
 nodes_pt[0]->set_variable(0.0, 0);
 nodes_pt[n_nodes-1]->set_position(0.0, 0);
 nodes_pt[n_nodes-1]->set_variable(1.0, 0);
 
 // --------------------------------------------------------------
 // Set the problem and solve it
 // --------------------------------------------------------------
 // Create the distance matrix
 
 // TODO: The distance matrix may be formed while we loop over the
 // nodes to extract their position
 
 // Loop over the nodes and extract their position
 // Store the position of the nodes
 CCVector<double> nodes_position(n_nodes);
 nodes_position.create_zero_vector();
 for (unsigned i = 0; i < n_nodes; i++)
  {
   for (unsigned k = 0; k < dim; k++)
    {
     nodes_position(i)=nodes_pt[i]->get_position(k);
    }
  }
 
 // Store the distance matrix
 CCMatrix<double> distance_matrix(n_nodes, n_nodes);
 distance_matrix.create_zero_matrix();
 compute_distance_matrix(nodes_position, nodes_position, distance_matrix);
 
 // Set right-hand side
 CCVector<double> b(n_nodes);
 b.create_zero_vector();
 
 // Take the position of the centers
 
 // The solution vector (with the respective number of rows)
 CCVector<double> sol(n_nodes);
 
 // --------------------------------------------------------------
 // Solve
 // --------------------------------------------------------------
 // Create a linear solver
 CCLUSolverNumericalRecipes<double> linear_solver;
 
 // Solve the system of equations
 linear_solver.solve(distance_matrix, b, sol);
 
 // Evaluate (compute error RMSE)
 
 // Show results
 
 // Delete nodes storage
 for (unsigned i = 0; i < n_nodes; i++)
  {
   delete nodes_pt[i];
  }
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}

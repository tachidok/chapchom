#include <iostream>
#include <cmath>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The class to solve linear systems using numerical recipes
// implementation
#include "../../../src/linear_solvers/cc_lu_solver_numerical_recipes.h"

using namespace chapchom;

int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Create an square matrix
 const unsigned n_rows = 10;
 const unsigned n_cols = n_rows;
 
 double *vector_data_A = new double[n_rows*n_cols];
 double *vector_data_b = new double[n_rows];
 
 // Transform the "vectors" to matrices
 // The matrix A
 CCMatrix<double> A(n_rows, n_cols);
 A.set_matrix(vector_data_A, n_rows, n_cols);
 
 // The right hand side vector
 CCMatrix<double> b(n_rows, 1);
  
 // Create a linear solver with the matrix A (pass it size)
 //ACLinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes(A, n, n);
 CCLUSolverNumericalRecipes<double> linear_solver;
 
 // The solution vector
 CCMatrix<double> sol(n_cols, 1);
 
 // Solve the system of equations
 linear_solver.solve(A, b, sol);
 
 // Free memory
 delete [] vector_data_A;
 delete [] vector_data_b;
  
 // Finalise chapcom
 finalise_chapchom(); 
 
 return 0;
 
}

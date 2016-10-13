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
 
 // Create a square matrix
 const unsigned n_rows = 3;
 const unsigned n_cols = n_rows;
 
 double *vector_data_A = new double[n_rows*n_cols];
 double *vector_data_b = new double[n_rows];
 
 // Transform the "vectors" to matrices
 // The matrix A
 CCMatrix<double> A(vector_data_A, n_rows, n_cols);
 
 // The right hand side vector
 CCMatrix<double> b(n_rows);
 // Create a zero vector such that memory is allocated to store the
 // entries of the vector. Otherwise we could not use the b(i,i)
 // assignement without previous memory allocation
 b.create_zero_matrix();
 
 // Solve the following system of equations
 A(0,0) = 7.0;  A(0,1) = 5.0;  A(0,2) = -3.0;
 A(1,0) = 3.0;  A(1,1) = -5.0;  A(1,2) = 2.0;
 A(2,0) = 5.0;  A(2,1) = 3.0;  A(2,2) = -7.0;
 
 // ... with the following right hand side
 b(0,0) = 16.0;
 b(1,0) = -8.0;
 b(2,0) = 0.0;
 
 // Print the matrices
 std::cout << "Matrix A" << std::endl;
 A.print();
 std::cout << std::endl;
 std::cout << "Vector b" << std::endl;
 b.print();
 std::cout << std::endl;
 
 // Create a linear solver with the matrix A (pass it size)
 //ACLinearSolver *linear_solver_pt = new CCLUSolverNumericalRecipes(A, n, n);
 CCLUSolverNumericalRecipes<double> linear_solver;
 
 // The solution vector
 CCMatrix<double> sol(n_cols);
 
 // Solve the system of equations
 linear_solver.solve(A, b, sol);
 
 // Print the solution
 std::cout << "Vector sol" << std::endl;
 sol.print();
 std::cout << std::endl;
 
 // Apply the solution and check the result
 CCMatrix<double> C = A*sol;
 std::cout << "Matrix C" << std::endl;
 C.print();
 
 // Free memory
 delete [] vector_data_A;
 delete [] vector_data_b;
  
 // Finalise chapcom
 finalise_chapchom(); 
 
 return 0;
 
}

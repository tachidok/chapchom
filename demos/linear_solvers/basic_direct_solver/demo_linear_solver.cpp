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
 
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 // Create a square matrix
 const unsigned n_rows = 3;
 const unsigned n_cols = n_rows;
 
 // The matrix A
 CCMatrix<double> A(n_rows, n_cols);
 // Create a zero matrix such that memory is ALLOCATED to store the
 // entries of the matrix. Otherwise we could not use the A(i,j) = x;
 // assignement without previous memory allocation
 A.create_zero_matrix();
 
 // Fill in some data
 A(0,0) = 7.0;  A(0,1) = 5.0;  A(0,2) = -3.0;
 A(1,0) = 3.0;  A(1,1) = -5.0;  A(1,2) = 2.0;
 A(2,0) = 5.0;  A(2,1) = 3.0;  A(2,2) = -7.0;
 
 // ----------------------------------------------------------------
 // Solve using vectors for a unique right-hand side
 // ----------------------------------------------------------------
 {
  // The right hand side vector
  CCVector<double> b(n_rows);
  // Create a zero vector such that memory is ALLOCATED to store the
  // entries of the vector. Otherwise we could not use the b(i) = x;
  // assignement without previous memory allocation
  b.create_zero_vector();
  
  // Solve the following system of equations Ax = b
  
  // ... with the following right hand side
  b(0) = 16.0;
  b(1) = -8.0;
  b(2) = 0.0;
  
  // Print the matrices
  std::cout << "Matrix A" << std::endl;
  A.print();
  A.print(output_test);
  std::cout << std::endl;
  std::cout << "Vector b" << std::endl;
  b.print();
  b.print(output_test);
  std::cout << std::endl;
  
  // Create a linear solver
  CCLUSolverNumericalRecipes<double> linear_solver;
  
  // The solution vector (with the corresponding number of rows, that
  // in this case refers to the number of cols as well)
  CCVector<double> sol(n_cols);
  
  // Solve the system of equations
  linear_solver.solve(A, b, sol);
  
  // Print the solution
  std::cout << "Vector sol" << std::endl;
  sol.print();
  sol.print(output_test);
  std::cout << std::endl;
  
  // Apply the solution and check the result
  CCMatrix<double> C = A*sol;
  std::cout << "Matrix C" << std::endl;
  C.print();
  C.print(output_test);
 }
 
 // ----------------------------------------------------------------
 // Solve using matrices to store multiple right-hand sides
 // ----------------------------------------------------------------
 {
  // The right hand side vectors
  CCMatrix<double> B(n_rows);
  // Create a zero matrix such that memory is ALLOCATED to store the
  // entries of the matrix. Otherwise we could not use the b(i,j) = x;
  // assignement without previous memory allocation
  B.create_zero_matrix();
  
  // Solve the following system of equations AX = B
  
  // ... with the following right hand sides
  B(0,0) = 16.0;
  B(1,0) = -8.0;
  B(2,0) = 0.0;
  
  B(0,1) = 0.0;
  B(1,1) = -16.0;
  B(2,1) = -8.0;
  
  B(0,2) = 0.0;
  B(1,2) = 0.0;
  B(2,2) = 0.0;
  
  // Print the matrices
  std::cout << "Matrix A" << std::endl;
  A.print();
  A.print(output_test);
  std::cout << std::endl;
  std::cout << "Matrix B" << std::endl;
  B.print();
  B.print(output_test);
  std::cout << std::endl;
  
  // Create a linear solver
  CCLUSolverNumericalRecipes<double> linear_solver;
  
  // The solution vector
  CCMatrix<double> SOL(n_cols);
  
  // Solve the system of equations
  linear_solver.solve(A, B, SOL);
  
  // Print the solution
  std::cout << "Matrix SOL" << std::endl;
  SOL.print();
  SOL.print(output_test);
  std::cout << std::endl;
  
  // Apply the solution and check the result
  CCMatrix<double> C = A*SOL;
  std::cout << "Matrix C" << std::endl;
  C.print();
  C.print(output_test);
 }
 
 // Close the output for test
 output_test.close();
 
 // Finalise chapcom
 finalise_chapchom(); 
 
 return 0;
 
}

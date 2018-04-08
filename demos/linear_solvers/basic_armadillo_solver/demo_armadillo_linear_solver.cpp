#include <iostream>
#include <cmath>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The class to solve linear systems using Armadillo's type matrices
#include "../../../src/linear_solvers/cc_solver_armadillo.h"

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
 CCMatrixArmadillo<double> A(n_rows, n_cols);
 // Allocate memory
 A.allocate_memory();
 
 // Fill in some data
 A(0,0) = 7.0;  A(0,1) = 5.0;  A(0,2) = -3.0;
 A(1,0) = 3.0;  A(1,1) = -5.0;  A(1,2) = 2.0;
 A(2,0) = 5.0;  A(2,1) = 3.0;  A(2,2) = -7.0;
 
 // ----------------------------------------------------------------
 // Solve using vectors for a unique right-hand side
 // ----------------------------------------------------------------
 {
  // The right hand side vector
  CCMatrixArmadillo<double> b(n_rows, 1);
  // Allocate memory
  b.allocate_memory();
  
  // Solve the following system of equations Ax = b
  
  // ... with the following right hand side
  b(0,0) = 16.0;
  b(1,0) = -8.0;
  b(2,0) = 0.0;
  
  // Print the matrices
  std::cout << "Matrix A" << std::endl;
  A.print();
  A.print(output_test);
  std::cout << std::endl;
  std::cout << "Vector b" << std::endl;
  b.print();
  b.print(output_test);
  std::cout << std::endl;
  
  // Create an Armadillo linear solver
  CCSolverArmadillo<double> armadillo_linear_solver;
  
  // The solution vector (with the corresponding number of rows, that
  // in this case refers to the number of cols as well)
  CCMatrixArmadillo<double> sol(n_cols, 1);
  
  // Solve the system of equations
  armadillo_linear_solver.solve(A, b, sol);
  
  // Print the solution
  std::cout << "Vector sol" << std::endl;
  sol.print();
  sol.print(output_test);
  std::cout << std::endl;
  
  // Apply the solution and check the result
  CCMatrixArmadillo<double> C = A*sol;
  std::cout << "Matrix C" << std::endl;
  C.print();
  C.print(output_test);
 }
 
 // ----------------------------------------------------------------
 // Solve using matrices to store multiple right-hand sides
 // ----------------------------------------------------------------
 {
  // The right hand side vectors
  CCMatrixArmadillo<double> B(n_rows, 1);
  // Allocate memory
  B.allocate_memory();
  
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
  
  // Create an Armadillo linear solver
  CCSolverArmadillo<double> armadillo_linear_solver;
  
  // The solution vector
  CCMatrixArmadillo<double> SOL(n_cols, 1);
  
  // Solve the system of equations
  armadillo_linear_solver.solve(A, B, SOL);
  
  // Print the solution
  std::cout << "Matrix SOL" << std::endl;
  SOL.print();
  SOL.print(output_test);
  std::cout << std::endl;
  
  // Apply the solution and check the result
  CCMatrixArmadillo<double> C = A*SOL;
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

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
 CCMatrixArmadillo<Real> A(n_rows, n_cols);
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
  // The right hand side vector (by default it is created as a column
  // vector)
  CCVectorArmadillo<Real> b(n_rows);
  // Allocate memory
  b.allocate_memory();
  
  // Solve the following system of equations Ax = b
  
  // ... with the following right hand side
  b(0) = 16.0;
  b(1) = -8.0;
  b(2) = 0.0;
  
  // Print the matrices
  std::cout << std::endl;
  std::cout << "Matrix A" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix A" << std::endl;
  output_test << std::endl;
  A.print();
  A.print(output_test);
  std::cout << std::endl;
  std::cout << "Vector b" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Vector b" << std::endl;
  output_test << std::endl;
  b.print();
  b.print(output_test);
  std::cout << std::endl;
  output_test << std::endl;
  
  // Create an Armadillo linear solver
  CCSolverArmadillo<Real> armadillo_linear_solver;
  
  // The solution vector (with the corresponding number of rows, that
  // in this case refers to the number of cols as well)
  CCVectorArmadillo<Real> sol(n_cols);
  
  // Solve the system of equations
  armadillo_linear_solver.solve(A, b, sol);
  
  // Print the solution
  std::cout << std::endl;
  std::cout << "Vector sol -----" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Vector sol -----" << std::endl;
  output_test << std::endl;
  sol.print();
  sol.print(output_test);
  std::cout << std::endl;
  output_test << std::endl;
  
   // Apply the solution and check the result
  CCMatrixArmadillo<Real> C = A*sol;
  std::cout << std::endl;
  std::cout << "Matrix C" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix C" << std::endl;
  output_test << std::endl;
  C.print();
  C.print(output_test);
 }
 
 // ----------------------------------------------------------------
 // Solve using matrices to store multiple right-hand sides
 // ----------------------------------------------------------------
 {
  // The right hand side vectors
  CCMatrixArmadillo<Real> B(n_rows, n_rows);
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
  std::cout << std::endl;
  std::cout << "Matrix A" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix A" << std::endl;
  output_test << std::endl;
  A.print();
  A.print(output_test);
  std::cout << std::endl;
  std::cout << "Matrix B" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix B" << std::endl;
  output_test << std::endl;
  B.print();
  B.print(output_test);
  std::cout << std::endl;
  output_test << std::endl;
  
  // Create an Armadillo linear solver
  CCSolverArmadillo<Real> armadillo_linear_solver;
  
  // The solution vector
  CCMatrixArmadillo<Real> SOL(n_cols, 1);
  
  // Solve the system of equations
  armadillo_linear_solver.solve(A, B, SOL);
  
  // Print the solution
  std::cout << std::endl;
  std::cout << "Matrix SOL -----" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix SOL -----" << std::endl;
  output_test << std::endl;
  SOL.print();
  SOL.print(output_test);
  std::cout << std::endl;
  output_test << std::endl;
  
  // Apply the solution and check the result
  CCMatrixArmadillo<Real> C = A*SOL;
  std::cout << std::endl;
  std::cout << "Matrix C" << std::endl;
  std::cout << std::endl;
  output_test << std::endl;
  output_test << "Matrix C" << std::endl;
  output_test << std::endl;
  C.print();
  C.print(output_test);
 }
 
 // Close the output for test
 output_test.close();
 
 // Finalise chapcom
 finalise_chapchom(); 
 
 return 0;
 
}

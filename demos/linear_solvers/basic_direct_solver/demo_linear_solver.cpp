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
 
 // Get the wall and cpu execution time of the program
 time_t initial_wall_time = Timing::wall_time();
 clock_t initial_cpu_clock_time = Timing::cpu_clock_time();
 
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
 
 // The right hand side vector
 CCMatrix<double> b(n_rows);
 // Create a zero vector such that memory is ALLOCATED to store the
 // entries of the vector. Otherwise we could not use the b(i) = x;
 // assignement without previous memory allocation
 b.create_zero_matrix();
 
 // Solve the following system of equations
 // Ax = b
 
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
 sol.print(output_test);
 std::cout << std::endl;
 
 // Apply the solution and check the result
 CCMatrix<double> C = A*sol;
 std::cout << "Matrix C" << std::endl;
 C.print();
 C.print(output_test);
 
 // Get the wall and cpu execution time of the program
 time_t final_wall_time = Timing::wall_time();
 clock_t final_cpu_clock_time = Timing::cpu_clock_time();
 double total_wall_time =
  Timing::diff_wall_time(initial_wall_time, final_wall_time);
 double total_cpu_clock_time =
  Timing::diff_cpu_clock_time(initial_cpu_clock_time, final_cpu_clock_time);
 
 std::cout << "Total wall time: " << total_wall_time << std::endl;
 std::cout << "Total cpu clock time: " << total_cpu_clock_time << std::endl;
 
 // Close the output for test
 output_test.close();
 
 // Finalise chapcom
 finalise_chapchom(); 
 
 return 0;
 
}

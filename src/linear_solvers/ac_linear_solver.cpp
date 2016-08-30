// IN THIS FILE: Implementation of an abstract class to solve linear
// systems of equations, this class is inhereted by any concrete
// implementations of linear solvers

#include "ac_linear_solver.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 ACLinearSolver::ACLinearSolver() 
  : Matrix_A_has_been_set(false)
 { }

 // ===================================================================
 // Constructor where we specify the matrix A of size m X n
 // ===================================================================
 ACLinearSolver::ACLinearSolver(const CCMatrix &matrix)
 {
  // Set matrix A
  A = matrix;
 
  // Set the flag to indicate that the matrix A has been set
  Matrix_A_has_been_set = true;
 }

 // ===================================================================
 // Empty destructor
 // ===================================================================
 ACLinearSolver::~ACLinearSolver()
 {
  // Deallocate memory
  clean_up();
 }

 // ===================================================================
 // Set the matrix A
 // ===================================================================
 void ACLinearSolver::set_matrix_A(const CCMatrix &matrix)
 {
  // First clean any other previously stored matrix
  clean_up();
 
  // Set matrix A
  A = matrix;
 
  // Set the flag to indicate that the matrix A has been set
  Matrix_A_has_been_set = true;
 }

 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 void ACLinearSolver::clean_up()
 {
  // Check whether the matrix has been set
  if (Matrix_A_has_been_set)
   {
    // Delete the content of the matrix
    A.free_memory_for_matrix();
      
    // Mark the matrix as not been set
    Matrix_A_has_been_set = false;
   }
 
 }

}

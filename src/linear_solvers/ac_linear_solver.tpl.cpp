// IN THIS FILE: Implementation of an abstract class to solve linear
// systems of equations, this class is inhereted by any concrete
// implementations of linear solvers

#include "ac_linear_solver.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACLinearSolver<MAT_TYPE, VEC_TYPE>::ACLinearSolver() 
  : Matrix_A_has_been_set(false)
 { }

 // ===================================================================
 // Constructor where we specify the matrix A of size m X n
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACLinearSolver<MAT_TYPE, VEC_TYPE>::ACLinearSolver(const MAT_TYPE &matrix)
 {
  // Set matrix A
  A = matrix;
 
  // Set the flag to indicate that the matrix A has been set
  Matrix_A_has_been_set = true;
 }

 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACLinearSolver<MAT_TYPE, VEC_TYPE>::~ACLinearSolver()
 {
  // Deallocate memory
  clean_up();
 }

 // ===================================================================
 // Set the matrix A
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACLinearSolver<MAT_TYPE, VEC_TYPE>::set_matrix_A(const MAT_TYPE &matrix)
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
 template<class MAT_TYPE, class VEC_TYPE>
 void ACLinearSolver<MAT_TYPE, VEC_TYPE>::clean_up()
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

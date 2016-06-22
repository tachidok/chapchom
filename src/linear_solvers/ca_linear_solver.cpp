// IN THIS FILE: Implementation of an abstract class to solve linear
// systems of equations, this class is inhereted by any concrete
// implementations of linear solvers

#include "CALinearSolver.h"

// ===================================================================
// Constructor
// ===================================================================
CALinearSolver::CALinearSolver() 
 : Matrix_A_has_been_set(false)
{ 
 A_pt = 0;
}

// ===================================================================
// Constructor where we specify the matrix A of size m X n
// ===================================================================
CALinearSolver::CALinearSolver(CAMatrix *_A_pt)
{
 // Set the pointer of the matrix A
 A_pt = _A_pt;
 
 // Set the flag to indicate that the matrix A has been set
 Matrix_A_has_been_set = true;
}

// ===================================================================
// Empty destructor
// ===================================================================
CALinearSolver::~CALinearSolver()
{
 // Deallocate memory
 clean_up();
}

// ===================================================================
// Set the matrix A
// ===================================================================
void CALinearSolver::set_matrix_A(CAMatrix *_A_pt)
{
 // First clean any other previously stored matrix
 clean_up();
 
 // Set the pointer of the matrix A
 A_pt = _A_pt;
 
 // Set the flag to indicate that the matrix A has been set
 Matrix_A_has_been_set = true;
}

// ===================================================================
// Clean up for any dynamically stored data
// ===================================================================
void CALinearSolver::clean_up()
{
 // Check whether the matrix has been set
 if (Matrix_A_has_been_set)
  {
   // Delete the content of the matrix
   A_pt->free_memory_for_matrix();
   
   // Set thise pointer of the matrix to nothing
   A_pt = 0;
   
   // Mark the matrix as not been set
   Matrix_A_has_been_set = false;
  }
 
}

// ===================================================================
// Virtual function to re-solve a system of equations with the already
// stored matrix A (re-use of the LU decomposition or call the solve
// method for an iterative solver). We specify the right-hand side b
// and the x vector where the result is returned. We assume that the
// input/output vectors have the correct dimensions (size n).
// ===================================================================
void CALinearSolver::resolve(CAMatrix *_b_pt, CAMatrix *_x_pt)
{
 // Error message
 std:ostringstream error_message;
 error_message << "Virtual function not implemented in derived class"
	       << std::endl;
 throw ChapchomLibError(error_message.str(),
			CHAPCHOM_CURRENT_FUNCTION,
			CHAPCHOM_EXCEPTION_LOCATION);
}

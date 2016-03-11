// IN THIS FILE: Implementation of an abstract class to solve linear
// systems of equations, this class is inhereted by any concrete
// implementations of linear solvers

#include "CALinearSolver.h"

// ===================================================================
// Empty constructor
// ===================================================================
CALinearSolver::CALinearSolver() 
 : Matrix_A_has_been_set(false) { }

// ===================================================================
// Constructor where we specify the matrix A of size m X n
// ===================================================================
CALinearSolver::CALinearSolver(const double **_A,
			       const unsigned m, const unsigned n)
{
 // Store the number of rows and columns
 NRows = m;
 NColumns = n;
 
 // TODO Julio: Implement a class Matrix to efficiently store the
 // matrix
 
 // Create storage for the matrix
 A = new double*[NRows];
 for(unsigned i = 0; i < NRows; i++)
  {
   A[i] = new double[NColumns];
  }
 
 // ... and copy the matrix (an element by element copy, uff!!)
 for (unsigned i = 0; i < NRows; i++)
  {
   for (unsigned j = 0; j < NColumns; j++)
    {
     A[i][j] = _A[i][j];
    }
  }
 
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
void CALinearSolver::set_matrix_A(const double **_A,
				  const unsigned m, const unsigned n)
{
 // Before copying the values for the matrix we check whether we need
 // to clean up any previously stored matrix
 clean_up();
 
 // Store the number of rows and columns
 NRows = m;
 NColumns = n;
 
 // TODO Julio: Implement a class Matrix to efficiently store the
 // matrix
 
 // Create storage for the matrix
 A = new double*[NRows];
 for(unsigned i = 0; i < NRows; i++)
  {
   A[i] = new double[NColumns];
  }
 
 // ... and copy the matrix (an element by element copy, uff!!)
 for (unsigned i = 0; i < NRows; i++)
  {
   for (unsigned j = 0; j < NColumns; j++)
    {
     A[i][j] = _A[i][j];
    }
  }
 
 // Set the flag to indicate that the matrix A has been set
 Matrix_A_has_been_set = true;
}

// ===================================================================
// Clean up for any dynamically stored data
// ===================================================================
void CALinearSolver::clean_up()
{
 // Check whether the matrix A has been set, if that is the case then
 // free the allocated memory
 if (Matrix_A_has_been_set)
  {
   for(unsigned i = 0; i < NRows; i++)
    {
     delete A[i];
     A[i] = 0;
    }
   delete A;
   A = 0;
  }
 
 Matrix_A_has_been_set = false;
}

// ===================================================================
// Virtual function to re-solve a system of equations with the already
// stored matrix A (re-use of the LU decomposition or call the solve
// method for an iterative solver). We specify the right-hand side b
// and the x vector where the result is returned. We assume that the
// input/output vectors have the correct dimensions (size n).
// ===================================================================
void CALinearSolver::resolve(const double *b, double *x)
{
 // Throw an error if called
 
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CALinearSolver::resolve() - Virtual function not implemented in derived class" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

// ===================================================================
// Copy constructor (we do not want this class to be copiable because
// it contains dynamically allocated variables, A in this case). Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CALinearSolver::CALinearSolver(const CALinearSolver &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CALinearSolver::CALinearSolver() - Copy constructor called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}

// ===================================================================
// Assignment operator (we do not want this class to be copiable
// because it contains dynamically allocated variables, A in this
// case). Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CALinearSolver& CALinearSolver::operator=(const CALinearSolver &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CALinearSolver::operator=() - Assignment called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}


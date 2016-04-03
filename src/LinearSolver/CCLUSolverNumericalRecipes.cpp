// IN THIS FILE: Implementation of a concrete class to solve systems
// of equations by LU decomposition. This class calls the methods
// ludcmp() and lubksb() from numerical recipes to perform the LU
// decomposition and back-substitution, respectively.

#include "CCLUSolverNumericalRecipes.h"

// ===================================================================
// Empty constructor
// ===================================================================
CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes()
 : CALinearSolver(),
   Resolve_enabled(false) { }

// ===================================================================
// Constructor where we specify the matrix A of size m X n
// ===================================================================
CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes(CAMatrix *_A_pt)
 : CALinearSolver(_A_pt),
   Resolve_enabled(false) { }

// ===================================================================
// Empty destructor
// ===================================================================
CCLUSolverNumericalRecipes::~CCLUSolverNumericalRecipes() { }

// ===================================================================
// Solve a system of equations with input A. We specify the right-hand
// side b and the x vector where the result is returned. We assume
// that the input/output vectors have the correct dimensions (size n).
// ===================================================================
void CCLUSolverNumericalRecipes::solve(CAMatrix *_A_pt,
                                       CAMatrix *_b_pt,
                                       CAMatrix *_x_pt)
{
 // Set the matrix and its size
 set_matrix_A(_A_pt);
 
 // Solve
 solve(_b_pt, _x_pt);
 
}

// ===================================================================
// Solve a system of equations with the already stored matrix A. We
// specify the right-hand side b and the x vector where the result is
// returned. We assume that the input/output vectors have the correct
// dimensions (size n).
// ===================================================================
void CCLUSolverNumericalRecipes::solve(CAMatrix *_b_pt, CAMatrix *_x_pt)
{
 // We can only call solve if the matrix A has been set
 if (Matrix_A_has_been_set)
  {     
   // Factorise
   factorise();
   
   // ... and do back substitution
   back_substitution(_b_pt, _x_pt);
   
  }
 
}

// ===================================================================
// Re-solve a system of equations with the already stored matrix
// A. Reusing the LU decomposition. We specify the right-hand side b
// and the x vector where the result is returned. We assume that the
// input/output vectors have the correct dimensions (size n).
// ===================================================================
void CCLUSolverNumericalRecipes::resolve(CAMatrix *_b_pt, CAMatrix *_x_pt)
{
 // We can only do back-substitution if a matrix has been
 // factorised
 if (Resolve_enabled)
  {
   // Do the back substitution
   back_substitution(_b_pt, _x_pt);
  }
 
}

// ===================================================================
// Performs LU factorisation of the input matrix, the factorisation is
// internally stored such that it can be re-used when calling resolve
// ===================================================================
void CCLUSolverNumericalRecipes::factorise(CAMatrix *_A_pt)
{
 // Set the matrix and its size
 set_matrix_A(_A_pt);
 
 // Factorise
 factorise();
 
}

// ===================================================================
// Performs LU factorisation of already stored matrix A, the
// factorisation is internally stored such that it can be re-used when
// calling resolve
// ===================================================================
void CCLUSolverNumericalRecipes::factorise()
{
 // Prepare the matrix to call ludcmp() from Numerical Recipes
 
 // Check that we are working with an square matrix, otherwise this
 // will not work
 const unsigned long nrows = A_pt->nrows();
 const unsigned long ncolumns = A_pt->ncolumns();
 if (nrows!=ncolumns)
  {
   // TODO Julio: Implement a class to handle runtime errors and call
   // it here!!!
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "ERROR in CCLUSolverNumericalRecipes::factorise() - "
             << "The matrix is not square." << std::endl;
   std::cout << "The matrix is of size: " << nrows << " x "
             << ncolumns << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   throw(1);
  }
 
 // The matrix used as input and output, after calling ludcmp it has
 // the LU factorisation
 Mat_DP lu_a(nrows, ncolumns);
 
 // Output vector of size n x 1 that records the row permutations
 // performed by partial pivoting.
 Vec_INT lu_indx(nrows);
 
 // An output indicating whether the number of rows interchanges was
 // even or odd (+1 or -1, respectively)
 DP dummy;
 
 // Copy the matrix A to the representation required by ludcmp()
 for (unsigned i = 0; i < nrows; i++)
  {
   for (unsigned j = 0; j < ncolumns; j++)
    {
     lu_a[i][j] = A_pt->get_value(i,j);
    }
  }
 
 // Do the factorisation
 NR::ludcmp(lu_a, lu_indx, dummy);
 
 // Set the flag to indicate that resolve is enabled since we have
 // computed the LU decomposition
 Resolve_enabled = true; 
 
}

// ===================================================================
// Performs the back substitution with the LU decomposed matrix
// ===================================================================
void CCLUSolverNumericalRecipes::back_substitution(CAMatrix *_b_pt,
                                                   CAMatrix *_x_pt)
{
 // Prepare the data to call lubksb()
 
 // The size of the right-hand side
 const unsigned n_rows = _b_pt->nrows();
 
 // Number of right hand sizes (same as the number of output
 // x-vectors)
 const unsigned n_rhs = _b_pt->ncolumns();
 
 // The solution vector size n x 1 (Numerical Recipes definition)
 Vec_DP x(n_rows);
 
 // Copy the right-hand side into the solution vectors
 for (unsigned j = 0; j < n_rhs; j++)
  {
   for (unsigned i = 0; i < n_rows; i++)
    {
     x[i] = _b_pt->get_value(i,j);
    }
   
   // Back-substitution
   NR::lubksb(lu_a, lu_indx, x);
   
   // Copy the solution into the output vector
   for (unsigned i = 0; i < n_rows; i++)
    {
     x_pt->set_value(i, j, x[i]);
    }
   
  }
 
}

// ===================================================================
// Copy constructor (we do not want this class to be copiable because
// it contains dynamically allocated variables, A in this case). Check
// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
// ===================================================================
CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes(const CCLUSolverNumericalRecipes &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call it
 // here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in "
           << "CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes() "
           << "- Copy constructor called" << std::endl;
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
CCLUSolverNumericalRecipes& CCLUSolverNumericalRecipes::operator=(const CCLUSolverNumericalRecipes &copy)
{
 // TODO Julio: Implement a class to handle runtime errors and call it
 // here!!!
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << "ERROR in CCLUSolverNumericalRecipes::operator=() - "
           << "Assignment called" << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 throw(1);
}


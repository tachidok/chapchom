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
CCLUSolverNumericalRecipes::CCLUSolverNumericalRecipes(const double **_A,
                                                       const unsigned m,
                                                       const unsigned n)
 : CALinearSolver(_A, m, n),
   Resolve_enabled(false) { }

// ===================================================================
// Empty destructor
// ===================================================================
CCLUSolverNumericalRecipes::~CCLUSolverNumericalRecipes() { }

// ===================================================================
// Virtual function to solve a system of equations with input A. We
// specify the right-hand side b and the x vector where the result is
// returned. We assume that the input/output vectors have the correct
// dimensions (size n). Note that the input A is not modified, it is
// copied to an internal storage
// ===================================================================
void CCLUSolverNumericalRecipes::solve(const double **_A,
                                       const unsigned m,
                                       const unsigned n, 
                                       const double *b,
                                       double *x)
{
 // Set the matrix and its size
 set_matrix_A(_A, m, n);
 
 // Solve
 solve(b, x);
 
}

// ===================================================================
// Virtual function to solve a system of equations with the already
// stored matrix A. We specify the right-hand side b and the x vector
// where the result is returned. We assume that the input/output
// vectors have the correct dimensions (size n).
// ===================================================================
void CCLUSolverNumericalRecipes::solve(const double *b, double *x)
{
 // We can only call solve if the matrix A has been set
 if (Matrix_A_has_been_set)
  {     
   // Factorise
   factorise();
   
   // ... and do back substitution
   back_substitution(b, x);
   
  }
 
}

// ===================================================================
// Virtual function to re-solve a system of equations with the already
// stored matrix A. Reusing the LU decomposition. We specify the
// right-hand side b and the x vector where the result is returned. We
// assume that the input/output vectors have the correct dimensions
// (size n).
// ===================================================================
void CCLUSolverNumericalRecipes::resolve(const double *b, double *x)
{
 // We can only do back-substitution if a matrix has been
 // factorised
 if (Resolve_enabled)
  {
   // Do the back substitution
   back_substitution(b, x);
  }
 
}

// ===================================================================
// Performs LU factorisation of the input matrix, the factorisation is
// internally stored such that it can be re-used when calling resolve
// ===================================================================
void CCLUSolverNumericalRecipes::factorise(const double **_A,
                                           const unsigned m,
                                           const unsigned n)
{
 // Set the matrix and its size
 set_matrix_A(_A, m, n);
 
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
 if (NRows!=NColumns)
  {
   // TODO Julio: Implement a class to handle runtime errors and call
   // it here!!!
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "ERROR in CCLUSolverNumericalRecipes::factorise() - "
             << "The matrix is not square." << std::endl;
   std::cout << "The matrix is of size: " << NRows << " x " << NColumns 
	     << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   throw(1);
  }
 
 // The size of the matrix
 const unsigned n = NRows;
 
 // The matrix used as input and output, after calling ludcmp it has
 // the LU factorisation
 Mat_DP a(n, n);
 
 // Output vector of size n x 1 that records the row permutations
 // performed by partial pivoting.
 Vec_INT indx(n);
 
 // An output indicating whether the number of rows interchanges was
 // even or odd (+1 or -1, respectively)
 DP d;
 
 // Copy the matrix A to the representation expected by ludcmp()
 for (unsigned i = 0; i < n; i++)
  {
   for (unsigned j = 0; j < n; j++)
    {
     a[i][j] = A[i][j];
    }
  }
 
 // Do the factorisation
 NR::ludcmp(a, indx, d);
 
 // Set the flag to indicate that resolve is enabled since we have
 // computed the LU decomposition
 Resolve_enabled = true; 
 
}

// ===================================================================
// Performs the back substitution with the LU decomposed matrix
// ===================================================================
void CCLUSolverNumericalRecipes::back_substitution(const double *_b,
                                                   double *_x)
{
 // Prepare the data to call lubksb()
 
 // The size of the right-hand side
 const unsigned n = NRows;
 
 // Number of right hand sizes (same as the number of output
 // x-vectors)
 const unsigned n_rhs = 1;
 
 // The solution vector size n x 1 (Numerical Recipes definition)
 Vec_DP x(n);
 
 // Copy the right-hand side into the solution vectors
 for (unsigned i = 0; i < n; i++)
  {
   x[i] = _b[i];
  }
 
 // >> Backward substitution
 NR::lubksb(a, indx, x);
 
 // >> Copy the solution
 for (unsigned j = 0; j < n; j++)
  {
   _x[j] = x[j];
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


// IN THIS FILE: Implementation of the concrete class
// CCSolverArmadillo to solve systems of equations. This class calls
// the methods solve() or spsolve() from Armadillo to perform the
// solution of the system of equations.

#include "cc_solver_armadillo.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::CCSolverArmadillo()
  : ACLinearSolver<T>(),
    Resolve_enabled(false) { }

 // ===================================================================
 // Constructor where we specify the matrix A of size m X n
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::CCSolverArmadillo(const CCMatrix<T> &A)
  : ACLinearSolver<T>(A),
    Resolve_enabled(false) { }

 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCSolverArmadillo<T>::~CCSolverArmadillo() { }

 // ===================================================================
 // Solve a system of equations with input A. We specify the
 // right-hand side B and the X matrices where the results are
 // returned. We assume that the input/output matrices have the
 // correct dimensions: A.ncolumns() x A.nrows() for B, and A.nrows()
 // x A.ncolumns() for X.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrix<T> &A,
                                  const CCMatrix<T> &B,
                                           CCMatrix<T> &X)
 {
  // Set the matrix and its size
  this->set_matrix_A(A);
  
  // Solve
  solve(B, X);
  
 }

 // ===================================================================
 // Solve a system of equations with input A. We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the
 // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrix<T> &A,
                                  const CCVector<T> &b,
                                           CCVector<T> &x)
 {
  // Set the matrix and its size
  this->set_matrix_A(A);
  
  // Solve
  solve(b, x);
 }
 
 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side B and the X matrices where the results
 // are returned. We assume that the input/output matrices have the
 // correct dimensions: A.ncolumns() x A.nrows() for B, and A.nrows()
 // x A.ncolumns() for X.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCMatrix<T> &B,
                                  CCMatrix<T> &X)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // Check correct size of the matrix, right hand side and solution
    // vector    
    if (this->A.ncolumns() != B.nrows())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs matrix are not the same:\n"
                    << "A.ncolumns() = (" << this->A.ncolumns() << ")\n"
                    << "B.nrows() = (" << B.nrows() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    else if (this->A.nrows() != X.nrows())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of rows of the matrix and the number "
                    << "of rows of the solution matrix are not the same:\n"
                    << "A.nrows() = (" << this->A.nrows() << ")\n"
                    << "X.nrows() = (" << X.nrows() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    // The case for the same number of columns on the rhs vector and
    // the solution vector is tested in the back_substitution() method
    
    // Factorise
    factorise();
   
    // ... and do back substitution
    back_substitution(B, X);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specific any matrix for the system of\n"
                  << "equations. Set one matrix first by calling the/"
                  << "set_matrix() method or use the solve() method where\n"
                  << "you can specify the matrix associated to the system\n"
                  << "of equations." << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side b and the x vectors where the result
 // is returned. We assume that the input/output vectors have the
 // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::solve(const CCVector<T> &b,
                                  CCVector<T> &x)
 {
  // We can only call solve if the matrix A has been set
  if (this->Matrix_A_has_been_set)
   {
    // Check correct size of the matrix, right hand side and solution
    // vector    
    if (this->A.ncolumns() != b.nvalues())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of columns of the matrix and the number "
                    << "of rows of the rhs vector are not the same:\n"
                    << "A.ncolumns() = (" << this->A.ncolumns() << ")\n"
                    << "b.nvalues() = (" << b.nvalues() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    else if (this->A.nrows() != x.nvalues())
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of rows of the matrix and the number "
                    << "of rows of the solution vector are not the same:\n"
                    << "A.nrows() = (" << this->A.nrows() << ")\n"
                    << "x.nvalues() = (" << x.nvalues() << ")\n" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    // The case for the same number of columns on the rhs vector and
    // the solution vector is tested in the back_substitution() method
    
    // Factorise
    factorise();
    
    // ... and do back substitution
    back_substitution(b, x);
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specific any matrix for the system of\n"
                  << "equations. Set one matrix first by calling the/"
                  << "set_matrix() method or use the solve() method where\n"
                  << "you can specify the matrix associated to the system\n"
                  << "of equations." << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 // Re-solve a system of equations with the already stored matrix
 // A. Reusing the LU decomposition. We specify the right-hand side B
 // and the X matrices where the results are returned. We assume that
 // the input/output vectors have the correct dimensions: A.ncolumns()
 // x A.nrows() for B, and A.nrows() x A.ncolumns() for X.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::resolve(const CCMatrix<T> &B,
                                    CCMatrix<T> &X)
 {
  // We can only do back-substitution if a matrix has been factorised
  if (Resolve_enabled)
   {
    // Do the back substitution
    back_substitution(B, X);
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Resolve is not enabled.\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }

 // ===================================================================
 // Re-solve a system of equations with the already stored matrix A
 // (re-use of the LU decomposition or call the solve method for an
 // iterative solver). BROKEN beacuse iterative solvers may not
 // implement it. We specify the right-hand side b and the x vector
 // where the result is returned. We assume that the input/output
 // vectors have the correct dimensions: A.ncolumns() for b, and
 // A.nrows() for x.
 // ===================================================================
 template<class T>
 void CCSolverArmadillo<T>::resolve(const CCVector<T> &b,
                                    CCVector<T> &x)
 {
  // We can only do back-substitution if a matrix has been factorised
  if (Resolve_enabled)
   {
    // Do the back substitution
    back_substitution(b, x);
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Resolve is not enabled.\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
  
}

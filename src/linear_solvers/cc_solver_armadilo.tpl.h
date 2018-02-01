// IN THIS FILE: The definition of the concrete class
// CCSolverArmadillo to solve systems of equations. This class calls
// the methods solve() or spsolve() from Armadillo to perform the
// solution of the system of equations.

// Check whether the class has been already defined
#ifndef CCSOLVERARMADILLO_TPL_H
#define CCSOLVERARMADILLO_TPL_H

#include "ac_linear_solver.h"

// Add Armadillo's includes
#include <armadillo>

namespace chapchom
{

 // A concrete class for solving a linear system of equations. This
 // class uses the methods solve() or spsolve() from Armadillo to
 // perform the solution of the system of equations.
 template<class T>
  class CCSolverArmadillo : public virtual ACLinearSolver<T>
  {
 
  public:
 
   // Empty constructor
   CCSolverArmadillo();
   
   // Constructor where we specify the matrix A
   CCSolverArmadillo(const CCMatrix<T> &A);
 
   // Empty destructor
   ~CCSolverArmadillo();
 
   // Solve a system of equations with input A. We
   // specify the right-hand side B and the X matrices where the
   // results are returned. We assume that the input/output matrices
   // have the correct dimensions: A.ncolumns() x A.nrows() for B, and
   // A.nrows() x A.ncolumns() for X.
   void solve(const CCMatrix<T> &A, const CCMatrix<T> &B, CCMatrix<T> &X);

   // Solve a system of equations with input A. We specify the
   // right-hand side b and the x vector where the result is
   // returned. We assume that the input/output vectors have the
   // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
   void solve(const CCMatrix<T> &A, const CCVector<T> &b, CCVector<T> &x);
  
   // Solve a system of equations with the already stored matrix A. We
   // specify the right-hand side B and the X matrices where the
   // results are returned. We assume that the input/output matrices
   // have the correct dimensions: A.ncolumns() x A.nrows() for B, and
   // A.nrows() x A.ncolumns() for X.
   void solve(const CCMatrix<T> &B, CCMatrix<T> &X);
  
   // Solve a system of equations with the already stored matrix A. We
   // specify the right-hand side b and the x vectors where the result
   // is returned. We assume that the input/output vectors have the
   // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
   void solve(const CCVector<T> &b, CCVector<T> &x);
  
   // Re-solve a system of equations with the already stored matrix
   // A. Reusing the LU decomposition. We specify the right-hand
   // side B and the X matrices where the results are returned. We
   // assume that the input/output vectors have the correct dimensions:
   // A.ncolumns() x A.nrows() for B, and A.nrows() x A.ncolumns() for
   // X.
   void resolve(const CCMatrix<T> &B, CCMatrix<T> &X);
  
   // Re-solve a system of equations with the already stored matrix A
   // (re-use of the LU decomposition or call the solve method for an
   // iterative solver). BROKEN beacuse iterative solvers may not
   // implement it. We specify the right-hand side b and the x vector
   // where the result is returned. We assume that the input/output
   // vectors have the correct dimensions: A.ncolumns() for b, and
   // A.nrows() for x.
   void resolve(const CCVector<T> &b, CCVector<T> &x);
      
  private:
 
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCSolverArmadillo(const CCSolverArmadillo<T> &copy)
    {
     BrokenCopy::broken_copy("CCSolverArmadillo");
    }
 
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCSolverArmadillo<T> &copy)
    {
     BrokenCopy::broken_assign("CCSolverArmadillo");
    }
   
  };
 
}

#endif // #ifndef CCSOLVERARMADILLO_TPL_H

// IN THIS FILE: The definition of the concrete class
// CCSolverArmadillo to solve systems of equations. This class calls
// the methods solve() or spsolve() from Armadillo to perform the
// solution of the system of equations.

// Check whether the class has been already defined
#ifndef CCSOLVERARMADILLO_TPL_H
#define CCSOLVERARMADILLO_TPL_H

// Include the header from inherited class
#include "ac_linear_solver.h"

// Support for Armadillo's wrappers
#include "../../src/matrices/cc_matrix_armadillo.h"

namespace chapchom
{
 
 // A concrete class for solving a linear system of equations. This
 // class uses the methods solve() or spsolve() from Armadillo to
 // perform the solution of the system of equations.
 template<class T>
  class CCSolverArmadillo : public virtual ACLinearSolver<CCMatrixArmadillo<T>, CCVectorArmadillo<T> >
  {
 
  public:
   
   // Empty constructor
   CCSolverArmadillo();
   
   // Constructor where we specify the matrix A
   CCSolverArmadillo(const CCMatrixArmadillo<T> &A);
   
   // Empty destructor
   ~CCSolverArmadillo();
   
   // Solves a system of equations with input A_mat. We specify the
   // right-hand side B and the X matrices where the results are
   // returned. We assume that the input/output matrices have the
   // correct dimensions: A_mat.n_columns() x A_mat.n_rows() for B, and
   // A_mat.n_rows() x A_mat.n_columns() for X.
   void solve(const CCMatrixArmadillo<T> &A_mat, const CCMatrixArmadillo<T> &B, CCMatrixArmadillo<T> &X);
   
   // Solves a system of equations with input A_mat. We specify the
   // right-hand side b and the x vector where the result is
   // returned. We assume that the input/output vectors have the correct
   // dimensions: A_mat.n_columns() for b, and A_mat.n_rows() for x.
   void solve(const CCMatrixArmadillo<T> &A_mat, const CCVectorArmadillo<T> &b, CCVectorArmadillo<T> &x);
   
   // Solve a system of equations with the already stored matrix A. We
   // specify the right-hand side B and the X matrices where the
   // results are returned, B and X may be 1-column matrices
   // (vectors). We assume that the input/output matrices have the
   // correct dimensions.
   void solve(const CCMatrixArmadillo<T> &B, CCMatrixArmadillo<T> &X);
   
   // Solve a system of equations with the already stored matrix A. We
   // specify the right-hand side b and the x vectors where the result
   // is returned. We assume that the input/output vectors have the
   // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
   void solve(const CCVectorArmadillo<T> &b, CCVectorArmadillo<T> &x);
   
  private:
 
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCSolverArmadillo(const CCSolverArmadillo<T> &copy)
    : ACLinearSolver<CCMatrixArmadillo<T>, CCVectorArmadillo<T> >()
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

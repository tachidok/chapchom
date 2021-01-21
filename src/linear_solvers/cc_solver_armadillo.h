/// IN THIS FILE: The definition of the concrete class
/// CCSolverArmadillo to solve systems of equations. This class calls
/// the methods solve() or spsolve() from Armadillo to perform the
/// solution of the system of equations.

/// Check whether the class has been already defined
#ifndef CCSOLVERARMADILLO_H
#define CCSOLVERARMADILLO_H

// Include the header from inherited class
#include "ac_linear_solver.h"

namespace scicellxx
{
 
 /// A concrete class for solving a linear system of equations. This
 /// class uses the methods solve() or spsolve() from Armadillo to
 /// perform the solution of the system of equations.
 class CCSolverArmadillo : public virtual ACLinearSolver
 {
  
 public:
  
  /// Empty constructor
  CCSolverArmadillo();
  
  /// Constructor where we specify the matrix A
  CCSolverArmadillo(ACMatrix<Real> *const A_mat_pt);
  
  /// Empty destructor
  ~CCSolverArmadillo();
  
  /// Solves a system of equations with input A_mat. We specify the
  /// right-hand side B and the X matrices where the results are
  /// returned. We assume that the input/output matrices have the
  /// correct dimensions: A_mat.n_columns() x A_mat.n_rows() for B, and
  /// A_mat.n_rows() x A_mat.n_columns() for X.
  void solve(ACMatrix<Real> *const A_mat_pt, const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);
   
  /// Solves a system of equations with input A_mat. We specify the
  /// right-hand side b and the x vector where the result is
  /// returned. We assume that the input/output vectors have the
  /// correct dimensions: A_mat.n_columns() for b, and A_mat.n_rows()
  /// for x.
  void solve(ACMatrix<Real> *const A_mat_pt, const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
   
  /// Solve a system of equations with the already stored matrix A. We
  /// specify the right-hand side B and the X matrices where the
  /// results are returned, B and X may be 1-column matrices
  /// (vectors). We assume that the input/output matrices have the
  /// correct dimensions.
  void solve(const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);
   
  /// Solve a system of equations with the already stored matrix A. We
  /// specify the right-hand side b and the x vectors where the result
  /// is returned. We assume that the input/output vectors have the
  /// correct dimensions: A.ncolumns() for b, and A.nrows() for x.
  void solve(const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
   
 private:
 
  /// Copy constructor (we do not want this class to be copiable
  /// because it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCSolverArmadillo(const CCSolverArmadillo &copy)
  : ACLinearSolver()
   {
    BrokenCopy::broken_copy("CCSolverArmadillo");
   }
  
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCSolverArmadillo &copy)
   {
    BrokenCopy::broken_assign("CCSolverArmadillo");
   }
   
 };
 
}

#endif // #ifndef CCSOLVERARMADILLO_H

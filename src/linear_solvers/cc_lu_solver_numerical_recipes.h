/// IN THIS FILE: The definition of the concrete class
/// CCLUSolverNumericalRecipes to solve systems of equations by LU
/// decomposition. This class calls the methods ludcmp() and lubksb()
/// from numerical recipes to perform the LU decomposition and
/// back-substitution, respectively.

/// Check whether the class has been already defined
#ifndef CCLUSOLVERNUMERICALRECIPES_H
#define CCLUSOLVERNUMERICALRECIPES_H

// Include the header from inherited class
#include "ac_linear_solver.h"

// The LU factorisation and back-substitution from Numerical Recipes
#include "../../external_src/numerical_recipes/nr.h"

namespace scicellxx
{
 
 /// A concrete class for solving a linear system of equations. This
 /// class uses the methods ludcmp() and lubksb() from numerical recipes
 /// to perform the LU decomposition and back-substitution,
 /// respectively.
 class CCLUSolverNumericalRecipes : public virtual ACLinearSolver
 {
 
 public:
  
  /// Empty constructor
  CCLUSolverNumericalRecipes();
  
  /// Constructor where we specify the matrix A
  CCLUSolverNumericalRecipes(ACMatrix<Real> *const A_mat_pt);
  
  /// Empty destructor
  ~CCLUSolverNumericalRecipes();
  
  /// Solves a system of equations with input A_mat. We specify the
  /// right-hand side B and the X matrices where the results are
  /// returned. We assume that the input/output matrices have the
  /// correct dimensions: A_mat.ncolumns() x A_mat.nrows() for B, and
  /// A_mat.nrows() x A_mat.ncolumns() for X.
  void solve(ACMatrix<Real> *const A_mat_pt, const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);

  /// Solves a system of equations with input A_mat. We specify the
  /// right-hand side b and the x vector where the result is
  /// returned. We assume that the input/output vectors have the
  /// correct dimensions: A_mat.ncolumns() for b, and A_mat.nrows() for
  /// x.
  void solve(ACMatrix<Real> *const A_mat_pt, const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
  
  /// Solve a system of equations with the already stored matrix A. We
  /// specify the right-hand side B and the X matrices where the
  /// results are returned. We assume that the input/output matrices
  /// have the correct dimensions: A.ncolumns() x A.nrows() for B, and
  /// A.nrows() x A.ncolumns() for X.
  void solve(const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);
  
  /// Solve a system of equations with the already stored matrix A. We
  /// specify the right-hand side b and the x vectors where the result
  /// is returned. We assume that the input/output vectors have the
  /// correct dimensions: A.ncolumns() for b, and A.nrows() for x.
  void solve(const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
  
  /// Re-solve a system of equations with the already stored matrix
  /// A. Reusing the LU decomposition. We specify the right-hand
  /// side B and the X matrices where the results are returned. We
  /// assume that the input/output vectors have the correct dimensions:
  /// A.ncolumns() x A.nrows() for B, and A.nrows() x A.ncolumns() for
  /// X.
  void resolve(const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);
  
  /// Re-solve a system of equations with the already stored matrix A
  /// (re-use of the LU decomposition or call the solve method for an
  /// iterative solver). BROKEN beacuse iterative solvers may not
  /// implement it. We specify the right-hand side b and the x vector
  /// where the result is returned. We assume that the input/output
  /// vectors have the correct dimensions: A.ncolumns() for b, and
  /// A.nrows() for x.
  void resolve(const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
  
  /// Performs LU factorisation of the input matrix, the factorisation
  /// is internally stored such that it can be re-used when calling
  /// resolve
  void factorise(ACMatrix<Real> *const A_mat_pt);
 
  /// Performs LU factorisation of already stored matrix A, the
  /// factorisation is internally stored such that it can be re-used
  /// when calling resolve
  void factorise();
  
  /// Performs the back substitution with the LU decomposed matrix
  void back_substitution(const ACMatrix<Real> *const B_pt, ACMatrix<Real> *const X_pt);
  
  /// Performs the back substitution with the LU decomposed matrix
  void back_substitution(const ACVector<Real> *const b_pt, ACVector<Real> *const x_pt);
  
 protected:
  
  /// Flag to indicate whether resolve is enabled (only after calling
  /// factorise)
  bool Resolve_enabled;
  
 private:
  
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCLUSolverNumericalRecipes(const CCLUSolverNumericalRecipes &copy)
  : ACLinearSolver(), Resolve_enabled(false)
   {
    BrokenCopy::broken_copy("CCLUSolverNumericalRecipes");
   }
  
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCLUSolverNumericalRecipes &copy)
   {
    BrokenCopy::broken_assign("CCLUSolverNumericalRecipes");
   }
  
  /// Data used for ludcmp() and lubksb()
  Mat_DP *lu_a;
  Vec_INT *lu_indx;
  
 };
 
}

#endif // #ifndef CCLUSOLVERNUMERICALRECIPES_H

// IN THIS FILE: The definition of the concrete class
// CCLUSolverNumericalRecipes to solve systems of equations by LU
// decomposition. This class calls the methods ludcmp() and lubksb()
// from numerical recipes to perform the LU decomposition and
// back-substitution, respectively.

// Check whether the class has been already defined
#ifndef CCLUSOLVER_H
#define CCLUSOLVER_H

#include "ac_linear_solver.h"

// The LU factorisation and back-substitution from Numerical Recipes
#include "../../external_src/numerical_recipes/nr.h"

// A concrete class for solving a linear system of equations. This
// class uses the methods ludcmp() and lubksb() from numerical recipes
// to perform the LU decomposition and back-substitution,
// respectively.
class CCLUSolverNumericalRecipes : public virtual ACLinearSolver
{
 
 public:
 
 // Empty constructor
 CCLUSolverNumericalRecipes();
 
 // Constructor where we specify the matrix A
 CCLUSolverNumericalRecipes(const CCMatrix &A);
 
 // Empty destructor
 ~CCLUSolverNumericalRecipes();
 
 // Solve a system of equations with input A. We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n).
 void solve(const CCMatrix &A, const CCMatrix &b, CCMatrix &x);
 
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n).
 void solve(const CCMatrix &b, CCMatrix &x);
 
 // Re-solve a system of equations with the already stored matrix
 // A. Reusing the LU decomposition. We specify the right-hand side b
 // and the x vector where the result is returned. We assume that the
 // input/output vectors have the correct dimensions (size n).
 void resolve(const CCMatrix &b, CCMatrix &x);
  
 // Performs LU factorisation of the input matrix, the factorisation
 // is internally stored such that it can be re-used when calling
 // resolve
 void factorise(const CCMatrix &A);
 
 // Performs LU factorisation of already stored matrix A, the
 // factorisation is internally stored such that it can be re-used
 // when calling resolve
 void factorise();
 
 // Performs the back substitution with the LU decomposed matrix
 void back_substitution(const CCMatrix &b, CCMatrix &x);
 
 protected:
 
 // Flag to indicate whether resolve is enabled (only after calling
 // factorise)
 bool Resolve_enabled;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCLUSolverNumericalRecipes(const CCLUSolverNumericalRecipes &copy)
  {
   BrokenCopy::broken_copy("CCLUSolverNumericalRecipes");
  }
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCLUSolverNumericalRecipes &copy)
  {
   BrokenCopy::broken_assign("CCLUSolverNumericalRecipes");
  }
 
 // Data used for ludcmp()
 Mat_DP lu_a;
 Vec_INT *lu_indx;
  
};

#endif // #ifndef CCLUSOLVER_H

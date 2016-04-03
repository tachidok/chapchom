// IN THIS FILE: The definition of the concrete class
// CCLUSolverNumericalRecipes to solve systems of equations by LU
// decomposition. This class calls the methods ludcmp() and lubksb()
// from numerical recipes to perform the LU decomposition and
// back-substitution, respectively.

// Check whether the class has been already defined
#ifndef CCLUSOLVER_H
#define CCLUSOLVER_H

#include "CALinearSolver.h"

// The LU factorisation and back-substitution from Numerical Recipes
#include "../../external_src/NumericalRecipes/nr.h"

// A concrete class for solving a linear system of equations. This
// class uses the methods ludcmp() and lubksb() from numerical recipes
// to perform the LU decomposition and back-substitution,
// respectively.
class CCLUSolverNumericalRecipes : public virtual CALinearSolver
{
 
 public:
 
 // Empty constructor
 CCLUSolverNumericalRecipes();
 
 // Constructor where we specify the matrix A
 CCLUSolverNumericalRecipes(CAMatrix *_A_pt);
 
 // Empty destructor
 ~CCLUSolverNumericalRecipes();
 
 // Solve a system of equations with input A. We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n).
 void solve(CAMatrix *_A_pt, CAMatrix *_b_pt, CAMatrix *_x_pt);
 
 // Solve a system of equations with the already stored matrix A. We
 // specify the right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n).
 void solve(CAMatrix *_b_pt, CAMatrix *_x_pt);
 
 // Re-solve a system of equations with the already stored matrix
 // A. Reusing the LU decomposition. We specify the right-hand side b
 // and the x vector where the result is returned. We assume that the
 // input/output vectors have the correct dimensions (size n).
 void resolve(CAMatrix *_b_pt, CAMatrix *_x_pt);
 
 // Performs LU factorisation of the input matrix, the factorisation
 // is internally stored such that it can be re-used when calling
 // resolve
 void factorise(CAMatrix *_A_pt);
 
 // Performs LU factorisation of already stored matrix A, the
 // factorisation is internally stored such that it can be re-used
 // when calling resolve
 void factorise();
 
 // Performs the back substitution with the LU decomposed matrix
 void back_substitution(CAMatrix *_b_pt, CAMatrix *_x_pt);
 
 protected:
 
 // Flag to indicate whether resolve is enabled (only after calling
 // factorise)
 bool Resolve_enabled;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCLUSolverNumericalRecipes(const CCLUSolverNumericalRecipes &copy);
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCLUSolverNumericalRecipes& operator=(const CCLUSolverNumericalRecipes &copy);
 
 // Data used for ludcmp()
 Mat_DP lu_a;
 Vec_INT *lu_indx;
  
};

#endif // #ifndef CCLUSOLVER_H

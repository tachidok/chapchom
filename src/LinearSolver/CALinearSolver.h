// IN THIS FILE: The definition of an abstract class to solve linear
// systems of equations. Concrete or specific solvers MUST inherent
// from this abstract class and implement the methods solve() and
// resolve()

// Check whether the class has been already defined
#ifndef CALINEARSOLVER_H
#define CALINEARSOLVER_H

#include "../General/HCommon_includes.h"

// Abstract class to solve linear systems of equations, this class is
// inhereted by any concrete implementations of linear solvers.
class CALinearSolver
{

 public:
 
 // Empty constructor
 CALinearSolver();
 
 // Constructor where we specify the matrix A of size m X n
 CALinearSolver(const double **_A, const unsigned m, const unsigned n);
 
 // Empty destructor
 virtual ~CALinearSolver();
 
 // Set the matrix A
 void set_matrix_A(const double **_A, const unsigned m, const unsigned n);

 // Clean up for any dynamically stored data
 void clean_up();
 
 // Virtual function to solve a system of equations with input A. We
 // specify the right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n). Note that the input A is not modified, it is
 // copied to an internal storage
 virtual void solve(const double **_A, const unsigned m, const unsigned n, 
		    const double *b, double *x) = 0;
 
 // Virtual function to solve a system of equations with the already
 // stored matrix A. We specify the right-hand side b and the x vector
 // where the result is returned. We assume that the input/output
 // vectors have the correct dimensions (size n).
 virtual void solve(const double *b, double *x) = 0;
 
 // Virtual function to re-solve a system of equations with the
 // already stored matrix A (re-use of the LU decomposition or call
 // the solve method for an iterative solver). We specify the
 // right-hand side b and the x vector where the result is
 // returned. We assume that the input/output vectors have the correct
 // dimensions (size n).
 virtual void resolve(const double *b, double *x);
 
 protected:
 
 // The matrix A
 double **A;
 
 // The size of the matrix
 unsigned NRows;
 unsigned NColumns;
 
 // Flag to indicate whether the matrix A has been set
 bool Matrix_A_has_been_set;
 
 private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CALinearSolver(const CALinearSolver &copy);
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CALinearSolver& operator=(const CALinearSolver &copy);
};

#endif // #ifndef CALINEARSOLVER_H

// IN THIS FILE: The definition of an abstract class to solve linear
// systems of equations. Concrete or specific solvers MUST inherent
// from this abstract class and implement the methods solve() and
// resolve()

// Check whether the class has been already defined
#ifndef ACLINEARSOLVER_H
#define ACLINEARSOLVER_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/cc_matrix.h"

namespace chapchom
{

 // Abstract class to solve linear systems of equations, this class is
 // inhereted by any concrete implementations of linear solvers.
 class ACLinearSolver
 {

 public:
 
  // Constructor
  ACLinearSolver();
 
  // Constructor where we specify the matrix A
  ACLinearSolver(const CCMatrix &matrix);
 
  // Empty destructor
  virtual ~ACLinearSolver();
 
  // Set the matrix A
  void set_matrix_A(const CCMatrix &matrix);
 
  // Clean up for any dynamically stored data
  void clean_up();
 
  // Virtual function to solve a system of equations with input A. We
  // specify the right-hand side b and the x vector where the result is
  // returned. We assume that the input/output vectors have the correct
  // dimensions (size n).
  virtual void solve(const CCMatrix &A, const CCMatrix &b, CCMatrix &x) = 0;
 
  // Virtual function to solve a system of equations with the already
  // stored matrix A. We specify the right-hand side b and the x vector
  // where the result is returned. We assume that the input/output
  // vectors have the correct dimensions (size n).
  virtual void solve(const CCMatrix &b, CCMatrix &x) = 0;
 
  // Virtual function to re-solve a system of equations with the
  // already stored matrix A (re-use of the LU decomposition or call
  // the solve method for an iterative solver). BROKEN beacuse
  // iterative solvers may not implement it. We specify the right-hand
  // side b and the x vector where the result is returned. We assume
  // that the input/output vectors have the correct dimensions (size
  // n).
  virtual void resolve(const CCMatrix &b, CCMatrix &x)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Virtual function to resolve systems of equations should be\n"
                 << "implemented in derived class" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 protected:
 
  // The matrix A
  CCMatrix A;
 
  // Flag to indicate whether the matrix A has been set
  bool Matrix_A_has_been_set;
 
 private:
 
  // Copy constructor (we do not want this class to be copiable). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACLinearSolver(const ACLinearSolver &copy)
   {
    BrokenCopy::broken_copy("ACLinearSolver");
   }
 
  // Assignment operator (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACLinearSolver &copy)
   {
    BrokenCopy::broken_assign("ACLinearSolver");
   }
 
 };

}
 
#endif // #ifndef ACLINEARSOLVER_H

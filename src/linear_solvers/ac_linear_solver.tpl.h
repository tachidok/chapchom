// IN THIS FILE: The definition of an abstract class to solve linear
// systems of equations. Concrete or specific solvers MUST inherent
// from this abstract class and implement the methods solve() and
// resolve()

// Check whether the class has been already defined
#ifndef ACLINEARSOLVER_TPL_H
#define ACLINEARSOLVER_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/cc_matrix.h"
// We do not require to include the cc_vector.h file since it is
// already included in the cc_matrix.h file.

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo headers since the templates may include Armadillo
// matrices types
#include <armadillo>
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

namespace chapchom
{

 // Abstract class to solve linear systems of equations, this class is
 // inhereted by any concrete implementations of linear solvers.
 template<class MAT_TYPE, class VEC_TYPE>
  class ACLinearSolver
  {

 public:
 
  // Constructor
  ACLinearSolver();
 
  // Constructor where we specify the matrix A
  ACLinearSolver(const MAT_TYPE &matrix);
 
  // Empty destructor
  virtual ~ACLinearSolver();
  
  // Set the matrix A
  void set_matrix_A(const MAT_TYPE &matrix);
  
  // Clean up for any dynamically stored data
  void clean_up();
  
  // Virtual function to solve a system of equations with input A. We
  // specify the right-hand side B and the X matrices where the
  // results are returned. We assume that the input/output matrices
  // have the correct dimensions: A.ncolumns() x A.nrows() for B, and
  // A.nrows() x A.ncolumns() for X.
  virtual void solve(const MAT_TYPE &A, const MAT_TYPE &B, MAT_TYPE &X) = 0;
  
  // Virtual function to solve a system of equations with input A. We
  // specify the right-hand side b and the x vector where the result
  // is returned. We assume that the input/output vectors have the
  // correct dimensions: A.ncolumns() for b, and A.nrows() for x.
  virtual void solve(const MAT_TYPE &A, const VEC_TYPE &b, VEC_TYPE &x) = 0;
  
  // Virtual function to solve a system of equations with the already
  // stored matrix A. We specify the right-hand side B and the X
  // matrices where the results are returned. We assume that the
  // input/output matrices have the correct dimensions: A.ncolumns() x
  // A.nrows() for B, and A.nrows() x A.ncolumns() for X.
  virtual void solve(const MAT_TYPE &B, MAT_TYPE &X) = 0;
  
  // Virtual function to solve a system of equations with the already
  // stored matrix A. We specify the right-hand side b and the x
  // vectors where the result is returned. We assume that the
  // input/output vectors have the correct dimensions: A.ncolumns()
  // for b, and A.nrows() for x.
  virtual void solve(const VEC_TYPE &b, VEC_TYPE &x) = 0;
  
  // Virtual function to re-solve a system of equations with the
  // already stored matrix A (re-use of the LU decomposition or call
  // the solve method for an iterative solver). BROKEN beacuse
  // iterative solvers may not implement it. We specify the right-hand
  // side B and the X matrices where the results are returned. We
  // assume that the input/output vectors have the correct dimensions:
  // A.ncolumns() x A.nrows() for B, and A.nrows() x A.ncolumns() for
  // X.
  virtual void resolve(const MAT_TYPE &B, MAT_TYPE &X)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Virtual function to resolve systems of equations should be\n"
                 << "implemented in derived class" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
  
  // Virtual function to re-solve a system of equations with the
  // already stored matrix A (re-use of the LU decomposition or call
  // the solve method for an iterative solver). BROKEN beacuse
  // iterative solvers may not implement it. We specify the right-hand
  // side b and the x vector where the result is returned. We assume
  // that the input/output vectors have the correct dimensions:
  // A.ncolumns() for b, and A.nrows() for x.
  virtual void resolve(const VEC_TYPE &b, VEC_TYPE &x)
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
  MAT_TYPE A;
  
  // Flag to indicate whether the matrix A has been set
  bool Matrix_A_has_been_set;
  
 private:
 
  // Copy constructor (we do not want this class to be copiable). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACLinearSolver(const ACLinearSolver<MAT_TYPE, VEC_TYPE> &copy)
   {
    BrokenCopy::broken_copy("ACLinearSolver");
   }
 
  // Assignment operator (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACLinearSolver<MAT_TYPE, VEC_TYPE> &copy)
   {
    BrokenCopy::broken_assign("ACLinearSolver");
   }
 
 };

}
 
#endif // #ifndef ACLINEARSOLVER_TPL_H

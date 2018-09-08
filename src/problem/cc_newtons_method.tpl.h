// IN THIS FILE: The definition of the concrete class CCNewtonsMethod
// to apply Newton's methods for the solution of a given problem

// Check whether the class has been already defined
#ifndef CCNEWTONSMETHOD_TPL_H
#define CCNEWTONSMETHOD_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Includes the abstract class for strategies to compute the Jacobian
#include "ac_jacobian.tpl.h"

namespace chapchom
{
 
#define DEFAULT_NEWTON_SOLVER_TOLERANCE 1.0e-8
#define DEFAULT_MAXIMUM_NEWTON_ITERATIONS 10
#define DEFAULT_MAXIMUM_ALLOWED_RESIDUAL 10.0
 
 // A concrete class for solving a given problem by means of Newton's
 // method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCNewtonsMethod
  {
   
  public:
   
   // Empty constructor
   CCNewtonsMethod();
   
   // Empty destructor
   ~CCNewtonsMethod();
   
   // Set the Jacobian computation strategy
   void set_jacobian_computation_strategy(const ACJacobian<MAT_TYPE> *jacobian_strategy_pt);
   
   // Gets access to the Jacobian computation strategy
   inline ACJacobian<MAT_TYPE> *jacobian_strategy_pt() {return Jacobian_strategy_pt;}
   
   // Applies Newton's method to solve the problem given by the
   // already stored Jacobian and the rhs. The initial guess is set in
   // the dx vector where the final solution (if any) is returned
   void solve(const VEC_TYPE &rhs, VEC_TYPE &dx);
   
  protected:
   
   // A pointer for the strategy to compute the Jacobian
   ACJacobian<MAT_TYPE> *Jacobian_strategy_pt;
   
   // Newton's solver tolerance
   double Newton_solver_tolerance;
   
   // Maximun number of Newton's iterations
   unsigned Maximum_newton_interations;

   // Maximum allowed residual
   double Maximum_allowed_residual;
   
   // Flag to indicate whether the Jacobian computation strategy has been set
   bool Jacobian_computation_strategy_has_been_set;
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCNewtonsMethod(const CCNewtonsMethod<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCNewtonsMethod");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCNewtonsMethod<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCNewtonsMethod");
    }
   
  };
 
}

#endif // #ifndef CCNEWTONSMETHOD_TPL_H


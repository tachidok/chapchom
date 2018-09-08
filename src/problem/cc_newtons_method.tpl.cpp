// IN THIS FILE: Implementation of the concrete class CCNewtonMethod
// to solve a given problem by means of Newton's method

#include "cc_newtons_method.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::CCNewtonsMethod()
  : Newton_solver_tolerance(DEFAULT_NEWTON_SOLVER_TOLERANCE),
    Maximum_newton_interations(DEFAULT_MAXIMUM_NEWTON_ITERATIONS),
    Maximum_allowed_residual(DEFAULT_MAXIMUM_ALLOWED_RESIDUAL),
    Jacobian_computation_strategy_has_been_set(false)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethod()
 {
  
 }
 
 // ===================================================================
 // Set the Jacobian matrix
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 set_jacobian_computation_strategy(const ACJacobian<MAT_TYPE> *jacobian_strategy_pt)
 {  
  // Set the Jacobian computation strategy
  Jacobian_strategy_pt = jacobian_strategy_pt;
  
  // Indicate that the Jacobian computation strategy has been set
  Jacobian_computation_strategy_has_been_set = true;
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem with the rhs. The
 // initial guess is set in the dx vector where the final solution (if
 // any) is returned
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve(const VEC_TYPE &rhs,
                                                 VEC_TYPE &dx)
 {
  // We need to check whether a Jacobian computation strategy has been
  // set
  if (!this->Jacobian_computation_strategy_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified a Jacobian compuitation strategy.\n"
                  << "Set it first by calling the method\n\n"
                  << "set_jacobian_computation_strategy()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
  
  // We need to pass an strategy to compute the Jacobian matrix and
  // the residuals because they need to be updated every single newton
  // step
  
  // Compute the initial residual
  
  
  // Check for convergence
  
  // Solve the system of equations

  // Compute the new residuals
  
  // Check for convergence
  
 }

}


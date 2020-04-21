/// IN THIS FILE: The definition of the concrete class
/// CCNewtonsMethodForBackwardEuler to apply Newton's methods for
/// Backward Euler method

/// Check whether the class has been already defined
#ifndef CCNEWTONSMETHODFORBACKWARDEULER_H
#define CCNEWTONSMETHODFORBACKWARDEULER_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "cc_jacobian_and_residual_for_backward_euler.h"
#include "ac_newtons_method_for_implicit_time_stepper.h"

namespace chapchom
{
 
 /// A concrete class that implements Newton's method for time stepping
 /// methods
 class CCNewtonsMethodForBackwardEuler : public virtual ACNewtonsMethodForImplicitTimeStepper
 {
  
 public:
  
  /// Constructor
  CCNewtonsMethodForBackwardEuler();
  
  /// Empty destructor
  ~CCNewtonsMethodForBackwardEuler();
  
 protected:
   
  /// Performs actions before initial converngence check
  void actions_before_initial_convergence_check();
   
 private:
  
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCNewtonsMethodForBackwardEuler(const CCNewtonsMethodForBackwardEuler &copy)
   {
    BrokenCopy::broken_copy("CCNewtonsMethodForBackwardEuler");
   }
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCNewtonsMethodForBackwardEuler &copy)
   {
    BrokenCopy::broken_assign("CCNewtonsMethodForBackwardEuler");
   }
   
  /// The Jacobiand and residual computation strategy that implements
  /// Backward-Euler method
  CCJacobianAndResidualForBackwardEuler Jacobian_and_residual_for_backward_euler;
   
 };
 
}

#endif ///= #ifndef CCNEWTONSMETHODFORBACKWARDEULER_H


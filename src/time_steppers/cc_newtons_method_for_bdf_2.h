/// IN THIS FILE: The definition of the concrete class
/// CCNewtonsMethodForBDF2 to apply Newton's methods for BDF 2 method

/// Check whether the class has been already defined
#ifndef CCNEWTONSMETHODFORBDF2_H
#define CCNEWTONSMETHODFORBDF2_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "cc_jacobian_and_residual_for_bdf_2.h"
#include "ac_newtons_method_for_implicit_time_stepper.h"

namespace chapchom
{
 
 /// A concrete class that implements Newton's method for time stepping
 /// methods
 class CCNewtonsMethodForBDF2 : public virtual ACNewtonsMethodForImplicitTimeStepper
 {
   
 public:
   
  /// Constructor
  CCNewtonsMethodForBDF2();
   
  /// Empty destructor
  ~CCNewtonsMethodForBDF2();
   
 protected:
   
  /// Performs actions before initial converngence check
  void actions_before_initial_convergence_check();
   
 private:
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCNewtonsMethodForBDF2(const CCNewtonsMethodForBDF2 &copy)
   {
    BrokenCopy::broken_copy("CCNewtonsMethodForBDF2");
   }
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCNewtonsMethodForBDF2 &copy)
   {
    BrokenCopy::broken_assign("CCNewtonsMethodForBDF2");
   }
   
  /// The Jacobian and Residual computation strategy that implements
  /// BDF 2 method
  CCJacobianAndResidualForBDF2 Jacobian_and_residual_for_bdf_2;
   
 };
 
}

#endif // #ifndef CCNEWTONSMETHODFORBDF2_H


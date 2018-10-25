#ifndef CCBACKWARDEULERMETHOD_TPL_H
#define CCBACKWARDEULERMETHOD_TPL_H

#include "ac_time_stepper.h"

// Newton's method
#include "cc_newtons_method_for_backward_euler.h"

// Time stepper to compute the initial guess for Newton's method
#include "cc_euler_method.h"

namespace chapchom
{
 
 /// @class CCBackwardEulerMethod cc_backward_euler_method.h This
 /// class implements Backward Euler's method to integrate ODE's
 template<class MAT_TYPE, class VEC_TYPE>
  class CCBackwardEulerMethod : public virtual ACTimeStepper
 {
  
 public:
  
  /// Constructor
  CCBackwardEulerMethod();
  
  /// Empty destructor
  virtual ~CCBackwardEulerMethod();
  
  /// Applies Backward Euler method to the given odes from the current
  /// time "t" to the time "t+h".
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCBackwardEulerMethod(const CCBackwardEulerMethod<MAT_TYPE, VEC_TYPE> &copy)
  : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCBackwardEulerMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCBackwardEulerMethod<MAT_TYPE, VEC_TYPE> &copy)
   {
    BrokenCopy::broken_assign("CCBackwardEulerMethod");
   }
  
  // Newton's method for backward Euler
  CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE> Newtons_method;
  
  // The time stepper used to compute the initial guess
  CCEulerMethod Time_stepper_initial_guess;
  
 };
 
}

#endif // #ifndef CCBACKWARDEULERMETHOD_TPL_H

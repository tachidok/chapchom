#ifndef CCADAPTIVERK45DPMETHOD_H
#define CCADAPTIVERK45DPMETHOD_H

#include "ac_adaptive_time_stepper.h"

namespace chapchom
{
 
 /// @class CCAdaptiveRK45DPMethod cc_adaptive_runge_kutta_45DP_method.h
 /// This class implements the Dormand-Prince method for Runge-Kutta 4(5) to
 /// integrate ODE's
 class CCAdaptiveRK45DPMethod : public virtual ACAdaptiveTimeStepper
 {
  
 public:
  
  /// Constructor
  CCAdaptiveRK45DPMethod();
  
  /// Empty destructor
  virtual ~CCAdaptiveRK45DPMethod();
  
  /// Applies Runge-Kutta 4(5) Dormand-Prince method to the given odes
  /// from the current time "t" to the time "t+h". The values of u at
  /// time t+h will be stored at index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u, const unsigned k = 0);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCAdaptiveRK45DPMethod(const CCAdaptiveRK45DPMethod &copy)
  : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCAdaptiveRK45DPMethod");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCAdaptiveRK45DPMethod &copy)
   {
    BrokenCopy::broken_assign("CCAdaptiveRK45DPMethod");
   }
  
 };
 
}
 
#endif // #ifndef CCADAPTIVERK45DPMETHOD_H

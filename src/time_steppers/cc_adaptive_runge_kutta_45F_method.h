#ifndef CCADAPTIVERK45FMETHOD_H
#define CCADAPTIVERK45FMETHOD_H

#include "ac_adaptive_time_stepper.h"

namespace chapchom
{
 
 /// @class CCAdaptiveRK45FMethod cc_adaptive_runge_kutta_45F_method.h
 /// This class implements the Fehlberg method for Runge-Kutta 4(5) to
 /// integrate ODE's
 class CCAdaptiveRK45FMethod : public virtual ACAdaptiveTimeStepper
 {
  
 public:
  
  /// Constructor
  CCAdaptiveRK45FMethod();
  
  /// Empty destructor
  virtual ~CCAdaptiveRK45FMethod();
  
  /// Applies Runge-Kutta 4(5) Fehlberg method to the given odes from
  /// the current time "t" to the time "t+h". The values of u at time
  /// t+h will be stored at index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u, const unsigned k = 0);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCAdaptiveRK45FMethod(const CCAdaptiveRK45FMethod &copy)
  : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCAdaptiveRK45FMethod");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCAdaptiveRK45FMethod &copy)
   {
    BrokenCopy::broken_assign("CCAdaptiveRK45FMethod");
   }
  
 };
 
}
 
#endif // #ifndef CCADAPTIVERK45FMETHOD_H

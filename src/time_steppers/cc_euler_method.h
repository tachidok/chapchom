#ifndef CCEULERMETHOD_H
#define CCEULERMETHOD_H

#include "ac_time_stepper.h"

namespace scicellxx
{

 /// @class CCEulerMethod cc_euler_method.h
 /// This class implements Euler's method to integrate ODE's
 class CCEulerMethod : public virtual ACTimeStepper
 {
 
 public:

  /// Constructor
  CCEulerMethod();
  
  /// Empty destructor
  virtual ~CCEulerMethod();
  
  /// Applies Eulers method to the given odes from the current time
  /// "t" to the time "t+h". The values of u at time t+h will be
  /// stored at index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData &u, const unsigned k = 0);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCEulerMethod(const CCEulerMethod &copy)
   : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCEulerMethod");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCEulerMethod &copy)
   {
    BrokenCopy::broken_assign("CCEulerMethod");
   }

 };

}
 
#endif // #ifndef CCEULERMETHOD_H

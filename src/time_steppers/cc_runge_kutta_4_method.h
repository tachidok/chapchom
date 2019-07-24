#ifndef CCRK4METHOD_H
#define CCRK4METHOD_H

#include "ac_time_stepper.h"

namespace chapchom
{

 /// @class CCRK4Method cc_runge_kutta_4_method.h
 /// This class implements Runge-Kutta 4 method to integrate ODE's
 class CCRK4Method : public virtual ACTimeStepper
 {
 
 public:

  /// Constructor
  CCRK4Method();
  
  /// Empty destructor
  virtual ~CCRK4Method();
  
  /// Applies RK4 method to the given odes from the current time "t"
  /// to the time "t+h". The values of u at time t+h will be stored at
  /// index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u, const unsigned k = 0);
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCRK4Method(const CCRK4Method &copy)
  : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCRK4Method");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCRK4Method &copy)
   {
    BrokenCopy::broken_assign("CCRK4Method");
   }

 };

}
 
#endif // #ifndef CCRK4METHOD_H

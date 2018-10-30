#ifndef CCADAMSMOULTON2PREDICTORCORRECTORMETHOD_H
#define CCADAMSMOULTON2PREDICTORCORRECTORMETHOD_H

#include "ac_time_stepper.h"

namespace chapchom
{

 /// @class CCAdamsMoulton2PCMethod
 /// cc_adams_moulton_2_predictor_corrector_method.h This class
 /// implements Adams-Moulton 2 method or Trapezoidal rule as a
 /// predictor corrector to integrate ODE's. The predictor method is
 /// an Euler method
 class CCAdamsMoulton2PCMethod : public virtual ACTimeStepper
 {
 
 public:

  /// Constructor
  CCAdamsMoulton2PCMethod();
  
  /// Empty destructor
  virtual ~CCAdamsMoulton2PCMethod();
  
  /// Applies Adams-Moulton 2 method implemented as
  /// Predictor-Corrector to the given odes from the current time "t"
  /// to the time "t+h".  The values of u at time t+h will be stored
  /// at index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u, const unsigned k = 0);
  
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCAdamsMoulton2PCMethod(const CCAdamsMoulton2PCMethod &copy)
   : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCAdamsMoulton2PCMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCAdamsMoulton2PCMethod &copy)
   {
    BrokenCopy::broken_assign("CCAdamsMoulton2PCMethod");
   }

 };

}
 
#endif // #ifndef CCADAMSMOULTON2PREDICTORCORRECTORMETHOD_H

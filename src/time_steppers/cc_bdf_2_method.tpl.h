#ifndef CCBDF2METHOD_TPL_H
#define CCBDF2METHOD_TPL_H

#include "ac_time_stepper.h"

// Newton's method
#include "cc_newtons_method_for_bdf_2.h"

// Time stepper to compute the initial guess for Newton's method
#include "cc_euler_method.h"

namespace chapchom
{
 
 /// @class CCBDF2Method cc_bdf2_method.h This class implements
 /// Backward Differentiation Formula method to integrate ODE's
 template<class MAT_TYPE, class VEC_TYPE>
  class CCBDF2Method : public virtual ACTimeStepper
 {
  
 public:
  
  /// Constructor
  CCBDF2Method();
  
  /// Empty destructor
  virtual ~CCBDF2Method();
  
  /// Applies BDF2 method to the given odes from the current time "t"
  /// to the time "t+h". The values of u at time t+h will be stored at
  /// index k (default k = 0).
  void time_step(ACODEs &odes, const Real h, const Real t,
                 CCData<Real> &u, const unsigned k = 0);
  
  // Enables the computation of u_{t+h}
  inline void enable_computation_of_u_at_t_plus_h() {Compute_u_at_time_t_plus_h = true;}
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCBDF2Method(const CCBDF2Method<MAT_TYPE, VEC_TYPE> &copy)
  : ACTimeStepper()
   {
    BrokenCopy::broken_copy("CCBDF2Method");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCBDF2Method<MAT_TYPE, VEC_TYPE> &copy)
   {
    BrokenCopy::broken_assign("CCBDF2Method");
   }
  
  // Newton's method for BDF2
  CCNewtonsMethodForBDF2<MAT_TYPE, VEC_TYPE> Newtons_method;
  
  // The time stepper used to compute the initial guess
  CCEulerMethod Time_stepper_initial_guess;
  
 private:
  
  // Flag to enable the computation of u at time 't+h', it should be
  // enabled ONLY the first time a time_step() is performed
  bool Compute_u_at_time_t_plus_h;
  
 };
 
}

#endif // #ifndef CCBDF2METHOD_TPL_H

#ifndef CCADAPTIVERK45FMETHOD_H
#define CCADAPTIVERK45FMETHOD_H

#include "ac_time_stepper.h"

namespace chapchom
{

#define DEFAULT_RK45F_MAXIMUM_ITERATIONS 5
#ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_RK45F_MAXIMUM_STEP_SIZE 1.0
#define DEFAULT_RK45F_MINIMUM_STEP_SIZE 1.0e-4
#define DEFAULT_RK45F_MAXIMUM_TOLERANCE 1.0e-4
#define DEFAULT_RK45F_MINIMUM_TOLERANCE 1.0e-8
#else
#define DEFAULT_RK45F_MAXIMUM_STEP_SIZE 1.0
#define DEFAULT_RK45F_MINIMUM_STEP_SIZE 1.0e-4
#define DEFAULT_RK45F_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_RK45F_MINIMUM_TOLERANCE 1.0e-6
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
 
 /// @class CCAdaptiveRK45FMethod cc_adaptive_runge_kutta_45F_method.h
 /// This class implements the Fehlberg method for Runge-Kutta 4(5) to
 /// integrate ODE's
 class CCAdaptiveRK45FMethod : public virtual ACTimeStepper
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
  
  /// Resets the time stepper to its initial state. A next step size
  /// must be computed from at least one calling to the "time_step()"
  /// method
  void reset()
  {Next_step_size_computed = false;}
  
  // Set default maximum number of iterations
  inline void set_default_maximum_iterations() 
  {Maximum_iterations = DEFAULT_RK45F_MAXIMUM_ITERATIONS;}
  
  // Set default maximum step size
  inline void set_default_maximum_step_size()
  {Maximum_step_size = DEFAULT_RK45F_MAXIMUM_STEP_SIZE;}

  // Set default minimum step size
  inline void set_default_minimum_step_size()
  {Minimum_step_size = DEFAULT_RK45F_MINIMUM_STEP_SIZE;}

  // Set default maximum error tolerance
  inline void set_default_maximum_tolerance()
  {Maximum_tolerance = DEFAULT_RK45F_MAXIMUM_TOLERANCE;}
  
  // Set default minimum error tolerance
  inline void set_default_minimum_tolerance()
  {Minimum_tolerance = DEFAULT_RK45F_MINIMUM_TOLERANCE;}
  
  // Set new maximum number of iterations
  inline void set_maximum_iterations(const Real new_maximum_iterations)
  {Maximum_iterations = new_maximum_iterations;}
  
  // Set new maximum step size
  inline void set_new_maximum_step_size(const Real new_maximum_step_size)
  {Maximum_step_size = new_maximum_step_size;}

  // Set new minimum step size
  inline void set_new_minimum_step_size(const Real new_minimum_step_size)
  {Minimum_step_size = new_minimum_step_size;}

  // Set new maximum error tolerance
  inline void set_new_maximum_tolerance(const Real new_maximum_tolerance)
  {Maximum_tolerance = new_maximum_tolerance;}

  // Set new minimum error tolerance
  inline void set_new_minimum_tolerance(const Real new_minimum_tolerance)
  {Minimum_tolerance = new_minimum_tolerance;}
  
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
  
  // Maximum number of iterations before accepting a step size
  unsigned Maximum_iterations;
  
  // Maximum step size
  Real Maximum_step_size;
  
  // Minimum step size
  Real Minimum_step_size;
  
  // Maximum error tolerance
  Real Maximum_tolerance;
  
  // Minimum error tolerance
  Real Minimum_tolerance;
  
  // Store the step size for the next time step
  Real Next_step_size;
  
  // A flag to indicate that a time step has been taken thus a
  // Next_step_size for the next time step has been computed
  bool Next_step_size_computed;
};
 
}
 
#endif // #ifndef CCADAPTIVERK45FMETHOD_H

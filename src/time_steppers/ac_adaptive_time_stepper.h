#ifndef CCADAPTIVETIMESTEPPER_H
#define CCADAPTIVETIMESTEPPER_H

#include "ac_time_stepper.h"

namespace chapchom
{

#define DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_ITERATIONS 5
#ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_STEP_SIZE 1.0
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_STEP_SIZE 1.0e-4
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_TOLERANCE 1.0e-8
#else
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_STEP_SIZE 1.0
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_STEP_SIZE 1.0e-2
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_TOLERANCE 1.0e-6
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
 
 /// @class ACAdaptiveTimeStepper ac_adaptive_time_stepper.h This
 /// class implements the interface for the adaptive time stepper
 /// methods to integrate ODE's
 class ACAdaptiveTimeStepper : public virtual ACTimeStepper
 {
  
 public:
  
  /// Constructor
  ACAdaptiveTimeStepper();
  
  /// Empty destructor
  virtual ~ACAdaptiveTimeStepper();
  
  /// Applies an adaptive method to the given odes from the current
  /// time "t" to the time "t+h". The values of u at time t+h will be
  /// stored at index k (default k = 0).
  virtual void time_step(ACODEs &odes, const Real h, const Real t,
                         CCData<Real> &u, const unsigned k = 0) = 0;
  
  /// Resets the time stepper to its initial state. Throw any
  /// automatically computed step size and use that given by the user
  void reset() 
  {
   Next_auto_step_size_computed = false;
   enable_fixed_output();
  }
  
  // Set default maximum number of iterations
  inline void set_default_maximum_iterations() 
  {Maximum_iterations = DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_ITERATIONS;}
  
  // Set default maximum step size
  inline void set_default_maximum_step_size()
  {Maximum_step_size = DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_STEP_SIZE;}

  // Set default minimum step size
  inline void set_default_minimum_step_size()
  {Minimum_step_size = DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_STEP_SIZE;}

  // Set default maximum error tolerance
  inline void set_default_maximum_tolerance()
  {Maximum_tolerance = DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_TOLERANCE;}
  
  // Set default minimum error tolerance
  inline void set_default_minimum_tolerance()
  {Minimum_tolerance = DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_TOLERANCE;}
  
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

  // Enables fixed output, that means, an approximation is computed at
  // the given user step size independently of the adaptive step size
  inline void enable_fixed_output()
  {Fixed_output = true;}
  
  // Disables fixed output, that means, an approximation is computed
  // only at the automatically computed step sizes. The user given
  // step size is only used as an initial step size
  inline void disable_fixed_output()
  {Fixed_output = false;}
  
  // Read only access to the automatically computed step size that was
  // used for the current time step
  const Real current_auto_step_size() const {return Current_auto_step_size;}
  
  // Read only access to the next automatically computed step size
  // that may be used for the next time step
  const Real next_auto_step_size() const {return Next_auto_step_size;}
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 ACAdaptiveTimeStepper(const ACAdaptiveTimeStepper &copy)
    : ACTimeStepper()
   {
    BrokenCopy::broken_copy("ACAdaptiveTimeStepper");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACAdaptiveTimeStepper &copy)
   {
    BrokenCopy::broken_assign("ACAdaptiveTimeStepper");
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
  
  // Store the step size automatically computed that was used for the
  // time step method()
  Real Current_auto_step_size;
  
  // Store the step size automatically computed that will be used for
  // the next time step
  Real Next_auto_step_size;
  
  // A flag to indicate that a time step has been taken thus a next
  // step size has been automatically computed
  bool Next_auto_step_size_computed;
  
  // Indicated whether the adaptive method should output an
  // approximation at the user step size or should be only used as an
  // initial step size
  bool Fixed_output;
 };
 
}
 
#endif // #ifndef CCADAPTIVETIMESTEPPER_H

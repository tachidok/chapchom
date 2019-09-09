#ifndef ACADAPTIVETIMESTEPPER_H
#define ACADAPTIVETIMESTEPPER_H

#include "ac_time_stepper.h"
#include "ac_adaptive_new_step_size_strategy.h"
// Default strategy for adaptive time stepper
#include "cc_adaptive_new_step_size_half_double.h"

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
 
 /// @class ACAdaptiveTimeStepper ac_adaptive_time_stepper.h
 
 // ==============================================================
 /// @class ACAdaptiveTimeStepper ac_adaptive_time_stepper.h This
 /// class implements the interface for the adaptive time stepper
 /// methods to integrate ODE's
 // ==============================================================
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
  }
  
  // In charge of free memory (if any given to the strategy to compute
  // the new step size)
  void clean_up();
  
  // Set the default configuration
  void set_default_configuration();
  
  // Set the default to compute the new time step
  void set_default_new_step_size_strategy();
  
  // Set the strategy to compute the new time step
  void set_new_step_size_strategy(ACAdaptiveNewStepSizeStrategy *new_time_step_strategy_pt);
  
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
  {
   Maximum_tolerance = DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_TOLERANCE;
   New_time_step_strategy_pt->set_default_maximum_tolerance();
  }
  
  // Set default minimum error tolerance
  inline void set_default_minimum_tolerance()
  {
   Minimum_tolerance = DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_TOLERANCE;
   New_time_step_strategy_pt->set_default_minimum_tolerance();
  }
  
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
  {
   Maximum_tolerance = new_maximum_tolerance;
   New_time_step_strategy_pt->set_new_maximum_tolerance(new_maximum_tolerance);
  }

  // Set new minimum error tolerance
  inline void set_new_minimum_tolerance(const Real new_minimum_tolerance)
  {
   Minimum_tolerance = new_minimum_tolerance;
   New_time_step_strategy_pt->set_new_minimum_tolerance(new_minimum_tolerance);
  }
  
  // Read only access to the automatically computed step size that was
  // used for the current time step
  const Real taken_auto_step_size() const {return Taken_auto_step_size;}
  
  // Read only access to the next automatically computed step size
  // that may be used for the next time step
  const Real next_auto_step_size() const {return Next_auto_step_size;}
  
  // Enables output messages for adaptive step size method
  inline void enable_output_messages() {Output_messages=true;}
  
  // Disables output messages for adaptive step size method
  inline void disable_output_messages() {Output_messages=false;}
  
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
  
  // A pointer to the strategy to compute the new time step
  ACAdaptiveNewStepSizeStrategy *New_time_step_strategy_pt;
  
  // Indicates whether the class is in charge of free the memory
  // associated with the strategy to compute the new step size
  bool Free_memory_for_new_time_step_strategy;
  
  // Indicates whether the strategy for new step size has been set
  bool New_time_step_strategy_has_been_set;
  
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
  Real Taken_auto_step_size;
  
  // Store the step size automatically computed that will be used for
  // the next time step
  Real Next_auto_step_size;
  
  // A flag to indicate that a time step has been taken thus a next
  // step size has been automatically computed
  bool Next_auto_step_size_computed;
  
  // Flag to indicate whether output messages are enabled or disabled
  // (enabled by default)
  bool Output_messages;
 };
 
}

#endif // #ifndef ACADAPTIVETIMESTEPPER_H

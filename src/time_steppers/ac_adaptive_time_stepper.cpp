#include "ac_adaptive_time_stepper.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 ACAdaptiveTimeStepper::ACAdaptiveTimeStepper()
  : ACTimeStepper(),
    Maximum_iterations(DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_ITERATIONS),
    Maximum_step_size(DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_STEP_SIZE),
    Minimum_step_size(DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_STEP_SIZE),
    Maximum_tolerance(DEFAULT_ADAPTIVE_TIME_STEPPER_MAXIMUM_TOLERANCE),
    Minimum_tolerance(DEFAULT_ADAPTIVE_TIME_STEPPER_MINIMUM_TOLERANCE),
    Fixed_output(true)
 {
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 ACAdaptiveTimeStepper::~ACAdaptiveTimeStepper()
 {
  
 }
 
}

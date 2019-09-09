#include "ac_predictor_corrector_time_stepper.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 ACPredictorCorrectorTimeStepper::ACPredictorCorrectorTimeStepper()
  : ACTimeStepper(),
    Maximum_iterations(DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_ITERATIONS),
    Maximum_tolerance(DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_TOLERANCE),
    Minimum_tolerance(DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MINIMUM_TOLERANCE),
    Output_messages(false),
    Fixed_number_of_iterations(false),
    Perform_final_evaluation(false)
 {
  // Sets the default new time step strategy
  set_default_configuration();
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 ACPredictorCorrectorTimeStepper::~ACPredictorCorrectorTimeStepper()
 { 

 }

 // ===================================================================
 // Set the default configuration
 // ===================================================================
 void ACPredictorCorrectorTimeStepper::set_default_configuration()
 {
  set_default_maximum_iterations();
  set_default_maximum_tolerance(); 
  set_default_minimum_tolerance();
  
  // By default output messages are disabled
  disable_output_messages();
  // By default disable fixed number of operations
  disable_fixed_number_of_corrections();
  // By default disable the last evaluation
  disable_final_evaluation();
 }
 
}

#include "cc_adaptive_new_step_size_half_double.h"

namespace chapchom
{
 // ===================================================================
 // Constructor (empty)
 // ===================================================================
 CCAdaptiveNewStepSizeHalfDouble::CCAdaptiveNewStepSizeHalfDouble()
  : ACAdaptiveNewStepSizeStrategy()
 {
    
 }

 // ===================================================================
 // Destructor (empty)
 // ===================================================================
 CCAdaptiveNewStepSizeHalfDouble::~CCAdaptiveNewStepSizeHalfDouble()
 {
    
 }
 
 // ===================================================================
 // The strategy to compute the new step size
 // ===================================================================
 Real CCAdaptiveNewStepSizeHalfDouble::new_step_size(const Real local_error, const Real h)
 {
  // Check whether the local error was too much (the step size was
  // too big)
  if (local_error > this->maximum_tolerance())
   {
    // Step was too big
    return h * 0.5;
   }
  else
   {
    // Step was too small
    return h * 2.0;
   }
 }
  
}

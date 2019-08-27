#include "ac_adaptive_new_step_size_strategy.h"

namespace chapchom
{

 // ===================================================================
 // Constructor (empty)
 // ===================================================================
 ACAdaptiveNewStepSizeStrategy::ACAdaptiveNewStepSizeStrategy()
  : Maximum_tolerance(DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MAXIMUM_TOLERANCE),
    Minimum_tolerance(DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MINIMUM_TOLERANCE)
 {
  
 }

 // ===================================================================
 // Destructor (empty)
 // ===================================================================
 ACAdaptiveNewStepSizeStrategy::~ACAdaptiveNewStepSizeStrategy()
 {
  
 } 
 
}

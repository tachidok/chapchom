#ifndef CCADAPTIVENEWSTEPSIZEHALFDOUBLE_H
#define CCADAPTIVENEWSTEPSIZEHALFDOUBLE_H

#include "ac_adaptive_new_step_size_strategy.h"

namespace scicellxx
{ 
 /// @class CCAdaptiveNewStepSizeHalfDouble cc_adaptive_new_step_size_half_double.h
 
 // ==============================================================
 // @class CCAdaptiveNewStepSizeHalfDouble This class implements a
 // concrete strategy to compute the new step size in adaptive time
 // stepping methods
 // ==============================================================
 class CCAdaptiveNewStepSizeHalfDouble : public virtual ACAdaptiveNewStepSizeStrategy
 {
 public:
  // Constructor (empty)
  CCAdaptiveNewStepSizeHalfDouble();
  
  // Destructor (empty)
  virtual ~CCAdaptiveNewStepSizeHalfDouble();
  
  // The strategy to compute the new step size
  Real new_step_size(const Real local_error, const Real h);
  
 private:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCAdaptiveNewStepSizeHalfDouble(const CCAdaptiveNewStepSizeHalfDouble &copy)
   {
    BrokenCopy::broken_copy("CCAdaptiveNewStepSizeHalfDouble");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCAdaptiveNewStepSizeHalfDouble &copy)
   {
    BrokenCopy::broken_assign("CCAdaptiveNewStepSizeHalfDouble");
   }
  
 };
 
}

#endif // #ifndef CCADAPTIVENEWSTEPSIZEHALFDOUBLE_H

#ifndef ACADAPTIVENEWSTEPSIZESTRATEGY_H
#define ACADAPTIVENEWSTEPSIZESTRATEGY_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

namespace chapchom
{
#ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MINIMUM_TOLERANCE 1.0e-8
#else
#define DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MINIMUM_TOLERANCE 1.0e-6
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
 
 /// @class ACAdaptiveNewStepSizeStrategy ac_adaptive_new_step_size_strategy.h
 
 // ==============================================================
 /// @class ACAdaptiveNewStepSizeStrategy This class implements the
 /// interface for the strategies to compute the new step size in
 /// adaptive time stepping methods
 // ==============================================================
 class ACAdaptiveNewStepSizeStrategy
 {
 public:
  
  // Constructor (empty)
  ACAdaptiveNewStepSizeStrategy();
  
  // Destructor (empty)
  virtual ~ACAdaptiveNewStepSizeStrategy();
  
  // Set default maximum error tolerance
  inline void set_default_maximum_tolerance()
  {Maximum_tolerance = DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MAXIMUM_TOLERANCE;}
  
  // Set default minimum error tolerance
  inline void set_default_minimum_tolerance()
  {Minimum_tolerance = DEFAULT_ADAPTIVE_NEW_STEP_SIZE_MINIMUM_TOLERANCE;}
  
  // Set new maximum error tolerance
  inline void set_new_maximum_tolerance(const Real new_maximum_tolerance)
  {Maximum_tolerance = new_maximum_tolerance;}
  
  // Set new minimum error tolerance
  inline void set_new_minimum_tolerance(const Real new_minimum_tolerance)
  {Minimum_tolerance = new_minimum_tolerance;}
  
  // Read-only maximum error tolerance
  inline const Real maximum_tolerance() const {return Maximum_tolerance;}
  
  // Read-only minimum error tolerance
  inline const Real minimum_tolerance() const {return Minimum_tolerance;}
   
  // The strategy to compute the new step size
  virtual Real new_step_size(const Real local_error, const Real h) = 0;
  
 private:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACAdaptiveNewStepSizeStrategy(const ACAdaptiveNewStepSizeStrategy &copy)
   {
    BrokenCopy::broken_copy("ACAdaptiveNewStepSizeStrategy");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACAdaptiveNewStepSizeStrategy &copy)
   {
    BrokenCopy::broken_assign("ACAdaptiveNewStepSizeStrategy");
   }
  
  // Maximum error tolerance
  Real Maximum_tolerance;
  
  // Minimum error tolerance
  Real Minimum_tolerance;
  
 };
 
}

#endif // #ifndef ACADAPTIVENEWSTEPSIZESTRATEGY_H

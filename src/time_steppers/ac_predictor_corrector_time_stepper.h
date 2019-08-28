#ifndef ACPREDICTORCORRECTORTIMESTEPPER_H
#define ACPREDICTORCORRECTORTIMESTEPPER_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type vector for residual
#include "../matrices/cc_vector_armadillo.h"
#else
#include "../matrices/cc_vector.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

#include "./ac_time_stepper.h"

namespace chapchom
{
#define DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_ITERATIONS 10
#ifdef TYPEDEF_REAL_IS_DOUBLE
#define DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MINIMUM_TOLERANCE 1.0e-8
#else
#define DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_TOLERANCE 1.0e-3
#define DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MINIMUM_TOLERANCE 1.0e-6
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
 
 /// @class ACPredictorCorrectorTimeStepper ac_predictor_corrector_time_stepper.h

 /// This class implements the interfaces for integration methods to
 /// solve ODE's that implement a predictor-corrector strategy
 class ACPredictorCorrectorTimeStepper : public virtual ACTimeStepper
 {
 
 public:
 
  /// Empty constructor
  ACPredictorCorrectorTimeStepper();
 
  /// Empty destructor
  virtual ~ACPredictorCorrectorTimeStepper();
  
  /// Performs a time step applying a time integration method to the
  /// given odes from the current time "t" to the time "t+h".
  /// Previous the call of the method, the values of u at time "t"
  /// should be stored at index k (default k = 0). After the call, the
  /// values at time "t+h" will be stored at index k, therefore the
  /// values at time "t" will be at index k+1
  virtual void time_step(ACODEs &odes, const Real h,
                         const Real t,
                         CCData<Real> &u,
                         unsigned k = 0) = 0;

  // Set the default configuration
  void set_default_configuration();
  
  // Set default maximum number of iterations
  inline void set_default_maximum_iterations() 
  {Maximum_iterations = DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_ITERATIONS;}
  
  // Set default maximum error tolerance
  inline void set_default_maximum_tolerance()
  {
   Maximum_tolerance = DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MAXIMUM_TOLERANCE;
  }
  
  // Set default minimum error tolerance
  inline void set_default_minimum_tolerance()
  {
   Minimum_tolerance = DEFAULT_PREDICTOR_CORRECTOR_TIME_STEPPER_MINIMUM_TOLERANCE;
  }
  
  // Set new maximum number of iterations
  inline void set_maximum_iterations(const Real new_maximum_iterations)
  {Maximum_iterations = new_maximum_iterations;}
  
  // Set new maximum error tolerance
  inline void set_new_maximum_tolerance(const Real new_maximum_tolerance)
  {
   Maximum_tolerance = new_maximum_tolerance;
  }

  // Set new minimum error tolerance
  inline void set_new_minimum_tolerance(const Real new_minimum_tolerance)
  {
   Minimum_tolerance = new_minimum_tolerance;
  }
  
  // Enables output messages for adaptive step size method
  inline void enable_output_messages() {Output_messages=true;}
  
  // Disables output messages for adaptive step size method
  inline void disable_output_messages() {Output_messages=false;}
  
  // Maximum number of iterations for the predictor-corrector
  // implementations
  inline unsigned maximum_iterations() const {return Maximum_iterations;}
  
  // Maximum error tolerance for the predictor-corrector
  // implementations
  inline Real maximum_tolerance() const {return Maximum_tolerance;}
  
  // Minimum error tolerance for the predictor-corrector
  // implementations
  inline Real minimum_tolerance() const {return Minimum_tolerance;}
  
  // Flag to indicate whether output messages are enabled or disabled
  // (enabled by default)
  inline bool output_messages() const {return Output_messages;}
  
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACPredictorCorrectorTimeStepper(const ACPredictorCorrectorTimeStepper &copy)
   {
    BrokenCopy::broken_copy("ACPredictorCorrectorTimeStepper");
   }

  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACPredictorCorrectorTimeStepper &copy)
   {
    BrokenCopy::broken_assign("ACPredictorCorrectorTimeStepper");
   }
  
  // Maximum number of iterations for the predictor-corrector
  // implementations
  unsigned Maximum_iterations;
  
  // Maximum error tolerance for the predictor-corrector
  // implementations
  Real Maximum_tolerance;
  
  // Minimum error tolerance for the predictor-corrector
  // implementations
  Real Minimum_tolerance;
  
  // Flag to indicate whether output messages are enabled or disabled
  // (enabled by default)
  bool Output_messages;
  
 };

}
 
#endif // #ifndef ACPREDICTORCORRECTORTIMESTEPPER_H

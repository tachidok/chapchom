#include "cc_adams_moulton_2_predictor_corrector_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCAdamsMoulton2PCMethod::CCAdamsMoulton2PCMethod()
  : ACPredictorCorrectorTimeStepper()
 {
  
  // Sets the number of history values
  N_history_values = 2;
  
  // Enable output messages
  //enable_output_messages();
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCAdamsMoulton2PCMethod::~CCAdamsMoulton2PCMethod()
 {
 
 }
 
 // ===================================================================
 // Applies Adams-Moulton 2 method implemented as Predictor-Corrector
 // to the given odes from the current time "t" to the time "t+h".
 // The values of u at time t+h will be stored at index k (default k =
 // 0).
 // ===================================================================
 void CCAdamsMoulton2PCMethod::time_step(ACODEs &odes, const Real h,
                                         const Real t,
                                         CCData<Real> &u,
                                         const unsigned k)
 {
  // Check if the ode has the correct number of history values to
  // apply Adams-Moulton 2 method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by Adams-Moulton 2 method\n"
                  << "Required number of history values: "
                  << N_history_values << "\n"
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // The method is implemented following an P(EC)^k with an optional
  // final evaluation step of the model at the end, then making it an
  // P(EC)^k E strategy
  
  unsigned n_iterations = 0;
  
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  
  // The residual vector
#ifdef CHAPCHOM_USES_ARMADILLO
  CCVectorArmadillo<Real> local_error_vector(n_odes);
#else 
  CCVector<Real> local_error_vector(n_odes);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
  
  // Allocate memory for the local error vector
  local_error_vector.allocate_memory();
  // Initialise local error with 0
  Real local_error = 0;
  
  // -----------------------------------------------------------------
  // -- Prediction phase --
  // -----------------------------------------------------------------
  // Temporary vector to store the evaluation of the odes.
  CCData<Real> dudt(n_odes);
  // Evaluate the ODE at time "t" using the current values of "u"
  // stored in index k
  odes.evaluate_derivatives(t, u, dudt, k);
  
  // Store the PREDICTED value by the external time stepper. Copy the
  // initial values from u
  CCData<Real> u_p(u);
  
  // Prediction step (Forward Euler)
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_p(i,k) = u(i,k) + (h * (dudt(i)));
   }
  
  // -----------------------------------------------------------------
  // -- Evaluation phase
  // -----------------------------------------------------------------
  // -- Temporary vector to store the evaluation of the odes with the
  // -- predicted values.
  CCData<Real> dudt_p(n_odes);
  
  do {
   // Evaluate the ODE at time "t+h" using the predicted values of
   // "u_p" stored at index k=0 because u_p has not history values
   odes.evaluate_derivatives(t+h, u_p, dudt_p, 0);
   
   // -----------------------------------------------------------------
   // -- Correction phase
   // -----------------------------------------------------------------
   const Real half_h = h * 0.5;
   for (unsigned i = 0; i < n_odes; i++)
   {
    u_p(i,k) = u(i,k) + (half_h * (dudt_p(i) + dudt(i)));
   }
   
   // Compute error
   for (unsigned i = 0; i < n_odes; i++)
    {
     local_error_vector(i) = (u_p(i,k) - u(i,k)) / u_p(i,k);
    }
   
   // Get the maximum norm
   local_error = local_error_vector.norm_inf();
   // Is local error smaller than allowed tolerance
   if (local_error < minimum_tolerance())
    {
     if (output_messages())
      {
       chapchom_output << "Local error is smaller than minimum tolerance value ["
                       << local_error << "] < [" << minimum_tolerance() << "]" << std::endl;
      }
    }
   
   // Increase the number of iterations
   n_iterations++;
   
   if (n_iterations >= maximum_iterations())
    {
     if (output_messages())
      {
       chapchom_output << "Maximum number of iterations reached ["<< maximum_iterations()
                       <<"], local error [" << local_error << "], maximum_tolerance ["
                       << maximum_tolerance() << "]\n"
                       << "You can change the maximum number of iterations by calling the method\n"
                       << "set_maximum_iterations()\n"
                       << "You can change the maximum tolerance by calling the method\n"
                       << "set_new_maximum_tolerance()" << std::endl;
      }
     
    }
   
   // Check whether a fixed number of iterations is enabled
   if (fixed_number_of_iterations())
    {
     // Force local error to be greater than maximum tolerance
     local_error = maximum_tolerance() + 1.0;
    }
   
   // Check whether reaching maximum number of iteratios or error in
   // tolerance ranges
  }while(local_error > maximum_tolerance() && n_iterations < maximum_iterations());
  
  // Shift values to the right to provide storage for the new values
  u.shift_history_values();
  
  // Copy the values to the original vector
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k) = u_p(i,k);
   }
  
 }
 
#if 0
 // ===================================================================
 // Applies Adams-Moulton 2 method implemented as Predictor-Corrector
 // to the given odes from the current time "t" to the time "t+h".
 // The values of u at time t+h will be stored at index k (default k =
 // 0).
 // ===================================================================
 void CCAdamsMoulton2PCMethod::time_step(ACODEs &odes, const Real h,
                                         const Real t,
                                         CCData<Real> &u,
                                         const unsigned k)
 {
  // Check if the ode has the correct number of history values to
  // apply Adams-Moulton 2 method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by Adams-Moulton 2 method\n"
                  << "Required number of history values: "
                  << N_history_values << "\n"
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // The method is implemented following an P(EC)^k with an optional
  // final evaluation step of the model at the end, then making it an
  // P(EC)^k E strategy.
  
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  
  // -----------------------------------------------------------------
  // -- Prediction phase --
  // -----------------------------------------------------------------
  // Temporary vector to store the evaluation of the odes.
  CCData<Real> dudt(n_odes);
  // Evaluate the ODE at time "t" using the current values of "u"
  // stored in index k
  odes.evaluate_derivatives(t, u, dudt, k);
  
  // Store the PREDICTED value by the external time stepper. Copy the
  // initial values from u
  CCData<Real> u_p(u);
  // Perfomed one prediction step and store the result in the
  // predicted u_p
  Time_stepper_initial_guess.time_step(odes, h, t, u_p, k);
  
  // -----------------------------------------------------------------
  // -- Correction phase
  // -----------------------------------------------------------------
  // -- Temporary vector to store the evaluation of the odes with the
  // -- predicted values.
  CCData<Real> dudt_p(n_odes);
  
  // Evaluate the ODE at time "t+h" using the predicted values of
  // "u_p" stored at index k=0 because u_p has not history values
  odes.evaluate_derivatives(t+h, u_p, dudt_p, 0);
  
  // Shift values to the right to provide storage for the new values
  u.shift_history_values();
  
  // -------------------------------------------------------
  // Perform the correction phase
  const Real half_h = h * 0.5;
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k) = u(i,k+1) + (half_h * (dudt_p(i) + dudt(i)));
   }
  
 }
#endif

}

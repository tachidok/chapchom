#include "cc_adams_moulton_2_predictor_corrector_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCAdamsMoulton2PCMethod::CCAdamsMoulton2PCMethod()
  : ACTimeStepper()
 {
  
  // Sets the number of history values
  N_history_values = 1;
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCAdamsMoulton2PCMethod::~CCAdamsMoulton2PCMethod()
 {
 
 }
 
 // ===================================================================
 // Applies Eulers method to the given odes from the current time "t"
 // to the time "t+h"
 // ===================================================================
 void CCAdamsMoulton2PCMethod::time_step(ACODEs &odes, const Real h,
                                         const Real t,
                                         CCData<Real> &u)
 {
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  // Check if the ode has the correct number of history values to
  // apply Euler's method
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

  // -------------------------------------------------------
  // -- Prediction phase
  // -------------------------------------------------------
  // Temporary vector to store the evaluation of the odes
  CCData<Real> dudt(n_odes);
  
  // Evaluate the ODE at time "t" using the current values of "u"
  odes.evaluate(t, u, dudt);
  
  // Index for history values
  const unsigned k = 0;
  
  // Once the derivatives have been obtained do one step of Euler's
  // method and store the result in the predicted u
  CCData<Real> u_p(n_odes, 0); // We do not require history values
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_p(i,k) = u(i,k) + (h * dudt(i));
   }
  
  // -------------------------------------------------------
  // -- Correction phase
  // -- -----------------------------------------------------
  // -- Temporary vector to store the evaluation of the odes with the
  // -- predicted values
  CCData<Real> dudt_p(n_odes);
  
  // Evaluate the ODE at time "t+h" using the predicted values of
  // "u_p"
  odes.evaluate(t+h, u_p, dudt_p);

  // -------------------------------------------------------
  // Perform the correction phase
  const Real half_h = h *0.5;
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k+1) = u(i,k) + (half_h * (dudt_p(i) + dudt(i)));
   }
  
 }

}

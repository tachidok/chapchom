#include "cc_euler_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCEulerMethod::CCEulerMethod()
  : ACTimeStepper()
 {
  
  // Sets the number of history values
  N_history_values = 2;
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCEulerMethod::~CCEulerMethod()
 {
 
 }
 
 // ===================================================================
 // Applies Eulers method to the given odes from the current time "t"
 // to the time "t+h". The values of u at time t+h will be stored at
 // index k (default k = 0).
 // ===================================================================
 void CCEulerMethod::time_step(ACODEs &odes, const Real h,
                               const Real t,
                               CCData &u,
                               const unsigned k)
 {
#ifdef SCICELLXX_PANIC_MODE
  // Check if the ode has the correct number of history values to
  // apply Euler's method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by Euler's method\n"
                  << "Required number of history values: "
                  << N_history_values << "\n"
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
#endif // #ifdef SCICELLXX_PANIC_MODE
  
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  
  // Temporary vector to store the evaluation of the odes.
  CCData dudt(n_odes);
  
  // Evaluate the ODE at time "t" using the values of "u" at index k
  odes.evaluate_derivatives(t, u, dudt, k);
  
  // Shift values to the right to provide storage for the new values
  u.shift_history_values();
  
  // Perform one step of Euler's method
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k) = u(i,k+1) + (h * dudt(i));
   }
  
 }

}

#include "cc_runge_kutta_4_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCRK4Method::CCRK4Method()
  : ACTimeStepper()
 {
 
  // Sets the number of history values
  N_history_values = 1;
 
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCRK4Method::~CCRK4Method()
 {
 
 }
 
 // ===================================================================
 // Applies Runge-Kutta 4 method to the given odes from the current
 // time "t" to the time "t+h"
 // ===================================================================
 void CCRK4Method::time_step(ACODEs &odes, const Real h,
                             const Real t,
                             CCData<Real> &u)
 {
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  // Check if the ode has the correct number of history values to
  // apply Runge-Kutta 4 method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by RK4 methods" << std::endl;
    std::cout << "Required number of history values: "
              << N_history_values << std::endl;
    std::cout << "Number of history values: "
              << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Temporary vector to store the evaluation of the odes
  CCData<Real> dudt(n_odes);
  
  // Evaluate the ODE at time "t" using the current values of "u"
  odes.evaluate(t, u, dudt);
  
  // Index for history values
  const unsigned k = 0;
  
  // Temporary vector to store the K_i evaluations proper of
  // Runge-Kutta methods
  CCData<Real> K1(n_odes);
  CCData<Real> K2(n_odes);
  CCData<Real> K3(n_odes);
  CCData<Real> K4(n_odes);
  
  // Create a copy of the y vector
  CCData<Real> u_temp(u);
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t" using the current values of "u"
  odes.evaluate(t, u, K1);
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "u+(h/2)K1"
  const Real h_half = h*0.5;
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_temp(i,k) = u(i,k)+h_half*K1(i);
   }
  odes.evaluate(t+h_half, u_temp, K2);
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "u+(h/2)K2"
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_temp(i,k) = u(i,k)+h_half*K2(i);
   }
  odes.evaluate(t+h_half, u_temp, K3);
  
  // -------------------------------------------------------------------- 
  // Evaluate the ODE at time "t+h" and with "u+hK3"
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_temp(i,k) = u(i,k)+h*K3(i);
   }
  odes.evaluate(t+h, u_temp, K4);
  
  // Once the derivatives have been obtained compute the new "u" as
  // the weighted sum of the K's
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k+1) = u(i,k) + (h/6.0)*(K1(i) + 2.0*K2(i) + 2.0*K3(i) + K4(i));
   }
 
 }

}

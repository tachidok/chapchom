#include "cc_adaptive_runge_kutta_45DP_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCAdaptiveRK45DPMethod::CCAdaptiveRK45DPMethod()
  : ACTimeStepper()
 {
  
  // Sets the number of history values
  N_history_values = 2;
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCAdaptiveRK45DPMethod::~CCAdaptiveRK45DPMethod()
 {
  
 }
 
 // ===================================================================
 // Applies Runge-Kutta 4(5) Dormand-Prince method to the given odes
 // from the time "t" to the time "t+h". The values of u at time t+h
 // will be stored at index k (default k = 0).
 // ===================================================================
 void CCAdaptiveRK45DPMethod::time_step(ACODEs &odes, const Real h,
                                        const Real t,
                                      CCData<Real> &u,
                                      const unsigned k)
 {
  // Check if the ode has the correct number of history values to
  // apply Runge-Kutta 4(5) Dormand-Prince method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by Adaptive RK45DP method" << std::endl
                  << "Required number of history values: "
                  << N_history_values << std::endl
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  
  // Temporary vector to store the evaluation of the odes.
  CCData<Real> dudt(n_odes);
  
  // Evaluate the ODE at time "t" using the current values of "u"
  odes.evaluate_derivatives(t, u, dudt, k);
  
  // Temporary vector to store the K_i evaluations proper of
  // Runge-Kutta methods
  CCData<Real> K1(n_odes);
  CCData<Real> K2(n_odes);
  CCData<Real> K3(n_odes);
  CCData<Real> K4(n_odes);
  
  // Create a copy of the u vector
  CCData<Real> u_copy(u);
  
  // --------------------------------------------------------------------
  // Runge-Kutta 4(5) Dormand-Prince method
  // --------------------------------------------------------------------
  // K1 = y(t, u)
  // K2 = y(t + \frac{1}{4}h, u + h(\frac{1}{4}K1))
  // K3 = y(t + \frac{3}{8}h, u + h(\frac{3}{32}K1 + \frac{9}{32}K2))
  // K4 = y(t + \frac{12}{13}h, u + h(\frac{1932}{2197}K1 - \frac{7200}{2197}K2 + \frac{7296}{2197}K3))
  // K5 = y(t + h, u + h(\frac{439}{216}K1 - 8K2 + \frac{3680}{513}K3 - \frac{845}{4104}K4))
  // K6 = y(t + \frac{1}{2}h, u + h(-\frac{8}{27}K1 + 2K2 - \frac{3544}{2565}K3 + \frac{1859}{4104}K4 - \frac{11}{40}K5))
  
  // \hat{u}(t+h) = u(t) + \frac{1}{8}h (\frac{25}{216} K1 + \frac{1408}{2565} K3 + \frac{2197}{4104} K4 - \frac{1}{5} K5)
  // \tilde{u}(t+h) = u(t) + \frac{1}{8}h (\frac{16}{135} K1 + \frac{6656}{12825} K3 + \frac{28561}{56430} K4 - \frac{9}{50} K5 + \frac{2}{55} K6)

  // error = \hat{u}(t+h) - \tilde{u}(t+h) = h(\frac{1}{360} K1 - \frac{128}{4275} K3 - \frac{2197}{75240} K4 + \frac{1}{50} K5 + \frac{2}{55} K6)
  // -------------------------------------------------------------------- 
  // Butcher tableau
  // --------------------------------------------------------------------
  // 0             |
  // \frac{1}{4}   | \frac{1}{4}
  // \frac{3}{8}   | \frac{3}{32}        \frac{9}{32}
  // \frac{12}{13} | \frac{1932}{2197}   -\frac{7200}{2197}  \frac{7296}{2197}
  // 1             | \frac{439}{216}     -8                  \frac{3680}{513}     -\frac{845}{4104}
  // \frac{1}{2}   | -\frac{8}{27}       2                  -\frac{3544}{2565}     \frac{1859}{4104}   -\frac{11}{40}
  // --------------------------------------------------------------
  //               | [\frac{25}{216}      0                   \frac{1408}{2565}     \frac{2197}{4104}   -\frac{1}{5}]    0             \frac{1}{8}h
  //               | [\frac{16}{135}      0                   \frac{6656}{12825}    \frac{28561}{56430}  -\frac{9}{50}   \frac{2}{55}] \frac{1}{8}h
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t" using the current values of "u"
  odes.evaluate_derivatives(t, u, K1, k);
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "u+(h/2)K1"
  const Real h_half = h*0.5;
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_copy(i,k) = u(i,k)+h_half*K1(i);
   }
  odes.evaluate_derivatives(t+h_half, u_copy, K2, k);
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "u+(h/2)K2"
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_copy(i,k) = u(i,k)+h_half*K2(i);
   }
  odes.evaluate_derivatives(t+h_half, u_copy, K3, k);
  
  // -------------------------------------------------------------------- 
  // Evaluate the ODE at time "t+h" and with "u+hK3"
  for (unsigned i = 0; i < n_odes; i++)
   {
    u_copy(i,k) = u(i,k)+h*K3(i);
   }
  odes.evaluate_derivatives(t+h, u_copy, K4);
  
  // Shift values to the right to provide storage for the new values
  u.shift_history_values();
  
  // Once the derivatives have been obtained compute the new "u" as
  // the weighted sum of the K's
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k) = u(i,k+1) + (h/6.0)*(K1(i) + 2.0*K2(i) + 2.0*K3(i) + K4(i));
   }
 
 }

}

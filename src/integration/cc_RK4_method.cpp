#include "cc_RK4_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCRK4Method::CCRK4Method()
  : ACExplicitIntegrationMethod()
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
 // Applies Runge-Kutta 4 method to the given odes from time
 // "t_initial" to time "t_final" using an h-step size
 // ===================================================================
 void CCRK4Method::integrate(ACODEs &odes, const double h,
                             const double t_initial,
                             const double t_final,
                             std::vector<std::vector<double> > &y)
 {
  // Current time
  double t = t_initial;
 
  // Loop from "t_initial" to "t_final" with "h" size steps
  while (t <= t_final)
   {
    // Do one integration step
    integrate_step(odes, h, t, y);
    t+=h;
   }
 
 }

 // ===================================================================
 // Applies Runge-Kutta 4 method to the given odes from the current
 // time "t" to the time "t+h"
 // ===================================================================
 void CCRK4Method::integrate_step(ACODEs &odes, const double h,
                                  const double t,
                                  std::vector<std::vector<double> > &y)
 {
  // Check whether we have enough history values to apply Euler's
  // method
  const unsigned n_history_values = y.size();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is not enough to apply this "
                  << "integration method" << std::endl;
    error_message << "Required number of history values: "
                  << N_history_values << std::endl;
    error_message << "Number of history values in input vector 'y': "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Rename a variable
  const unsigned k = n_history_values-2;
 
  // Get the number of odes
  const unsigned n_odes = odes.nodes();
 
  // Temporary vector to store the K_i evaluations proper of
  // Runge-Kutta methods
  std::vector<double> K1(n_odes);
  std::vector<double> K2(n_odes);
  std::vector<double> K3(n_odes);
  std::vector<double> K4(n_odes);
 
  std::vector<double> y_temp(n_odes);
 
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t" using the current values of "y"
  odes.evaluate(t, y[k], K1);
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "y+(h/2)K1"
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i] = y[k][i]+(h/2.0)*K1[i];
   }
  odes.evaluate(t+(h/2.0), y_temp, K2);
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "y+(h/2)K2"
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i] = y[k][i]+(h/2.0)*K2[i];
   }
  odes.evaluate(t+(h/2.0), y_temp, K3);
  // -------------------------------------------------------------------- 
  // Evaluate the ODE at time "t+h" and with "y+hK3"
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i] = y[k][i]+h*K3[i];
   }
  odes.evaluate(t+(h/2.0), y_temp, K4);
 
  // Once the derivatives have been obtained compute the new "y" as the
  // weighted sum defined by the K_i
  for (unsigned i = 0; i < n_odes; i++)
   {
    y[k+1][i] = y[k][i] + (h/6.0)*(K1[i] + 2.0*K2[i] + 2.0*K3[i] + K4[i]);
   }
 
 }

}

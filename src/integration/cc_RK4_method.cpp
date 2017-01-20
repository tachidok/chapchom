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
  // Get the number of odes
  const unsigned n_odes = odes.nodes();
  // Check if each ode has the right number of history values to apply
  // Euler's method
  for (unsigned i = 0; i < n_odes; i++)
   {
    const unsigned n_history_values = y[i].size();
    if (n_history_values < N_history_values)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "The number of history values of ode [" << i
                    << "] is less than the required by Euler's methods" << std::endl;
      std::cout << "Required number of history values: "
                << N_history_values << std::endl;
      std::cout << "Number of history values in ode [" << i << "]: "
                << n_history_values << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
   }
    
  // Temporary vector to store the evaluation of the odes
  std::vector<double> dy(n_odes);
  
  // Evaluate the ODE at time "t" using the current values of "y"
  odes.evaluate(t, y, dy);
  
  // Index for history values
  const unsigned k = 0;
   
  // Temporary vector to store the K_i evaluations proper of
  // Runge-Kutta methods
  std::vector<double> K1(n_odes);
  std::vector<double> K2(n_odes);
  std::vector<double> K3(n_odes);
  std::vector<double> K4(n_odes);
  
  // Create a copy of the y vector
  std::vector<std::vector<double> > y_temp(y);
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t" using the current values of "y"
  odes.evaluate(t, y, K1);
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "y+(h/2)K1"
  const double h_half = h*0.5;
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i][k] = y[i][k]+h_half*K1[i];
   }
  odes.evaluate(t+h_half, y_temp, K2);
  
  // --------------------------------------------------------------------
  // Evaluate the ODE at time "t+(h/2)" and with "y+(h/2)K2"
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i][k] = y[i][k]+h_half*K2[i];
   }
  odes.evaluate(t+h_half, y_temp, K3);
  
  // -------------------------------------------------------------------- 
  // Evaluate the ODE at time "t+h" and with "y+hK3"
  for (unsigned i = 0; i < n_odes; i++)
   {
    y_temp[i][k] = y[i][k]+h*K3[i];
   }
  odes.evaluate(t+h, y_temp, K4);
  
  // Once the derivatives have been obtained compute the new "y" as
  // the weighted sum of the K's
  for (unsigned i = 0; i < n_odes; i++)
   {
    y[i][k+1] = y[i][k] + (h/6.0)*(K1[i] + 2.0*K2[i] + 2.0*K3[i] + K4[i]);
   }
 
 }

}

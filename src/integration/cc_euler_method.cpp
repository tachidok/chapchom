#include "cc_euler_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCEulerMethod::CCEulerMethod()
  : ACExplicitIntegrationMethod()
 {
 
  // Sets the number of history values
  N_history_values = 1;
 
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCEulerMethod::~CCEulerMethod()
 {
 
 }

 // ===================================================================
 // Applies Euler's method to the given odes from time "t_initial" to
 // time "t_final" using an h-step size
 // ===================================================================
 void CCEulerMethod::integrate(ACODEs &odes, const double h,
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
 // Applies Eulers method to the given odes from the current time "t"
 // to the time "t+h"
 // ===================================================================
 void CCEulerMethod::integrate_step(ACODEs &odes, const double h,
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
  
  // Once the derivatives have been obtained do one step of Euler's
  // method
  for (unsigned i = 0; i < n_odes; i++)
   {
    y[i][k+1] = y[i][k] + (h * dy[i]);
   }
  
 }

}

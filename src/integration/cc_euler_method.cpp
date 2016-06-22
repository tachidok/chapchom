#include "cc_euler_method.h"

// ===================================================================
// Constructor
// ===================================================================
CCEulerMethod::CCEulerMethod()
 : CAExplicitIntegrationMethod()
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
void CCEulerMethod::integrate(CAODEs &odes, const double h,
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
void CCEulerMethod::integrate_step(CAODEs &odes, const double h,
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
   error_message << "The number of history values is not enough to apply "
		 << "this integration method" << std::endl;
   std::cout << "Required number of history values: "
	     << N_history_values << std::endl;
   std::cout << "Number of history values in input vector 'y': "
	     << n_history_values << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Rename a variable
 const unsigned k = n_history_values-2;
 
 // Get the number of odes
 const unsigned n_odes = odes.nodes();
 // Temporary vector to store the evaluation of the odes
 std::vector<double> dy(n_odes);
 
 // Evaluate the ODE at time "t" using the current values of "y"
 odes.evaluate(t, y[k], dy);
 
 // Once the derivatives have been obtained do one step of Euler's
 // method
 for (unsigned i = 0; i < n_odes; i++)
  {
   y[k+1][i] = y[k][i] + (h * dy[i]);
  }
 
}


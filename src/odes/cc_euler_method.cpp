/** \file This file implements the methods of the CCEulerMethod class
 */
#include "cc_euler_method.h"

 
// ===================================================================
// Empty constructor
// ===================================================================
CCEulerMethod::CCEulerMethod()
 : CAExplicitMethod()
{
 
}
 
// ===================================================================
// Empty destructor
// ===================================================================
CCEulerMethod::~CCEulerMethod()
{
 
}

// ===================================================================
// Applies Eulers method to the given odes from time "t_initial" to
// time "t_final" using a step given by "h"
// ===================================================================
void CCEulerMethod::integrate(CAODEs &odes, const double h,
			      const double t_initial, const double t_final,
			      std::vector<double> &y)
{
 // Current time
 double t = t_initial;
 // Rename a variable
 double t_step = h;
 
 // Loop from "t_initial" to "t_final" with steps of "t_step"
 while (t <= t_final)
  {
   // Do one Euler's step
   integrate_step(odes, t_step, t, y);
   t+=t_step;
  }
 
}

// ===================================================================
// Applies Eulers method to the given odes from the current time "t"
// to the time "t+h"
// ===================================================================
void CCEulerMethod::integrate_step(CAODEs &odes, const double h,
				   const double t,
				   std::vector<double> &y)
{
 // Get the number of odes
 const unsigned n_odes = odes.nodes();
 // Temporary vector to store the evaluation of the odes
 std::vector<double> dy(n_odes);
 
 // Evaluate the ODE at the current time "t", all of them before doing
 // the updating of the "y's"
 //for (unsigned i = 0; i < n_odes; i++)

// TODO: tachidok, we need to implement this other way such that we
// can evaluate all of the equations even though we call integrate
// step
  {
   //odes.evaluate(i, t, y, dy);
   odes.evaluate(t, y, dy);
  }
 
 // Once the derivatives have been evaluated do one step of Euler's
 // method
 for (unsigned i = 0; i < n_odes; i++)
  {
   y[i] = y[i] + (h * dy[i]);
  }
 
}


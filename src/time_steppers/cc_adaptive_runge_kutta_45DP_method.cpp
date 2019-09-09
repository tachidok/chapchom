#include "cc_adaptive_runge_kutta_45DP_method.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 CCAdaptiveRK45DPMethod::CCAdaptiveRK45DPMethod()
  : ACAdaptiveTimeStepper()
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
 // from "t" to the time "t+h". The values of u at time t+h will be
 // stored at index k (default k = 0).
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
  CCData<Real> K5(n_odes);
  CCData<Real> K6(n_odes);
  CCData<Real> K7(n_odes);
  
  // Create a copy of the u vector
  CCData<Real> u_copy(u);
  
  // Counter for iterations
  unsigned n_iterations = 0;
  // Sum up the error
  Real local_error = 0.0;
  
  // --------------------------------------------------------------------
  // Runge-Kutta 4(5) Dormand-Prince method
  // --------------------------------------------------------------------
  // K1 = y(t, u)
  // K2 = y(t + \frac{1}{5}h, u + h(\frac{1}{5}K1))
  // K3 = y(t + \frac{3}{10}h, u + h(\frac{3}{40}K1 + \frac{9}{40}K2))
  // K4 = y(t + \frac{4}{5}h, u + h(\frac{44}{45}K1 - \frac{56}{15}K2 + \frac{32}{9}K3))
  // K5 = y(t + \frac{8}{9}h, u + h(\frac{19372}{6561}K1 - \frac{25360}{2187}K2 + \frac{64448}{6561}K3 - \frac{212}{729}K4))
  // K6 = y(t + h, u + h(\frac{9017}{3168}K1 - \frac{355}{33}K2 + \frac{46732}{5247}K3 + \frac{49}{176}K4 - \frac{5103}{18656}K5))
  // K7 = y(t + h, u + h(\frac{35}{384}K1 + \frac{500}{1113}K3 + \frac{125}{192}K4 - \frac{2187}{6784}K5 + \frac{11}{84}K6))
  
  // \hat{u}(t+h) = u(t) + (\frac{35}{384} K1 + \frac{500}{1113} K3 + \frac{125}{192} K4 - \frac{2187}{6784} K5 + \frac{11}{84} K6)
  // \tilde{u}(t+h) = u(t) + (\frac{5179}{57600} K1 + \frac{7571}{16695} K3 + \frac{393}{640} K4 - \frac{92097}{339200} K5 + \frac{187}{2100} K6 + \frac{1}{40} K7)
  
  // error = \hat{u}(t+h) - \tilde{u}(t+h) = h(\frac{71}{57600} K1 - \frac{71}{16695} K3 + \frac{71}{1920} K4 - \frac{17253}{339200} K5 + \frac{22}{525} K6 - \frac{1}{40} K7)
  
  // -------------------------------------------------------------------- 
  // Butcher tableau  
  // --------------------------------------------------------------------
  // 0             |
  // \frac{1}{5}   | \frac{1}{5}
  // \frac{3}{10}  | \frac{3}{40}        \frac{9}{40}
  // \frac{4}{5}   | \frac{44}{45}      -\frac{56}{15}       \frac{32}{9}
  // \frac{8}{9}   | \frac{19372}{6561} -\frac{25360}{2187}  \frac{64448}{6561}   -\frac{212}{729}
  // 1             | \frac{9017}{3168}  -\frac{355}{33}      \frac{46732}{5247}    \frac{49}{176}      -\frac{5103}{18656}
  // 1             | \frac{35}{384}      0                   \frac{500}{1113}      \frac{125}{192}     -\frac{2187}{6784}     \frac{11}{84}
  // --------------------------------------------------------------
  //               | \frac{35}{384}      0                   \frac{500}{1113}      \frac{125}{192}     -\frac{2187}{6784}     \frac{11}{84}      0
  //               | \frac{5179}{57600}  0                   \frac{7571}{16695}    \frac{393}{640}     -\frac{92097}{339200}  \frac{187}{2100}   \frac{1}{40}
  
  // Break loop if step size bounds have been reached
  bool break_loop = false;
  // Perform at least one computation
  do
   {
    // If new step size has been computed then take it as the initial
    // step size
    Real hh = h;
    if (this->Next_auto_step_size_computed)
     {
      hh = this->Next_auto_step_size;
     }
    else // First time to compute a time step (check user given step size)
     {
      // Check step size bounds
      if (hh > this->Maximum_step_size)
       {
        hh = this->Maximum_step_size;
       }
      else if (hh < this->Minimum_step_size)
       {
        hh = this->Minimum_step_size;
       }
     }
    
    this->Taken_auto_step_size = hh;
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t" using the current values of "u"
    // K1
    odes.evaluate_derivatives(t, u, K1, k);
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+(hh/5)" and with "u+(hh/5)K1"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+(hh*(0.2*K1(i)));
     }
    // K2
    odes.evaluate_derivatives(t+(0.2*hh), u_copy, K2, k);
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+(3hh/10)" and with "u+(3hh/40)K1 + 9hh/40"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+hh*((3.0/40.0)*K1(i)+(9.0/40.0)*K2(i));
     }
    // K3
    odes.evaluate_derivatives(t+((3.0/10.0)*hh), u_copy, K3, k);
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+(4hh/5)" and with "u+(44/45)K1 - (56/15)K2 + (32/9)K3"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+hh*((44.0/45.0)*K1(i)-(56.0/15.0)*K2(i)+(32.0/9.0)*K3(i));
     }
    // K4
    odes.evaluate_derivatives(t+((4.0/5.0)*hh), u_copy, K4);
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+(8hh/9)" and with "u+(19372hh/6561)K1 - (25360hh/2187)K2 + (64448hh/6561)K3 - (212hh/729)K4"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+hh*((19372.0/6561.0)*K1(i)-(25360.0/2187.0)*K2(i)+(64448.0/6561.0)*K3(i)-(212.0/729.0)*K4(i));
     }
    // K5
    odes.evaluate_derivatives(t+((4.0/5.0)*hh), u_copy, K5);
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+hh" and with "u+(9017hh/3168)K1 - (355hh/33)K2 + (46732hh/5247)K3 + (49hh/176)K4 - (5103hh/18656)K5"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+hh*((9017.0/3168.0)*K1(i)-(355.0/33.0)*K2(i)+(46732.0/5247.0)*K3(i)+(49.0/176.0)*K4(i)-(5103.0/18656.0)*K5(i));
     }
    // K6
    odes.evaluate_derivatives(t+hh, u_copy, K6);
    
    // --------------------------------------------------------------------
    // Evaluate the ODE at time "t+hh" and with "u+(35hh/384)K1 + (500hh/1113)K3 + (125hh/192)K4 - (2187hh/6784)K5 + (11hh/84)K6"
    for (unsigned i = 0; i < n_odes; i++)
     {
      u_copy(i,k) = u(i,k)+hh*((35.0/384.0)*K1(i)+(500.0/1113.0)*K3(i)+(125.0/192.0)*K4(i)-(2187.0/6784.0)*K5(i)+(11.0/84.0)*K6(i));
     }
    // K7
    odes.evaluate_derivatives(t+hh, u_copy, K7);
    
    // A storage for the error
    CCData<Real> error(n_odes);
    // Reset the error
    local_error = 0.0;
    for (unsigned i = 0; i < n_odes; i++)
     {
      error(i) = hh*((71.0/57600.0)*K1(i) - (71.0/16695.0)*K3(i) + (71.0/1920.0)*K4(i) - (17253.0/339200.0)*K5(i) + (22.0/525.0)*K6(i) - (1.0/40.0)*K7(i));
      local_error+=error(i); 
     }
    
    // Compute the new step size based on the established strategy
    hh = New_time_step_strategy_pt->new_step_size(local_error, hh);
    
    //Real new_h = safety_coefficient * h * (local_error/Maximum_tolerance, goodPower);
    
    // Check step size bounds and store it for the next iteration
    if (hh > this->Maximum_step_size)
     {
      hh = this->Maximum_step_size;
      break_loop = true;
      if (Output_messages)
       {
        chapchom_output << "Runge-Kutta 4(5) Dormand-Prince MAXIMUM STEP SIZE reached ["<<this->Maximum_step_size<<"]\n"
                        << "If you consider you require a larger step size you can\n"
                        << "set your own by calling the method\n\n"
                        << "set_maximum_step_size()\n"
                        << std::endl;
       }
     }
    else if (hh < this->Minimum_step_size)
     {
      hh = this->Minimum_step_size;
      break_loop = true;
      if (Output_messages)
       {
        chapchom_output << "Runge-Kutta 4(5) Dormand-Prince MINIMUM STEP SIZE reached ["<<this->Minimum_step_size<<"]\n"
                        << "If you consider you require an smaller step size you can\n"
                        << "set your own by calling the method\n\n"
                        << "set_minimum_step_size()\n"
                        << std::endl;
       }
     }
    
    this->Next_auto_step_size = hh;
    // Automatically computed step size
    this->Next_auto_step_size_computed = true;
    
    // Increase the number of iterations
    n_iterations++;
    
    if (n_iterations >= Maximum_iterations)
     {
      if (Output_messages)
       {
        chapchom_output << "Runge-Kutta 4(5) Dormand-Prince MAXIMUM NUMBER OF ITERATIONS reached ["<<this->Maximum_iterations<<"]\n"
                        << "If you consider you require more iterations you can\n"
                        << "set your own by calling the method\n\n"
                        << "set_maximum_interations()\n"
                        << std::endl;
       }
     }
    
   }while(!(this->Minimum_tolerance <= local_error && local_error <= this->Maximum_tolerance) &&
          n_iterations < this->Maximum_iterations &&
          !break_loop);
  
  // Shift values to the right to provide storage for the new values
  u.shift_history_values();
  
  // Once the derivatives have been obtained compute the new "u" as
  // the weighted sum of the K's
  Real hh = this->taken_auto_step_size();
  for (unsigned i = 0; i < n_odes; i++)
    {
     u(i,k) = u(i,k+1) + hh*((35.0/384.0)*K1(i)+(500.0/1113.0)*K3(i)+(125.0/192.0)*K4(i)-(2187.0/6784.0)*K5(i)+(11.0/84.0)*K6(i));
    }
  
 }
 
}

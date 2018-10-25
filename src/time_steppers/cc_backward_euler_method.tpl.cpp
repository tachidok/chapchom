#include "cc_backward_euler_method.tpl.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::CCBackwardEulerMethod()
  : ACTimeStepper()
 {  
  // Sets the number of history values
  N_history_values = 1;
  
  //Newtons_method.set_newton_solver_tolerance(1.0e-3);
  //Newtons_method.set_maximum_newton_iterations(100);
  
  // Disable output for Newton's method
  Newtons_method.disable_output_messages();
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::~CCBackwardEulerMethod()
 {
  
 }
 
 // ===================================================================
 // Applies Backward Euler method to the given odes from the current
 // time "t" to the time "t+h"
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::time_step(ACODEs &odes, const Real h,
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
                  << "the required by Backward Euler's method" << std::endl
                  << "Required number of history values: "
                  << N_history_values << std::endl
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // -----------------------------------------------------------------
  // Compute initial guess
  // -----------------------------------------------------------------
  // Temporary storage for Newton's method
  CCData<Real> u_guess(u);
  
  // Compute the initial guess for Newton's method
  Time_stepper_initial_guess.time_step(odes, h, t, u_guess); 
  
  // Create a vector with the initial guess from the second row (1)
  // since values have not been shifted
  VEC_TYPE u_0(u_guess.history_values_row_pt(1), n_odes);
  
  // Pass the data required for Newton's method
  Newtons_method.set_ODEs(&odes);
  Newtons_method.set_U(&u);
  Newtons_method.set_U_new(&u_guess);
  Newtons_method.set_time_step(h);
  Newtons_method.set_current_time(t);
  
  // Solver using Newton's method
  Newtons_method.solve(u_0);
  
  // Index for history values
  const unsigned k = 0;
  
  // Copy solution into output vector
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k+1) = u_0(i);
   }
  
 }

}


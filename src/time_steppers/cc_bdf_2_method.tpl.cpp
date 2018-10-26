#include "cc_bdf_2_method.tpl.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBDF2Method<MAT_TYPE,VEC_TYPE>::CCBDF2Method()
  : ACTimeStepper(),
    Compute_u_plus_h(true)
 {
  // Sets the number of history values
  N_history_values = 2;
  
  //Newtons_method.set_newton_solver_tolerance(1.0e-3);
  
  // Disable output for Newton's method
  Newtons_method.disable_output_messages();
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBDF2Method<MAT_TYPE,VEC_TYPE>::~CCBDF2Method()
 {
  
 }
 
 // ===================================================================
 // Applies BDF2 method to the given odes from the current time "t" to
 // the time "t+h"
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCBDF2Method<MAT_TYPE,VEC_TYPE>::time_step(ACODEs &odes, const Real h,
                                                 const Real t,
                                                 CCData<Real> &u)
 {
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  // Check if the ode has the correct number of history values to
  // apply BDF2 method
  const unsigned n_history_values = u.n_history_values();
  if (n_history_values < N_history_values)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of history values is less than\n"
                  << "the required by BDF2 method" << std::endl
                  << "Required number of history values: "
                  << N_history_values << std::endl
                  << "Number of history values: "
                  << n_history_values << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }

  // -----------------------------------------------------------------
  // Compute the value of u_{i+h} if this is the very first time the
  // method is called and store the result in u_{i+h}
  if (Compute_u_plus_h)
   {
    // Compute the values for u(i,1) using the same time stepper used
    // to compute the initial guess for Newton's method
    Time_stepper_initial_guess.time_step(odes, h, t, u);
    
    // This should be performed only once
    Compute_u_plus_h = false;
   }
  
  // -----------------------------------------------------------------
  // Compute initial guess
  // -----------------------------------------------------------------
  // Temporary storage for Newton's method
  CCData<Real> u_guess(u);
  
  // Shift the values to compute the value of u_{i+2h} based on the
  // values of u_{i+h}
  u_guess.shift_history_values();
  
  // Compute the initial guess for Newton's method
  Time_stepper_initial_guess.time_step(odes, h, t+h, u_guess);
  
  // Create a vector with the initial guess from the second row (1)
  // since values have not been shifted
  VEC_TYPE u_0(u_guess.history_values_row_pt(1), n_odes);

  // -----------------------------------------------------------------
  // Apply Newton's method
  // -----------------------------------------------------------------
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
    u(i,k+2) = u_0(i);
   }
  
 }
 
}


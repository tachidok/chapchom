#include "cc_bdf_2_method.h"

namespace scicellxx
{
 
 // ===================================================================
 /// Constructor
 // ===================================================================
 CCBDF2Method::CCBDF2Method()
  : ACTimeStepper(),
    Compute_u_at_time_t_plus_h(true)
 {
  // Sets the number of history values
  N_history_values = 3;
  
  //Newtons_method.set_newton_absolute_solver_tolerance(1.0e-3);
  //Newtons_method.set_maximum_allowed_residual(1.0e-1);
  
  // Disable output for Newton's method and relative tolerance
  Newtons_method.disable_output_messages();
  Newtons_method.disable_newton_relative_solver_tolerance();
 }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCBDF2Method::~CCBDF2Method()
 {
  
 }
 
 // ===================================================================
 /// Applies BDF2 method to the given odes from the current time "t" to
 /// the time "t+h". The values of u at time t+h will be stored at
 /// index k (default k = 0).
 // ===================================================================
 void CCBDF2Method::time_step(ACODEs &odes, const Real h,
                              const Real t,
                              CCData &u,
                              const unsigned k)
 {
#ifdef SCICELLXX_PANIC_MODE
  // Check if the ode has the correct number of history values to
  // apply Backward-Euler's method
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
#endif // #ifdef SCICELLXX_PANIC_MODE
  
  // -----------------------------------------------------------------
  // Compute the value of u_{t+h} if this is the first time
  if (Compute_u_at_time_t_plus_h)
   {
    // Compute the values for u_{t+h} using the same time stepper to
    // compute the initial guess for Newton's method
    Time_stepper_initial_guess.time_step(odes, h, t, u, k);
    
    // This should be performed only once
    Compute_u_at_time_t_plus_h = false;
    
    // Return. The next time we will have the required values for BDF2
    // u_{t} and u_{t+h}
    return;
   }
  
  // -----------------------------------------------------------------
  // Compute initial guess
  // -----------------------------------------------------------------  
  // Compute the initial guess for Newton's method using the values of
  // u at time 't', the values of u at time 't+h' are automatically
  // shifted at index k
  Time_stepper_initial_guess.time_step(odes, h, t, u, k);
  
  // ---------------------------------------------------
  // Transform the initial guess into a vector
  // ---------------------------------------------------
  // Get the number of odes
  const unsigned n_odes = odes.n_odes();
  
  // Create a vector with the initial guess from the first row (0)
  // since the values have been shift
  ACVector<Real> *u_initial_guess_pt = this->Factory_matrices_and_vectors.create_vector();
  u_initial_guess_pt->set_vector(u.history_values_row_pt(0), n_odes);
  
  // It is not required to shift the values to the right to provide
  // storage for the new values since they were shift when computing
  // the initial guess
  
  // Pass the required data to Newton's method. The solution is stored
  // in u at index k, therefore the values of u at time 't' are stored
  // at index k+1
  Newtons_method.set_data_for_jacobian_and_residual(&odes, h, t, &u, k);
  
  // Solve using Newton's method, the solution is automatically copied
  // back at the u data structure
  Newtons_method.solve(u_initial_guess_pt);
  
 }
 
}


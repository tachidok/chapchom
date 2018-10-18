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
  
  // Create the Jacobian and residual strategy for Backward Euler used
  // for Newton's method
  Jacobian_and_residual_for_backward_euler_pt =
   new CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>();
  
  // Set Jacobian strategy for Newton's method
  Newtons_method.set_jacobian_and_residual_strategy(Jacobian_and_residual_for_backward_euler_pt);
  
  // Create the linear solver
#ifdef CHAPCHOM_USES_ARMADILLO
  Linear_solver_pt = new CCSolverArmadillo<Real>();
#else
  Linear_solver_pt = new CCLUSolverNumericalRecipes<Real>();
#endif
  
  // Set linear solver for Newton's method
  Newtons_method.set_linear_solver(Linear_solver_pt);
  
  // Create an instance of an explicit method to compute the initial
  // guess for Newton's method
  Time_stepper_initial_guess_pt = new CCEulerMethod();
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::~CCBackwardEulerMethod()
 {  
  delete Jacobian_and_residual_for_backward_euler_pt;
  Jacobian_and_residual_for_backward_euler_pt = 0;
  
  delete Linear_solver_pt;
  Linear_solver_pt = 0;

  delete Time_stepper_initial_guess_pt;
  Time_stepper_initial_guess_pt = NULL;
  
 }
 
 // ===================================================================
 // Applies Eulers method to the given odes from the current time "t"
 // to the time "t+h"
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
                  << "the required by Euler's method" << std::endl;
    std::cout << "Required number of history values: "
              << N_history_values << std::endl;
    std::cout << "Number of history values: "
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
  Time_stepper_initial_guess_pt->time_step(odes, h, t, u_guess); 
  
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


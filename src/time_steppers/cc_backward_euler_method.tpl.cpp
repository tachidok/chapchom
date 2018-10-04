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
  
  // Create the Jacobian strategy for F(Y) (if you have the analytical
  // Jacobian you can set it here)
  Jacobian_FY_pt = new CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>();
  
  // Set the Jacobian for F(Y) for Backward Euler
  Jacobian_and_residual_for_backward_euler_pt->set_jacobian_and_residual_strategy_for_FY(Jacobian_FY_pt);
  
  // Create Newton's method for time stepping
  Newtons_method_pt = new CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>();
  
  // Set Jacobian strategy
  Newtons_method_pt->
   set_jacobian_and_residual_strategy(Jacobian_and_residual_for_backward_euler_pt);
  
#ifdef CHAPCHOM_USES_ARMADILLO
  // Create the linear solver
  Linear_solver_pt = new CCSolverArmadillo<double>();
#else
   // Create the linear solver
  Linear_solver_pt = new CCLUSolverNumericalRecipes<double>();
#endif
  
  // Set linear solver
  Newtons_method_pt->set_linear_solver(Linear_solver_pt);
  
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::~CCBackwardEulerMethod()
 {
  // Deallocate memory
  delete Jacobian_FY_pt;
  Jacobian_FY_pt = 0;
  
  delete Jacobian_and_residual_for_backward_euler_pt;
  Jacobian_and_residual_for_backward_euler_pt = 0;
  
  delete Newtons_method_pt;
  Newtons_method_pt = 0;
  
  delete Linear_solver_pt;
  Linear_solver_pt = 0;
  
 }
 
 // ===================================================================
 // Applies Eulers method to the given odes from the current time "t"
 // to the time "t+h"
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCBackwardEulerMethod<MAT_TYPE,VEC_TYPE>::time_step(ACODEs &odes, const double h,
                                                          const double t,
                                                          CCData<double> &u)
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
  
  // Pass the data required to the jacobian strategies
  Jacobian_and_residual_for_backward_euler_pt->set_odes(&odes);
  Jacobian_and_residual_for_backward_euler_pt->set_U(u);
  Jacobian_and_residual_for_backward_euler_pt->set_time_step(h);
  Jacobian_and_residual_for_backward_euler_pt->set_current_time(t);

  // -----------------------------------------------------------------
  // Compute initial guess
  // -----------------------------------------------------------------
  // Create an instance of an explicit method to compute the initial
  // guess in for Newton's method
  CCEulerMethod euler_method;
  
  // Temporary storage for Newton's method
  CCData<double> u_guess(u);
  
  // Compute the initial guess for Newton's method
  euler_method.time_step(odes, h, t, u_guess);
  
  // Create a temporary vector to store the extracted history values
  double *extracted_column_initial_guess_pt = new double(n_odes);
  
  u_guess.extract_history_values(extracted_column_initial_guess_pt);
  
  // Create a vector with the initial guess
  VEC_TYPE du(extracted_column_initial_guess_pt, n_odes);
  
  // Set Newton's U iterate u_{t+1}
  Newtons_method_pt->solve(du);
  
  // Index for history values
  const unsigned k = 0;
  
  // Copy solution into output vector
  for (unsigned i = 0; i < n_odes; i++)
   {
    u(i,k+1) = u(i,k) + du(i);
   }
  
 }

}


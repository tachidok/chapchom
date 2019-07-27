// IN THIS FILE: Implementation of the concrete class CCNewtonMethod
// to solve a given problem by means of Newton's method

#include "cc_newtons_method.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::CCNewtonsMethod()
  : Newton_absolute_solver_tolerance(DEFAULT_NEWTON_ABSOLUTE_SOLVER_TOLERANCE),
    Newton_relative_solver_tolerance(DEFAULT_NEWTON_RELATIVE_SOLVER_TOLERANCE),
    Maximum_newton_iterations(DEFAULT_MAXIMUM_NEWTON_ITERATIONS),
    Maximum_allowed_residual(DEFAULT_MAXIMUM_ALLOWED_RESIDUAL),
    Initial_guess_has_been_set(false),
    Jacobian_and_residual_strategy_has_been_set(false),
    Linear_solver_has_been_set(false),
    Free_memory_for_linear_solver(false),
    Reuse_jacobian(false),
    Jacobian_and_residual_strategy_pt(NULL),
    Linear_solver_pt(NULL),
    X_pt(NULL),
    Output_messages(true)
 {
  // Performs default configuration
  set_default_configuration(); 
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethod()
 {
  // Performs clean up
  clean_up();
 }
 
 // ===================================================================
 // Set the Jacobian matrix
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::set_jacobian_and_residual_strategy(ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *jacobian_and_residual_strategy_pt)
 {
  // Set the Jacobian and residual computation strategy
  Jacobian_and_residual_strategy_pt = jacobian_and_residual_strategy_pt;
  
  // Indicate that the Jacobian and residual computation strategy has
  // been set
  Jacobian_and_residual_strategy_has_been_set = true;
 }
 
 // ===================================================================
 // Set the Linear solver
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 set_linear_solver(ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt)
 {
  // Free memory for previous linear solver
  clean_up();
  
  // Assign the new linear solver
  Linear_solver_pt = linear_solver_pt;
  
  // Make sure to indicate that the new linear solver is set
  Linear_solver_has_been_set = true;
  
  // An external new linear solver has been set, then we no longer
  // need to worry about freeing its allocated memory
  Free_memory_for_linear_solver = false;
 }
 
 // ===================================================================
 // Gets access to the Jacobian and residual computation strategy
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 jacobian_and_residual_strategy_pt()
 {
  if (Jacobian_and_residual_strategy_pt != NULL && Jacobian_and_residual_strategy_has_been_set)
   {
    return Jacobian_and_residual_strategy_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the strategy for Jacobian\n"
                  << "and residual computation."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 }
 
 // ===================================================================
 // Gets access to the linear solver
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACLinearSolver<MAT_TYPE, VEC_TYPE> *CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::linear_solver_pt()
 {
  if (Linear_solver_pt != NULL && Linear_solver_has_been_set)
   {
    return Linear_solver_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established a linear solver."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
 }

 // ===================================================================
 // Set the initial guess. You should override this method if you
 // require to copy the initial guess to some other data structures
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::set_initial_guess(VEC_TYPE &x)
 {
  // Create a pointer to the initial guess vector
  X_pt = &x;
  
  // Update flag to indicate initial guess has been set
  Initial_guess_has_been_set = true;
 }
 
 // ===================================================================
 // Gets access to the last stored solution vector
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 const VEC_TYPE *CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::x_pt()
 {
  if (X_pt != NULL)
   {
    return X_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "There are no stored solution available."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 // ===================================================================
 // Clean up, free allocated memory
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::clean_up()
 {
  // Check whether we should free the memory associated for the linear
  // solver
  if (Free_memory_for_linear_solver)
   {
    // Free memory
    delete Linear_solver_pt;
    Linear_solver_pt = 0;

    // Indicate there are not linear solver established
    Linear_solver_has_been_set = false;
    
    // Memory has been already free
    Free_memory_for_linear_solver = false;
    
   }
  
 }
 
 // ===================================================================
 // Sets default configuration
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::set_default_configuration()
 {
  // Cleans up
  clean_up();
  
  // Create the linear solver
#ifdef CHAPCHOM_USES_ARMADILLO
  Linear_solver_pt = new CCSolverArmadillo<Real>();
#else
  Linear_solver_pt = new CCLUSolverNumericalRecipes<Real>();
#endif
  
  // Set linear solver for Newton's method
  Linear_solver_has_been_set = true;
  
  // In charge of free the memory for linear solver
  Free_memory_for_linear_solver = true;
  
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem given by the
 // Jacobian and the residual computed by the estalished strategy.
 // The initial guess is already set by previously calling the
 // function set_initial_guess(). The final solution (if any) is
 // stored in the X_pt vector
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve()
 {
  // We need to check whether a Jacobian computation strategy has been
  // set
  if (Jacobian_and_residual_strategy_pt == NULL || !Jacobian_and_residual_strategy_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified a Jacobian compuitation strategy.\n"
                  << "Set it first by calling the method\n\n"
                  << "set_jacobian_computation_strategy()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
  
  // We need to check whether a linear solver has been set
  if (Linear_solver_pt == NULL || !Linear_solver_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified a Linear solver.\n"
                  << "Set it first by calling the method\n\n"
                  << "set_linear_solver()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // We need to check whether the initial guess has been set or not
  if (X_pt == NULL || !Initial_guess_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified an initial guess.\n"
                  << "Set it first by calling the method\n\n"
                  << "set_inital_guess()\n\n"
                  << "or call the newtons method with the initial\n"
                  << "guess as a parameter\n\n"
                  << "solve(x_0)"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // ----------------------------------------------------------------
  // Initial residual convergence check
  // ----------------------------------------------------------------
  actions_before_initial_convergence_check();
  
  // Compute the initial residual
  Jacobian_and_residual_strategy_pt->compute_residual();
  
  // The residual vector
  VEC_TYPE residual = Jacobian_and_residual_strategy_pt->residual();
  
  // Compute the norm of the residual
  const Real initial_residual_norm = residual.norm_inf();

  // Is output message enabled?
  if (Output_messages)
   {
    chapchom_output << "Initial residual norm: " << initial_residual_norm << std::endl;
   }
  
  // Check for convergence
  if (initial_residual_norm < Newton_absolute_solver_tolerance)
   {
    // Is output message enabled?
    if (Output_messages)
     {
      // Finish Newton iteration
      chapchom_output << "The initial residual is smaller than the newton's absolute residual tolerance\n"
                      << "Newton_absolute_solver_tolerance: " << Newton_absolute_solver_tolerance << "\n"
                      << "Initial residual: " << initial_residual_norm
                      << std::endl;
     }
    
   }
  
  // Flag to indicate that the Jacobian has been computed by the first
  // time in Newton's method
  bool jacobian_has_been_computed = false;
  
  // Keep count on the number of newton iterations
  unsigned n_newton_iterations = 0;
  
  // Store the residual of the current iteration
  Real current_residual_norm = initial_residual_norm;
  
  // Compute the relative tolerance
  Real relative_tolerance = initial_residual_norm * Newton_relative_solver_tolerance;
  
  // Compute the termination tolerance
  Real termination_tolerance = relative_tolerance + Newton_absolute_solver_tolerance;
  
  // ---------------------------------------------------------------
  // The solution vector
  // ---------------------------------------------------------------
  // Get the number of variables
  const unsigned n_dof = X_pt->n_values();
  // Create the vector to store the solution of the system of
  // equations during Newton's steps
  VEC_TYPE dx(n_dof);
  
  // Time Newton's method
  clock_t initial_clock_time_for_newtons_method = Timing::cpu_clock_time();
  
  // Newton iterations
  while(n_newton_iterations < Maximum_newton_iterations && current_residual_norm >= termination_tolerance)
   {
    // Increase the numbew of Newton iterations
    n_newton_iterations++;
     
    // Perform actions before Newton's step
    actions_before_newton_step();
     
    // ---------------------------------------------------------------------
    // Computation of the Jacobian
    // ---------------------------------------------------------------------
     
    // Time the computation of the Jacobian matrix
    clock_t initial_clock_time_for_jacobian = Timing::cpu_clock_time();
     
    if (!jacobian_has_been_computed)
     {
      // Compute the Jacobian
      Jacobian_and_residual_strategy_pt->compute_jacobian();
      jacobian_has_been_computed = true;
     }
    else
     {
      if (!Reuse_jacobian)
       {
        // Compute the Jacobian
        Jacobian_and_residual_strategy_pt->compute_jacobian();
       }
     }
     
    // Time the computation of the Jacobian matrix
    clock_t final_clock_time_for_jacobian = Timing::cpu_clock_time();
     
    const double total_cpu_clock_time_for_jacobian =
     Timing::diff_cpu_clock_time(initial_clock_time_for_jacobian,
                                 final_clock_time_for_jacobian);
    
    // Is output message enabled?
    if (Output_messages)
     {
      chapchom_output << "CPU time for Jacobian in Newton solve: ["
                      << total_cpu_clock_time_for_jacobian << "]" << std::endl;
     }
    
    // Get a pointer to the Jacobian
    MAT_TYPE Jacobian = Jacobian_and_residual_strategy_pt->jacobian();
    
    // ---------------------------------------------------------------------
    // Linear solver
    // ---------------------------------------------------------------------
    
    // Time the linear solver
    clock_t initial_clock_time_for_linear_solver = Timing::cpu_clock_time();
    
    // Solve the system of equations
    Linear_solver_pt->solve(Jacobian, residual, dx);
    
    // Time the linear solver
    clock_t final_clock_time_for_linear_solver = Timing::cpu_clock_time();
    
    const double total_cpu_clock_time_for_linear_solver =
     Timing::diff_cpu_clock_time(initial_clock_time_for_linear_solver,
                                 final_clock_time_for_linear_solver);
    
    // Is output message enabled?
    if (Output_messages)
     {
      chapchom_output << "CPU time for linear solver in Newton solve: ["
                      << total_cpu_clock_time_for_linear_solver << "]" << std::endl;
     }
    
    // Update initial guess
    for (unsigned i_dof = 0; i_dof < n_dof; i_dof++)
     {
      X_pt->value(i_dof)+=dx(i_dof);
     }
    
    // Perform actions after Newton's step
    actions_after_newton_step();
    
    // ----------------------------------------------------------------
    // Convergence check
    // ----------------------------------------------------------------
    // Compute the new residual
    Jacobian_and_residual_strategy_pt->compute_residual();
    
    // Get a pointer to the residual
    residual = Jacobian_and_residual_strategy_pt->residual();
    
    // Compute the norm of the residual
    current_residual_norm = residual.norm_inf();
    
    // Is output message enabled?
    if (Output_messages)
     {
      chapchom_output << "Newton iteration " << n_newton_iterations
                      << ": Residual norm (termination tolerance) " << current_residual_norm << " (" << termination_tolerance << ")"<< std::endl;
     }
    
    if (current_residual_norm > Maximum_allowed_residual)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Newton's method MAXIMUM ALLOWED RESIDUAL error ["<<Maximum_allowed_residual<<"]\n"
                    << "If you consider you require a larger allowed residual you can\n"
                    << "set your own by calling the method\n\n"
                    << "set_maximum_allowed_residual()\n"
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
    if (n_newton_iterations >= Maximum_newton_iterations)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Newton's method MAXIMUM NUMBER OF ITERATIONS reached ["<<Maximum_newton_iterations<<"]\n"
                    << "If you consider you require more iterations you can\n"
                    << "set your own by calling the method\n\n"
                    << "set_maximum_newton_interations()\n"
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
   } // while(n_newton_iterations < Maximum_newton_iterations && current_residual_norm >= termination_tolerance)
  
  // Time Newton's method
  clock_t final_clock_time_for_newtons_method = Timing::cpu_clock_time();
  
  const double total_cpu_clock_time_for_newtons_method =
   Timing::diff_cpu_clock_time(initial_clock_time_for_newtons_method,
                               final_clock_time_for_newtons_method);
  
  // Is output message enabled?
  if (Output_messages)
   {
    chapchom_output << "CPU time for Newton's method: ["
                    << total_cpu_clock_time_for_newtons_method << "]" << std::endl;
   }
  
  // Update flag to indicate initial guess has been used and Newton's
  // method has finished
  Initial_guess_has_been_set = false;
  
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem given by the Jacobian
 // and the residual computed by the estalished strategy. The initial
 // guess is set in the input/output x vector where the final solution
 // (if any) is returned
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve(VEC_TYPE &x)
 {
  // Set the initial guess and perform Newton's method
  set_initial_guess(x);
  
  // Newton's method
  solve();
  
 }
 
}


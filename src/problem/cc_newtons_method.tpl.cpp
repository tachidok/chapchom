// IN THIS FILE: Implementation of the concrete class CCNewtonMethod
// to solve a given problem by means of Newton's method

#include "cc_newtons_method.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::CCNewtonsMethod()
  :     Jacobian_and_residual_strategy_pt(NULL),
        Linear_solver_pt(NULL),
        Newton_solver_tolerance(DEFAULT_NEWTON_SOLVER_TOLERANCE),
        Maximum_newton_iterations(DEFAULT_MAXIMUM_NEWTON_ITERATIONS),
        Maximum_allowed_residual(DEFAULT_MAXIMUM_ALLOWED_RESIDUAL),
        Jacobian_and_residual_strategy_has_been_set(false),
        Linear_solver_has_been_set(false)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethod()
 {
  
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
  Linear_solver_pt = linear_solver_pt;
  
  Linear_solver_has_been_set = true;
 }

 // ===================================================================
 // Gets access to the Jacobian and residual computation strategy
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 const ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> *CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
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
 const ACLinearSolver<MAT_TYPE, VEC_TYPE> *CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::linear_solver_pt()
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
 // Set Newton's solver tolerance
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 set_newton_solver_tolerance(const double new_newton_solver_tolerance)
 {
  Newton_solver_tolerance = new_newton_solver_tolerance;
 }

 // ===================================================================
 // Set the Maximun number of Newton's iterations
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 set_maximum_newton_interations(const unsigned new_maximum_newton_iterations)
 {
  Maximum_newton_iterations = new_maximum_newton_iterations;
 }
 
 // ===================================================================
 // Set the Maximum allowed residual
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::
 set_maximum_allowed_residual(const double new_maximum_allowed_residual)
 {
  Maximum_allowed_residual = new_maximum_allowed_residual;
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem given by the
 // Jacobian and the residual computed by the estalished strategy.
 // The initial guess is set in the dx vector where the final
 // solution (if any) is returned
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve(VEC_TYPE &dx)
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
                  << "set_linear_solver()()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get access to the dx vector so that it can be used in other
  // method of this class
  Dx_pt = &dx;
  
  // ----------------------------------------------------------------
  // Initial residual convergence check
  // ----------------------------------------------------------------
  actions_before_initial_convergence_check();
  
  // Compute the initial residual
  Jacobian_and_residual_strategy_pt->compute_residual();
  
  // The residual vector
  VEC_TYPE residual = Jacobian_and_residual_strategy_pt->residual();
  
  // Compute the norm of the residual
  const double initial_residual_norm = residual.max();
  
  chapchom_output << "Initial residual norm: " << initial_residual_norm << std::endl;
  
  // Check for convergence
  if (initial_residual_norm < Newton_solver_tolerance)
   {
    // Finish Newton iteration
    chapchom_output << "The initial residual is smaller than the newton's residual tolerance\n"
                    << "Newton_solver_tolerance: " << Newton_solver_tolerance << "\n"
                    << "Initial residual: " << initial_residual_norm << "\n"
                    << std::endl; 
   }
  
  // Flag to indicate that the Jacobian has been computed by the first
  // time in Newton's method
  bool jacobian_has_been_computed = false;
  
  // Keep count on the number of newton iterations
  unsigned n_newton_iterations = 0;
  
  // Store the residual of the current iteration
  double current_residual_norm = initial_residual_norm;
  
  // Time Newton's method
  clock_t initial_clock_time_for_newtons_method = Timing::cpu_clock_time();
  
  // Newton iterations
  while(n_newton_iterations < Maximum_newton_iterations && current_residual_norm >= Newton_solver_tolerance)
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
     
    chapchom_output << "CPU time for Jacobian in Newton solve: ["
                    << total_cpu_clock_time_for_jacobian << "]" << std::endl; 
     
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
     
    chapchom_output << "CPU time for linear solver in Newton solve: ["
                    << total_cpu_clock_time_for_linear_solver << "]" << std::endl;
    
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
    current_residual_norm = residual.max();
    
    chapchom_output << "Newton iteration " << n_newton_iterations
                    << ": Residual norm " << current_residual_norm << std::endl;
    
    if (current_residual_norm > Maximum_allowed_residual)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Newton's method MAXIMUM ALLOWED RESIDUAL error\n"
                    << "If you consider you require more iterations you can\n"
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
      error_message << "Newton's method MAXIMUM NUMBER OF ITERATIONS reached\n"
                    << "If you consider you require more iterations you can\n"
                    << "set your own by calling the method\n\n"
                    << "set_maximum_newton_interations()\n"
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
      
   } // while(n_newton_iterations < Maximum_newton_iterations && current_residual_norm >= Newton_solver_tolerance)
  
  
  // Time Newton's method
  clock_t final_clock_time_for_newtons_method = Timing::cpu_clock_time();
  
  const double total_cpu_clock_time_for_newtons_method =
   Timing::diff_cpu_clock_time(initial_clock_time_for_newtons_method,
                               final_clock_time_for_newtons_method);
  
  chapchom_output << "CPU time for Newton's method: ["
                  << total_cpu_clock_time_for_newtons_method << "]" << std::endl; 
  
 }
 
}


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
  : Newton_solver_tolerance(DEFAULT_NEWTON_SOLVER_TOLERANCE),
    Maximum_newton_interations(DEFAULT_MAXIMUM_NEWTON_ITERATIONS),
    Maximum_allowed_residual(DEFAULT_MAXIMUM_ALLOWED_RESIDUAL),
    Jacobian_matrix_has_been_set(false)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethod()
 {
  // Deallocate any dynamically allocated memory
  clean_up();
 }
 
 // ===================================================================
 // Set the Jacobian matrix
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::set_jacobian_matrix(const MAT_TYPE &jacobian)
 {
  // Clean up any other previous stored matrix
  clean_up();
  
  // Set the matrix
  Jacobian = jacobian;

  // Indicate that the Jacobian matrix has been set
  Jacobian_matrix_has_been_set = true;
 }
 
 // ===================================================================
 // Clean up for any dynamically stored data
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::clean_up()
 {
  // Check whether the Jacobian matrix has been set
  if (Jacobian_matrix_has_been_set)
   {
    // Delete the content of the Jacobian matrix
    Jacobian.free_memory_for_matrix();
    
    // Indicate that the Jacobian has not been setf
    Jacobian_matrix_has_been_set = false;
   }
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem given by the
 // Jacobian and the rhs. The initial guess is set in the dx vector
 // where the final solution (if any) is returned
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve(const MAT_TYPE &jacobian,
                                                 const VEC_TYPE &rhs,
                                                 VEC_TYPE &dx)
 {
  // Set the jacobian matrix and call the solve version when the
  // Jacobian has been already set
  this->set_jacobian_matrix(jacobian);
  // Call the solve method
  this->solve(rhs, dx);
 }
 
 // ===================================================================
 // Applies Newton's method to solve the problem given by the
 // already stored Jacobian and the rhs. The initial guess is set in
 // the dx vector where the final solution (if any) is returned
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::solve(const VEC_TYPE &rhs,
                                                 VEC_TYPE &dx)
 {
  // We need to check whether the Jacobian matrix has been set
  if (!this->Jacobian_matrix_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not specified the Jacobian matrix.\n"
                  << "Set it first by calling the set_jacobian() method\n"
                  << "or use the solve() method where you can specify the\n"
                  << "Jacobian matrix" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
  
  // We need to pass an strategy to compute the Jacobian matrix and
  // the residuals because they need to be updated every single newton
  // step
  
  // Compute the initial residual
  
  // Check for convergence
  
  // Solve the system of equations

  // Compute the new residuals
  
  // Check for convergence
  
 }


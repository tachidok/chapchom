// IN THIS FILE: Implementation of the concrete class
// CCNewtonMethodForBackwardEuler

#include "cc_newtons_method_for_backward_euler.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::CCNewtonsMethodForBackwardEuler()
  : CCNewtonsMethod<MAT_TYPE, VEC_TYPE>(),
  ODEs_pt(NULL),
  ODEs_has_been_set(false),
  U_pt(NULL),
  U_has_been_set(false),
  Current_time_has_been_set(false),
  Time_step_has_been_set(false),
  U_next_pt(NULL)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethodForBackwardEuler()
 {
  delete U_next_pt;
  U_next_pt = 0;
 }
 
 // ===================================================================
 // Set the initial guess, we copy the initial guess to the 'U_next'
 // structure, we could do this as well in the
 // actions_before_initial_convergence_check() method
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::
 set_initial_guess(VEC_TYPE &x)
 {
  // Create U next
  U_next_pt = new CCData<Real>(x.n_values());
  // Set values for U next
  const unsigned long n_data = U_next_pt->n_values();
  for (unsigned long i = 0; i < n_data; i++)
   {
    U_next_pt->value(i)=x(i);
   }
  
  // Call parent class method
  CCNewtonsMethod<MAT_TYPE, VEC_TYPE>::set_initial_guess(x);
  
 }
 
 // ===================================================================
 // Performs actions before initial convergence check
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::actions_before_initial_convergence_check()
 {
  jacobian_and_residual_for_backward_euler_pt()->set_ODEs(ODEs_pt);
  jacobian_and_residual_for_backward_euler_pt()->set_U(U_pt);
  jacobian_and_residual_for_backward_euler_pt()->set_U_next(U_next_pt);
  jacobian_and_residual_for_backward_euler_pt()->set_current_time(Current_time);
  jacobian_and_residual_for_backward_euler_pt()->set_time_step(Time_step);
 }
 
 // ===================================================================
 // Performs actions before Newton's method step
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::actions_before_newton_step()
 {
  
 }
 
 // ===================================================================
 // Performs actions after Newton's method step
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::actions_after_newton_step()
 {
  // Update U next
  const unsigned long n_data = U_next_pt->n_values();
  for (unsigned long i = 0; i < n_data; i++)
   {
    U_next_pt->value(i)=this->x_pt()->value(i);
    printf("U_next_pt: %f\n", U_next_pt->value(i));
   }
  
 }
 
 // ===================================================================
 // Dynamic cast to get access to the strategy for Jacobian and
 // Residual computation for Backward Euler
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE> *CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::jacobian_and_residual_for_backward_euler_pt()
 {
  CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE> *jacobian_and_residual_cast_pt = 
   dynamic_cast<CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>* >(this->jacobian_and_residual_strategy_pt());
  if (jacobian_and_residual_cast_pt!=0)
   {
    return jacobian_and_residual_cast_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dynamic cast for\n"
                  << "CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>\n"
                  << "could not be performed."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 }
 
 // ===================================================================
 // Set the ODEs
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_ODEs(ACODEs *odes_pt)
 {
  // Set the odes
  ODEs_pt = odes_pt;
  
  // Indicate that the ODEs have been set
  ODEs_has_been_set = true;
  
 }
 
 // ===================================================================
 // Set the U vector/matrix with the values of the function at the
 // current time
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_U(CCData<Real> *u_pt)
 {
  // Set the storage of the data
  U_pt = u_pt;
  
  // Indicate that the U vector has been set
  U_has_been_set = true;
  
 }
 
 // ===================================================================
 // Sets the current time
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_current_time(const Real t)
 {
  // Set the constant time
  Current_time = t;
  
  // Indicate that the current time has been set
  Current_time_has_been_set = true; 
 }
  
 // ===================================================================
 // Sets the time step
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_time_step(const Real h)
 {
  // Set the time step 
  Time_step = h;

  // Indicate that the time step has been set
  Time_step_has_been_set = true;
  
 }
 
}


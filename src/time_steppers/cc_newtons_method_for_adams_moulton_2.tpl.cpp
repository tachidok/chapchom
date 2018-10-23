// IN THIS FILE: Implementation of the concrete class
// CCNewtonMethodForAdamsMoulton2

#include "cc_newtons_method_for_adams_moulton_2.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::CCNewtonsMethodForAdamsMoulton2()
  : CCNewtonsMethod<MAT_TYPE, VEC_TYPE>(),
  ODEs_pt(NULL),
  ODEs_has_been_set(false),
  U_pt(NULL),
  U_has_been_set(false),
  U_new_pt(NULL),
  U_new_has_been_set(false),
  Current_time_has_been_set(false),
  Time_step_has_been_set(false)
 {
  // Set the Jacobian and residual strategy for Newton's method (used
  // for parent class)
  this->set_jacobian_and_residual_strategy(&Jacobian_and_residual_for_adams_moulton_2);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethodForAdamsMoulton2()
 {
  
 }
 
 // ===================================================================
 // Performs actions before initial convergence check
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::actions_before_initial_convergence_check()
 {
  Jacobian_and_residual_for_adams_moulton_2.set_ODEs(ODEs_pt);
  Jacobian_and_residual_for_adams_moulton_2.set_U(U_pt);
  Jacobian_and_residual_for_adams_moulton_2.set_U_new(U_new_pt);
  Jacobian_and_residual_for_adams_moulton_2.set_current_time(Current_time);
  Jacobian_and_residual_for_adams_moulton_2.set_time_step(Time_step);
  // Enables the evaluation of the odes with the U_pt values ONLY once
  // per Newton's method completion
  Jacobian_and_residual_for_adams_moulton_2.enable_odes_evaluation_with_u_values();
 }
 
 // ===================================================================
 // Performs actions before Newton's method step
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::actions_before_newton_step()
 {
  
 }
 
 // ===================================================================
 // Performs actions after Newton's method step
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::actions_after_newton_step()
 {
  // Update U next
  const unsigned long n_data = U_new_pt->n_values();
  for (unsigned long i = 0; i < n_data; i++)
   {
    U_new_pt->value(i)=this->x_pt()->value(i);
    printf("U_new_pt: %f\n", U_new_pt->value(i));
   }
  
 }
 
 // ===================================================================
 // Set the ODEs
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_ODEs(ACODEs *odes_pt)
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
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_U(CCData<Real> *u_pt)
 {
  // Set the storage of the data
  U_pt = u_pt;
  
  // Indicate that the U vector has been set
  U_has_been_set = true;
  
 }

 // ===================================================================
 // Set the U new vector/matrix storage for the new values of the
 // function after Newton's iteration
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_U_new(CCData<Real> *u_new_pt)
 {
  // Set the storage of the data
  U_new_pt = u_new_pt;
  
  // Indicate that the U new vector has been set
  U_new_has_been_set = true;
  
 }
 
 // ===================================================================
 // Sets the current time
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_current_time(const Real t)
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
 void CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_time_step(const Real h)
 {
  // Set the time step 
  Time_step = h;

  // Indicate that the time step has been set
  Time_step_has_been_set = true;
  
 }
 
}


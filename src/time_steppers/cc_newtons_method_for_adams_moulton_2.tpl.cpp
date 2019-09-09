// IN THIS FILE: Implementation of the concrete class
// CCNewtonMethodForAdamsMoulton2

#include "cc_newtons_method_for_adams_moulton_2.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::CCNewtonsMethodForAdamsMoulton2()
  : ACNewtonsMethodForImplicitTimeStepper<MAT_TYPE, VEC_TYPE>()
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
  // Get the odes
  ACODEs *odes_pt = this->odes_pt();
  // Get the time step
  const Real h = this->time_step();
  // Get the current time
  const Real t = this->current_time();
  // Get the u values
  CCData<Real> *u_pt = this->u_pt();
  // Get the index of the history values at time 't+h'
  const unsigned k = this->history_index();
  // Set the data for the computation of the jacobian and the residual
  Jacobian_and_residual_for_adams_moulton_2.set_data_for_jacobian_and_residual(odes_pt, h, t, u_pt, k); 
  // Enables the evaluation of the odes with the u_pt values ONLY once
  // per Newton's method completion
  Jacobian_and_residual_for_adams_moulton_2.enable_evaluation_of_odes_with_u_old_values();
 }
 
}


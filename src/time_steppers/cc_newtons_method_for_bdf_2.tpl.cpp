// IN THIS FILE: Implementation of the concrete class
// CCNewtonMethodForBDF2

#include "cc_newtons_method_for_bdf_2.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForBDF2<MAT_TYPE, VEC_TYPE>::CCNewtonsMethodForBDF2()
  : ACNewtonsMethodForImplicitTimeStepper<MAT_TYPE, VEC_TYPE>()
 {
  // Set the Jacobian and residual strategy for Newton's method (used
  // for parent class)
  this->set_jacobian_and_residual_strategy(&Jacobian_and_residual_for_bdf_2);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCNewtonsMethodForBDF2<MAT_TYPE, VEC_TYPE>::~CCNewtonsMethodForBDF2()
 {
  
 }
 
 // ===================================================================
 // Performs actions before initial convergence check
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCNewtonsMethodForBDF2<MAT_TYPE, VEC_TYPE>::actions_before_initial_convergence_check()
 {
  // Get the odes
  ACODEs *odes_pt = this->odes_pt();
  // Get the time step
  const Real h = this->time_step();
  // Get the current time
  const Real t = this->current_time();
  // Get the u values
  CCData *u_pt = this->u_pt();
  // Get the index of the history values at time 't+h'
  const unsigned k = this->history_index();
  // Set the data for the computation of the jacobian and the residual
  Jacobian_and_residual_for_bdf_2.set_data_for_jacobian_and_residual(odes_pt, h, t, u_pt, k);
 }
 
}


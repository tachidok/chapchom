/// IN THIS FILE: Implementation of the concrete class
/// CCNewtonMethodForAdamsMoulton2

#include "cc_newtons_method_for_adams_moulton_2.h"

namespace chapchom
{

 // ===================================================================
 /// Constructor
 // ===================================================================
 CCNewtonsMethodForAdamsMoulton2::CCNewtonsMethodForAdamsMoulton2()
  : ACNewtonsMethodForImplicitTimeStepper()
 {
  // Set the Jacobian and residual strategy for Newton's method (used
  // for parent class)
  this->set_jacobian_and_residual_strategy(&Jacobian_and_residual_for_adams_moulton_2);
 }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCNewtonsMethodForAdamsMoulton2::~CCNewtonsMethodForAdamsMoulton2()
 {
  
 }
 
 // ===================================================================
 /// Performs actions before initial convergence check
 // ===================================================================
 void CCNewtonsMethodForAdamsMoulton2::actions_before_initial_convergence_check()
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
  Jacobian_and_residual_for_adams_moulton_2.set_data_for_jacobian_and_residual(odes_pt, h, t, u_pt, k); 
  // Enables the evaluation of the odes with the u_pt values ONLY once
  // per Newton's method completion
  Jacobian_and_residual_for_adams_moulton_2.enable_evaluation_of_odes_with_u_old_values();
 }
 
}


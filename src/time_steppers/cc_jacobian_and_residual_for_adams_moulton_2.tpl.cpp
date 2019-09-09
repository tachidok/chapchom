#include "cc_jacobian_and_residual_for_adams_moulton_2.tpl.h"

namespace chapchom
{
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::CCJacobianAndResidualForAdamsMoulton2()
  : ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE, VEC_TYPE>(),
  DUDT_old(NULL),
  Evaluate_odes_with_u_old_values(false)
 {
  // Assign the default strategy (the Finite Differences strategy) for
  // computation of the Jacobian of the ODEs
  this->set_strategy_for_odes_jacobian(&Jacobian_by_FD_strategy);
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::~CCJacobianAndResidualForAdamsMoulton2()
 {
  
 }
 
 // ===================================================================
 // In charge of computing the Jacobian
 // (virtual function implementation)
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::compute_jacobian()
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
  
  // Check whether the data for the computation of the jacobian has
  // been set
  if (!this->data_for_jacobian_and_residual_has_been_set() || odes_pt == NULL || u_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the data required for\n"
                  << "the computation of the Jacobian\n"
                  << "You need to call the method\n"
                  << "set_data_for_jacobian_and_residual()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // -------------------------------------------
  // Compute the Jacobian of F(Y) at time t+h
  // -------------------------------------------

  // Get a pointer to the strategy to compute the Jacobian of the ODEs
  ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE, VEC_TYPE> *jacobian_strategy_odes_pt =
   this->jacobian_FY_strategy_pt();
  
  // Set the data for the computation of the jacobian and the residual
  jacobian_strategy_odes_pt->set_data_for_jacobian_and_residual(odes_pt, h, t, u_pt, k);
  
  // Compute Jacobian
  jacobian_strategy_odes_pt->compute_jacobian(); 
  
  // Store the Jacobian for FY, used in the computation of the
  // backward Euler Jacobian $J = I - (h * Jacobian_{FY})$
  MAT_TYPE Jacobian_FY = jacobian_strategy_odes_pt->jacobian();
  
  // Get the number of ODEs
  const unsigned n_dof = odes_pt->n_odes();
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian.allocate_memory(n_dof, n_dof);
  
  // Half time step
  const Real h_half = h * 0.5;
  
  // Compute the approximated Jacobian (I - h * Jacobian_FY(i, j))
  for (unsigned i = 0; i < n_dof; i++)
   {
    for (unsigned j = 0; j < n_dof; j++)
     {
      if (i == j)
       {
        this->Jacobian(i, j) = 1.0 - (h_half * Jacobian_FY(i, j));
       }
      else
       {
        this->Jacobian(i, j) = 0.0 - (h_half * Jacobian_FY(i, j));
       }
     }
   }
  
 }
 
 // ===================================================================
 // In charge of computing the residual
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::compute_residual()
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
  
  // Check whether the data for the computation of the jacobian has
  // been set
  if (!this->data_for_jacobian_and_residual_has_been_set() || odes_pt == NULL || u_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the data required for\n"
                  << "the computation of the Jacobian\n"
                  << "You need to call the method\n"
                  << "set_data_for_jacobian_and_residual()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   } 
  
  // Get the number of ODEs
  const unsigned n_dof = odes_pt->n_odes();
  
  // Is this the first time we called this method?
  if (Evaluate_odes_with_u_old_values)
   {
    // Free memory if there is something in there
    if (DUDT_old!= NULL)
     {
      delete DUDT_old;
      DUDT_old = NULL;
     }
    
    // Temporary vector to store the evaluation of the odes with u
    // values at time 't' (constant values)
    DUDT_old = new CCData<Real>(n_dof);
    
    // Evaluate the ODEs with the values of u at time "t". Constant
    // during Newton's iteration
    odes_pt->evaluate_derivatives(t, (*u_pt), (*DUDT_old), k+1);
    
    // Avoid evaluation of the same function during following Newton's
    // iterations
    Evaluate_odes_with_u_old_values = false;
    
   }
  
  // Check whether we have previously evaluated the derivative with
  // the values of u at time 't'
  if (DUDT_old==NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not evaluated the odes with the values of u at time 't'\n"
                  << "These values are required to compute the residual\n"
                  << "Call the method\n"
                  << "enable_evaluation_of_odes_with_old_u_values()\n"
                  << "ONLY before the FIRST computation of the residual\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Temporary vector to store the evaluation of the odes with the
  // values of u at time 't+h' (current Newton's iteration)
  CCData<Real> dudt(n_dof);
  
  // Evaluate the ODE at time "t+h"
  odes_pt->evaluate_derivatives(t+h, (*u_pt), dudt, k);
  
  // Allocate memory for the Residual (delete previous data)
  this->Residual.allocate_memory(n_dof);
  
  // Half time step
  const Real h_half = h * 0.5;

  // F(Y) = -(u_{t+h} - u_{t} - \frac{1}{2} (f(t+h, u_{t+h}) + f(t, u_{t})) )
  for (unsigned i = 0; i < n_dof; i++)
   {
    this->Residual(i) =
     -(u_pt->value(i,k) - u_pt->value(i,k+1) - (h_half * (dudt(i) + DUDT_old->value(i))));
   }
  
 }
 
}


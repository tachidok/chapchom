#include "cc_jacobian_by_fd_and_residual_from_odes.h"

namespace chapchom
{
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCJacobianByFDAndResidualFromODEs::CCJacobianByFDAndResidualFromODEs()
  : ACJacobianAndResidualForImplicitTimeStepper()
 {
  
 }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCJacobianByFDAndResidualFromODEs::~CCJacobianByFDAndResidualFromODEs()
 {
 
 }
 
 // ===================================================================
 /// In charge of computing the Jacobian using Finite Differences
 /// (virtual function implementation)
 // ===================================================================
 void CCJacobianByFDAndResidualFromODEs::compute_jacobian()
 {
  // Get a pointer to the ODEs
  ACODEs *odes_pt = this->odes_pt();
  
  // Get a pointer to the u values
  CCData *u_pt = this->u_pt();
  
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
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian_pt->allocate_memory(n_dof, n_dof);
  
  // Get the current time
  const Real t = this->current_time();
  
  // Get the time step
  const Real h = this->time_step();
  
  // Get the index of history values of the u vector at time 't+h'
  // that should be used to compute the values of the Jacobian
  const unsigned k = this->history_index();
  
  // Store the evaluation of the odes
  CCData dudt(n_dof);
  
  // Evaluate the ODEs using the history values of u at time t+h'
  // indicated in the index k
  odes_pt->evaluate_derivatives(t+h, (*u_pt), dudt, k);
  
  // Compute the approximated Jacobian
  for (unsigned i = 0; i < n_dof; i++)
   {
    // Create a copy of the U values and add an slight perturbation in
    // the i-th DOF and histroy value k, then evaluate all the
    // equations (this will helps us to approximate the column i of
    // the Jacobian)
    CCData u_plus((*u_pt));
    const Real delta_u = 1.0e-8;
    // ... the perturbation
    u_plus(i,k)+=delta_u;
    
    // Evaluate the ODEs with the slighted perturbed data
    CCData dudt_plus(n_dof);
    // Evaluate the ODEs using the history values indicated in the
    // index K
    odes_pt->evaluate_derivatives(t+h, u_plus, dudt_plus, k);
    // Compute the values for the Jacobian matrix, add entries for the
    // current i-column only (all functions with an slight
    // perturbation in the i-th dof)
    for (unsigned j = 0; j < n_dof; j++)
     {
      // The indices are reversed because we are computing the
      // approximation to the i-th column of the Jacobian (all
      // equations -index j- with a perturbation in the i-th dof)
      (*this->Jacobian_pt)(j, i) = (dudt_plus(j) - dudt(j)) / delta_u;
     }
   }
  
 }
 
 // ===================================================================
 /// In charge of computing the residual
 // ===================================================================
 void CCJacobianByFDAndResidualFromODEs::compute_residual()
 {
  
 } 
 
}

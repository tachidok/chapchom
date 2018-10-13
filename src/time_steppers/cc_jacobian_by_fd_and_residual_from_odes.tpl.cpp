#include "cc_jacobian_by_fd_and_residual_from_odes.tpl.h"

namespace chapchom
{
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::CCJacobianByFDAndResidualFromODEs()
  : ACJacobianAndResidual<MAT_TYPE, VEC_TYPE>(),
  ODEs_pt(NULL),
  ODEs_has_been_set(false),
  U_pt(NULL),
  U_has_been_set(false),
  Current_time_has_been_set(false)
 {
  
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::~CCJacobianByFDAndResidualFromODEs()
 {
 
 }
 
 // ===================================================================
 // In charge of computing the Jacobian using Finite Differences
 // (virtual function implementation)
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::compute_jacobian()
 {
  // Check whether the ODEs have been set
  if (!ODEs_has_been_set || ODEs_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the ODEs used to compute\n"
                  << "the Jacobian matrix.\n"
                  << "You need to call the method set_ODEs()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
     // Check whether the U values have been set
  if (!U_has_been_set || U_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U function values\n"
                  << "used to compute the Jacobian matrix.\n"
                  << "You need to call the method set_U()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the constant time has been set
  if (!Current_time_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the current time\n"
                  << "used to compute the Jacobian matrix.\n"
                  << "You need to call the method set_current_time()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = ODEs_pt->n_odes();
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian.allocate_memory(n_dof, n_dof);
  
  // Store the evaluation of the ODEs with the current U's values
  CCData<Real> dudt(n_dof);
  
  // Evaluate the ODEs
  ODEs_pt->evaluate(Current_time, (*U_pt), dudt);
  
  // Compute the approximated Jacobian
  for (unsigned i = 0; i < n_dof; i++)
   {
    // Create a copy of the U values and add an slight perturbation in
    // the current DOF (indicated by the index i) and evaluate all the
    // equations (this will helps us to approximate the column i of
    // the Jacobian)
    CCData<Real> U_plus((*U_pt));
    const Real delta_u = 1.0e-8;
    // ... the perturbation
    U_plus(i)+=delta_u;
    
    // Evaluate the ODEs with the slighted perturbed data
    CCData<Real> dudt_plus(n_dof);
    // Evaluate the ODEs
    ODEs_pt->evaluate(Current_time, U_plus, dudt_plus);
    // Compute the values for the Jacobian matrix, add entries for the
    // current i-column only (all functions with an slight
    // perturbation in the i-th dof)
    for (unsigned j = 0; j < n_dof; j++)
     {
      // The indices are reversed because we are computing the
      // approximation to the i-th column of the Jacobian (all
      // equations -index j- with a perturbation in the i-th dof)
      this->Jacobian(j, i) = (dudt_plus(j) - dudt(j)) / delta_u;
     }
   }
  
 }
 
 // ===================================================================
 // In charge of computing the residual
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::compute_residual()
 {
  
 }
 
 // ===================================================================
 // Set the ODEs
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::set_ODEs(ACODEs *odes_pt)
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
 void CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::set_U(CCData<Real> *u_pt)
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
 void CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE>::set_current_time(const Real t)
 {  
  // Set the constant time
  Current_time = t;
  
  // Indicate that the current time has been set
  Current_time_has_been_set = true; 
 }
 
}

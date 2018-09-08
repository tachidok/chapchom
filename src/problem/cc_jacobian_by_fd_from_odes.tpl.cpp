#include "cc_jacobian_by_fd_from_odes.tpl.h"

namespace chapchom
{
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE>
 CCJacobianByFDFromODEs<MAT_TYPE>::CCJacobianByFDFromODEs()
  : ODEs_has_been_set(false),
    U_has_been_set(false)
 {
 
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class MAT_TYPE>
 CCJacobianByFDFromODEs<MAT_TYPE>::~CCJacobianByFDFromODEs()
 {
 
 }
 
 // ===================================================================
 // In charge of computing the Jacobian using Finite Differences
 // (virtual function implementation)
 // ===================================================================
 template<class MAT_TYPE>
 void CCJacobianByFDFromODEs<MAT_TYPE>::compute_jacobian()
 {
  // Check whether the constant time has been set
  if (!Constant_time_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established a constant time to compute\n"
                  << "the Jacobian matrix\n."
                  << "You need to call the method\n\n"
                  << "compute_jacobian(const double t)\n\n"
                  << "which automatically calls this method to compute the\n"
                  << "Jacobian matrix." << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = ODEs.n_odes();
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian.allocate_memory(n_dof, n_dof);
  
  // Store the evaluation of the ODEs with the current U's values
  CCData<double> dudt(n_dof);

  // Evaluate the ODEs
  ODEs.evaluate(Constant_time, U, dudt);
  
  // Compute the approximated Jacobian
  for (unsigned i = 0; i < n_dof; i++)
   {
    // Create a copy of the U values and add an slight perturbation in
    // the current DOF (indicated by the index i) and evaluate all the
    // equations (this will helps us to approximate the column i of
    // the Jacobian)
    CCData<double> U_plus(U);
    const double delta_u = 1.0e-8;
    // ... the perturbation
    U_plus(i)+=delta_u;
    
    // Evaluate the ODEs with the slighted perturbed data
    CCData<double> dudt_plus(n_dof);
    // Evaluate the ODEs
    ODEs.evaluate(Constant_time, U_plus, dudt_plus);
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
  
  // Change the status of the constant time flag to avoid calling by
  // error again
  Constant_time_has_been_set = false;
  
 }
 
 // ===================================================================
 // In charge of computing the Jacobian using Finite Differences
 // ===================================================================
 template<class MAT_TYPE>
 void CCJacobianByFDFromODEs<MAT_TYPE>::compute_jacobian(const double t)
 {
  // Check whether the ODEs have been set
  if (!ODEs_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the ODEs that should be\n"
                  << "used to compute the Jacobian matrix\n."
                  << "Call the method set_ODEs() to specify the set of ODEs\n"
                  << "used to compute the Jacobian matrix." << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the U values have been set
  if (!U_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the values of the function U\n"
                  << "that are used to help computing the Jacobian matrix\n."
                  << "Call the method set_U() to specify the values of the U\n"
                  << "function used to compute the Jacobian matrix." << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Set the constant time
  Constant_time = t;

  // Indicate that the constant time has been set
  Constant_time_has_been_set = true;

  // ----------------------------------------------------
  // Perform the computation of the Jacobian
  // ----------------------------------------------------
  compute_jacobian();
  
  // Unset constant time
  Constant_time = 0.0;

  // Disable calling of the method that computes the Jacobian
  Constant_time_has_been_set = false;
  
 }
 
 // ===================================================================
 // Set the ODEs to compute the Jacobian
 // ===================================================================
 template<class MAT_TYPE>
 void CCJacobianByFDFromODEs<MAT_TYPE>::set_ODEs(const ACODEs &odes)
 {
  // Set a pointer to the odes
  ODEs = odes;

  // Indicate that the ODEs have been set
  ODEs_has_been_set = true;
  
 }
 
 // ===================================================================
 // Set the U vector/matrix with the values of the function at the
 // current time
 // ===================================================================
 template<class MAT_TYPE>
 void CCJacobianByFDFromODEs<MAT_TYPE>::set_U(const CCData<double> &u)
 {
  // Set a pointer to the storage of the data 
  U = u;
  
  // Indicate that the U vector has been set
  U_has_been_set = true;
  
 }

}

#include "cc_jacobian_and_residual_for_backward_euler.tpl.h"

namespace chapchom
{
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::CCJacobianAndResidualForBackwardEuler()
  : ODEs_has_been_set(false),
    U_has_been_set(false),
    U_next_has_been_set(false),
    Current_time_has_been_set(false),
    Time_step_has_been_set(false),
    Jacobian_for_FY_has_been_set(false)
 {
  
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::~CCJacobianAndResidualForBackwardEuler()
 {
  
 }
 
 // ===================================================================
 // In charge of computing the Jacobian
 // (virtual function implementation)
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::compute_jacobian()
 {
  // Check whether the ODEs have been set
  if (!ODEs_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the ODEs used to compute\n"
                  << "the Jacobian matrix\n."
                  << "You need to call the method set_ODEs()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the U values have been set
  if (!U_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U function values\n"
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_U()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the U_next values have been set
  if (!U_next_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U_next function values\n"
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_U_next()\n"
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
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_current_time()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the time step has been set
  if (!Time_step_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the time step to compute\n"
                  << "the residual vector and the Jacobian matrix\n."
                  << "You need to call the method set_time_step()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the Jacobian strategy for F(Y) has been set
  if (!Jacobian_for_FY_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established an strategy to compute the\n"
                  << "Jacobian matrix for F(Y)\n"
                  << "You need to call the method\n\n"
                  << "set_jacobian_and_residual_strategy_for_FY()\n\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = ODEs_pt->n_odes();
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian.allocate_memory(n_dof, n_dof);
  
  // Set the data required to compute the Jacobian of F(Y)
  Jacobian_FY_pt->set_odes(ODEs_pt);
  Jacobian_FY_pt->set_U(U_next);
  Jacobian_FY_pt->set_current_time(Current_time);
  
  // Store the Jacobian for FY, used in the computation of the
  // backward Euler Jacobian $J = I - (h * Jacobian_{FY})$
  MAT_TYPE Jacobian_FY = Jacobian_FY_pt->compute_jacobian();
  
  // Compute the approximated Jacobian (I - h * Jacobian_FY(i, j))
  for (unsigned i = 0; i < n_dof; i++)
   {
    for (unsigned j = 0; j < n_dof; j++)
     {
      if (i == j)
       {
        this->Jacobian(i, j) = 1.0 -  (Time_step * Jacobian_FY(i, j));
       }
      else
       {
        this->Jacobian(i, j) = 0.0 - (Time_step * Jacobian_FY(i, j));
       }
     }
   }
  
 }
 
 // ===================================================================
 // In charge of computing the residual
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::compute_residual()
 {
  // Check whether the ODEs have been set
  if (!ODEs_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the ODEs used to compute\n"
                  << "the Jacobian matrix\n."
                  << "You need to call the method set_ODEs()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the U values have been set
  if (!U_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U function values\n"
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_U()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the U_next values have been set
  if (!U_next_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U_next function values\n"
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_U_next()\n"
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
                  << "used to compute the Jacobian matrix\n."
                  << "You need to call the method set_current_time()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the time step has been set
  if (!Time_step_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the time step to compute\n"
                  << "the residual vector and the Jacobian matrix\n."
                  << "You need to call the method set_time_step()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the Jacobian strategy for F(Y) has been set
  if (!this->Jacobian_for_FY_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established an strategy to compute the\n"
                  << "residual vector\n"
                  << "You need to call the method\n\n"
                  << "set_jacobian_and_residual_strategy_for_FY()\n\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = ODEs_pt->n_odes();
  
  // Temporary vector to store the evaluation of the odes
  CCData<double> dudt(n_dof);
  
  // Evaluate the ODE at time "t" using the "u" values of the current
  // Newton's iteration
  ODEs_pt->evaluate(Current_time, U_next, dudt);
  
  for (unsigned i = 0; i < n_dof; i++)
   {
    this->Residual(i) =  U_next(i) - U(i) - (Time_step * dudt(i));
   }
  
 }
 
 // ===================================================================
 // Set the ODEs
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_ODEs(ACODEs *odes_pt)
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
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_U(CCData<double> &u)
 {
  // Set the storage of the data
  U = u;
  
  // Indicate that the U vector has been set
  U_has_been_set = true;
  
 }

 // ===================================================================
 // Set the U vector/matrix with the values of the function at the
 // current Newton's iteration
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_U_next(CCData<double> &u_next)
 {
  // Set the storage of the data
  U_next = u_next;
  
  // Indicate that the U_next vector has been set
  U_next_has_been_set = true;
  
 }
 
 // ===================================================================
 // Sets the current time
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_current_time(const double t)
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
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::set_time_step(const double h)
 {
  // Set the time step 
  Time_step = h;

  // Indicate that the time step has been set
  Time_step_has_been_set = true;
  
 }
 
 // ===================================================================
 // Set the strategy used to compute the Jacobian of FY and the residual
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE>::
 set_jacobian_and_residual_strategy_for_FY(ACJacobianAndResidual<MAT_TYPE, VEC_TYPE> *jacobian_FY_pt)
 {
  // Set a pointer to the Jacobian strategy for F(Y)
  Jacobian_FY_pt = jacobian_FY_pt;
  
  // Indicate that the jacobian strategy for F(Y) has been set
  Jacobian_for_FY_has_been_set = true;
 }
 
}


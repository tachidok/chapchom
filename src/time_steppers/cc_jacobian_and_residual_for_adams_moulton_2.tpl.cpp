#include "cc_jacobian_and_residual_for_adams_moulton_2.tpl.h"

namespace chapchom
{
 // ===================================================================
 // Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::CCJacobianAndResidualForAdamsMoulton2()
  : ACJacobianAndResidual<MAT_TYPE, VEC_TYPE>(),
  ODEs_pt(NULL),
  ODEs_has_been_set(false), 
  U_pt(NULL),
  U_has_been_set(false),
  U_new_pt(NULL),
  U_new_has_been_set(false),
  Current_time_has_been_set(false),
  Time_step_has_been_set(false),
  DUDT(NULL),
  Evaluate_ODEs_with_U_values(false)
 {
  
 }
 
 // ===================================================================
 // Destructor
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
  
  // Check whether the U_new values have been set
  if (!U_new_has_been_set || U_new_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U_new function values\n"
                  << "used to compute the Jacobian matrix.\n"
                  << "You need to call the method set_U_new()\n"
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
  
  // Check whether the time step has been set
  if (!Time_step_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the time step to compute\n"
                  << "the residual vector and the Jacobian matrix.\n"
                  << "You need to call the method set_time_step()\n"
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
  Jacobian_FY_strategy.set_ODEs(ODEs_pt);
  Jacobian_FY_strategy.set_U(U_new_pt);
  Jacobian_FY_strategy.set_current_time(Current_time+Time_step);
  
  // Compute Jacobian
  Jacobian_FY_strategy.compute_jacobian();
  
  // Store the Jacobian for FY, used in the computation of the
  // backward Euler Jacobian $J = I - (h * J_{FY})$
  MAT_TYPE Jacobian_FY = Jacobian_FY_strategy.jacobian();
  
  // Half time step
  const Real half_time_step = Time_step * 0.5;
  
  // Compute the approximated Jacobian (I - h * Jacobian_FY(i, j))
  for (unsigned i = 0; i < n_dof; i++)
   {
    for (unsigned j = 0; j < n_dof; j++)
     {
      if (i == j)
       {
        this->Jacobian(i, j) = 1.0 - (half_time_step * Jacobian_FY(i, j));
       }
      else
       {
        this->Jacobian(i, j) = 0.0 - (half_time_step * Jacobian_FY(i, j));
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
  
  // Check whether the U_new values have been set
  if (!U_new_has_been_set || U_new_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the U_new function values\n"
                  << "used to compute the Jacobian matrix.\n"
                  << "You need to call the method set_U_new()\n"
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
  
  // Check whether the time step has been set
  if (!Time_step_has_been_set)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the time step to compute\n"
                  << "the residual vector and the Jacobian matrix.\n"
                  << "You need to call the method set_time_step()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = ODEs_pt->n_odes();

  // Is this the first time we called this method with the U_pt
  // values, if that is the case then
  if (Evaluate_ODEs_with_U_values)
   {
    // Free memory if there is something in there
    if (DUDT!= NULL)
     {
      delete DUDT;
      DUDT = NULL;
     }
    
    // Temporary vector to store the evaluation of the odes with U_pt
    // (constant values)
    DUDT = new CCData<Real>(n_dof);
    
    // Evaluate the ODE at time "t" using the "u" values of U_pt,
    // constant during Newton's iteration
    ODEs_pt->evaluate(Current_time, (*U_pt), (*DUDT));

    // Avoid evaluation of the same function during following Newton's
    // iterations
    Evaluate_ODEs_with_U_values = false;
    
   }
  
  // Check whether we have previously evaluated the derivative with
  // U_pt values
  if (DUDT==NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not evaluated the odes with the values of U_pt\n"
                  << "These values are required to compute the residual\n"
                  << "Call the method\n"
                  << "enable_odes_evaluation_with_u_values()\n"
                  << "ONLY before the FIRST computation of the residual\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Temporary vector to store the evaluation of the odes with
  // U_new_pt (current Newton's iteration)
  CCData<Real> dudt_new(n_dof);
  
  // Evaluate the ODE at time "t" using the "u" values of the current
  // Newton's iteration
  ODEs_pt->evaluate(Current_time+Time_step, (*U_new_pt), dudt_new);
  
  // Allocate memory for the Residual (delete previous data)
  this->Residual.allocate_memory(n_dof);

  // Half time step
  const Real half_time_step = Time_step * 0.5;
  
  for (unsigned i = 0; i < n_dof; i++)
   {
    this->Residual(i) =
     -(U_new_pt->value(i) - U_pt->value(i) - (half_time_step * (dudt_new(i) + DUDT->value(i))));
   }
  
 }
 
 // ===================================================================
 // Set the ODEs
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_ODEs(ACODEs *odes_pt)
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
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_U(CCData<Real> *u_pt)
 {
  // Set the storage of the data
  U_pt = u_pt;
  
  // Indicate that the U vector has been set
  U_has_been_set = true;
  
 }

 // ===================================================================
 // Set the U vector/matrix with the values of the function at the
 // current Newton's iteration
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_U_new(CCData<Real> *u_new_pt)
 {
  // Set the storage of the data
  U_new_pt = u_new_pt;
  
  // Indicate that the U_new vector has been set
  U_new_has_been_set = true;
  
 }
 
 // ===================================================================
 // Sets the current time
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_current_time(const Real t)
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
 void CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE>::set_time_step(const Real h)
 {
  // Set the time step 
  Time_step = h;

  // Indicate that the time step has been set
  Time_step_has_been_set = true;
  
 }
 
}


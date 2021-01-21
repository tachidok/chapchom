#include "ac_jacobian_and_residual_for_implicit_time_stepper.h"

namespace scicellxx
{
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 ACJacobianAndResidualForImplicitTimeStepper::ACJacobianAndResidualForImplicitTimeStepper()
  : ACJacobianAndResidual(),
    ODEs_pt(NULL),
    U_pt(NULL),
    Data_for_jacobian_and_residual_has_been_set(false),
    Jacobian_FY_strategy_pt(NULL)
 {
  
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 ACJacobianAndResidualForImplicitTimeStepper::~ACJacobianAndResidualForImplicitTimeStepper()
 {
  // Free the pointer
  Jacobian_FY_strategy_pt = NULL;
 }
 
 // ===================================================================
 /// Set data for Jacobian and residual computation. The odes, the time
 /// step 'h', the current time 't', the values of 'u' and the index
 /// where the values of 'u' at time 't+h' will be stored
 // ===================================================================
 void ACJacobianAndResidualForImplicitTimeStepper::
 set_data_for_jacobian_and_residual(ACODEs *odes_pt, const Real h, const Real t,
                                    CCData *u_pt, const unsigned k)
 {
  // Set the odes
  ODEs_pt = odes_pt;
  
  // Set the time step 
  Time_step = h;
  
  // Set the constant time
  Current_time = t;
  
  // Set the storage of the data
  U_pt = u_pt;
  
  // Set the index of where the values of u at time 't+h' should be
  // stored
  History_index = k;
  
  // Change the flag indicating that the data for the computation of
  // the Jacobian and the residual has been set
  Data_for_jacobian_and_residual_has_been_set = true;
  
 }
 
 // ===================================================================
 /// Set the strategy to compute the ODE's Jacobian
 // ===================================================================
 void ACJacobianAndResidualForImplicitTimeStepper::
 set_strategy_for_odes_jacobian(ACJacobianAndResidualForImplicitTimeStepper *jacobian_strategy_for_odes_pt)
 {
  if (jacobian_strategy_for_odes_pt != NULL)
   {
    Jacobian_FY_strategy_pt = jacobian_strategy_for_odes_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The strategy for the computation of the Jacobian of the ODEs\n"
                  << "that you are setting is not valid (NULL)\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
 // =================================================================== 
 /// Get access to the strategy to compute the Jacobian of the ODEs
 // ===================================================================
 ACJacobianAndResidualForImplicitTimeStepper *ACJacobianAndResidualForImplicitTimeStepper::
 jacobian_FY_strategy_pt()
 {
  if (Jacobian_FY_strategy_pt != NULL)
   {
    return Jacobian_FY_strategy_pt;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The strategy for the computation of the Jacobian of the ODEs\n"
                  << "is not valid (NULL)\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
 }
 
}


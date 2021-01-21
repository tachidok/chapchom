#ifndef ACJACOBIANANDRESIDUALFORIMPLICITTIMESTEPPER_H
#define ACJACOBIANANDRESIDUALFORIMPLICITTIMESTEPPER_H

#include "../equations/ac_jacobian_and_residual.h"
#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

namespace scicellxx
{
 
 /// An abstract class to define the interfaces for the computation of
 /// the Jacobian and the resiudal vector for implicit time stepper
 /// methods
 class ACJacobianAndResidualForImplicitTimeStepper : virtual public ACJacobianAndResidual
 {
  
 public:
   
  /// Empty constructor
  ACJacobianAndResidualForImplicitTimeStepper();
  
  /// Destructor
  ~ACJacobianAndResidualForImplicitTimeStepper();
  
  /// In charge of computing the Jacobian
  virtual void compute_jacobian() = 0;
  
  /// In charge of computing the residual
  virtual void compute_residual() = 0;
  
  /// Set data for Jacobian and residual computation. The odes, the
  /// time step 'h', the current time 't', the values of 'u' and the
  /// index where the values of 'u' at time 't' are stored
  void set_data_for_jacobian_and_residual(ACODEs *odes_pt, const Real h, const Real t,
                                          CCData *u_pt, const unsigned k);
  
  /// Set the strategy to compute the ODE's Jacobian
  void set_strategy_for_odes_jacobian(ACJacobianAndResidualForImplicitTimeStepper *jacobian_strategy_for_odes_pt);
   
 protected:
  
  /// Get access to the odes pointer
  inline ACODEs* odes_pt() {return ODEs_pt;}
   
  /// Gets access to the time step
  inline Real time_step() const {return Time_step;}
   
  /// Gets access to the current time
  inline Real current_time() const {return Current_time;}
   
  /// Gets access to the u values
  inline CCData *u_pt() {return U_pt;}
   
  /// Get access to the history index
  inline unsigned history_index() {return History_index;}
   
  /// Checks whether the data to compute the Jacobian and the residual
  /// has been set
  inline bool data_for_jacobian_and_residual_has_been_set()
  {return Data_for_jacobian_and_residual_has_been_set;}
   
  /// Get access to the strategy to compute the Jacobian of the ODEs
  ACJacobianAndResidualForImplicitTimeStepper *jacobian_FY_strategy_pt();
   
 private:
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACJacobianAndResidualForImplicitTimeStepper(const ACJacobianAndResidualForImplicitTimeStepper &copy)
   {
    BrokenCopy::broken_copy("ACJacobianAndResidualForImplicitTimeStepper");
   }
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACJacobianAndResidualForImplicitTimeStepper &copy)
   {
    BrokenCopy::broken_assign("ACJacobianAndResidualForImplicitTimeStepper");
   }
   
  /// The ODEs
  ACODEs *ODEs_pt;
   
  /// The U values of the function at the current time
  CCData *U_pt;
   
  /// The current time
  Real Current_time;
   
  /// The current time step of the Time Stepper
  Real Time_step;
   
  /// The index of the values of u at time "Current_time"
  unsigned History_index;
   
  /// A flag to indicate whether the data for the Jacobian and
  /// residual computation has been set
  bool Data_for_jacobian_and_residual_has_been_set;
  
  /// A pointer to the strategy to compute the Jacobian of the ODEs
  ACJacobianAndResidualForImplicitTimeStepper *Jacobian_FY_strategy_pt;
  
 };
 
}

#endif // #ifndef ACJACOBIANANDRESIDUALFORIMPLICITTIMESTEPPER_H


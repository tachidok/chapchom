// IN THIS FILE: The definition of the concrete class
// CCNewtonsMethodForBackwardEuler to apply Newton's methods for
// Backward Euler method

// Check whether the class has been already defined
#ifndef CCNEWTONSMETHODFORBACKWARDEULER_TPL_H
#define CCNEWTONSMETHODFORBACKWARDEULER_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../problem/cc_newtons_method.h"
#include "cc_jacobian_and_residual_for_backward_euler.h"

namespace chapchom
{
 
 // A concrete class that implements Newton's method for time stepping
 // methods
 template<class MAT_TYPE, class VEC_TYPE>
  class CCNewtonsMethodForBackwardEuler : public virtual CCNewtonsMethod<MAT_TYPE, VEC_TYPE>
  {
  
 public:
  
  // Empty constructor
  CCNewtonsMethodForBackwardEuler();
  
  // Empty destructor
  ~CCNewtonsMethodForBackwardEuler();
  
  // Set the ODEs
  void set_ODEs(ACODEs *odes_pt);
   
  // Set the U vector/matrix with the values of the function at the
  // current time
  void set_U(CCData<Real> *u_pt);
  
  // Set the U new vector/matrix storage for the new values of the
  // function after Newton's iteration
  void set_U_new(CCData<Real> *u_new_pt);
  
  // Sets the current time
  void set_current_time(const Real t);
   
  // Sets the time step
  void set_time_step(const Real h);
  
  protected:
  
  // Performs actions before initial converngence check
  void actions_before_initial_convergence_check();
  
  // Performs actions before Newton's method step
  void actions_before_newton_step();
   
  // Performs actions after Newton's method step
  void actions_after_newton_step();
  
  // Dynamic cast to get access to the strategy for Jacobian and
  // Residual computation for Backward Euler
  CCJacobianAndResidualForBackwardEuler<MAT_TYPE, VEC_TYPE> *jacobian_and_residual_for_backward_euler_pt();
  
  // The ODEs
  ACODEs* ODEs_pt;
  
  // A flag to indicate whether the ODEs have been set or not
  bool ODEs_has_been_set;
  
  // The U values of the function at the current time
  CCData<Real> *U_pt;
   
  // A flag to indicate whether the U values have been set or not
  bool U_has_been_set;
  
  // Stores the U new values of the function after each Newton's iteration
  CCData<Real> *U_new_pt;
  
  // A flag to indicate whether the U new values have been set or not
  bool U_new_has_been_set;
  
  // The current time
  Real Current_time;
   
  // Flag to indicate whether the current time has been set
  bool Current_time_has_been_set;
   
  // The current time step of the Time Stepper
  Real Time_step;
   
  // Flag to indicate whether the time step has been set
  bool Time_step_has_been_set;
  
  private:
  
  // Copy constructor (we do not want this class to be copiable because
  // it contains dynamically allocated variables, A in this
  // case). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCNewtonsMethodForBackwardEuler(const CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE> &copy)
   {
    BrokenCopy::broken_copy("CCNewtonsMethodForBackwardEuler");
   }
   
  // Copy constructor (we do not want this class to be copiable because
  // it contains dynamically allocated variables, A in this
  // case). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCNewtonsMethodForBackwardEuler<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCNewtonsMethodForBackwardEuler");
    }
   
 };
 
}

#endif // #ifndef CCNEWTONSMETHODFORBACKWARDEULER_TPL_H


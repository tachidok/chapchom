#ifndef CCJACOBIANANDRESIDUALFORBACKWARDEULER_TPL_H
#define CCJACOBIANANDRESIDUALFORBACKWARDEULER_TPL_H

#include "../equations/ac_jacobian_and_residual.h"
#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

namespace chapchom
{
 
 // A concrete class to compute the Jacobian matrix and the residual
 // vector for Backward Euler used for Newton's method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCJacobianAndResidualForBackwardEuler : virtual public ACJacobianAndResidual<MAT_TYPE,VEC_TYPE>
  {
   
  public:
   
   // Constructor
   CCJacobianAndResidualForBackwardEuler();
   
   // Destructor
   ~CCJacobianAndResidualForBackwardEuler();
   
   // In charge of computing the Jacobian
   // (virtual function implementation)
   void compute_jacobian();
   
   // In charge of computing the residual
   void compute_residual();
   
   // Set the ODEs
   void set_ODEs(ACODEs *odes_pt);
   
   // Set the U vector/matrix with the values of the function at the
   // current time
   void set_U(CCData<double> &u);
   
   // Set the U vector/matrix with the values of the function at the
   // current Newton's iteration
   void set_U_next(CCData<double> &u_next);
   
   // Sets the current time
   void set_current_time(const double t);
   
   // Sets the time step
   void set_time_step(const double h);
   
   // Set the strategy used to compute the Jacobian of F(Y) and the
   // residual
   void set_jacobian_and_residual_strategy_for_FY(ACJacobianAndResidual<MAT_TYPE, VEC_TYPE> *jacobian_FY_pt);
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCJacobianAndResidualForBackwardEuler(const CCJacobianAndResidualForBackwardEuler<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCJacobianAndResidualForBackwardEuler");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCJacobianAndResidualForBackwardEuler<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCJacobianAndResidualForBackwardEuler");
    }

   // The ODEs
   ACODEs *ODEs_pt;
   
   // A flag to indicate whether the ODEs have been set or not
   bool ODEs_has_been_set;
   
   // The U values of the function at the current time
   CCData<double> U;
   
   // A flag to indicate whether the U values have been set or not
   bool U_has_been_set;
   
   // The U values of the function at the current Newton's iteration
   CCData<double> U_next;
   
   // A flag to indicate whether the U values for the current Newton's
   // iteration has been set or not
   bool U_next_has_been_set;
   
   // The current time
   double Current_time;
   
   // Flag to indicate whether the current time has been set
   bool Current_time_has_been_set;
   
   // The current time step of the Time Stepper
   double Time_step;
   
   // Flag to indicate whether the time step has been set
   bool Time_step_has_been_set;
   
   // A pointer for the strategy to compute the Jacobian
   // $\frac{\partial \mathbf{F}(\mathbf{Y})}{\partial \mathbf{Y}}$,
   // where $\mathbf{Y} = \mathbf{y}_{k+1}$.
   ACJacobianAndResidual<MAT_TYPE, VEC_TYPE> *Jacobian_FY_pt;
   
   // Flag to indicate that an strategy to compute the Jacobian of
   // F(Y) and the residual has been set
   bool Jacobian_for_FY_has_been_set;
   
  };
 
}

#endif // #ifndef CCJACOBIANANDRESIDUALFORBACKWARDEULER_TPL_H


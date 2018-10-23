#ifndef CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H
#define CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H

#include "../equations/ac_jacobian_and_residual.h"
#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

// One of the possible Jacobian strategies to compute FY
#include "cc_jacobian_by_fd_and_residual_from_odes.h"

namespace chapchom
{
 
 // A concrete class to compute the Jacobian matrix and the residual
 // vector for Adams-Moulton 2 or Trapezoidal Rule used for Newton's
 // method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCJacobianAndResidualForAdamsMoulton2 : virtual public ACJacobianAndResidual<MAT_TYPE,VEC_TYPE>
  {
   
  public:
   
   // Constructor
   CCJacobianAndResidualForAdamsMoulton2();
   
   // Destructor
   ~CCJacobianAndResidualForAdamsMoulton2();
   
   // In charge of computing the Jacobian
   // (virtual function implementation)
   void compute_jacobian();
   
   // In charge of computing the residual
   void compute_residual();
   
   // Set the ODEs
   void set_ODEs(ACODEs *odes_pt);
   
   // Set the U vector/matrix with the values of the function at the
   // current time
   void set_U(CCData<Real> *u_pt);
   
   // Set the U new vector/matrix with the values of the function at
   // the current Newton's iteration
   void set_U_new(CCData<Real> *u_new_pt);
   
   // Sets the current time
   void set_current_time(const Real t);
   
   // Sets the time step
   void set_time_step(const Real h);
   
   // Enables the evaluation of the odes using the U_pt values
   inline void enable_odes_evaluation_with_u_values() {Evaluate_ODEs_with_U_values=true;}
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCJacobianAndResidualForAdamsMoulton2(const CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCJacobianAndResidualForAdamsMoulton2");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCJacobianAndResidualForAdamsMoulton2");
    }

   // The ODEs
   ACODEs *ODEs_pt;
   
   // A flag to indicate whether the ODEs have been set or not
   bool ODEs_has_been_set;
   
   // The U values of the function at the current time
   CCData<Real> *U_pt;
   
   // A flag to indicate whether the U values have been set or not
   bool U_has_been_set;
   
   // The U values of the function at the current Newton's iteration
   CCData<Real> *U_new_pt;
   
   // A flag to indicate whether the U new values for the current
   // Newton's iteration has been set or not
   bool U_new_has_been_set;
   
   // The current time
   Real Current_time;
   
   // Flag to indicate whether the current time has been set
   bool Current_time_has_been_set;
   
   // The current time step of the Time Stepper
   Real Time_step;
   
   // Flag to indicate whether the time step has been set
   bool Time_step_has_been_set;
   
   // A strategy to compute the Jacobian $\frac{\partial
   // \mathbf{F}(\mathbf{Y})}{\partial \mathbf{Y}}$, where $\mathbf{Y}
   // = \mathbf{y}_{k+1}$.
   CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE> Jacobian_FY_strategy;
   
   // Temporary vector to store the evaluation of the odes with
   // U_pt, constant during Newton's iterations
   CCData<Real> *DUDT;
   
   // A flag to indicate whether to evaluate the odes with U_pt
   // values. These values are to keep constant during Newton's
   // iterations
   bool Evaluate_ODEs_with_U_values;
   
  };
 
}

#endif // #ifndef CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H


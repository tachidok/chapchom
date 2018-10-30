#ifndef CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H
#define CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H

#include "ac_jacobian_and_residual_for_implicit_time_stepper.h"

// One of the possible Jacobian strategies to compute FY
#include "cc_jacobian_by_fd_and_residual_from_odes.h"

namespace chapchom
{
 
 // A concrete class to compute the Jacobian matrix and the residual
 // vector for Adams-Moulton 2 or Trapezoidal Rule used for Newton's
 // method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCJacobianAndResidualForAdamsMoulton2 : virtual public ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE,VEC_TYPE>
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
   
   // Enables the evaluation of the odes using the values of u at time
   // 't'
   inline void enable_evaluation_of_odes_with_u_old_values() {Evaluate_odes_with_u_old_values=true;}
   
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
   
   // A strategy to compute the Jacobian $\frac{\partial
   // \mathbf{F}(\mathbf{Y})}{\partial \mathbf{Y}}$, where $\mathbf{Y}
   // = \mathbf{y}_{k+1}$.
   CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE> Jacobian_FY_strategy;
   
   // Temporary vector to store the evaluation of the odes with the
   // values of u at time 't'. These are kept constant during Newton's
   // iterations
   CCData<Real> *DUDT_old;
   
   // A flag to indicate whether to evaluate the odes with the values
   // of u at time 't'. These values are kept constant during Newton's
   // iterations
   bool Evaluate_odes_with_u_old_values;
   
  };
 
}

#endif // #ifndef CCJACOBIANANDRESIDUALFORADAMSMOULTON2_TPL_H


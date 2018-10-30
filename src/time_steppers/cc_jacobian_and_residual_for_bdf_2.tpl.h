#ifndef CCJACOBIANANDRESIDUALFORBDF2_TPL_H
#define CCJACOBIANANDRESIDUALFORBDF2_TPL_H

#include "ac_jacobian_and_residual_for_implicit_time_stepper.h"

// One of the possible Jacobian strategies to compute FY
#include "cc_jacobian_by_fd_and_residual_from_odes.h"

namespace chapchom
{
 
 // A concrete class to compute the Jacobian matrix and the residual
 // vector for BDF2 used for Newton's method
 template<class MAT_TYPE, class VEC_TYPE>
  class CCJacobianAndResidualForBDF2 : virtual public ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE,VEC_TYPE>
  {
   
  public:
   
   // Empty constructor
   CCJacobianAndResidualForBDF2();
   
   // Empty destructor
   ~CCJacobianAndResidualForBDF2();
   
   // In charge of computing the Jacobian
   // (virtual function implementation)
   void compute_jacobian();
   
   // In charge of computing the residual
   void compute_residual(); 
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCJacobianAndResidualForBDF2(const CCJacobianAndResidualForBDF2<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCJacobianAndResidualForBDF2");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCJacobianAndResidualForBDF2<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCJacobianAndResidualForBDF2");
    }
   
   // A strategy to compute the Jacobian $\frac{\partial
   // \mathbf{F}(\mathbf{Y})}{\partial \mathbf{Y}}$, where $\mathbf{Y}
   // = \mathbf{y}_{k+1}$.
   CCJacobianByFDAndResidualFromODEs<MAT_TYPE, VEC_TYPE> Jacobian_FY_strategy;
      
  };
 
}

#endif // #ifndef CCJACOBIANANDRESIDUALFORBDF2_TPL_H


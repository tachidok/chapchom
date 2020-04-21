#ifndef CCJACOBIANANDRESIDUALFORBACKWARDEULER_H
#define CCJACOBIANANDRESIDUALFORBACKWARDEULER_H

#include "ac_jacobian_and_residual_for_implicit_time_stepper.h"

// One of the possible Jacobian strategies to compute FY
#include "cc_jacobian_by_fd_and_residual_from_odes.h"

namespace chapchom
{
 
 /// A concrete class to compute the Jacobian matrix and the residual
 /// vector for Backward Euler used for Newton's method
 class CCJacobianAndResidualForBackwardEuler : virtual public ACJacobianAndResidualForImplicitTimeStepper
 {
   
 public:
  
  /// Constructor
  CCJacobianAndResidualForBackwardEuler();
  
  /// Empty destructor
  ~CCJacobianAndResidualForBackwardEuler();
  
  /// In charge of computing the Jacobian (virtual function
  /// implementation)
  void compute_jacobian();
   
  /// In charge of computing the residual
  void compute_residual();
   
 private:
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCJacobianAndResidualForBackwardEuler(const CCJacobianAndResidualForBackwardEuler &copy)
   {
    BrokenCopy::broken_copy("CCJacobianAndResidualForBackwardEuler");
   }
   
  /// Copy constructor (we do not want this class to be copiable because
  /// it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCJacobianAndResidualForBackwardEuler &copy)
   {
    BrokenCopy::broken_assign("CCJacobianAndResidualForBackwardEuler");
   }
  
  /// A strategy to compute the Jacobian $\frac{\partial
  /// \mathbf{F}(\mathbf{Y})}{\partial \mathbf{Y}}$, where $\mathbf{Y}
  /// = \mathbf{y}_{k+1}$.
  CCJacobianByFDAndResidualFromODEs Jacobian_by_FD_strategy;
   
 };
 
}

#endif // #ifndef CCJACOBIANANDRESIDUALFORBACKWARDEULER_H


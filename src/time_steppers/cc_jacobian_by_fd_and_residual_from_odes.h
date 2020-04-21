#ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_H
#define CCJACOBIANBYFDANDRESIDUALFROMODES_H

#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

#include "ac_jacobian_and_residual_for_implicit_time_stepper.h"

namespace chapchom
{

 /// A concrete class to compute the Jacobian matrix using Finite
 /// Differences from a set of ODES
 class CCJacobianByFDAndResidualFromODEs : virtual public ACJacobianAndResidualForImplicitTimeStepper
 {
  
 public:
  
  /// Empty constructor
  CCJacobianByFDAndResidualFromODEs();
   
  /// Empty destructor
  ~CCJacobianByFDAndResidualFromODEs();
   
  /// In charge of computing the Jacobian using Finite Differences
  /// (virtual function implementation)
  void compute_jacobian();
   
  /// In charge of computing the residual
  void compute_residual();
   
 private:
   
  /// Copy constructor (we do not want this class to be copiable
  /// because it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCJacobianByFDAndResidualFromODEs(const CCJacobianByFDAndResidualFromODEs &copy)
   {
    BrokenCopy::broken_copy("CCJacobianByFDAndResidualFromODEs");
   }
   
  /// Copy constructor (we do not want this class to be copiable
  /// because it contains dynamically allocated variables, A in this
  /// case). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCJacobianByFDAndResidualFromODEs &copy)
   {
    BrokenCopy::broken_assign("CCJacobianByFDAndResidualFromODEs");
   }
  
 };
 
}

#endif // #ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_H


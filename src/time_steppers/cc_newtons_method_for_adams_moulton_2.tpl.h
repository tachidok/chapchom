// IN THIS FILE: The definition of the concrete class
// CCNewtonsMethodForAdamsMoulton2 to apply Newton's methods for
// Adams-Moulton 2 or Trapezoidal Rule method

// Check whether the class has been already defined
#ifndef CCNEWTONSMETHODFORADAMSMOULTON2_TPL_H
#define CCNEWTONSMETHODFORADAMSMOULTON2_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "cc_jacobian_and_residual_for_adams_moulton_2.h"
#include "ac_newtons_method_for_implicit_time_stepper.h"

namespace chapchom
{
 
 // A concrete class that implements Newton's method for time stepping
 // methods
 template<class MAT_TYPE, class VEC_TYPE>
  class CCNewtonsMethodForAdamsMoulton2 : public virtual ACNewtonsMethodForImplicitTimeStepper<MAT_TYPE, VEC_TYPE>
  {
   
  public:
   
   // Constructor
   CCNewtonsMethodForAdamsMoulton2();
   
   // Empty destructor
   ~CCNewtonsMethodForAdamsMoulton2();
   
  protected:
  
   // Performs actions before initial converngence check
   void actions_before_initial_convergence_check();
   
  private:
  
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCNewtonsMethodForAdamsMoulton2(const CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCNewtonsMethodForAdamsMoulton2");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCNewtonsMethodForAdamsMoulton2<MAT_TYPE, VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCNewtonsMethodForAdamsMoulton2");
    }
   
   // The Jacobian and Residual computation strategy that implements
   // Adams-Moulton or Trapezoidal rule method
   CCJacobianAndResidualForAdamsMoulton2<MAT_TYPE, VEC_TYPE> Jacobian_and_residual_for_adams_moulton_2;
   
  };
 
}

#endif // #ifndef CCNEWTONSMETHODFORADAMSMOULTON2_TPL_H


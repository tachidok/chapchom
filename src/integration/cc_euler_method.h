#ifndef CCEULERMETHOD_H
#define CCEULERMETHOD_H

#include "ac_explicit_integration_method.h"

namespace chapchom
{

 /// @class CCEulerMethod cc_euler_method.h
 /// This class implements Euler's method to integrate ODE's
 class CCEulerMethod : public virtual ACExplicitIntegrationMethod
 {
 
 public:

  /// Constructor
  CCEulerMethod();
  
  /// Empty destructor
  virtual ~CCEulerMethod();
 
  /// Applies Eulers method to the given odes from time "t_initial" to
  /// time "t_final" using a step given by "h".
  void integrate(ACODEs &odes, const double h,
                 const double t_initial, const double t_final,
                 std::vector<std::vector<double> > &y);

  /// Applies Eulers method to the given odes from the current time "t"
  /// to the time "t+h".
  void integrate_step(ACODEs &odes, const double h, const double t,
                      std::vector<std::vector<double> > &y);
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCEulerMethod(const CCEulerMethod &copy)
   {
    BrokenCopy::broken_copy("CCEulerMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCEulerMethod &copy)
   {
    BrokenCopy::broken_assign("CCEulerMethod");
   }

 };

}
 
#endif // #ifndef CCEULERMETHOD_H

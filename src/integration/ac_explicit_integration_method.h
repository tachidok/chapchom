#ifndef ACEXPLICITINTEGRATIONMETHOD_H
#define ACEXPLICITINTEGRATIONMETHOD_H

#include "ac_integration_method.h"

namespace chapchom
{

 /// @class ACExplicitIntegrationMethod ac_explicit_integration_method.h
 /// This class implements the interfaces for explicit integration
 /// methods to solve ODE's
 class ACExplicitIntegrationMethod : public virtual ACIntegrationMethod
 {
 
 public:
 
  /// Empty constructor
  ACExplicitIntegrationMethod();
 
  /// Empty destructor
  virtual ~ACExplicitIntegrationMethod();
 
  /// Applies the explicit method to the given odes from time
  /// "t_initial" to time "t_final" using a step given by "h".
  virtual void integrate(ACODEs &odes, const double h,
                         const double t_initial, const double t_final,
                         std::vector<std::vector<double> > &y) = 0;
 
  /// Applies the explicit method to the given odes from the current
  /// time "t" to the time "t+h".
  virtual void integrate_step(ACODEs &odes, const double h,
                              const double t,
                              std::vector<std::vector<double> > &y) = 0;
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACExplicitIntegrationMethod(const ACExplicitIntegrationMethod &copy)
   {
    BrokenCopy::broken_copy("ACExplicitIntegrationMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACExplicitIntegrationMethod &copy)
   {
    BrokenCopy::broken_assign("ACExplicitIntegrationMethod");
   }
 
 };

}
 
#endif // #ifndef ACEXPLICITINTEGRATIONMETHOD_H

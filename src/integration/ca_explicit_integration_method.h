#ifndef CAEXPLICITINTEGRATIONMETHOD_H
#define CAEXPLICITINTEGRATIONMETHOD_H

#include "ca_integration_method.h"

/// @class CAExplicitIntegrationMethod ca_explicit_integration_method.h
/// This class implements the interfaces for explicit integration
/// methods to solve ODE's
class CAExplicitIntegrationMethod : public virtual CAIntegrationMethod
{
 
 public:
 
 /// Empty constructor
 CAExplicitIntegrationMethod();
 
 /// Empty destructor
 virtual ~CAExplicitIntegrationMethod();
 
 /// Applies the explicit method to the given odes from time
 /// "t_initial" to time "t_final" using a step given by "h".
 virtual void integrate(CAODEs &odes, const double h,
			const double t_initial, const double t_final,
			std::vector<std::vector<double> > &y) = 0;
 
 /// Applies the explicit method to the given odes from the current
 /// time "t" to the time "t+h".
 virtual void integrate_step(CAODEs &odes, const double h,
			     const double t,
			     std::vector<std::vector<double> > &y) = 0;
 
 protected:
 
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CAExplicitIntegrationMethod(const CAExplicitIntegrationMethod &copy)
  {
   BrokenCopy::broken_copy("CAExplicitIntegrationMethod");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CAExplicitIntegrationMethod &copy)
  {
   BrokenCopy::broken_assign("CAExplicitIntegrationMethod");
  }
 
};

#endif // #ifndef CAEXPLICITINTEGRATIONMETHOD_H

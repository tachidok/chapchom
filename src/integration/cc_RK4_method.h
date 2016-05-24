#ifndef CCRK4METHOD_H
#define CCRK4METHOD_H

#include "ca_explicit_integration_method.h"

/// @class CCRK4Method cc_RK4_method.h
/// This class implements Runge-Kutta 4 method to integrate ODE's
class CCRK4Method : public CAExplicitIntegrationMethod
{
 
 public:

 /// Constructor
 CCRK4Method();
  
 /// Empty destructor
 virtual ~CCRK4Method();
 
 /// Applies Eulers method to the given odes from time "t_initial" to
 /// time "t_final" using a step given by "h".
 void integrate(CAODEs &odes, const double h,
		const double t_initial, const double t_final,
		std::vector<std::vector<double> > &y);

 /// Applies Eulers method to the given odes from the current time "t"
 /// to the time "t+h".
 void integrate_step(CAODEs &odes, const double h, const double t,
		     std::vector<std::vector<double> > &y);
 
 protected:
 
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCRK4Method(const CCRK4Method &copy);
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCRK4Method& operator=(const CCRK4Method &copy);

};

#endif // #ifndef CCEULERMETHOD_H
#ifndef CCEULERMETHOD_H
#define CCEULERMETHOD_H

#include "ca_explicit_integration_method.h"

/// @class CCEulerMethod cc_euler_method.h
/// This class implements Euler's method to integrate ODE's
class CCEulerMethod : public CAExplicitIntegrationMethod
{
 
 public:

 /// Constructor
 CCEulerMethod();
  
 /// Empty destructor
 virtual ~CCEulerMethod();
 
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
 CCEulerMethod(const CCEulerMethod &copy);
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCEulerMethod& operator=(const CCEulerMethod &copy);

};

#endif // #ifndef CCEULERMETHOD_H
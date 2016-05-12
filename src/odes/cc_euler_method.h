/** \file The definition of Euler's method to integrate ODE's
 */

// Check whether the class has been already defined
#ifndef CCEULERMETHOD_H
#define CCEULERMETHOD_H

#include "ca_explicit_method.h"

/** \class CCEulerMethod cc_euler_method.h
    
    \brief This class implements Euler's method to integrate ODE's
 */
class CCEulerMethod : public CAExplicitMethod
{
 
 public:

 /** Empty constructor
  */
 CCEulerMethod();
  
 /** Empty destructor
  */
 virtual ~CCEulerMethod();
 
 /** \brief Applies Eulers method to the given odes from time
     "t_initial" to time "t_final" using a step given by "h".
 */
 void integrate(CAODEs &odes, const double h,
		const double t_initial, const double t_final,
		std::vector<double> &y);

 /** \brief Applies Eulers method to the given odes from the current
  time "t" to the time "t+h".
 */
 void integrate_step(CAODEs &odes, const double h, const double t,
		     std::vector<double> &y);
 
 protected:
 
 /** \brief Copy constructor (we do not want this class to be
     copiable). Check
     http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCEulerMethod(const CCEulerMethod &copy);

 /** \brief Assignment operator (we do not want this class to be
  copiable. Check
  http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCEulerMethod& operator=(const CCEulerMethod &copy);

};

#endif // #ifndef CCEULERMETHOD_H

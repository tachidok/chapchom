/** \file The definition of Explicit methods to integrate ODE's
 */

// Check whether the class has been already defined
#ifndef CAEXPLICITMETHOD_H
#define CAEXPLICITMETHOD_H

#include "../general/h_common_includes.h"
#include "ca_odes.h"

/** \class CAExplicitMethod ca_explicit_method.h

    \brief This class implements the interfaces for explicit
    integration methods to solve ODE's
 */
class CAExplicitMethod
{
 
 public:

 /** Empty constructor
  */
 CAExplicitMethod();
  
 /** Empty destructor
  */
 ~CAExplicitMethod();
 
 /** \brief Applies the explicit method to the given odes from time
     "t_initial" to time "t_final" using a step given by "h".
 */
 virtual void integrate(CAODEs &odes, const double h,
			const double t_initial, const double t_final,
			std::vector<double> &y) = 0;

 /** \brief Applies the explicit method to the given odes from the
  current time "t" to the time "t+h".
 */
 virtual void integrate_step(CAODEs &odes, const double h,
			     const double t, std::vector<double> &y) = 0;
 
 protected:
 
 /** \brief Copy constructor (we do not want this class to be
     copiable). Check
     http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CAExplicitMethod(const CAExplicitMethod &copy);

 /** \brief Assignment operator (we do not want this class to be
  copiable. Check
  http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CAExplicitMethod& operator=(const CAExplicitMethod &copy);

};

#endif // #ifndef CAEXPLICITMETHOD_H

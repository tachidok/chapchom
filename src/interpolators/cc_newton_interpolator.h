/** \file This file implements the Newton form of the interpolation
    polynomial
 */

// Check whether the class has been already defined
#ifndef CCNEWTONINTERPOLATOR_H
#define CCNEWTONINTERPOLATOR_H

#include "../general/h_common_includes.h"
#include "ca_interpolator.h"

/** \class CCNewtonInterpolator cc_newton_interpolator.h

    \brief This class implements the Newton form of the interpolation
    polynomial
 */
class CCNewtonInterpolator : public virtual CAInterpolator
{
 
 public:

 /** Empty constructor
  */
 CCNewtonInterpolator();

 /** Empty destructor
  */
 ~CCNewtonInterpolator();
 
 /** \brief Does the interpolation specifying the set data points, the
     order of the interpolation and the desired "x" value to
     interpolate
 */
 double interpolate_1D(std::vector<double> &x_points,
		       std::vector<double> &fx_points,
		       const double x,
		       const unsigned order);
 
 protected:
 
 /** \brief Copy constructor (we do not want this class to be
     copiable). Check
     http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCNewtonInterpolator(const CCNewtonInterpolator &copy);

 /** \brief Assignment operator (we do not want this class to be
  copiable. Check
  http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCNewtonInterpolator& operator=(const CCNewtonInterpolator &copy);

};

#endif // #ifndef CCNEWTONINTERPOLATOR_H

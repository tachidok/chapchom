#ifndef CCNEWTONINTERPOLATOR_H
#define CCNEWTONINTERPOLATOR_H

#include "ca_interpolator.h"

/// @class CCNewtonInterpolator cc_newton_interpolator.h
/// This class implements the Newton form of the interpolation
/// polynomial
class CCNewtonInterpolator : public virtual CAInterpolator
{
 
 public:

 /// Empty constructor
 CCNewtonInterpolator();

 /// Empty destructor
 ~CCNewtonInterpolator();
 
 /// Does the interpolation specifying the set data points, the order
 /// of the interpolation and the desired "x" value to interpolate
 double interpolate_1D(std::vector<double> &x_points,
		       std::vector<double> &fx_points,
		       const double x,
		       const unsigned order);
 
 protected:
 
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCNewtonInterpolator(const CCNewtonInterpolator &copy)
  {
   BrokenCopy::broken_copy("CCNewtonInterpolator");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCNewtonInterpolator &copy)
  {
   BrokenCopy::broken_assign("CCNewtonInterpolator");
  }

};

#endif // #ifndef CCNEWTONINTERPOLATOR_H

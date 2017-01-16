#ifndef CCNEWTONINTERPOLATOR_H
#define CCNEWTONINTERPOLATOR_H

#include "ac_interpolator.h"

namespace chapchom
{

 /// @class CCNewtonInterpolator cc_newton_interpolator.h
 /// This class implements the Newton form of the interpolation
 /// polynomial
 class CCNewtonInterpolator : public virtual ACInterpolator
 {
 
 public:

  /// Empty constructor
  CCNewtonInterpolator();

  /// Empty destructor
  ~CCNewtonInterpolator();
  
  /// Does the interpolation specifying the set data points, the order
  /// of the interpolation and the desired "x" value to
  /// interpolate. We use Newton's polynomial formula to construct a
  /// given order polynomial and interpolate.
  /// N(n) = b0 + b1(x-x0) + b2(x-x0)(x-x1) + b3(x-x0)(x-x1)(x-x2) ...
  double interpolate_1D(std::vector<double> &x_points,
                        std::vector<double> &fx_points,
                        const double x,
                        const unsigned order);
  
  /// Does the interpolation specifying the set data points, the order
  /// of the interpolation and the desired "x" values to
  /// interpolate. We use Newton's polynomial formula to construct a
  /// given order polynomial and interpolate.
  /// N(n) = b0 + b1(x-x0) + b2(x-x0)(x-x1) + b3(x-x0)(x-x1)(x-x2) ...
  void interpolate_1D(std::vector<double> &x_points,
                      std::vector<double> &fx_points,
                      std::vector<double> &x,
                      std::vector<double> &fx,
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

}
 
#endif // #ifndef CCNEWTONINTERPOLATOR_H

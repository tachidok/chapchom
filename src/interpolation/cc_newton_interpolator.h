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
  /// of the interpolation and the desired "x_interpolate" value to
  /// interpolate. We use Newton's polynomial formula to construct a
  /// given order polynomial and interpolate.
  /// N(n) = b0 + b1(x_interpolate-x0) +
  /// b2(x_interpolate-x0)(x_interpolate-x1) +
  /// b3(x_interpolate-x0)(x_interpolate-x1)(x_interpolate-x2) ...
  double interpolate_1D(std::vector<double> &x,
                        std::vector<double> &fx,
                        const double x_interpolate,
                        const unsigned order);
  
  /// Does the interpolation specifying the set data points, the order
  /// of the interpolation and the desired "x_interpolate" values to
  /// interpolate. We use Newton's polynomial formula to construct a
  /// given order polynomial and interpolate.
  /// N(n) = b0 + b1(x_interpolate-x0) +
  /// b2(x_interpolate-x0)(x_interpolate-x1) +
  /// b3(x_interpolate-x0)(x_interpolate-x1)(x_interpolate-x2) ...
  void interpolate_1D(std::vector<double> &x,
                      std::vector<double> &fx,
                      std::vector<double> &x_interpolate,
                      std::vector<double> &fx_interpolated,
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

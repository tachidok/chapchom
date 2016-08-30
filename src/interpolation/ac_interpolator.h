#ifndef ACINTERPOLATOR_H
#define ACINTERPOLATOR_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{

 /// @class ACInterpolator ac_interpolator.h

 /// This class implements the interfaces for interpolation methods
 class ACInterpolator
 {
 
 public:

  /// Empty constructor
  ACInterpolator();
  
  /// Empty destructor
  virtual ~ACInterpolator();
 
  /// Does 1D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" value to interpolate
  virtual double interpolate_1D(std::vector<double> &x_points,
                                std::vector<double> &fx_points,
                                const double x,
                                const unsigned order);

  /// Does 2D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" value to interpolate
  virtual double interpolate_2D(std::vector<std::vector<double> > &x_points,
                                std::vector<std::vector<double> > &fx_points,
                                std::vector<double> &x,
                                const unsigned order);

  /// Does 3D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" value to interpolate
  virtual double interpolate_3D(std::vector<std::vector<std::vector<double> > > &x_points,
                                std::vector<std::vector<std::vector<double> > > &fx_points,
                                std::vector<double> &x,
                                const unsigned order);
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACInterpolator(const ACInterpolator &copy)
   {
    BrokenCopy::broken_copy("ACInterpolator");
   }

  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACInterpolator &copy)
   {
    BrokenCopy::broken_assign("ACInterpolator");
   }

 };

}
 
#endif // #ifndef ACINTERPOLATOR_H

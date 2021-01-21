#ifndef ACINTERPOLATOR_H
#define ACINTERPOLATOR_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace scicellxx
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
  virtual Real interpolate_1D(std::vector<Real> &x_points,
                              std::vector<Real> &fx_points,
                              const Real,
                              const unsigned order);
  
  /// Does 1D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" values to interpolate
  virtual void interpolate_1D(std::vector<Real> &x_points,
                              std::vector<Real> &fx_points,
                              std::vector<Real> &x,
                              std::vector<Real> &fx,
                              const unsigned order);
  
  /// Does 2D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" value to interpolate
  virtual Real interpolate_2D(std::vector<std::vector<Real> > &x_points,
                              std::vector<Real> &fx_points,
                              std::vector<Real> &x,
                              const unsigned order);
  
  /// Does 2D interpolation specifying the data points, the order of the
  /// interpolation and the desired "x" values to interpolate
  virtual void interpolate_2D(std::vector<std::vector<Real> > &x_points,
                              std::vector<Real> &fx_points,
                              std::vector<std::vector<Real> > &x,
                              std::vector<Real> &fx,
                              const unsigned order);
  
  /// Does 3D interpolation specifying the data points, the order of
  /// the interpolation and the desired "x" value to interpolate
  virtual Real interpolate_3D(std::vector<std::vector<Real> > &x_points,
                              std::vector<Real> &fx_points,
                              std::vector<std::vector<Real> > &x,
                              const unsigned order);
  
  /// Does 3D interpolation specifying the data points, the order of the
  /// interpolation and the desired "x" values to interpolate
  virtual void interpolate_3D(std::vector<std::vector<Real> > &x_points,
                              std::vector<Real> &fx_points,
                              std::vector<std::vector<Real> > &x,
                              std::vector<Real> &fx,
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

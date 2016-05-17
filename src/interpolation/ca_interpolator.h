#ifndef CAINTERPOLATOR_H
#define CAINTERPOLATOR_H

#include "../general/h_common_includes.h"

/// @class CAInterpolator ca_interpolator.h

/// This class implements the interfaces for interpolation methods
class CAInterpolator
{
 
 public:

 /// Empty constructor
 CAInterpolator();
  
 /// Empty destructor
 virtual ~CAInterpolator();
 
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
 CAInterpolator(const CAInterpolator &copy);

 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CAInterpolator& operator=(const CAInterpolator &copy);

};

#endif // #ifndef CAINTERPOLATOR_H

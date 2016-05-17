/** \file This file implements the methods of the CAInterpolator class
 */
#include "ca_interpolator.h"

// ===================================================================
// Empty constructor
// ===================================================================
CAInterpolator::CAInterpolator()
{ 

}

// ===================================================================
// Empty destructor
// ===================================================================
CAInterpolator::~CAInterpolator()
{ 

}

// ===================================================================
// Does 1D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double CAInterpolator::interpolate_1D(std::vector<double> &x_points,
				      std::vector<double> &fx_points,
				      const double x,
				      const unsigned order)
{
 std::cout << "ERROR in CAInterpolator::interpolate_1D() - The used interpolator does not support this functionality" << std::endl;
 throw(1);
 return 0;
}

// ===================================================================
// Does 2D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double CAInterpolator::interpolate_2D(std::vector<std::vector<double> > &x_points,
				      std::vector<std::vector<double> > &fx_points,
				      std::vector<double> &x,
				      const unsigned order)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << "ERROR in CAInterpolator::interpolate_2D() - The used interpolator does not support this functionality" << std::endl;
 throw(1);
 return 0;
}

// ===================================================================
// Does 3D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double CAInterpolator::interpolate_3D(std::vector<std::vector<std::vector<double> > > &x_points,
				      std::vector<std::vector<std::vector<double> > > &fx_points,
				      std::vector<double> &x,
				      const unsigned order)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << "ERROR in CAInterpolator::interpolate_3D() - The used interpolator does not support this functionality" << std::endl;
 throw(1);
 return 0;
}

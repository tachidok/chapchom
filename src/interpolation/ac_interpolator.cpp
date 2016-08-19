#include "ac_interpolator.h"

// ===================================================================
// Empty constructor
// ===================================================================
ACInterpolator::ACInterpolator()
{ 

}

// ===================================================================
// Empty destructor
// ===================================================================
ACInterpolator::~ACInterpolator()
{ 

}

// ===================================================================
// Does 1D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double ACInterpolator::interpolate_1D(std::vector<double> &x_points,
				      std::vector<double> &fx_points,
				      const double x,
				      const unsigned order)
{
 // Error message
 std::ostringstream error_message;
 error_message << "The used interpolator does not support this "
	       << "functionality" << std::endl;
 throw ChapchomLibError(error_message.str(),
			CHAPCHOM_CURRENT_FUNCTION,
			CHAPCHOM_EXCEPTION_LOCATION);
}

// ===================================================================
// Does 2D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double ACInterpolator::interpolate_2D(std::vector<std::vector<double> > &x_points,
				      std::vector<std::vector<double> > &fx_points,
				      std::vector<double> &x,
				      const unsigned order)
{
 // Error message
 std::ostringstream error_message;
 error_message << "The used interpolator does not support this "
	       << "functionality" << std::endl;
 throw ChapchomLibError(error_message.str(),
			CHAPCHOM_CURRENT_FUNCTION,
			CHAPCHOM_EXCEPTION_LOCATION);
}

// ===================================================================
// Does 3D interpolation specifying the data points, the order of the
// interpolation and the desired "x" value to interpolate
// ===================================================================
double ACInterpolator::interpolate_3D(std::vector<std::vector<std::vector<double> > > &x_points,
				      std::vector<std::vector<std::vector<double> > > &fx_points,
				      std::vector<double> &x,
				      const unsigned order)
{
 // Error message
 std::ostringstream error_message;
 error_message << "The used interpolator does not support this functionality"
	       << std::endl;
 throw ChapchomLibError(error_message.str(),
			CHAPCHOM_CURRENT_FUNCTION,
			CHAPCHOM_EXCEPTION_LOCATION);
}

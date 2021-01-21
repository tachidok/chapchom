#include "ac_interpolator.h"

namespace scicellxx
{

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
 Real ACInterpolator::interpolate_1D(std::vector<Real> &x_points,
                                     std::vector<Real> &fx_points,
                                     const Real,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this "
                << "functionality" << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
 // ===================================================================
 // Does 1D interpolation specifying the data points, the order of
 // the interpolation and the desired "x" values to interpolate
 // ===================================================================
 void ACInterpolator::interpolate_1D(std::vector<Real> &x_points,
                                     std::vector<Real> &fx_points,
                                     std::vector<Real> &x,
                                     std::vector<Real> &fx,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this "
                << "functionality" << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
 // ===================================================================
 // Does 2D interpolation specifying the data points, the order of the
 // interpolation and the desired "x" value to interpolate
 // ===================================================================
 Real ACInterpolator::interpolate_2D(std::vector<std::vector<Real> > &x_points,
                                     std::vector<Real> &fx_points,
                                     std::vector<Real> &x,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this "
                << "functionality" << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
 // ===================================================================
 // Does 2D interpolation specifying the data points, the order of the
 // interpolation and the desired "x" values to interpolate
 // ===================================================================
 void ACInterpolator::interpolate_2D(std::vector<std::vector<Real> > &x_points,
                                     std::vector<Real> &fx_points,
                                     std::vector<std::vector<Real> > &x,
                                     std::vector<Real> &fx,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this "
                << "functionality" << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
 // ===================================================================
 // Does 3D interpolation specifying the data points, the order of the
 // interpolation and the desired "x" value to interpolate
 // ===================================================================
 Real ACInterpolator::interpolate_3D(std::vector<std::vector<Real> > &x_points,
                                     std::vector<Real> &fx_points,
                                     std::vector<std::vector<Real> > &x,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this functionality"
                << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
 // ===================================================================
 // Does 3D interpolation specifying the data points, the order of the
 // interpolation and the desired "x" values to interpolate
 // ===================================================================
 void ACInterpolator::interpolate_3D(std::vector<std::vector<Real> > &x_points,
                                     std::vector<Real> &fx_points,
                                     std::vector<std::vector<Real> > &x,
                                     std::vector<Real> &fx,
                                     const unsigned order)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "The used interpolator does not support this functionality"
                << std::endl;
  throw SciCellxxLibError(error_message.str(),
                         SCICELLXX_CURRENT_FUNCTION,
                         SCICELLXX_EXCEPTION_LOCATION);
 }
 
}

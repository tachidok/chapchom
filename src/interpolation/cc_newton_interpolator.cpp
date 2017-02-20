#include "cc_newton_interpolator.h"

namespace chapchom
{
 
 // ===================================================================
 // Empty constructor
 // ===================================================================
 CCNewtonInterpolator::CCNewtonInterpolator()
 {

 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCNewtonInterpolator::~CCNewtonInterpolator()
 { 
  
 }
 
 // ===================================================================
 // Does the interpolation specifying the set data points, the order
 // of the interpolation and the desired "x" value to interpolate. We
 // use Newton's polynomial formula to construct a given order
 // polynomial and interpolate.
 // N(n) = b0 + b1(x-x0) + b2(x-x0)(x-x1) + b3(x-x0)(x-x1)(x-x2) ...
 // ===================================================================
 double CCNewtonInterpolator::interpolate_1D(std::vector<double> &x_points,
                                             std::vector<double> &fx_points,
                                             const double x,
                                             const unsigned order)
 {
  // We assume the data points are in order, thus we do not check for
  // that
  
  // Get the size of the data set
  const unsigned n_x_points = x_points.size();
  const unsigned n_fx_points = fx_points.size();
  
  if (n_x_points != n_fx_points)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of data points do not match" << std::endl
                  << "Number of x-points: " << n_x_points << std::endl
                  << "Number of fx-points: " << n_fx_points << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // We check whether we have the corresponding number of data points
  // to perform the given order interpolation
  if (n_x_points - 1 != order)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of data points do not match with the "
                  << "requested\ninterpolation order" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that the value to interpolate is within the interval
  // [x_points[0], x_points[n-1]]
  if (x < x_points[0] || x > x_points[n_x_points])
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolated value is not within the range\n"
                  << "[" << x_points[0] << ", " << x_points[n_x_points] << "].\n"
                  << "The requested x value is: " << x << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // The coefficients vector (we use b as mostly used in Newton's
  // polynomial notation)
  std::vector<double> b(order + 1);
  
  // What interpolation to perform
  if (order == 0) // zero interpolation or no interpolation
   {
    b[0] = fx_points[0];
    return b[0];
   }
  else if (order == 1) // linear interpolation
   {
    b[0] = fx_points[0];
    // Using divided differences notation
    const double f10 =
     (fx_points[1] - fx_points[0]) / (x_points[1] - x_points[0]);
    b[1] = f10;
    
    // Do interpolation
    return b[0] + b[1] * (x - x_points[0]);
   }
  else if (order == 2) // quadratic interpolation
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Corrected, but left to test\n"
                  << "Test before use it\n"
                  << "Look for 'TEST HERE' in code"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
    
    b[0] = fx_points[0];
    // Using divided differences notation
    const double f10 =
     (fx_points[1] - fx_points[0]) / (x_points[1] - x_points[0]);
    b[1] = f10;
    const double f21 =
     (fx_points[2] - fx_points[1]) / (x_points[2] - x_points[1]);
    const double f210 =
     (f21 - f10) / (x_points[2] - x_points[0]);
    b[2] = f210;
    
    // Do interpolation
    return b[0] + b[1] * (x - x_points[0]) +
     b[2] * (x - x_points[0]) * (x - x_points[1]);
   }
  else if (order == 3) // cubic interpolation
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Test before use it\n"
                  << "Look for 'TEST HERE' in code"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
    
    b[0] = fx_points[0];
    // Using divided differences notation
    const double f10 =
     (fx_points[1] - fx_points[0]) / (x_points[1] - x_points[0]);
    b[1] = f10;
    const double f21 =
     (fx_points[2] - fx_points[1]) / (x_points[2] - x_points[1]);
    const double f32 =
     (fx_points[3] - fx_points[2]) / (x_points[3] - x_points[2]);
    const double f210 =
     (f21 - f10) / (x_points[2] - x_points[0]);
    b[2] = f210;
    const double f321 =
     (f32 - f21) / (x_points[3] - x_points[1]);
    const double f3210 =
     (f321 - f210) / (x_points[3] - x_points[0]);
    b[3] = f3210;
    
    // Do interpolation
    return b[0] + b[1] * (x - x_points[0]) +
     b[2] * (x - x_points[0]) * (x - x_points[1]) +
     b[3] * (x - x_points[0]) * (x - x_points[1]) * (x - x_points[2]);
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolation order is not yet implemented"
                  << std::endl;
    std::cout << "We only implement zero, linear, quadratic and cubic interpolation"
              << std::endl;
    std::cout << "Requested interpolation order: " << order << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
 }

 // ===================================================================
 // Does the interpolation specifying the set data points, the order
 // of the interpolation and the desired "x" values to
 // interpolate. We use Newton's polynomial formula to construct a
 // given order polynomial and interpolate.
 // N(n) = b0 + b1(x-x0) + b2(x-x0)(x-x1) + b3(x-x0)(x-x1)(x-x2) ...
 // ===================================================================
 void CCNewtonInterpolator::interpolate_1D(std::vector<double> &x_points,
                                           std::vector<double> &fx_points,
                                           std::vector<double> &x,
                                           std::vector<double> &fx,
                                           const unsigned order)
 {
  // We assume the data points are in order, thus we do not check for
  // that
  
  // Get the size of the data set
  const unsigned n_x_points = x_points.size();
  const unsigned n_fx_points = fx_points.size();
  
  if (n_x_points != n_fx_points)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of data points do not match" << std::endl
                  << "Number of x-points: " << n_x_points << std::endl
                  << "Number of fx-points: " << n_fx_points << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // We check whether we have at least the corresponding number of
  // data points to perform the given order interpolation
  if (n_x_points - 1 < order)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We do not have enough points to perform this type of"
                  << "interpolation order" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // The coefficients vector (we use b as mostly used in Newton's
  // polynomial notation)
  std::vector<double> b(order + 1);
  
  // What interpolation to perform
  if (order == 0) // zero interpolation or no interpolation
   {
    // Index for the nearest values to x
    unsigned k = 1;
    double min_diff = std::fabs(x_points[0] - x[0]);
    for (unsigned i = 0; i < n_x_points; i++)
     {
      // Get the nearest value to x[i] in x_points
      for (unsigned j = k ; j < n_x_points-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x_points[j] - x[j]);
        // If the difference is lower that means we are moving closer
        // and should update the min diff
        if (diff < min_diff)
         {
          min_diff = diff;
          k = j;
         }
        // If the difference is increasing that means the last value
        // is the minimum and we should stop searching
        else
         {
          break;
         }
       }
      // --------------------
      // Do interpolation
      fx[i] = fx_points[k];
      
     } // for (i < n_x_points)
    
   }
  else if (order == 1) // linear interpolation
   {
    // Index for the nearest values to x
    unsigned k = 1;
    double min_diff = std::fabs(x_points[0] - x[0]);
    for (unsigned i = 0; i < n_x_points; i++)
     {
      // Get the nearest value to x[i] in x_points
      for (unsigned j = k ; j < n_x_points-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x_points[j] - x[j]);
        // If the difference is lower that means we are moving closer
        // and should update the min diff
        if (diff < min_diff)
         {
          min_diff = diff;
          k = j;
         }
        // If the difference is increasing that means the last value
        // is the minimum and we should stop searching
        else
         {
          break;
         }
       }
      
      // --------------------
      // Do interpolation
      b[0] = fx_points[k];
      // Using divided differences notation
      const double f10 =
       (fx_points[k+1] - fx_points[k]) / (x_points[k+1] - x_points[k]);
      b[1] = f10;
      
      // Do interpolation
      fx[i] = b[0] + b[1] * (x[i] - x_points[k]);
      
     } // for (i < n_x_points)
    
   }
  else if (order == 2) // quadratic interpolation
   {
    // Index for the nearest values to x
    unsigned k = 1;
    double min_diff = std::fabs(x_points[0] - x[0]);
    for (unsigned i = 0; i < n_x_points; i++)
     {
      // Get the nearest value to x[i] in x_points
      for (unsigned j = k ; j < n_x_points-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x_points[j] - x[j]);
        // If the difference is lower that means we are moving closer
        // and should update the min diff
        if (diff < min_diff)
         {
          min_diff = diff;
          k = j;
         }
        // If the difference is increasing that means the last value
        // is the minimum and we should stop searching
        else
         {
          break;
         }
       }
      
      // --------------------
      // Do interpolation
      
      b[0] = fx_points[k];
      // Using divided differences notation
      const double f10 =
       (fx_points[k+1] - fx_points[k]) / (x_points[k+1] - x_points[k]);
      b[1] = f10;
      const double f21 =
       (fx_points[k+2] - fx_points[k+1]) / (x_points[k+2] - x_points[k+1]);
      const double f210 =
       (f21 - f10) / (x_points[k+2] - x_points[k]);
      b[2] = f210;
      
      // Do interpolation
      fx[i] = b[0] + b[1] * (x[i] - x_points[k]) +
       b[2] * (x[i] - x_points[k]) * (x[i] - x_points[k+1]);
      
     } // for (i < n_x_points)
    
   }
  else if (order == 3) // cubic interpolation
   {
    // Index for the nearest values to x
    unsigned k = 1;
    double min_diff = std::fabs(x_points[0] - x[0]);
    for (unsigned i = 0; i < n_x_points; i++)
     {
      // Get the nearest value to x[i] in x_points
      for (unsigned j = k ; j < n_x_points-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x_points[j] - x[j]);
        // If the difference is lower that means we are moving closer
        // and should update the min diff
        if (diff < min_diff)
         {
          min_diff = diff;
          k = j;
         }
        // If the difference is increasing that means the last value
        // is the minimum and we should stop searching
        else
         {
          break;
         }
       }
      
      // --------------------
      // Do interpolation    
      b[0] = fx_points[k];
      // Using divided differences notation
      const double f10 =
       (fx_points[k+1] - fx_points[k]) / (x_points[k+1] - x_points[k]);
      b[1] = f10;
      const double f21 =
       (fx_points[k+2] - fx_points[k+1]) / (x_points[k+2] - x_points[k+1]);
      const double f32 =
       (fx_points[k+3] - fx_points[k+2]) / (x_points[k+3] - x_points[k+2]);
      const double f210 =
       (f21 - f10) / (x_points[k+2] - x_points[k]);
      b[2] = f210;
      const double f321 =
       (f32 - f21) / (x_points[k+3] - x_points[k+1]);
      const double f3210 =
       (f321 - f210) / (x_points[k+3] - x_points[k]);
      b[3] = f3210;
    
      // Do interpolation
      fx[i] = b[0] + b[1] * (x[i] - x_points[k]) +
       b[2] * (x[i] - x_points[k]) * (x[i] - x_points[k+1]) +
       b[3] * (x[i] - x_points[k]) * (x[i] - x_points[k+1]) * (x[i] - x_points[k+2]);
      
     }  // for (i < n_x_points)
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolation order is not yet implemented"
                  << std::endl;
    std::cout << "We only implement zero, linear, quadratic and cubic interpolation"
              << std::endl;
    std::cout << "Requested interpolation order: " << order << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
}

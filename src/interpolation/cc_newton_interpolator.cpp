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
 /// Does the interpolation specifying the set data points, the order
 /// of  //        the interpolation and the desired "x_interpolate" value to
 // /// interpolate. We use Newton's polynomial formula to construct a
 // /// given order polynomial and interpolate.
 // /// N(n) = b0 + b1(x_interpolate-x0) +
 // /// b2(x_interpolate-x0)(x_interpolate-x1) +
 // /// b3(x_interpolate-x0)(x_interpolate-x1)(x_interpolate-x2) ...
 // // ===================================================================
 // double CCNewtonInterpolator::interpolate_1D(std::vector<double> &x,
 //                                             std::vector<double> &fx,
 //                                             const double x_interpolate,
 //                                             const unsigned order)
 // {
 //  // We assume the data points are in order, thus we do not check for
 //  // that
  
 //  // Get the size of the data set
 //  const unsigned n_x = x.size();
 //  const unsigned n_fx = fx.size();
  
 //  if (n_x != n_fx)
 //   {
 //    // Error message
 //    std::ostringstream error_message;
 //    error_message << "The number of data points do not match" << std::endl
 //                  << "Number of x-points: " << n_x << std::endl
 //                  << "Number of fx-points: " << n_fx << std::endl;
 //    throw ChapchomLibError(error_message.str(),
 //                           CHAPCHOM_CURRENT_FUNCTION,
 //                           CHAPCHOM_EXCEPTION_LOCATION);
 //   }
  
 //  // We check whether we have the corresponding number of data points
 //  // to perform the given order interpolation
 //  if (n_x - 1 != order)
 //   {
 //    // Error message
 //    std::ostringstream error_message;
 //    error_message << "The number of data points do not match with the "
 //                  << "requested\ninterpolation order" << std::endl;
 //    throw ChapchomLibError(error_message.str(),
 //                           CHAPCHOM_CURRENT_FUNCTION,
 //                           CHAPCHOM_EXCEPTION_LOCATION);
 //   }
  
 //  // Check that the value to interpolate is within the interval
 //  // [x[0], x[n-1]]
 //  if (x_interpolate < x[0] || x_interpolate > x[n_x])
 //   {
 //    // Error message
 //    std::ostringstream error_message;
 //    error_message << "The requested interpolated value is not within the range\n"
 //                  << "[" << x[0] << ", " << x[n_x] << "].\n"
 //                  << "The requested x_interpolate value is: " << x_interpolate << std::endl;
 //    throw ChapchomLibError(error_message.str(),
 //                           CHAPCHOM_CURRENT_FUNCTION,
 //                           CHAPCHOM_EXCEPTION_LOCATION);
 //   }
  
 //  // The coefficients vector (we use b as mostly used in Newton's
 //  // polynomial notation)
 //  std::vector<double> b(order + 1);
  
 //  // What interpolation to perform
 //  if (order == 0) // zero interpolation or no interpolation
 //   {
 //    b[0] = fx[0];
 //    return b[0];
 //   }
 //  else if (order == 1) // linear interpolation
 //   {
 //    b[0] = fx[0];
 //    // Using divided differences notation
 //    const double f10 =
 //     (fx[1] - fx[0]) / (x[1] - x[0]);
 //    b[1] = f10;
    
 //    // Do interpolation
 //    return b[0] + b[1] * (x_interpolate - x[0]);
 //   }
 //  else if (order == 2) // quadratic interpolation
 //   {
 //    // Error message
 //    std::ostringstream error_message;
 //    error_message << "Corrected, but left to test\n"
 //                  << "Test before use it\n"
 //                  << "Look for 'TEST HERE' in code"
 //                  << std::endl;
 //    throw ChapchomLibError(error_message.str(),
 //                           CHAPCHOM_CURRENT_FUNCTION,
 //                           CHAPCHOM_EXCEPTION_LOCATION);
    
 //    b[0] = fx[0];
 //    // Using divided differences notation
 //    const double f10 =
 //     (fx[1] - fx[0]) / (x[1] - x[0]);
 //    b[1] = f10;
 //    const double f21 =
 //     (fx[2] - fx[1]) / (x[2] - x[1]);
 //    const double f210 =
 //     (f21 - f10) / (x[2] - x[0]);
 //    b[2] = f210;
    
 //    // Do interpolation
 //    return b[0] +
 //     b[1] * (x_interpolate - x[0]) +
 //     b[2] * (x_interpolate - x[0]) * (x_interpolate - x[1]);
 //   }
 //  else if (order == 3) // cubic interpolation
 //   {
 //    // Error message
 //    std::ostringstream error_message;
 //    error_message << "Test before use it\n"
 //                  << "Look for 'TEST HERE' in code"
 //                  << std::endl;
 //    throw ChapchomLibError(error_message.str(),
 //                           CHAPCHOM_CURRENT_FUNCTION,
 //                           CHAPCHOM_EXCEPTION_LOCATION);
    
 //    b[0] = fx[0];
 //    // Using divided differences notation
 //    const double f10 =
 //     (fx[1] - fx[0]) / (x[1] - x[0]);
 //    b[1] = f10;
 //    const double f21 =
 //     (fx[2] - fx[1]) / (x[2] - x[1]);
 //    const double f32 =
 //     (fx[3] - fx[2]) / (x[3] - x[2]);
 //    const double f210 =
 //     (f21 - f10) / (x[2] - x[0]);
 //    b[2] = f210;
 //    const double f321 =
 //     (f32 - f21) / (x[3] - x[1]);
 //    const double f3210 =
 //     (f321 - f210) / (x[3] - x[0]);
 //    b[3] = f3210;
    
 //    // Do interpolation
 //    return b[0] +
 //     b[1] * (x_interpolate - x[0]) +
 //     b[2] * (x_interpolate - x[0]) * (x_interpolate - x[1]) +
 //     b[3] * (x_interpolate - x[0]) * (x_interpolate - x[1]) * (x_interpolate - x[2]);
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolation order is not yet implemented"
                  << std::endl;
    std::cout << "We have only implemented zero, linear, quadratic and cubic "
              << "interpolation" << std::endl;
    std::cout << "Requested interpolation order: " << order << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
 }
 
 // ===================================================================
 /// Does the interpolation specifying the set data points, the order
 /// of the interpolation and the desired "x_interpolate" values to
 /// interpolate. We use Newton's polynomial formula to construct a
 /// given order polynomial and interpolate.
 /// N(n) = b0 + b1(x_interpolate-x0) +
 /// b2(x_interpolate-x0)(x_interpolate-x1) +
 /// b3(x_interpolate-x0)(x_interpolate-x1)(x_interpolate-x2) ...
 // ===================================================================
 void CCNewtonInterpolator::interpolate_1D(std::vector<double> &x,
                                           std::vector<double> &fx,
                                           std::vector<double> &x_interpolate,
                                           std::vector<double> &fx_interpolated,
                                           const unsigned order)
 {
  // We assume the data points are in order, thus we do not check for
  // that
  
  // Get the size of the data set
  const unsigned n_x = x.size();
  const unsigned n_fx = fx.size();
  
  if (n_x != n_fx)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of data points do not match" << std::endl
                  << "Number of x-points: " << n_x << std::endl
                  << "Number of fx-points: " << n_fx << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // We check whether we have at least the corresponding number of
  // data points to perform the given order interpolation
  if (n_x - 1 < order)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We do not have enough points to perform this type of"
                  << "interpolation order" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check that the fx_interpolated vector has the same size as the x_interpolate vector
  const unsigned n_x_interpolate = x_interpolate.size();
  const unsigned n_fx_interpolated = fx_interpolated.size();
  
  if (n_x_interpolate != n_fx_interpolated)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The vectors 'x_interpolate' and 'fx_interpolated' have"
                  << "different sizes" << std::endl
                  << "n_x_interpolate: " << n_x_interpolate << std::endl
                  << "n_fx_interpolated" << n_fx_interpolated << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Loop over the ""x_interpolate" values and for each one search for
  // the closest "x" values that will be used to interpolate
  for (unsigned i = 0; i < n_x_interpolate; i++)
   {
    // Search for the greater value smaller than "x_interpolate[i]",
    // and the smaller value larger than "x_interpolate[i]" to use
    // them as the "x"s points for interpolation

    // Indexes for the position of the values to the left and right of
    // "x_interpolate[i]"
    int i_left = 0;
    int i_right = n_x_interpolate - 1;
    
    // Flag to indicate to continue looping
    bool loop = true;
    
    // Flag to indicate whether the value were found or not
    bool found_value = false;
    
    // Indicates whether interpolation should be performed or not
    bool do_interpolation = false;
    
    while(loop)
     {
      // Check whether left index is larger than right index
      if (i_left > i_right)
       {
        // Indicate we have failured to find the value
        loop = false;
       }

      // Check whether the left value is the same as the one we are
      // looking for
      if (x_interpolate[i_left] == x_interpolate[i])
       {
        do_interpolation = false;
        loop = false;
        found_value = true;
       }
      // Check whether the right value is the same as the one we are
      // looking for
      else if (x_interpolate[i_right] == x_interpolate[i])
       {
        do_interpolation = false;
        loop = false;
        found_value = true;
       }
      else
       {
        // Compute the middle index in the current range
        const int i_middle = std::floor(i_left + (i_right - i_left)/ 2);
#if 0
        std::cout << "T: (" << t << ")" << std::endl;
        std::cout << "i_left: (" << i_left << ") i_middle: ("
                  << i_middle << ") i_right: ("
                  << i_right << ")" << std::endl;
        std::cout << "[i_left]: (" << Table_time[i_left] << ") [i_middle]: ("
                  << Table_time[i_middle] << ") [i_right]: ("
                  << Table_time[i_right] << ")" << std::endl;
#endif // #if 0
        // The i_left and i_right variables already store the indices
        // for the left and right values to x_interpolate[i]
        if ((i_middle == i_left || i_middle == i_right) &&
            ((i_right - i_left) == 1))
         {
          //std::cout << "[END]" << std::endl;
          // Found data
          loop = false;
          found_value = true;
         }
        // Move the left index to the middle
        else if (x_interpolate[i_middle] < x_interpolate[i])
         {
          //std::cout << "[MOVE LEFT TO MIDDLE]" << std::endl;
          i_left = i_middle;
         } // Move the right index to the middle 
        else if (x_interpolate[i_middle] > x_interpolate[i])
         {
          //std::cout << "[MOVE RIGHT TO MIDDLE]" << std::endl;
          i_right = i_middle;
         }
        else
         {
          // Error message
          std::ostringstream error_message;
          error_message << "The requested 'x_interpolated[i]' value is not between the supplied"
                        << "x's values"
                        << std::endl;
          throw ChapchomLibError(error_message.str(),
                                 CHAPCHOM_CURRENT_FUNCTION,
                                 CHAPCHOM_EXCEPTION_LOCATION);
         }
        
       } // The searched value is not exactly in the table
      
     } // while(loop)
    

    // TODO HERE
    // FILL SUB VECTORS WITH DATA
    // CALL INTERPOLATION METHODS
    
   } // for (i < n_x_interpolate)
  
  // The coefficients vector (we use b as mostly used in Newton's
  // polynomial notation)
  std::vector<double> b(order + 1);

  // Here add a search method and when the value has been found then
  // call the corresponding interpolation function with the
  // x_interpolate
  
  
  // What interpolation to perform
  if (order == 0) // zero interpolation or no interpolation
   {
    // Index for the nearest values to x
    unsigned k = 0;
    // Loop over the ""x_interpolate" values and for each one search
    // for the closest "x" values that will be used to interpolate
    for (unsigned i = 0; i < n_x_interpolate; i++)
     {
      double min_diff = std::fabs(x[k] - x_interpolate[i]);
      // Get the nearest value to x_interpolate[i] in x
      for (unsigned j = k ; j < n_x-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x[j] - x_interpolate[i]);
        // If the difference is smaller than previous one that means
        // we are approaching the closer 'x' value to
        // 'x_interpolate'. We must update the 'min_diff' value
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
      fx_interpolated[i] = fx[k];
      
     } // for (i < n_x_interpolate)
    
   }
  else if (order == 1) // linear interpolation
   {
    // Index for the nearest values to x
    unsigned k = 0;
    // Loop over the ""x_interpolate" values and for each one search
    // for the closest "x" values that will be used to interpolate
    for (unsigned i = 0; i < n_x_interpolate; i++)
     {
      double min_diff = std::fabs(x[k] - x_interpolate[i]);
      // Get the nearest value to x_interpolate[i] in x
      for (unsigned j = k ; j < n_x-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x[j] - x_interpolate[i]);
        // If the difference is smaller than previous one that means
        // we are approaching the closer 'x' value to
        // 'x_interpolate'. We must update the 'min_diff' value
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
      b[0] = fx[k];
      // Using divided differences notation
      const double f10 =
       (fx[k+1] - fx[k]) / (x[k+1] - x[k]);
      b[1] = f10;
      
      // Do interpolation
      fx_interpolated[i] = b[0] +
       b[1] * (x_interpolate[i] - x[k]);
      
     } // for (i < n_x_interpolate)
    
   }
  else if (order == 2) // quadratic interpolation
   {
    // Index for the nearest values to x
    unsigned k = 0;
    // Loop over the ""x_interpolate" values and for each one search
    // for the closest "x" values that will be used to interpolate
    for (unsigned i = 0; i < n_x_interpolate; i++)
     {
      double min_diff = std::fabs(x[k] - x_interpolate[i]);
      // Get the nearest value to x_interpolate[i] in x
      for (unsigned j = k ; j < n_x-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x[j] - x_interpolate[i]);
        // If the difference is smaller than previous one that means
        // we are approaching the closer 'x' value to
        // 'x_interpolate'. We must update the 'min_diff' value
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
      
      b[0] = fx[k];
      // Using divided differences notation
      const double f10 =
       (fx[k+1] - fx[k]) / (x[k+1] - x[k]);
      b[1] = f10;
      const double f21 =
       (fx[k+2] - fx[k+1]) / (x[k+2] - x[k+1]);
      const double f210 =
       (f21 - f10) / (x[k+2] - x[k]);
      b[2] = f210;
      
      // Do interpolation
      fx_interpolated[i] = b[0] +
       b[1] * (x_interpolate[i] - x[k]) +
       b[2] * (x_interpolate[i] - x[k]) * (x_interpolate[i] - x[k+1]);
      
     } // for (i < n_x_interpolate)
    
   }
  else if (order == 3) // cubic interpolation
   {
    // Index for the nearest values to x
    unsigned k = 0;
    // Loop over the ""x_interpolate" values and for each one search
    // for the closest "x" values that will be used to interpolate
    for (unsigned i = 0; i < n_x_interpolate; i++)
     {
      double min_diff = std::fabs(x[k] - x_interpolate[i]);
      // Get the nearest value to x_interpolate[i] in x
      for (unsigned j = k ; j < n_x-order; j++)
       {
        // Get the difference to the current point
        const double diff = std::fabs(x[j] - x_interpolate[i]);
        // If the difference is smaller than previous one that means
        // we are approaching the closer 'x' value to
        // 'x_interpolate'. We must update the 'min_diff' value
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
      b[0] = fx[k];
      // Using divided differences notation
      const double f10 =
       (fx[k+1] - fx[k]) / (x[k+1] - x[k]);
      b[1] = f10;
      const double f21 =
       (fx[k+2] - fx[k+1]) / (x[k+2] - x[k+1]);
      const double f32 =
       (fx[k+3] - fx[k+2]) / (x[k+3] - x[k+2]);
      const double f210 =
       (f21 - f10) / (x[k+2] - x[k]);
      b[2] = f210;
      const double f321 =
       (f32 - f21) / (x[k+3] - x[k+1]);
      const double f3210 =
       (f321 - f210) / (x[k+3] - x[k]);
      b[3] = f3210;
    
      // Do interpolation
      fx_interpolated[i] = b[0] +
       b[1] * (x_interpolate[i] - x[k]) +
       b[2] * (x_interpolate[i] - x[k]) * (x_interpolate[i] - x[k+1]) +
       b[3] * (x_interpolate[i] - x[k]) * (x_interpolate[i] - x[k+1]) * (x_interpolate[i] - x[k+2]);
      
     }  // for (i < n_x_interpolate)
    
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolation order is not yet implemented"
                  << std::endl;
    std::cout << "We have only implemented zero, linear, quadratic and cubic "
              << "interpolation" << std::endl;
    std::cout << "Requested interpolation order: " << order << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
}

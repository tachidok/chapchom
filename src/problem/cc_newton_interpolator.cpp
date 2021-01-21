#include "cc_newton_interpolator.h"

namespace scicellxx
{
 
 // ===================================================================
 /// Empty constructor
 // ===================================================================
 CCNewtonInterpolator::CCNewtonInterpolator()
  : ACInterpolator()
 {

 }
 
 // ===================================================================
 /// Empty destructor
 // ===================================================================
 CCNewtonInterpolator::~CCNewtonInterpolator()
 { 
  
 }
 
 // ===================================================================
 /// Does the interpolation specifying the set data points, the order
 /// of the interpolation and the desired "x_interpolate" value to
 /// interpolate. We use Newton's polynomial formula to construct a
 /// given order polynomial and interpolate.  N(n) = b0 +
 /// b1(x_interpolate-x0) + b2(x_interpolate-x0)(x_interpolate-x1) +
 /// b3(x_interpolate-x0)(x_interpolate-x1)(x_interpolate-x2) ...
 // ===================================================================
 Real CCNewtonInterpolator::interpolate_1D(std::vector<Real> &x,
                                           std::vector<Real> &fx,
                                           const Real x_interpolate,
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // We check whether we have the corresponding number of data points
  // to perform the given order interpolation
  if (n_x - 1 != order)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of data points do not match with the "
                  << "requested\ninterpolation order" << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // Check that the value to interpolate is within the interval
  // [x[0], x[n-1]]
  if (x_interpolate < x[0] || x_interpolate > x[n_x-1])
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The requested interpolated value is not within the range\n"
                  << "[" << x[0] << ", " << x[n_x-1] << "].\n"
                  << "The requested x_interpolate value is: " << x_interpolate << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // The coefficients vector (we use b as mostly used in Newton's
  // polynomial notation)
  std::vector<Real> b(order + 1);
  
  // What interpolation to perform
  if (order == 0) // zero interpolation or no interpolation
   {
    b[0] = fx[0];
    return b[0];
   }
  else if (order == 1) // linear interpolation
   {
    b[0] = fx[0];
    // Using divided differences notation
    const Real f10 =
     (fx[1] - fx[0]) / (x[1] - x[0]);
    b[1] = f10;
    
    // Do interpolation
    return b[0] + b[1] * (x_interpolate - x[0]);
   }
  else if (order == 2) // quadratic interpolation
   {    
    b[0] = fx[0];
    // Using divided differences notation
    const Real f10 =
     (fx[1] - fx[0]) / (x[1] - x[0]);
    b[1] = f10;
    const Real f21 =
     (fx[2] - fx[1]) / (x[2] - x[1]);
    const Real f210 =
     (f21 - f10) / (x[2] - x[0]);
    b[2] = f210;
    
    // Do interpolation
    return b[0] +
     b[1] * (x_interpolate - x[0]) +
     b[2] * (x_interpolate - x[0]) * (x_interpolate - x[1]);
   }
  else if (order == 3) // cubic interpolation
   {    
    b[0] = fx[0];
    // Using divided differences notation
    const Real f10 =
     (fx[1] - fx[0]) / (x[1] - x[0]);
    b[1] = f10;
    const Real f21 =
     (fx[2] - fx[1]) / (x[2] - x[1]);
    const Real f32 =
     (fx[3] - fx[2]) / (x[3] - x[2]);
    const Real f210 =
     (f21 - f10) / (x[2] - x[0]);
    b[2] = f210;
    const Real f321 =
     (f32 - f21) / (x[3] - x[1]);
    const Real f3210 =
     (f321 - f210) / (x[3] - x[0]);
    b[3] = f3210;
    
    // Do interpolation
    return b[0] +
     b[1] * (x_interpolate - x[0]) +
     b[2] * (x_interpolate - x[0]) * (x_interpolate - x[1]) +
     b[3] * (x_interpolate - x[0]) * (x_interpolate - x[1]) * (x_interpolate - x[2]);
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
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
 void CCNewtonInterpolator::interpolate_1D(std::vector<Real> &x,
                                           std::vector<Real> &fx,
                                           std::vector<Real> &x_interpolate,
                                           std::vector<Real> &fx_interpolated,
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // We check whether we have at least the corresponding number of
  // data points to perform the given order interpolation
  if (n_x - 1 < order)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We do not have enough points to perform this type of"
                  << "interpolation order" << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
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
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
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
    int i_right = n_x - 1;
    
    // Flag to indicate to continue looping
    bool loop = true; 
    
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
      if (x[i_left] == x_interpolate[i])
       {
        do_interpolation = false; // Indicate to not perform interpolation
        loop = false;
        
        // Get the funtion value for x_interpolate[i]
        fx_interpolated[i] = fx[i_left];
        // Then break the loop and continue with the next value
        break;
        
       }
      // Check whether the right value is the same as the one we are
      // looking for
      else if (x[i_right] == x_interpolate[i])
       {
        do_interpolation = false; // Indicate to not perform interpolation
        loop = false;
        
        // Get the funtion value for x_interpolate[i]
        fx_interpolated[i] = fx[i_right];
        // Then break the loop and continue with the next value
        break;
        
       }
      else
       {
        // Compute the middle index in the current range
        const int i_middle = std::floor(i_left + (i_right - i_left) / 2);
#if 0
        std::cout << "x_interpolate[i]: (" << x_interpolate[i] << ")" << std::endl;
        std::cout << "i_left: (" << i_left << ") i_middle: ("
                  << i_middle << ") i_right: ("
                  << i_right << ")" << std::endl;
        std::cout << "[i_left]: (" << x[i_left] << ") [i_middle]: ("
                  << x[i_middle] << ") [i_right]: ("
                  << x[i_right] << ")" << std::endl;
#endif // #if 0
        // Check whether the i_left or i_right variables already are
        // the indices for the left and right values to
        // x_interpolate[i]
        if ((i_middle == i_left || i_middle == i_right) &&
            ((i_right - i_left) == 1))
         {
          //std::cout << "[END]" << std::endl;
          // Found data
          loop = false;
          do_interpolation = true;
          
          // Break and go for the interpolation step
           break;
         }
        // Move the left index to the middle
        else if (x[i_middle] <= x_interpolate[i])
         {
          //std::cout << "[MOVE LEFT TO MIDDLE]" << std::endl;
          i_left = i_middle;
         } // Move the right index to the middle 
        else if (x[i_middle] > x_interpolate[i])
         {
          //std::cout << "[MOVE RIGHT TO MIDDLE]" << std::endl;
          i_right = i_middle;
         }
        else
         {
          // Error message
          std::ostringstream error_message;
          error_message << "The requested 'x_interpolated[i]' value is not between the supplied\n"
                        << "x's values"
                        << std::endl;
          throw SciCellxxLibError(error_message.str(),
                                 SCICELLXX_CURRENT_FUNCTION,
                                 SCICELLXX_EXCEPTION_LOCATION);
         }
        
       } // Binary search condition
      
     } // while(loop)

    // Check whether we sould perform interpolation or not
    if (do_interpolation)
     {
      // Vectors to extract the near values to perform interpolation
      std::vector<Real> sub_x(order + 1);
      std::vector<Real> sub_fx(order + 1);
      
      // Check whether the number of data to the right are enough to
      // perform the interpolation
      if (i_right + order - 1 < n_x)
       {
        // Fill with data from i_left to i_right + order - 1
        unsigned k = 0;
        for (unsigned j = i_left; j <= i_right + order - 1; j++, k++)
         {
          sub_x[k] = x[j];
          sub_fx[k] = fx[j];
         }
        
       }
      // Check whether the number of data to the left are enough to
      // perform the interpolation
      else if (static_cast<int>(i_left - order + 1) >= 0)
       {
        // Fill with data from i_left - order + 1 to i_right
        unsigned k = 0;
        for (unsigned j = i_left - order + 1; j <= static_cast<unsigned>(i_right); j++, k++)
         {
          sub_x[k] = x[j];
          sub_fx[k] = fx[j];
         }
       }
      else
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The number of data in the input vectors 'x's and fx'x are not enough\n"
                      << "to perform an " << order << "-th order interpolation"
                      << "i_left: " << i_left
                      << "i_right: " << i_right
                      << "size of vector: " << n_x_interpolate
                      << std::endl;
        throw SciCellxxLibError(error_message.str(),
                               SCICELLXX_CURRENT_FUNCTION,
                               SCICELLXX_EXCEPTION_LOCATION);
        
       }
      
      fx_interpolated[i] = interpolate_1D(sub_x, sub_fx, x_interpolate[i], order);
      
     } // if (do_interpolation)
    
   } // for (i < n_x_interpolate)
    
 }
 
}

#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The required classes to solve Initial Value Problems (IVP)
// The factory to create the integration method
#include "../../../src/integration/cc_factory_integration_method.h"
// Integration methods
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_sensors_TelitSL869-DR.h"
// The nmea decoder
#include "cc_nmea_decoder.h"

//#define OLD_IMPLEMENTATION
#define COMPUTE_ACC_FROM_GPS_VELOCITY

#define GRAVITY 9.81

#define APPLY_CONVOLUTION
#ifndef APPLY_CONVOLUTION
//#define APPLY_LOW_PASS_FILTER
#endif // #ifndef APPLY_CONVOLUTION

//#define CORRECT_ACCELEROMETER_MISALIGNMENT
//#define CORRECT_X_AXIS_POINTING_TO_FRONT
#define CORRECT_INERTIAL_SENSORES_MISALIGNMENT

#define ROTATION_MATRIX_YAW_PITCH_ROLL // Original
//#define ROTATION_MATRIX_ROLL_PITCH_YAW

#define GYRO_THRESHOLD_Z 1.0 * TO_RADIANS // One degree threshold
#define AZGADS_CONSTANT 1.1285
//#define ACCELERATION_OFFSET 0.2

//#define THRESHOLDS
#ifdef THRESHOLDS
//#define GYRO_THRESHOLD 1.0 * TO_RADIANS // One degree threshold
//#define EULER_ANGLES_RATE_THRESHOLD 5.0 * TO_RADIANS
//#define ACCELERATION_THRESHOLD 0.4 // One meter per second per second
#endif // #ifdef THRESHOLDS

//#define GRAVITY_TO_BODY_FRAME

//#define GRAVITY_TO_BODY_FRAME
//#define INERTIAL_ACCELERATION_THRESHOLD GRAVITY
//#define GYRO_THRESHOLD 1.0 * TO_RADIANS // One degree threshold
//#define ACCELERATION_THRESHOLD 1.0 // One meter per second per second
//#define GYRO_AVERAGE
//#define ACCELEROMETER_AVERAGE

#define MAX_SIGNAL_SIZE 40

using namespace chapchom;

// ===================================================================
// Gets the average of the signal and store it in the averaged signal
// ===================================================================
void average(std::vector<std::vector<double> > &signal,
             std::vector<std::vector<double> > &averaged_signal)
{
 // Get the size of the input signal
 const unsigned n_signal = signal.size();
 // Check that the averaged signal size is one dimensional only
 const unsigned n_averaged_signal = averaged_signal.size();
 if (n_averaged_signal != 1)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The averaged signal size is not one dimensional\n"
                 << "n_averaged_signal: " << n_averaged_signal
                 << std::endl << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Initialise data
 std::vector<double> average(DIM, 0.0);
 // get the average
 for (unsigned i = 0; i < n_signal; i++)
  {
   for (unsigned j = 0; j < DIM; j++)
    {
     average[j]+= signal[i][j];
    }
  } // for (i < n_signal)
 
 // Resize the output averaged signal
 averaged_signal[0].resize(DIM);
 for (unsigned j = 0; j < DIM; j++)
  {
   averaged_signal[0][j] = average[j] / n_signal;
  }
 
}

// ===================================================================
// Modified convolution method, it applies convolution to the non
// processed data when the kernel size fits into the data. Originally
// took from
// http://stackoverflow.com/questions/8424170/1d-linear-convolution-in-ansi-c-code
// ===================================================================
void convolve_use_non_processed_data(double *signal, const unsigned n_signal,
                                     double *kernel, const unsigned n_kernel,
                                     double *convolved_signal,
                                     const double n_convolved_signal)
{
 // This modified convolution applies only if the kernel size is
 // smaller or equal than the signal size
 if (n_kernel > n_signal)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The kernel size is larger than the number of elements in the signal\n"
                 << "n_kernel: " << n_kernel
                 << "n_signal: " << n_signal
                 << "This modified convolve function only applies if the size\n"
                 << "of the kernel is smaller or equal than size of the signal\n"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Loop over the size of the convolved_signal
 for (unsigned i = 0; i < n_convolved_signal; i++)
  {
   // Initialise
   convolved_signal[i] = 0.0;
   
   for (unsigned k = 0; k < n_kernel; k++)
    {
     convolved_signal[i] += signal[i+k] * kernel[k];
    }
   
  } // for (i < n_convolved_signal)
 
}

// ===================================================================
// Modified convolution method, it applies the convultion only if all
// the values of the kernel fit into the signal. Originally took from
// http://stackoverflow.com/questions/8424170/1d-linear-convolution-in-ansi-c-code
// ===================================================================
void convolve_modified(std::vector<std::vector<double> > &signal,
                       double *kernel,
                       const unsigned n_kernel,
                       std::vector<std::vector<double> > &convolved_signal)
{
 // Get the size of the signal
 const unsigned n_signal = signal.size();
 // This modified convolution applies only if the kernel size is
 // smaller or equal than the signal size
 if (n_kernel > n_signal)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The kernel size is larger than the signal size\n"
                 << "n_kernel: " << n_kernel
                 << "n_signal: " << n_signal
                 << "This modified convolve function only applies if the size\n"
                 << "of the kernel is smaller than the size of the signal\n"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Get the size of the convolved signal
 const unsigned n_convolved_signal = convolved_signal.size();
 if (n_signal - n_kernel + 1 != n_convolved_signal)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The size of the container for the convolved signal is not as expected\n"
                 << "The size of the container for the convoled signal must be 'n_signal - n_kernel + 1'\n"
                 << "but we got: "
                 << "n_signal: " << n_signal
                 << "n_kernel: " << n_kernel
                 << "n_convolved_signal: " << n_convolved_signal << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Loop over the size of the convolved_signal
 for (unsigned i = 0; i < n_convolved_signal; i++)
  {
   // Initialise
   convolved_signal[i].resize(DIM,0);
   
   for (unsigned j = 0; j < n_kernel; j++)
    {
     for (unsigned k = 0; k < DIM; k++)
      {
       convolved_signal[i][k] += signal[i+j][k] * kernel[j];
      }
     
    } // for (j < n_kernel)
   
  } // for (i < n_convolved_signal)
 
}

// ===================================================================
// Convolution took from //
// http://stackoverflow.com/questions/8424170/1d-linear-convolution-in-ansi-c-code
// ===================================================================
void convolve(std::vector<std::vector<double> > &signal, double *kernel,
              const unsigned n_kernel,
              std::vector<std::vector<double> > &convolved_signal)
{
 // Get the size of the signal
 const unsigned n_signal = signal.size();
 // Get the size of the convolved signal
 const unsigned n_convolved_signal = convolved_signal.size();
 if (n_signal + n_kernel - 1 != n_convolved_signal)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The size of the container for the convolved signal is not as expected\n"
                 << "The size of the container for the convoled signal must be 'n_signal + n_kernel - 1'\n"
                 << "but we got: "
                 << "n_signal: " << n_signal
                 << "n_kernel: " << n_kernel
                 << "n_convolved_signal: " << n_convolved_signal << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Loop over the size of the convolved_signal
 for (unsigned i = 0; i < n_convolved_signal; i++)
  {
   // Initialise
   convolved_signal[i].resize(DIM,0);
   
   unsigned k_min;
   unsigned k_max;
   
   if (i >= n_kernel - 1)
    {
     k_min = i - (n_kernel - 1);
    }
   else
    {
     k_min = 0;
    }

   if (i < n_signal - 1)
    {
     k_max = i;
    }
   else
    {
     k_max = n_signal - 1;
    }
   
   for (unsigned k = k_min; k <= k_max; k++)
    {
     for (unsigned j = 0; j < DIM; j++)
      {
       convolved_signal[i][j] += signal[k][j] * kernel[i - k];
      }
    }
   
  } // for (i < limit)
 
}

// ===================================================================
// Low pass filter based on frequency. Took from
// https://www.quora.com/Whats-the-C-coding-for-a-low-pass-filter and
// adapted for the current demo. Pass the sample rate of Hz of our
// example and the cut-off frequency, the frequencies below this value
// are allowed to passed by the low-pass filter
// ===================================================================
void low_pass_filter_frequency(std::vector<std::vector<double> > &noisy_signal,
                               std::vector<std::vector<double> > &filtered_signal,
                               const double cut_off_frequency,
                               const double sample_rate)
{
 // Check whether the number of input and output data are the same
 const unsigned n_noisy_data = noisy_signal.size();
 const unsigned n_filtered_data = filtered_signal.size();
 if (n_noisy_data != n_filtered_data)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The size of the containers for the noisy and filtered data is different\n"
                 << "noisy_data.size(): " << n_noisy_data
                 << "filtered_data.size(): " << n_filtered_data << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 const double RC = 1.0/(cut_off_frequency*2*3.14);
 const double dt = 1.0/sample_rate;
 const double alpha = dt/(RC+dt);
 DEB(RC);
 DEB(dt);
 DEB(alpha);
 
 // Copy the first data into the output data
 filtered_signal[0] = noisy_signal[0];
 // Apply the filter
 for(unsigned i = 1; i < n_noisy_data; ++i)
  {
   filtered_signal[i].resize(DIM);
   for (unsigned j = 0; j < DIM; j++)
    {
#ifdef APPLY_LOW_PASS_FILTER
     filtered_signal[i][j] = filtered_signal[i-1][j] + (alpha*(noisy_signal[i][j] - filtered_signal[i-1][j]));     
#else
     filtered_signal[i][j] = noisy_signal[i][j];
#endif // #ifdef APPLY_LOW_PASS_FILTER

    } // for (j < DIM)
  } // for (i < n_noisy_data)
 
}

// ===================================================================
// Fast Fourier Transform, classical implementation of the
// Cooley-Tukey algorithm from Numerical Recipes in C++ [5], p.513.
// ===================================================================
void fft(double* data, unsigned long nn)
{
 unsigned long n, mmax, m, j, istep, i;
 double wtemp, wr, wpr, wpi, wi, theta;
 double tempr, tempi;
 
 // reverse-binary reindexing
 n = nn<<1;
 j=1;
 for (i=1; i<n; i+=2)
  {
   if (j>i)
    {
     std::swap(data[j-1], data[i-1]);
     std::swap(data[j], data[i]);
    }
   m = nn;
   while (m>=2 && j>m)
    {
     j -= m;
     m >>= 1;
    }
   j += m;
  };
 
 // here begins the Danielson-Lanczos section
 mmax=2;
 while (n>mmax)
  {
   istep = mmax<<1;
   theta = -(2*M_PI/mmax);
   wtemp = sin(0.5*theta);
   wpr = -2.0*wtemp*wtemp;
   wpi = sin(theta);
   wr = 1.0;
   wi = 0.0;
   for (m=1; m < mmax; m += 2)
    {
     for (i=m; i <= n; i += istep)
      {
       j=i+mmax;
       tempr = wr*data[j-1] - wi*data[j];
       tempi = wr * data[j] + wi*data[j-1];
       
       data[j-1] = data[i-1] - tempr;
       data[j] = data[i] - tempi;
       data[i-1] += tempr;
       data[i] += tempi;
      }
     wtemp=wr;
     wr += wr*wpr - wi*wpi;
     wi += wi*wpr + wtemp*wpi;
    }
   
   mmax=istep;
   
  } // while (n>mmax)
 
}

// ===================================================================
// Fills the matrix that performs the transformation from angular
// velocities to Euler-rates
// ===================================================================
void fill_angular_velocities_to_euler_rates_matrix(std::vector<std::vector<double> > &A,
                                                   std::vector<double> &euler_angles)
{
 // New variable names
 const double phi = euler_angles[0];
 const double theta = euler_angles[1];
 // Get trigonometric function values
 const double sin_phi = sin(phi);
 const double cos_phi = cos(phi);
 const double sec_theta = 1.0/cos(theta);
 const double tan_theta = tan(theta);
 
 // Fill the matrix
 A[0][0] = 1.0;
 A[0][1] = sin_phi * tan_theta;
 A[0][2] = cos_phi * tan_theta;
 A[1][0] = 0.0;
 A[1][1] = cos_phi;
 A[1][2] = -sin_phi;
 A[2][0] = 0.0;
 A[2][1] = sin_phi*sec_theta;
 A[2][2] = cos_phi*sec_theta;
}

#ifdef ROTATION_MATRIX_YAW_PITCH_ROLL
// ===================================================================
// Fills the matrices that transform from the inertial frame to the
// body frame
// ===================================================================
void fill_rotation_matrices(std::vector<std::vector<double> > &R,
                            std::vector<std::vector<double> > &R_t,
                            const double theta_x,
                            const double theta_y,
                            const double theta_z)
{
 const double sin_theta_x = sin(theta_x);
 const double sin_theta_y = sin(theta_y);
 const double sin_theta_z = sin(theta_z);
 const double cos_theta_x = cos(theta_x);
 const double cos_theta_y = cos(theta_y);
 const double cos_theta_z = cos(theta_z);
 
 R[0][0] = cos_theta_y*cos_theta_z;
 R[0][1] = cos_theta_y*sin_theta_z;
 R[0][2] = -sin_theta_y;
 
 R[1][0] = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
 R[1][1] = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
 R[1][2] = sin_theta_x*cos_theta_y;
 
 R[2][0] = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
 R[2][1] = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
 R[2][2] = cos_theta_x*cos_theta_y;
 
 R_t[0][0] = R[0][0];
 R_t[0][1] = R[1][0];
 R_t[0][2] = R[2][0];
 
 R_t[1][0] = R[0][1];
 R_t[1][1] = R[1][1];
 R_t[1][2] = R[2][1];
 
 R_t[2][0] = R[0][2];
 R_t[2][1] = R[1][2];
 R_t[2][2] = R[2][2];
}
#endif // #ifdef ROTATION_MATRIX_YAW_PITCH_ROLL

#ifdef ROTATION_MATRIX_ROLL_PITCH_YAW
// ===================================================================
// Fills the matrices that transform from the inertial frame to the
// body frame
// ===================================================================
void fill_rotation_matrices(std::vector<std::vector<double> > &R,
                            std::vector<std::vector<double> > &R_t,
                            const double theta_x,
                            const double theta_y,
                            const double theta_z)
{
 const double sin_theta_x = sin(theta_x);
 const double sin_theta_y = sin(theta_y);
 const double sin_theta_z = sin(theta_z);
 const double cos_theta_x = cos(theta_x);
 const double cos_theta_y = cos(theta_y);
 const double cos_theta_z = cos(theta_z);
 
 R[0][0] = cos_theta_y*cos_theta_z;
 R[0][1] = sin_theta_x*sin_theta_y*cos_theta_z+cos_theta_x*sin_theta_z;
 R[0][2] = sin_theta_x*sin_theta_z-cos_theta_x*sin_theta_y*cos_theta_z;
 
 R[1][0] = -cos_theta_y*sin_theta_z;
 R[1][1] = cos_theta_x*cos_theta_z-sin_theta_x*sin_theta_y*sin_theta_z;
 R[1][2] = cos_theta_x*sin_theta_y*sin_theta_z+sin_theta_x*cos_theta_z;
 
 R[2][0] = sin_theta_y;
 R[2][1] = -sin_theta_x*cos_theta_y;
 R[2][2] = cos_theta_x*cos_theta_y;
 
 R_t[0][0] = R[0][0];
 R_t[0][1] = R[1][0];
 R_t[0][2] = R[2][0];
 
 R_t[1][0] = R[0][1];
 R_t[1][1] = R[1][1];
 R_t[1][2] = R[2][1];
 
 R_t[2][0] = R[0][2];
 R_t[2][1] = R[1][2];
 R_t[2][2] = R[2][2];
}
#endif // #ifdef ROTATION_MATRIX_ROLL_PITCH_YAW

// ===================================================================
// Multiply a matrix by a vector
// ===================================================================
void multiply_matrix_times_vector(std::vector<std::vector<double> > &A,
                                  std::vector<double> &b,
                                  std::vector<double> &x)
{
 // Get the size of the matrix
 const unsigned n_rows_A = A.size(); 
 const unsigned n_cols_A = A[0].size();
 // Get the size of the input vector
 const unsigned n_rows_b = b.size();
 // Check that we can multiply
 if (n_cols_A != n_rows_b)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "We can not multiply, the input matrix has dimension ("
                 << n_rows_A << ", " << n_cols_A << ")" << std::endl;
   error_message << "The input vector has dimension dimension ("
                 << n_rows_b << ", 1)" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Get the size of the output vector
 const unsigned n_rows_x = x.size();
 // Check that we can multiply
 if (n_rows_A != n_rows_x)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "We can not muliply, the input matrix has dimension ("
                 << n_rows_A << ", " << n_cols_A << ")" << std::endl;
   error_message << "The output vector has dimension dimension ("
                 << n_rows_x << ", 1)" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Clear the vector x
 x.clear();
 x.resize(n_rows_x, 0.0);
 // Do the multiplication
 for (unsigned i = 0; i < n_rows_A; i++)
  {
   for (unsigned j = 0; j < n_cols_A; j++)
    {
     x[i]+= A[i][j] * b[j];
    } // for (j < n_cols_A)
   
  } // for (i < n_rows_A)
 
}

// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Initialise chapchom
 initialise_chapchom();
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 // The ode's
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/Cadenas_GNSS.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_1_espera.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_2_sin_espera_basura.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_3_sin_espera_sin_basura.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_4_sin_espera_sin_basura_final.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_5_espera_large.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_6_espera_large.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_7_espera_large.dat");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_8_car_ride_square_wait_large.dat");
 CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_9_car_ride_tona_acatepec_inaoe_wait_large.dat");
 // Create the factory for the methods
 CCFactoryIntegrationMethod *factory_integration_methods =
  new CCFactoryIntegrationMethod();
 // Create an instance of the integrator method
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("Euler");
 //ACIntegrationMethod *integrator =
 // factory_integration_methods->create_integration_method("RK4");
 // Get the number of history values required by the integration
 // method
 const unsigned n_history_values = integrator->n_history_values();
 // Get the number of odes
 const unsigned n_odes = odes.nodes();
 // Storage for the values of the function (plus one history value to
 // store the current one)
 std::vector<std::vector<double> > y(n_history_values+1);
 // Resize container for the number of odes
 for (unsigned i = 0; i < n_history_values+1; i++)
  {
   y[i].resize(n_odes);
  }
 
 // ----------------------------------------------------------------------------
 // FILES (BEGIN)
 // ----------------------------------------------------------------------------
 // Position
 char file_position_name[100];
 sprintf(file_position_name, "./RESLT/position.dat");
 std::ofstream outfile_position;
 outfile_position.open(file_position_name, std::ios::out);
 if (outfile_position.fail()) 
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_position_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Velocity
 char file_velocity_name[100];
 sprintf(file_velocity_name, "./RESLT/velocity.dat");
 std::ofstream outfile_velocity;
 outfile_velocity.open(file_velocity_name, std::ios::out);
 if (outfile_velocity.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_velocity_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // North-East velocity
 char file_north_east_velocity_name[100];
 sprintf(file_north_east_velocity_name, "./RESLT/north_east_velocity.dat");
 std::ofstream outfile_north_east_velocity;
 outfile_north_east_velocity.open(file_north_east_velocity_name, std::ios::out);
 if (outfile_north_east_velocity.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_north_east_velocity_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Raw gyro
 char file_raw_gyro_name[100];
 sprintf(file_raw_gyro_name, "./RESLT/raw_gyro.dat");
 std::ofstream outfile_raw_gyro;
 outfile_raw_gyro.open(file_raw_gyro_name, std::ios::out);
 if (outfile_raw_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Euler-angles rates
 char file_euler_angles_rates_name[100];
 sprintf(file_euler_angles_rates_name, "./RESLT/euler_angles_rates.dat");
 std::ofstream outfile_euler_angles_rates;
 outfile_euler_angles_rates.open(file_euler_angles_rates_name, std::ios::out);
 if (outfile_euler_angles_rates.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_euler_angles_rates_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Raw accelerations
 char file_raw_accelerations_name[100];
 sprintf(file_raw_accelerations_name, "./RESLT/raw_accelerations.dat");
 std::ofstream outfile_raw_acc;
 outfile_raw_acc.open(file_raw_accelerations_name, std::ios::out);
 if (outfile_raw_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_accelerations_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
#ifdef GRAVITY_TO_BODY_FRAME
 // Body frame gravity
 char file_body_frame_gravity_name[100];
 sprintf(file_body_frame_gravity_name, "./RESLT/body_frame_gravity.dat");
 std::ofstream outfile_body_frame_gravity;
 outfile_body_frame_gravity.open(file_body_frame_gravity_name, std::ios::out);
 if (outfile_body_frame_gravity.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_body_frame_gravity_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef GRAVITY_TO_BODY_FRAME
 
 // Inertial accelerations
 char file_inertial_accelerations_name[100];
 sprintf(file_inertial_accelerations_name, "./RESLT/inertial_accelerations.dat");
 std::ofstream outfile_inertial_acc;
 outfile_inertial_acc.open(file_inertial_accelerations_name, std::ios::out);
 if (outfile_inertial_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_inertial_accelerations_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }

 // Roll, pitch and yaw
 char file_roll_pitch_yaw_name[100];
 sprintf(file_roll_pitch_yaw_name, "./RESLT/roll_pitch_yaw.dat");
 std::ofstream outfile_roll_pitch_yaw;
 outfile_roll_pitch_yaw.open(file_roll_pitch_yaw_name, std::ios::out);
 if (outfile_roll_pitch_yaw.fail()) 
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }

 // -----------------------------------
 // GPS DATA [BEGIN]
 // -----------------------------------
 // True course in degrees
 char file_true_course_in_degrees_name[100];
 sprintf(file_true_course_in_degrees_name, "./RESLT/true_course_in_degrees.dat");
 std::ofstream outfile_true_course_in_degrees;
 outfile_true_course_in_degrees.open(file_true_course_in_degrees_name, std::ios::out);
 if (outfile_true_course_in_degrees.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_true_course_in_degrees_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Speed in knots
 char file_speed_in_knots_name[100];
 sprintf(file_speed_in_knots_name, "./RESLT/speed_in_knots.dat");
 std::ofstream outfile_speed_in_knots;
 outfile_speed_in_knots.open(file_speed_in_knots_name, std::ios::out);
 if (outfile_speed_in_knots.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_speed_in_knots_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Speed in m/s
 char file_speed_in_m_per_sec_name[100];
 sprintf(file_speed_in_m_per_sec_name, "./RESLT/speed_in_m_per_sec.dat");
 std::ofstream outfile_speed_in_m_per_sec;
 outfile_speed_in_m_per_sec.open(file_speed_in_m_per_sec_name, std::ios::out);
 if (outfile_speed_in_m_per_sec.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_speed_in_m_per_sec_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Acceleration from speed in m/s from GPS
 char file_acc_from_speed_in_m_per_sec_from_GPS_name[100];
 sprintf(file_acc_from_speed_in_m_per_sec_from_GPS_name, "./RESLT/acc_from_speed_in_m_per_sec_from_GPS.dat");
 std::ofstream outfile_acc_from_speed_in_m_per_sec_from_GPS;
 outfile_acc_from_speed_in_m_per_sec_from_GPS.open(file_acc_from_speed_in_m_per_sec_from_GPS_name, std::ios::out);
 if (outfile_acc_from_speed_in_m_per_sec_from_GPS.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_acc_from_speed_in_m_per_sec_from_GPS_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // -----------------------------------
 // GPS DATA [END]
 // -----------------------------------
 
 // Roll, pitch and yaw from accelerations
 char file_roll_pitch_yaw_from_acc_name[100];
 sprintf(file_roll_pitch_yaw_from_acc_name, "./RESLT/roll_pitch_yaw_from_acc.dat");
 std::ofstream outfile_roll_pitch_yaw_from_acc;
 outfile_roll_pitch_yaw_from_acc.open(file_roll_pitch_yaw_from_acc_name, std::ios::out);
 if (outfile_roll_pitch_yaw_from_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_from_acc_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Filtered gyro
 char file_filtered_gyro_name[100];
 sprintf(file_filtered_gyro_name, "./RESLT/filtered_gyro.dat");
 std::ofstream outfile_filtered_gyro;
 outfile_filtered_gyro.open(file_filtered_gyro_name, std::ios::out);
 if (outfile_filtered_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_filtered_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Filtered acc
 char file_filtered_acc_name[100];
 sprintf(file_filtered_acc_name, "./RESLT/filtered_acc.dat");
 std::ofstream outfile_filtered_acc;
 outfile_filtered_acc.open(file_filtered_acc_name, std::ios::out);
 if (outfile_filtered_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_filtered_acc_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // ----------------------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------------------
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (steps, h, initial
 // values)
 // -----------------------------------------------------------------
 // The step size is given by the number of data we have in a second
 // (15Hz)
 double h = 1.0/15.0;
 
 // Current time
 double time = 0.0;
 
 // Matrix that relates the angular velocities with the Euler rates
 std::vector<std::vector<double> >A(DIM);
 for (unsigned i = 0; i < DIM; i++)
  {
   A[i].resize(DIM);
  }
 
#ifdef APPLY_CONVOLUTION
 // The coefficients of the kernel signal to convolve with the
 // gyro data
 const unsigned n_kernel_gyro = 15;
 double kernel_gyro[] = {0.0102773244275157,	0.0162263834264182,	0.0328881753317823,	0.0570814837334001,	0.0840520641122108,	0.108434325903213,	0.125345958994944,	0.131388568141032,	0.125345958994944,	0.108434325903213,	0.0840520641122108,	0.0570814837334001,	0.0328881753317823,	0.0162263834264182,	0.0102773244275157};
#if 0
 const unsigned n_kernel_gyro = 29;
 double kernel_gyro[] = {0.00487565085802581,	0.00565023695447273,	0.00784203640693326,	0.0113870199555086,	0.0161430039027124,	0.0218963011150810,	0.0283726853564105,	0.0352520707992509,	0.0421860734791161,	0.0488174359593725,	0.0548001727490465,	0.0598192403672874,	0.0636085562411190,	0.0659662840046496,	0.0667664637020275,	0.0659662840046496,	0.0636085562411190,	0.0598192403672874,	0.0548001727490465,	0.0488174359593725,	0.0421860734791161,	0.0352520707992509,	0.0283726853564105,	0.0218963011150810,	0.0161430039027124,	0.0113870199555086,	0.00784203640693326,	0.00565023695447273,	0.00487565085802581};
#endif // #if 0
 
 // The coefficients of the kernel signal to convolve with the
 // accelerometer data
 const unsigned n_kernel_acc = 15;
 double kernel_acc[] = {0.0104226000635011,	0.0163818874099687,	0.0330775506149548,	0.0572325417966930,	0.0840719974006429,	0.108274081298100,	0.125032039259642,	0.131014604312996,	0.125032039259642,	0.108274081298100,	0.0840719974006429,	0.0572325417966930,	0.0330775506149548,	0.0163818874099687,	0.0104226000635011};
#if 0
 const unsigned n_kernel_acc = 29;
 double kernel_acc[] = {0.00516516454302776,	0.00592820768243009,	0.00815503499250421,	0.0117456327507358,	0.0165288970204929,	0.0222711447846357,	0.0286879389594637,	0.0354586185100425,	0.0422427786903709,	0.0486978400932577,	0.0544967845816832,	0.0593451246895173,	0.0629962114730087,	0.0652640721110309,	0.0660330982355974,	0.0652640721110309,	0.0629962114730087,	0.0593451246895173,	0.0544967845816832,	0.0486978400932577,	0.0422427786903709,	0.0354586185100425,	0.0286879389594637,	0.0222711447846357,	0.0165288970204929,	0.0117456327507358,	0.00815503499250421,	0.00592820768243009,	0.00516516454302776};
#endif // #if 0
#endif // #ifdef APPLY_CONVOLUTION
 
 // -----------------------------------------------------------------------------
 // Initialise
 // -----------------------------------------------------------------------------
 
 // Initial conditions
 y[0][0] = 0.0; // Initial x-position
 y[0][1] = 0.0; // Initial x-velocity
 y[0][2] = 0.0; // Initial y-position
 y[0][3] = 0.0; // Initial y-velocity
 y[0][4] = 0.0; // Initial z-position
 y[0][5] = 0.0; // Initial z-velocity
 // The data are in radians
 y[0][6] = 0.0; // Initial roll
 y[0][7] = 0.0; // Initial pitch
 //y[0][8] = 130.0*TO_RADIANS; // Initial yaw
 y[0][8] = 0.0; // Initial yaw
 
 // Flag to indicate whether to correct yaw or not. Used once we have
 // heading information to initialise the value of yaw and to perform
 // corrections of yaw when the value is out of range
 bool correct_yaw = true;
 
 // Output the initial data to screen
 std::cout << "t: " << time
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
           << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
 
 // Flag to indicate whether to continue looping
 bool LOOP = true;
 
 // The vectors store the lectures from gyro and accelerometer. The
 // number of non processed data indicates the starting position of
 // the data at the current lecture. Any data before
 // "n_non_processed_data" must be interpreted as previous time
 // information, only used at the convolution stage
 unsigned n_non_processed_data = 0;
 
 // Storage for the lectures from accelerometers and gyros
 double signal_acc_x[MAX_SIGNAL_SIZE];
 double signal_acc_y[MAX_SIGNAL_SIZE];
 double signal_acc_z[MAX_SIGNAL_SIZE];
 double signal_gyro_x[MAX_SIGNAL_SIZE];
 double signal_gyro_y[MAX_SIGNAL_SIZE];
 double signal_gyro_z[MAX_SIGNAL_SIZE];
 // Initialise to zero
 for (unsigned i = 0; i < MAX_SIGNAL_SIZE; i++)
  {
   signal_acc_x[i] = 0.0;
   signal_acc_y[i] = 0.0;
   signal_acc_z[i] = 0.0;
   signal_gyro_x[i] = 0.0;
   signal_gyro_y[i] = 0.0;
   signal_gyro_z[i] = 0.0;
  }
 
 // The matrices to rotate the inertial sensors' measurements to the
 // device coordinate system
 const double angle_to_rotate_gyro = -M_PI/2.0;
 std::vector<std::vector<double> > rotation_matrix_gyro(3);
 for (unsigned i = 0; i < DIM; i++)
  {
   rotation_matrix_gyro[i].resize(3);
  }
 rotation_matrix_gyro[0][0] = cos(angle_to_rotate_gyro);
 rotation_matrix_gyro[0][1] = sin(angle_to_rotate_gyro);
 rotation_matrix_gyro[0][2] = 0.0;
 rotation_matrix_gyro[1][0] = -sin(angle_to_rotate_gyro);
 rotation_matrix_gyro[1][1] = cos(angle_to_rotate_gyro);
 rotation_matrix_gyro[1][2] = 0.0;
 rotation_matrix_gyro[2][0] = 0.0;
 rotation_matrix_gyro[2][1] = 0.0;
 rotation_matrix_gyro[2][2] = 1.0;
 
 const double angle_to_rotate_acc = -M_PI;
 std::vector<std::vector<double> > rotation_matrix_acc(3);
 for (unsigned i = 0; i < DIM; i++)
  {
   rotation_matrix_acc[i].resize(3);
  } 
 rotation_matrix_acc[0][0] = cos(angle_to_rotate_acc);
 rotation_matrix_acc[0][1] = sin(angle_to_rotate_acc);
 rotation_matrix_acc[0][2] = 0.0;
 rotation_matrix_acc[1][0] = -sin(angle_to_rotate_acc);
 rotation_matrix_acc[1][1] = cos(angle_to_rotate_acc);
 rotation_matrix_acc[1][2] = 0.0;
 rotation_matrix_acc[2][0] = 0.0;
 rotation_matrix_acc[2][1] = 0.0;
 rotation_matrix_acc[2][2] = 1.0;
 
#ifdef COMPUTE_ACC_FROM_GPS_VELOCITY
 double previous_speed_in_m_per_sec = 0.0;
#endif // #ifdef COMPUTE_ACC_FROM_GPS_VELOCITY
 
 while (LOOP)
  {
   // Retrieve data from sensors
   LOOP = odes.get_sensors_lectures(); // tachidok
   if (!LOOP)
    {
     break;
    }
   
   // Get the number of acceleration data
   const unsigned n_acc_data = odes.nacceleration_data(); 
   // Double check that we have the same number of data for
   // accelerations and gyros
   const unsigned n_gyro_data = odes.ngyro_data();
   if (n_acc_data != n_gyro_data)
    {
     // Error message
     std::ostringstream error_message;
     error_message << "The number of data from the accelerometer and the gyro are different\n"
                   << "n_acc_data: " << n_acc_data << "\n"
                   << "n_gyro_data: " << n_gyro_data << "\n"
                   << std::endl;
     throw ChapchomLibError(error_message.str(),
                            CHAPCHOM_CURRENT_FUNCTION,
                            CHAPCHOM_EXCEPTION_LOCATION);
    }
#ifdef GYRO_AVERAGE
   std::vector<double> gyro_average(DIM, 0.0);
#endif // #ifdef GYRO_AVERAGE
#ifdef ACCELEROMETER_AVERAGE
   std::vector<double> acc_average(DIM, 0.0);
#endif // #ifdef ACCELEROMETER_AVERAGE
   
   // ------------------------------------------------------------------
   // Read and filter data
   // ------------------------------------------------------------------
#ifdef OLD_IMPLEMENTATION
   // Copy the data into a 3x3 vector
   std::vector<std::vector<double> > gyro(n_gyro_data);
   // Copy the data into a 3x3 vector
   std::vector<std::vector<double> > acc(n_acc_data);
#endif // #ifdef OLD_IMPLEMENTATION
   
   // Check whether there is enough space in the vector to store the
   // current time data
   if (n_non_processed_data + n_acc_data > MAX_SIGNAL_SIZE)
    {
     // Error message
     std::ostringstream error_message;
     error_message << "The number of data in the buffer plus the number of\n"
                   << "data from the current lecture is larger that the maximum\n"
                   << "signal buffer size\n"
                   << "n_non_processed_data: " << n_non_processed_data << "\n"
                   << "n_acc_data: " << n_acc_data << "\n"
                   << "n_non_processed_data + n_acc_data: " << n_non_processed_data +  n_acc_data << "\n"
                   << "MAX_SIGNAL_SIZE: " << MAX_SIGNAL_SIZE << "\n"
                   << std::endl;
     throw ChapchomLibError(error_message.str(),
                            CHAPCHOM_CURRENT_FUNCTION,
                            CHAPCHOM_EXCEPTION_LOCATION);
    }
   
   // Initial time at reading stage
   double time_read_stage = time;
   // The step size is given by the number of data reported in a second
   const double h_read_stage = 1.0 / n_acc_data;
   // Get heading information
   const double true_course_in_degrees = odes.true_course_in_degrees();
   const double true_course_in_radians = true_course_in_degrees * TO_RADIANS;
   // Get speed in knots
   const double speed_in_knots = odes.speed_in_knots();
   const double speed_in_m_per_sec = speed_in_knots*0.514444;
   
   for (unsigned i = 0; i < n_acc_data; i++)
    {
#ifdef OLD_IMPLEMENTATION
     // Resize containers
     gyro[i].resize(DIM);
     acc[i].resize(DIM);
#endif // #ifdef OLD_IMPLEMENTATION
     // Get the current reading from sensors
     std::vector<double> gyro_t = odes.get_angular_rates(i);
     std::vector<double> acc_t = odes.get_accelerations(i);
     
     const unsigned current_data_index = i+n_non_processed_data;
     // ---------------------------------------------------
     // Gyro
     // ---------------------------------------------------
     signal_gyro_x[current_data_index] = gyro_t[1];
     signal_gyro_y[current_data_index] = gyro_t[2];
     signal_gyro_z[current_data_index] = gyro_t[3];
     
#ifdef GYRO_THRESHOLD
     if (fabs(signal_gyro_x[current_data_index]) < GYRO_THRESHOLD)
      {
       signal_gyro_x[current_data_index] = 0.0;
      }
     
     if (fabs(signal_gyro_y[current_data_index]) < GYRO_THRESHOLD)
      {
       signal_gyro_y[current_data_index] = 0.0;
      }
     
     if (fabs(signal_gyro_z[current_data_index]) < GYRO_THRESHOLD)
      {
       signal_gyro_z[current_data_index] = 0.0;
      }
#endif // #ifdef GYRO_THRESHOLD
     
     // ---------------------------------------------------
     // Accelerations
     // ---------------------------------------------------
     
     // Multiply by 9.81 since the data from the gyro are given in 'g'
     // units
     signal_acc_x[current_data_index] = acc_t[1] * GRAVITY;
     signal_acc_y[current_data_index] = acc_t[2] * GRAVITY;
     signal_acc_z[current_data_index] = acc_t[3] * GRAVITY;
     
#ifdef OLD_IMPLEMENTATION
     for (unsigned j = 0; j < DIM; j++)
      {
       // ---------------------------------------------------
       // Gyro
       // ---------------------------------------------------       
       gyro[i][j] = gyro_t[j+1];
#ifdef GYRO_THRESHOLD
       if (fabs(gyro[i][j]) < GYRO_THRESHOLD)
        {
         gyro[i][j] = 0.0;
        }
#endif // #ifdef GYRO_THRESHOLD
#ifdef GYRO_AVERAGE
       gyro_average[j]+=gyro[i][j];
       gyro[i][j]=gyro_average[j]/static_cast<double>(i+1);
#endif // #ifdef GYRO_AVERAGE
       
       //gyro[i][j] = 0.0;
# if 0 // TODO: tachidok, what if we set the yaw data to 0.0 dps
       if (j == 2)
        {
         gyro[i][j] = 0.0;
        }
#endif
       
       // ---------------------------------------------------
       // Accelerations
       // ---------------------------------------------------
       
       // Multiply by 9.81 since the data from the gyro are given in
       // 'g' units       
       acc[i][j] = acc_t[j+1] * GRAVITY;
       
#ifdef OLD_IMPLEMENTATION
       
#ifdef ACCELERATION_THRESHOLD
       if (fabs(acc[i][j]) < ACCELERATION_THRESHOLD)
        {
         acc[i][j] = 0.0;
        }
#endif // #ifdef ACCELERATION_THRESHOLD
       
#ifdef ACCELEROMETER_AVERAGE
       acc_average[j]+=acc[i][j];
       acc[i][j]=acc_average[j]/static_cast<double>(i+1);
#endif // #ifdef ACCELEROMETER_AVERAGE
       
#endif // #ifdef OLD_IMPLEMENTATION
       
      } // for (j < DIM)
     
#ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     // Correct accelerations due to misalignment on device
     {
      const double tmp = -acc[i][0];
      acc[i][0] = acc[i][1];
      acc[i][1] = tmp;
     }
#endif // #ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     
#endif // #ifdef OLD_IMPLEMENTATION
     
#ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     // Correct accelerations due to misalignment on device
     {
      const double tmp = -signal_acc_x[current_data_index];
      signal_acc_x[current_data_index] = signal_acc_y[current_data_index];
      signal_acc_y[current_data_index] = tmp;
     }
#endif // #ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     
#ifdef CORRECT_INERTIAL_SENSORES_MISALIGNMENT
     std::vector<double> misaligned_gyro_vector(DIM);
     misaligned_gyro_vector[0] = signal_gyro_x[current_data_index];
     misaligned_gyro_vector[1] = signal_gyro_y[current_data_index];
     misaligned_gyro_vector[2] = signal_gyro_z[current_data_index];
     std::vector<double> aligned_gyro_vector(DIM);
     multiply_matrix_times_vector(rotation_matrix_gyro,
                                  misaligned_gyro_vector,
                                  aligned_gyro_vector);
     signal_gyro_x[current_data_index] = aligned_gyro_vector[0];
     signal_gyro_y[current_data_index] = aligned_gyro_vector[1];
     signal_gyro_z[current_data_index] = aligned_gyro_vector[2];
     
     std::vector<double> misaligned_acc_vector(DIM);
     misaligned_acc_vector[0] = signal_acc_x[current_data_index];
     misaligned_acc_vector[1] = signal_acc_y[current_data_index];
     misaligned_acc_vector[2] = signal_acc_z[current_data_index];
     std::vector<double> aligned_acc_vector(DIM);
     multiply_matrix_times_vector(rotation_matrix_acc,
                                  misaligned_acc_vector,
                                  aligned_acc_vector);
     signal_acc_x[current_data_index] = aligned_acc_vector[0];
     signal_acc_y[current_data_index] = aligned_acc_vector[1];
     signal_acc_z[current_data_index] = aligned_acc_vector[2];
     
#endif // #ifdef CORRECT_INERTIAL_SENSORES_MISALIGNMENT
     
     // Increase the time at the reading stage
     time_read_stage+=h_read_stage;
     
     // -----------------
     // Output data
     // -----------------
     
     // Raw gyro
     outfile_raw_gyro << time_read_stage
                      << " " << signal_gyro_x[current_data_index]
                      << " " << signal_gyro_y[current_data_index]
                      << " " << signal_gyro_z[current_data_index] << std::endl;
     // Raw accelerations
     outfile_raw_acc << time_read_stage
                     << " " << signal_acc_x[current_data_index]
                     << " " << signal_acc_y[current_data_index]
                     << " " << signal_acc_z[current_data_index] << std::endl;
     
#ifdef OLD_IMPLEMENTATION
     // Raw gyro
     outfile_raw_gyro << time_read_stage
                      << " " << gyro[i][0]
                      << " " << gyro[i][1]
                      << " " << gyro[i][2] << std::endl;
     // Raw accelerations
     outfile_raw_acc << time_read_stage
                     << " " << acc[i][0]
                     << " " << acc[i][1]
                     << " " << acc[i][2] << std::endl;
#endif // #ifdef OLD_IMPLEMENTATION
     
    } // for (i < n_acc_data)
   
   // Set the signal size
   const unsigned n_signal = n_non_processed_data + n_acc_data;
   
   // ------------------------------------------------------
   // Apply low pass filter to gyro and acceleration data
   // ------------------------------------------------------
   
#ifdef APPLY_CONVOLUTION
   // The size fo the convolved signal (how many times does the kernel
   // fits into the complete signal)
   const int n_filtered_signal_gyro = n_signal - n_kernel_gyro + 1;
   
   //const unsigned n_filtered_signal_gyro = n_gyro_data + n_kernel_gyro - 1;
   // Filtered data for gyro after convolution
   double *filtered_signal_gyro_x;
   double *filtered_signal_gyro_y;
   double *filtered_signal_gyro_z;
   bool apply_convolution_gyro = false;
   if (n_filtered_signal_gyro > 0)
    {
     apply_convolution_gyro = true;
     // Gyro x-signal
     filtered_signal_gyro_x = new double[n_filtered_signal_gyro];
     // Gyro y-signal
     filtered_signal_gyro_y = new double[n_filtered_signal_gyro];
     // Gyro z-signal
     filtered_signal_gyro_z = new double[n_filtered_signal_gyro];
     
     // Convolve x-signal
     convolve_use_non_processed_data(signal_gyro_x, n_signal,
                                     kernel_gyro, n_kernel_gyro,
                                     filtered_signal_gyro_x,
                                     n_filtered_signal_gyro);
     // Convolve y-signal
     convolve_use_non_processed_data(signal_gyro_y, n_signal,
                                     kernel_gyro, n_kernel_gyro,
                                     filtered_signal_gyro_y,
                                     n_filtered_signal_gyro);
     // Convolve z-signal
     convolve_use_non_processed_data(signal_gyro_z, n_signal,
                                     kernel_gyro, n_kernel_gyro,
                                     filtered_signal_gyro_z,
                                     n_filtered_signal_gyro);
    }
   
   // The size fo the convolved signal (how many times does the kernel
   // fits into the complete signal)
   const int n_filtered_signal_acc = n_signal - n_kernel_acc + 1;
   //const unsigned n_filtered_signal_acc = n_acc_data + n_kernel_acc - 1;
   // Filtered data for accelerometers after convolution
   double *filtered_signal_acc_x;
   double *filtered_signal_acc_y;
   double *filtered_signal_acc_z;
   bool apply_convolution_acc = false;
   if (n_filtered_signal_acc > 0)
    {
     apply_convolution_acc = true;
     // Acc x-signal
     filtered_signal_acc_x = new double[n_filtered_signal_acc];
     // Acc y-signal
     filtered_signal_acc_y = new double[n_filtered_signal_acc];
     // Acc z-signal
     filtered_signal_acc_z = new double[n_filtered_signal_acc];
     
     // Convolve x-signal
     convolve_use_non_processed_data(signal_acc_x, n_signal,
                                     kernel_acc, n_kernel_acc,
                                     filtered_signal_acc_x,
                                     n_filtered_signal_acc);
     // Convolve y-signal
     convolve_use_non_processed_data(signal_acc_y, n_signal,
                                     kernel_acc, n_kernel_acc,
                                     filtered_signal_acc_y,
                                     n_filtered_signal_acc);
     // Convolve z-signal
     convolve_use_non_processed_data(signal_acc_z, n_signal,
                                     kernel_acc, n_kernel_acc,
                                     filtered_signal_acc_z,
                                     n_filtered_signal_acc);
    }
   
#endif // #ifdef APPLY_CONVOLUTION
   
#ifdef OLD_IMPLEMENTATION
   
#ifdef APPLY_CONVOLUTION
   // Store the gyro-filtered data
   //std::vector<std::vector<double> > gyro_filtered(n_gyro_data + n_kernel_gyro - 1);
   unsigned n_filtered_gyro_data = 0;
   bool apply_convolution_gyro = false;
   if (n_gyro_data >= n_kernel_gyro)
    {
     apply_convolution_gyro = true;
     n_filtered_gyro_data = n_gyro_data - n_kernel_gyro + 1;
    }
   else
    {
     n_filtered_gyro_data = 1;
    }
   
   // Create the vector of data
   std::vector<std::vector<double> > gyro_filtered(n_filtered_gyro_data);
    // Convolve?
   if (apply_convolution_gyro)
    {     
     convolve_modified(gyro, kernel_gyro, n_kernel_gyro, gyro_filtered);
     //convolve(gyro, kernel_gyro, n_kernel_gyro, gyro_filtered);
    }
   else
    {
     average(gyro, gyro_filtered);
    }
   
   // Store the acc-filtered data
   //std::vector<std::vector<double> > acc_filtered(n_acc_data + n_kernel_acc - 1);
   unsigned n_filtered_acc_data = 0;
   bool apply_convolution_acc = false;
   if (n_acc_data >= n_kernel_acc)
    {
     apply_convolution_acc = true;
     n_filtered_acc_data = n_acc_data - n_kernel_acc + 1;
    }
   else
    {
     n_filtered_acc_data = 1;
    }
   
   // Create the vector of data
   std::vector<std::vector<double> > acc_filtered(n_filtered_acc_data);
   // Convolve?
   if (apply_convolution_acc)
    {
     convolve_modified(acc, kernel_acc, n_kernel_acc, acc_filtered);
     //convolve(acc, kernel_acc, n_kernel_acc, acc_filtered);
    }
   else
    {
     average(acc, acc_filtered);
    }
#else
   // Store the gyro-filtered data
   std::vector<std::vector<double> > gyro_filtered(n_gyro_data);
   // Store the acc-filtered data
   std::vector<std::vector<double> > acc_filtered(n_acc_data);
   const double sample_rate = 15;
   const double cut_off_frequency_gyro = 0.1;
   const double cut_off_frequency_acc = 0.01;
   // Apply the filter
   low_pass_filter_frequency(gyro, gyro_filtered, cut_off_frequency_gyro, sample_rate);
   low_pass_filter_frequency(acc, acc_filtered, cut_off_frequency_acc, sample_rate);
#endif // #ifdef APPLY_CONVOLUTION
   
#endif // #ifdef OLD_IMPLEMENTATION
   
   bool applied_convolution = apply_convolution_gyro || apply_convolution_acc;
   
   // Delete the processed data and move the non processed data to the
   // beginning of the array
   if (applied_convolution)
    {
     // Set the number of processed data
     unsigned counter = 0;
     for (unsigned i = n_filtered_signal_gyro; i < n_signal; i++)
      {
       signal_gyro_x[counter] = signal_gyro_x[i];
       signal_gyro_y[counter] = signal_gyro_y[i];
       signal_gyro_z[counter] = signal_gyro_z[i];
       counter++;
      }
     
     n_non_processed_data = counter;
     
    }
   else
    {
     n_non_processed_data+=n_gyro_data;
    }
   
   if (applied_convolution)
    {
     // Set the number of processed data
     unsigned counter = 0;
     for (unsigned i = n_filtered_signal_acc; i < n_signal; i++)
      {
       signal_acc_x[counter] = signal_acc_x[i];
       signal_acc_y[counter] = signal_acc_y[i];
       signal_acc_z[counter] = signal_acc_z[i];
       counter++;
      }
     
     n_non_processed_data = counter;
     
    }
   else
    {
     n_non_processed_data+=n_acc_data;
    }
   
   // The following steps are only performed if convolution was applied
   if (applied_convolution)
    {
     // The step size is given by the number of data reported in a second
     h  = 1.0 / static_cast<double>(n_filtered_signal_acc);
     //DEB(n_filtered_signal_acc);
     //h = 1.0 / 15.0;
     
     // Process data
     for (unsigned i = 0; i < static_cast<unsigned>(n_filtered_signal_acc); i++)
      {
       // ----------------------------------------------------------
       // ----------------------------------------------------------
       // Process the gyros data
       // ----------------------------------------------------------
       // ----------------------------------------------------------
       
       // --------------------------
       // Get the Euler angles
       // --------------------------
       // Store the Euler-angles
       std::vector<double> euler_angles(DIM);
       euler_angles[0] = y[0][6];
       euler_angles[1] = y[0][7];
       //euler_angles[2] = true_course_in_degrees * TO_RADIANS; // tachidok, no matter what this value is, it is not used in the calculations, oh!
       euler_angles[2] = y[0][8]; // tachidok, no matter what this value is, it is not used in the calculations, oh!
       //euler_angles[2] = 0.0; // tachidok, no matter what this value is, it is not used in the calculations, oh!
       
       // Fill the matrix that transforms from angular velocities to
       // Euler-rates
       fill_angular_velocities_to_euler_rates_matrix(A, euler_angles);
       
       // Store the Euler-angles rates
       std::vector<double> gyro_filtered(DIM);
#ifdef AZGADS_CONSTANT
       gyro_filtered[0] = filtered_signal_gyro_x[i] * AZGADS_CONSTANT;
       gyro_filtered[1] = filtered_signal_gyro_y[i] * AZGADS_CONSTANT;
       gyro_filtered[2] = filtered_signal_gyro_z[i] * AZGADS_CONSTANT;
#else
       gyro_filtered[0] = filtered_signal_gyro_x[i];
       gyro_filtered[1] = filtered_signal_gyro_y[i];
       gyro_filtered[2] = filtered_signal_gyro_z[i];
#endif
       
       //gyro_filtered[2] = 0.0; // HERE
       std::vector<double> euler_angular_rates(DIM);
       multiply_matrix_times_vector(A, gyro_filtered, euler_angular_rates);
       //euler_angular_rates[0] = 0.0;
       //euler_angular_rates[1] = 0.0;
       //euler_angular_rates[2] = 0.0;
       
#ifdef EULER_ANGLES_RATE_THRESHOLD
       for (unsigned j = 0; j < DIM; j++)
        {
         if (fabs(euler_angular_rates[j]) < EULER_ANGLES_RATE_THRESHOLD)
          {
           euler_angular_rates[j] = 0.0;
          }
        }
#endif // #ifdef EULER_ANGLES_RATE_THRESHOLD
       
       // Set the Euler angular rates
       odes.euler_angular_rates() = euler_angular_rates;
       
#ifdef GYRO_THRESHOLD_Z
       if (fabs(gyro_filtered[2]) < GYRO_THRESHOLD_Z)
        {
         gyro_filtered[2] = 0.0;
        }
       std::vector<double> yaw_change_rate_with_threshold(DIM);
       multiply_matrix_times_vector(A, gyro_filtered, yaw_change_rate_with_threshold);
       
       // Set Yaw obtained directly from gyro angular rates after
       // applying a threshold
       odes.yaw_change_rate_with_threshold() = yaw_change_rate_with_threshold[2];
#endif // #ifdef GYRO_THRESHOLD_Z
       
       // ----------------------------------------------------------
       // ----------------------------------------------------------
       // Process the acceleration data
       // ----------------------------------------------------------
       // ----------------------------------------------------------     
       
       // Get yaw correction
       //const double bias_yaw = -0.95 * 180.0/M_PI;
       //double yaw_correction = (-1.0 * bias_yaw) / n_steps_per_second;
       //double yaw_correction = 0.75 / n_steps_per_second;
       //double yaw_correction = (0.75 / n_steps_per_second) * M_PI / 180.0;
       //double yaw_correction = 0.001745278 * M_PI / 180.0;
       //double yaw_correction = 0.001745278 * M_PI / 180.0;
       //double yaw_correction = 0.003696498 * M_PI / 180.0;
       //double yaw_correction = (5.0 * 180.0/M_PI) / n_steps_per_second;
       //double yaw_correction = 0.013089969/n_steps_per_second; // 0.75 degreess per second
       //double yaw_correction = 0.013089969/n_steps_per_second;
       //double yaw_correction = 0.006544985/n_steps_per_second; // 0.01 degreess per second
       //double yaw_correction = 0.0;
       //double yaw_correction = odes.get_yaw_correction(t, n_steps_per_second);
     
       // -------------------------------------------------------------------
       // Apply complementary filter
       // -------------------------------------------------------------------
       // Complementary filter parameter
       const double alpha = 0.90;
       //const double alpha_yaw = 1.0;
       
       // Copy filtered data to vector
       std::vector<double> acc_filtered(3);
       acc_filtered[0] = filtered_signal_acc_x[i];
       acc_filtered[1] = filtered_signal_acc_y[i];
       acc_filtered[2] = filtered_signal_acc_z[i];       
       // Transform accelerations to angles
       std::vector<double> acc_angles(3, 0.0);
       
       //acc_angles[0] = atan2(acc_inertial[2], acc_inertial[1]);
       //acc_angles[1] = atan2(acc_inertial[0], acc_inertial[2]);
       //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
       
       //acc_angles[0] = atan2(acc_inertial[1], acc_inertial[2]);
       //acc_angles[1] = atan2(-acc_inertial[0], sqrt(acc_inertial[1]*acc_inertial[1]+acc_inertial[2]*acc_inertial[2]));
       //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
       
       acc_angles[0] = atan2(acc_filtered[1], acc_filtered[2]);
       acc_angles[1] =
        atan2(-acc_filtered[0], sqrt(acc_filtered[1]*acc_filtered[1]+acc_filtered[2]*acc_filtered[2]));
       //acc_angles[2] = atan2(acc[2], sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
       acc_angles[2] =
        atan2(sqrt(acc_filtered[0]*acc_filtered[0]+acc_filtered[1]*acc_filtered[1]), acc_filtered[0]); // HERE
       
       //acc_angles[2] = atan2(acc[1], acc[0]);
       //acc_angles[2] = atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
       //acc_angles[2] = (atan2(acc[1], acc[0]) + atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]))) / 2.0;
       
       // Update filtered Euler angles
       y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
       y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
       //y[0][8] = 0.0; HERE
#if 0
#if 0
       if (!correct_yaw && (y[0][8] > M_PI)) // || y[0][8] < -M_PI)) // Only
                                                                // check
                                                                // this
                                                                // if
                                                                // the
                                                                // value
                                                                // has
                                                                // been
                                                                // initialised
        {
         correct_yaw = true;
        }
#endif // #if 0
       
       if (time <= 129.0)
        {
         y[0][8] = 0.0;
        }
       else if (correct_yaw) // Correct once we have heading info,
                             // then when its value goes out of range
        {
         const double zero_heading_angle = 130.0*TO_RADIANS;
         if (zero_heading_angle >= 0.0)
          {
           if (y[0][8] < 0.0)
            {
             if (y[0][8] < -(M_PI-zero_heading_angle))
              {
               
              }
             else
              {
               y[0][8] = -y[0][8] + zero_heading_angle;
              }
            }
           else
            {
             if (y[0][8] > zero_heading_angle)
              {
               if (y[0][8] > M_PI)
                {
                 //y[0][8] = -(2*M_PI - y[0][8]);
                 y[0][8] = -(M_PI - (y[0][8] - zero_heading_angle));
                 // -(M_PI - zero_heading_angle);
                }
               else
                {
                 y[0][8] = -(y[0][8] - zero_heading_angle);
                }
              }
             else
              {
               y[0][8] = zero_heading_angle - y[0][8];
              }
             
            }
           
           correct_yaw = false;
           
          }
         
        }
       
       if (time <= 129.0)
        {
         y[0][8] = 0.0;
        }
#endif // #if 0
       
       //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * true_course_in_radians;
       // Complementary filter of Yaw with Yaw threshold
       y[0][8] = alpha * y[0][8] + (1.0 - alpha) * y[0][9];
       
       //y[0][8]+= yaw_correction;
       //y[0][8] = alpha_yaw * y[0][8];// + (1.0 - alpha) * yaw_correction;
       //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * (y[0][8] + yaw_correction);
       //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
       //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * magnetometer[1];
       
       // --------------------------------------------------
       // Gravity compensation
       // --------------------------------------------------
       // Extract gravity and output the raw and the modified
       // accelerations
     
       // Create the rotation matrices
       std::vector<std::vector<double> > R(DIM);
       std::vector<std::vector<double> > R_t(DIM);
       for (unsigned j = 0; j < DIM; j++)
        {
         R[j].resize(DIM);
         R_t[j].resize(DIM);
        }
       
       // Fill rotation matrices
       //fill_rotation_matrices(R, R_t, y[0][6], y[0][7], y[0][8]);
       //fill_rotation_matrices(R, R_t, y[0][7], y[0][6], y[0][8]);
       
       const double front_of_car_angle = 0.0; // Point to the front of
                                              // the car
#ifdef ROTATION_MATRIX_ROLL_PITCH_YAW
       fill_rotation_matrices(R, R_t, y[0][6], y[0][7], front_of_car_angle);
#endif // #ifdef ROTATION_MATRIX_ROLL_PITCH_YAW
#ifdef ROTATION_MATRIX_YAW_PITCH_ROLL
       //fill_rotation_matrices(R, R_t, y[0][7], y[0][6], front_of_car_angle);
       fill_rotation_matrices(R, R_t, -y[0][6], -y[0][7], front_of_car_angle);
#endif // #ifdef ROTATION_MATRIX_YAW_PITCH_ROLL
#if 0
       if (-M_PI/2.0 < y[0][8] && y[0][8] < M_PI/2.0)
        {
         fill_rotation_matrices(R, R_t, y[0][7], y[0][6], y[0][8]);
        }
       else if (y[0][8] <= -M_PI/2.0 || y[0][8] >= M_PI/2.0)
        {
         fill_rotation_matrices(R, R_t, y[0][6], -y[0][7], y[0][8]);
        }
       else
        {
         // Error message
         std::ostringstream error_message;
         error_message << "The course (Yaw) angle is neither in the interval (-pi/2.0, pi/2.0),"
                       << "nor the intervals (-Inf, -pi/2.0], [pi/2.0, Inf)\n"
                       << "Course angle (radians): " << y[0][8] << "\n"
                       << "Course angle (degrees): " << y[0][8] * TO_DEGREES
                       << std::endl << std::endl;
         throw ChapchomLibError(error_message.str(),
                                CHAPCHOM_CURRENT_FUNCTION,
                                CHAPCHOM_EXCEPTION_LOCATION);
        }
#endif // #if 0
       
       //fill_rotation_matrices(R, R_t, y[0][6], y[0][7], true_course_in_degrees * TO_RADIANS); // tachidok, not ntegative because that is why we are multiplying by Rt (inverse of R)
       //fill_rotation_matrices(R, R_t, -y[0][6], -y[0][7], -true_course_in_degrees * TO_RADIANS); // tachidok, not ntegative because that is why we are multiplying by Rt (inverse of R)
       
       //fill_rotation_matrices(R, R_t, y[0][6], y[0][7], 0.0); // tachidok
       
#ifdef GRAVITY_TO_BODY_FRAME
       // Store the acceleration of the body without gravity
       std::vector<double> acc_body(DIM, 0.0);
       std::vector<double> gravity(DIM, 0.0);
       gravity[2] = GRAVITY;
       std::vector<double> body_frame_gravity(DIM, 0.0);
       multiply_matrix_times_vector(R, gravity, body_frame_gravity);
       for (unsigned j = 0; j < DIM; j++)
        {
         acc_body[j] = acc_filtered[j] - body_frame_gravity[j];
        }
#else
       // Transform from the body reference frame to the inertial
       // reference frame
       std::vector<double> acc_inertial(DIM, 0.0);
       //multiply_matrix_times_vector(R_t, acc_filtered, acc_inertial);//tachidok
       multiply_matrix_times_vector(R, acc_filtered, acc_inertial);//tachidok       
       // Substract gravity
       acc_inertial[2]-=GRAVITY;
#ifdef ACCELERATION_OFFSET
       for (unsigned j = 0; j < DIM; j++)
        {
         acc_inertial[j]+=ACCELERATION_OFFSET;
        }
#endif // #ifdef ACCELERATION_OFFSET
#endif // #ifdef GRAVITY_TO_BODY_FRAME
       
#ifdef ACCELERATION_THRESHOLD
       for (unsigned j = 0; j < DIM; j++)
        {
         if (fabs(acc_inertial[j]) < ACCELERATION_THRESHOLD)
          {
           acc_inertial[j] = 0.0;
          }
        }
#endif // #ifdef ACCELERATION_THRESHOLD
       
#ifdef GRAVITY_TO_BODY_FRAME
       // Set body frame acceleration
       odes.linear_acceleration() = acc_body;
#else
       // Set linear acceleration
       odes.linear_acceleration() = acc_inertial;
#endif // #ifdef GRAVITY_TO_BODY_FRAME
       
       // Compute absolute velocities based on heading and relative velocities
       //odes.compute_north_east_velocities(y[0][1], y[0][3]);
       
       // -----------------------------------------------------------------
       // Integrate
       // -----------------------------------------------------------------
       //const double m_factor = 1.0;
       //const double h_integration_step = 1.0/(m_factor*50.0); // tachidok
       //const double h_integration_step = 1.0/(0.2*15.0);
       //integrator->integrate_step(odes, h_integration_step, time, y);
       //DEB(h);
       integrator->integrate_step(odes, h, time, y);
       
#if 0
       if (y[0][1] > y[1][1] && y[1][1] < 5.0)
        {
         y[1][1] = 0.0;
        }
#endif // #if 0
       
       // Update data
       for (unsigned j = 0; j < n_odes; j++)
        {
         y[0][j] = y[1][j];
        }
       // Update time
       time+=h;
       
       // -----------------
       // Output data
       // -----------------
       // Position
       outfile_position << time
                        << " " << y[0][0]
                        << " " << y[0][2]
                        << " " << y[0][4] << std::endl;
       // Consider that x+ points to north and y+ points to west
       //outfile_position << time
       //                 << " " << -y[0][2]
       //                 << " " << y[0][0]
       //                 << " " << y[0][4] << std::endl; 
       // Velocity
       outfile_velocity << time
                        << " " << y[0][1]
                        << " " << y[0][3]
                        << " " << y[0][5]
        //                      << " " << std::sqrt(y[0][1] * y[0][1] + y[0][3] * y[0][3] + y[0][5] * y[0][5])
                        << " " << std::sqrt(y[0][1] * y[0][1] + y[0][3] * y[0][3])
                        << std::endl;
       // North-East velocity
       outfile_north_east_velocity << time
                                   << " " << odes.north_velocity()
                                   << " " << odes.east_velocity()
        //<< " " << y[0][1]//odes.north_velocity()
        //<< " " << y[0][3]//odes.east_velocity()
                                   << std::endl;
       // Euler angles rates
       outfile_euler_angles_rates << time
                                  << " " << euler_angular_rates[0]
                                  << " " << euler_angular_rates[1]
                                  << " " << euler_angular_rates[2] << std::endl;
#ifdef GRAVITY_TO_BODY_FRAME
       // Body frame gravity
       outfile_body_frame_gravity << time
                                  << " " << body_frame_gravity[0]
                                  << " " << body_frame_gravity[1]
                                  << " " << body_frame_gravity[2]
                                  << " " << std::sqrt(body_frame_gravity[0] * body_frame_gravity[0] +
                                                      body_frame_gravity[1] * body_frame_gravity[1] + body_frame_gravity[2] * body_frame_gravity[2])
                                  << std::endl;
#endif // #ifdef GRAVITY_TO_BODY_FRAME

#ifdef GRAVITY_TO_BODY_FRAME
       // Inertial accelerations
       outfile_inertial_acc << time
                            << " " << acc_body[0]
                            << " " << acc_body[1]
                            << " " << acc_body[2] << std::endl;
#else
       // Inertial accelerations
       outfile_inertial_acc << time
                             << " " << acc_inertial[0]
                             << " " << acc_inertial[1]
                             << " " << acc_inertial[2] << std::endl;
#endif // #ifdef GRAVITY_TO_BODY_FRAME
       
       // Euler angles
       outfile_roll_pitch_yaw << time
                              << " " << y[0][6]
                              << " " << y[0][7]
                              << " " << y[0][8] << std::endl;
       //<< " " << true_course_in_degrees * TO_RADIANS << std::endl;
       
       // Euler angles from accelerations
       outfile_roll_pitch_yaw_from_acc << time
                                       << " " << acc_angles[0]
                                       << " " << acc_angles[1]
                                       << " " << acc_angles[2] << std::endl;
       // Filtered gyro
       outfile_filtered_gyro << time
                             << " " << gyro_filtered[0]
                             << " " << gyro_filtered[1]
                             << " " << gyro_filtered[2] << std::endl;
       // Filtered acc
       outfile_filtered_acc << time
                            << " " << acc_filtered[0]
                            << " " << acc_filtered[1]
                            << " " << acc_filtered[2] << std::endl;

       // --------------------------------------------------------------------------
       // GPS DATA [BEGIN]
       // --------------------------------------------------------------------------
       // True course in degrees (output here even though we have
       // repeated values, we need them to plot in Matlab, otherwise we
       // would have to interpolate in matlab)
       outfile_true_course_in_degrees << time
                                      << " " << true_course_in_degrees << std::endl;
       
       // --------------------------------------------------------------------------
       // GPS DATA [END]
       // --------------------------------------------------------------------------
       
       std::cout << "t: " << time
                 << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
                 << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
                 << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
                 << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
       
      } // for (i < n_acc_data)
     
    } // if (applied_convolution)
   
   // --------------------------------------------------------------------------
   // GPS DATA [BEGIN]
   // --------------------------------------------------------------------------
   // For each lecture of the sensors we have one for the speed
   outfile_speed_in_knots << time
                          << " " << speed_in_knots << std::endl;
   
   outfile_speed_in_m_per_sec << time
                              << " " << speed_in_m_per_sec << std::endl;
   
#ifdef COMPUTE_ACC_FROM_GPS_VELOCITY
   const double acc_from_speed_in_m_per_sec_from_gps =
    (speed_in_m_per_sec - previous_speed_in_m_per_sec) / (time - (time - 1));
   previous_speed_in_m_per_sec = speed_in_m_per_sec;
   outfile_acc_from_speed_in_m_per_sec_from_GPS << time
                                                << " " << acc_from_speed_in_m_per_sec_from_gps << std::endl;
#endif // #ifdef COMPUTE_ACC_FROM_GPS_VELOCITY
 
   // --------------------------------------------------------------------------
   // GPS DATA [END]
   // --------------------------------------------------------------------------
   
  } // while (LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 outfile_position.close();
 outfile_velocity.close();
 outfile_north_east_velocity.close();
 outfile_raw_gyro.close();
 outfile_euler_angles_rates.close();
 outfile_raw_acc.close();
#ifdef GRAVITY_TO_BODY_FRAME
 outfile_body_frame_gravity.close();
#endif // #ifdef GRAVITY_TO_BODY_FRAME
 outfile_inertial_acc.close();
 outfile_roll_pitch_yaw.close();
 // GPS DATA [BEGIN] --------------------------------------------
 outfile_true_course_in_degrees.close();
 outfile_speed_in_knots.close();
 outfile_speed_in_m_per_sec.close();
 outfile_acc_from_speed_in_m_per_sec_from_GPS.close();
 // GPS DATA [END] ----------------------------------------------
 outfile_roll_pitch_yaw_from_acc.close();
 outfile_filtered_gyro.close();
 outfile_filtered_acc.close();
 
 // Free memory
 delete integrator;
 integrator = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

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
// Matrices
#include "../../../src/matrices/cc_matrix.h"

//#define OLD_IMPLEMENTATION
#define OUTPUT_RAW_AND_ROTATED_SENSORS_DATA
#define OUTPUT_FILTERED_SENSORS_DATA
#define OUTPUT_ALIGNED_SENSORS_DATA

#define DEBUG_SPEED_AND_ACCELERATION_FROM_GPS







#define COMPUTE_ACC_FROM_GPS_VELOCITY

#define GRAVITY 9.81

#define APPLY_CONVOLUTION
#ifndef APPLY_CONVOLUTION
//#define APPLY_LOW_PASS_FILTER
#endif // #ifndef APPLY_CONVOLUTION

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

//#define INERTIAL_ACCELERATION_THRESHOLD GRAVITY
//#define GYRO_THRESHOLD 1.0 * TO_RADIANS // One degree threshold
//#define ACCELERATION_THRESHOLD 1.0 // One meter per second per second

#define MAX_SIGNAL_SIZE 40

using namespace chapchom;

// ===================================================================
// Rotate sensors data to match ASIKI's reference frame
// ===================================================================
void rotate_sensors_to_ASIKIs_reference_frame(std::vector<std::vector<double> > &raw_gyro_t,
                                              std::vector<std::vector<double> > &raw_acc_t,
                                              std::vector<std::vector<double> > &rotated_raw_gyro,
                                              std::vector<std::vector<double> > &rotated_raw_acc)
{
 // Get the number of data for gyro
 const unsigned n_gyro = raw_gyro_t.size();
 // Get the number of data for acc
 const unsigned n_acc = raw_acc_t.size();
 
 // -----------------------------------------------------------
 // Rotation matrices to rotate the gyro's and accelerometer's
 // reference frame to the ASIKI's reference frame
 // -----------------------------------------------------------
 // Rotation matrix for gyro data
 const double angle_to_rotate_gyro = -(M_PI/2.0) + M_PI;
 CCMatrix<double> R_g(DIM, DIM);
 R_g.create_zero_matrix();
 R_g(0,0)=cos(angle_to_rotate_gyro);  R_g(0,1)=sin(angle_to_rotate_gyro); R_g(0,2)=0.0;
 R_g(1,0)=-sin(angle_to_rotate_gyro); R_g(1,1)=cos(angle_to_rotate_gyro); R_g(1,2)=0.0;
 R_g(2,0)=0.0;                        R_g(2,1)=0.0;                       R_g(2,2)=1.0;
 
 // Rotation matrix for acc data
 const double angle_to_rotate_acc = -M_PI + M_PI;
 CCMatrix<double> R_a(DIM, DIM);
 R_a.create_zero_matrix();
 R_a(0,0)=cos(angle_to_rotate_acc);   R_a(0,1)=sin(angle_to_rotate_acc);  R_a(0,2)=0.0;
 R_a(1,0)=-sin(angle_to_rotate_acc);  R_a(1,1)=cos(angle_to_rotate_acc);  R_a(1,2)=0.0;
 R_a(2,0)=0.0;                        R_a(2,1)=0.0;                       R_a(2,2)=1.0;
 
 // A vector to temporary store the data read from sensors
 CCVector<double> raw_data(DIM);
 raw_data.create_zero_vector();
 
 CCVector<double> rotated_raw_gyro_vector(DIM);
 CCVector<double> rotated_raw_acc_vector(DIM);
 
 // -------------------------------------------------------------------
 // Get the data from the input structures and copy it into a CCVector
 // to perform the rotation. Then copy the result into the output
 // structure
 // -------------------------------------------------------------------
 for (unsigned i = 0; i < n_gyro; i++)
  {
   // -------------------------------------------------------------------------
   // Store the gyro data in a temporary vector
   raw_data(0) = raw_gyro_t[i][1]; // gyro_x
   raw_data(1) = raw_gyro_t[i][2]; // gyro_y
   raw_data(2) = raw_gyro_t[i][3]; // gyro_z
   
   // ==========================================================================
   // Rotate the gyro to match the reference frame of the ASIKI
   // ==========================================================================
   multiply_matrix_by_vector(R_g, raw_data, rotated_raw_gyro_vector);
   // --------------------------------------------------------------------------
   // Store data in gyro output structure
   rotated_raw_gyro[i][0] = rotated_raw_gyro_vector(0); // gyro_x
   rotated_raw_gyro[i][1] = rotated_raw_gyro_vector(1); // gyro_y
   rotated_raw_gyro[i][2] = rotated_raw_gyro_vector(2); // gyro_z
  } // for (i < n_gyro)
 
 for (unsigned i = 0; i < n_acc; i++)
  {
   // -------------------------------------------------------------------------   
   // Store the acc data in a temporary vector. Multiply by 9.81
   // since the data from the accelerometers are given in 'g' units
   raw_data(0) = raw_acc_t[i][1] * GRAVITY; // acc_x
   raw_data(1) = raw_acc_t[i][2] * GRAVITY; // acc_y
   raw_data(2) = raw_acc_t[i][3] * GRAVITY; // acc_z
   
   // ==========================================================================
   // Rotate the acc to match the reference frame of the ASIKI
   // ==========================================================================
   multiply_matrix_by_vector(R_a, raw_data, rotated_raw_acc_vector);
   // --------------------------------------------------------------------------
   // Store the data in Accelerations matrix
   rotated_raw_acc[i][0] = rotated_raw_acc_vector(0); // acc_x
   rotated_raw_acc[i][1] = rotated_raw_acc_vector(1); // acc_y
   rotated_raw_acc[i][2] = rotated_raw_acc_vector(2); // acc_z
  } // for (i < n_acc)
 
}

// ===================================================================
// Apply low pass filter via convolution
// ===================================================================
void filter_signal_by_convolution(double *noisy_signal,
                                  const unsigned n_processed_data,
                                  double *kernel,
                                  const unsigned n_kernel,
                                  double *filtered_signal,
                                  const unsigned n_filtered_signal)
{ 
 // Loop over the size of the filtered signal
 for (unsigned i = 0; i < n_filtered_signal; i++)
  {
   // Initialise
   filtered_signal[i] = 0.0;
   
   // Compute k-min (where the filter starts to apply)
   int k_min = n_kernel - n_processed_data - i - 1;
   
   // A counter
   unsigned j = 0;
   if (k_min < 0)
    {
     // Pass how many units k is less than zero to j to start at that
     // index of the noisy signal
     j+=abs(k_min);     
     k_min = 0;
    }
   
   for (int k = k_min; k < static_cast<int>(n_kernel); k++)
    {
     filtered_signal[i] += noisy_signal[j] * kernel[k];
     j++;
    }
   
  } // for (i < n_noisy_signal)
 
}

// ===================================================================
// Align sensor's data via linear interpolation using gyro's time
// stamps as base. We always have data in the following pattern A G A
// G A G ..., where A represents an acceleration data, and G a
// gyroscope data. We use the time stamp of the gyro as the base time
// and interpolate the accelerometer's data using gyros time stamp
// ===================================================================
void align_sensors_time_stamps(const unsigned n_data,
                               double *aligned_time,
                               const unsigned n_gyro_data,
                               double *filtered_gyro_signal_t,
                               double *filtered_gyro_signal_x,
                               double *filtered_gyro_signal_y,
                               double *filtered_gyro_signal_z,
                               double *aligned_gyro_signal_x,
                               double *aligned_gyro_signal_y,
                               double *aligned_gyro_signal_z,
                               const unsigned n_acc_data,
                               double *filtered_acc_signal_t,
                               double *filtered_acc_signal_x,
                               double *filtered_acc_signal_y,
                               double *filtered_acc_signal_z,
                               double *aligned_acc_signal_x,
                               double *aligned_acc_signal_y,
                               double *aligned_acc_signal_z)
{ 
 // Loop over the number of data in the aligned vectors
 for (unsigned i = 0; i < n_data-1; i++)
  {
   // Get the time stamp of the gyro
   const double time = filtered_gyro_signal_t[i];
   // Store the time in the time stamps vector
   aligned_time[i] = time;
   // Add the lectures of the gyro in the aligned gyro data
   aligned_gyro_signal_x[i] = filtered_gyro_signal_x[i];
   aligned_gyro_signal_y[i] = filtered_gyro_signal_y[i];
   aligned_gyro_signal_z[i] = filtered_gyro_signal_z[i];
   
   // Get the stamp times of the accelerometers
   const double t0 = filtered_acc_signal_t[i];
   const double t1 = filtered_acc_signal_t[i+1];
   
   // Is the gyro time stamp within [t0,t1], can we interpolate?
   if (time >= t0 && time <= t1)
    {
     // The step in time
     const double dt = t1 - t0;
     // Linear interpolation (for each dimension). Using Newton's
     // divided differences
     {
      // Get the values of the acceleration at current and next time
      const double fx0 = filtered_acc_signal_x[i];
      const double fx1 = filtered_acc_signal_x[i+1];
      const double b0 = fx0;
      const double b1 = (fx1 - fx0) / (dt);
      aligned_acc_signal_x[i] = b0 + b1 * (time - t0);
     }
     {
      // Get the values of the acceleration at current and next time
      const double fy0 = filtered_acc_signal_y[i];
      const double fy1 = filtered_acc_signal_y[i+1];
      const double b0 = fy0;
      const double b1 = (fy1 - fy0) / (dt);
      aligned_acc_signal_y[i] = b0 + b1 * (time - t0);
     }
     {
      // Get the values of the acceleration at current and next time
      const double fz0 = filtered_acc_signal_z[i];
      const double fz1 = filtered_acc_signal_z[i+1];
      const double b0 = fz0;
      const double b1 = (fz1 - fz0) / (dt);
      aligned_acc_signal_z[i] = b0 + b1 * (time - t0);
     }
     
    } // if (time >= t0 && time <= t1)
   else // No iterpolation, copy the nearest
    {
     if (fabs(time - t0) < fabs(time - t1))
      {
       aligned_acc_signal_x[i] = filtered_acc_signal_x[i];
       aligned_acc_signal_y[i] = filtered_acc_signal_y[i];
       aligned_acc_signal_z[i] = filtered_acc_signal_z[i];
      }
     else
      {
       aligned_acc_signal_x[i] = filtered_acc_signal_x[i+1];
       aligned_acc_signal_y[i] = filtered_acc_signal_y[i+1];
       aligned_acc_signal_z[i] = filtered_acc_signal_z[i+1];
      }
     
    } // else if (time >= t0 && time <= t1)
    
  } // for (i < n_data-1)

 // Since we only fill the vector up to (n_data - 1) we copy the last
 // value of the lectures into the last entry of the vector
 
 const unsigned i = n_data - 1;
 // Store the time in the time stamps vector
 aligned_time[i] = filtered_gyro_signal_t[i];
 // Add the last lectures of the gyro in the aligned gyro data
 aligned_gyro_signal_x[i] = filtered_gyro_signal_x[i];
 aligned_gyro_signal_y[i] = filtered_gyro_signal_y[i];
 aligned_gyro_signal_z[i] = filtered_gyro_signal_z[i];
 // Add the last lectures of the accelerometers in the aligned
 // accelerometers data
 aligned_acc_signal_x[i] = filtered_acc_signal_x[i];
 aligned_acc_signal_y[i] = filtered_acc_signal_y[i];
 aligned_acc_signal_z[i] = filtered_acc_signal_z[i];
 
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

// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Initialise chapchom
 initialise_chapchom();
 
 // ----------------------------------------------------------------
 // FILES (BEGIN)
 // ----------------------------------------------------------------
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
 
 // Rotated raw gyro
 char file_rotated_raw_gyro_name[100];
 sprintf(file_rotated_raw_gyro_name, "./RESLT/rotated_raw_gyro.dat");
 std::ofstream outfile_rotated_raw_gyro;
 outfile_rotated_raw_gyro.open(file_rotated_raw_gyro_name, std::ios::out);
 if (outfile_rotated_raw_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_rotated_raw_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Rotated raw accelerations
 char file_rotated_raw_accelerations_name[100];
 sprintf(file_rotated_raw_accelerations_name, "./RESLT/rotated_raw_accelerations.dat");
 std::ofstream outfile_rotated_raw_acc;
 outfile_rotated_raw_acc.open(file_rotated_raw_accelerations_name, std::ios::out);
 if (outfile_rotated_raw_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_rotated_raw_accelerations_name << "]"
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
 
 // Aligned gyro
 char file_aligned_gyro_name[100];
 sprintf(file_aligned_gyro_name, "./RESLT/aligned_gyro.dat");
 std::ofstream outfile_aligned_gyro;
 outfile_aligned_gyro.open(file_aligned_gyro_name, std::ios::out);
 if (outfile_aligned_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_aligned_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Aligned acc
 char file_aligned_acc_name[100];
 sprintf(file_aligned_acc_name, "./RESLT/aligned_acc.dat");
 std::ofstream outfile_aligned_acc;
 outfile_aligned_acc.open(file_aligned_acc_name, std::ios::out);
 if (outfile_aligned_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_aligned_acc_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }

#ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 // Speed in m/s from GPS
 char file_speed_in_m_per_sec_from_GPS_name[100];
 sprintf(file_speed_in_m_per_sec_from_GPS_name, "./RESLT/speed_in_m_per_sec_from_GPS.dat");
 std::ofstream outfile_speed_in_m_per_sec_from_GPS;
 outfile_speed_in_m_per_sec_from_GPS.open(file_speed_in_m_per_sec_from_GPS_name, std::ios::out);
 if (outfile_speed_in_m_per_sec_from_GPS.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_speed_in_m_per_sec_from_GPS_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Acceleration from speed in m/s from GPS
 char file_acc_in_m_per_sec_from_speed_from_GPS_name[100];
 sprintf(file_acc_in_m_per_sec_from_speed_from_GPS_name, "./RESLT/acc_in_m_per_sec_from_speed_from_GPS.dat");
 std::ofstream outfile_acc_in_m_per_sec_from_speed_from_GPS;
 outfile_acc_in_m_per_sec_from_speed_from_GPS.open(file_acc_in_m_per_sec_from_speed_from_GPS_name, std::ios::out);
 if (outfile_acc_in_m_per_sec_from_speed_from_GPS.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_acc_in_m_per_sec_from_speed_from_GPS_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 
#if 0
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

#endif
 
 // ----------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------
 
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
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // The discretised time
 double time = 0.0;
 
 // ----------------------------------------------------------------
 // Filter stage [BEGIN]
 // ----------------------------------------------------------------
 // Storage for nonfiltered signal previous to filter application
 double noisy_signal_gyro_x[MAX_SIGNAL_SIZE];
 double noisy_signal_gyro_y[MAX_SIGNAL_SIZE];
 double noisy_signal_gyro_z[MAX_SIGNAL_SIZE];
 double noisy_signal_acc_x[MAX_SIGNAL_SIZE];
 double noisy_signal_acc_y[MAX_SIGNAL_SIZE];
 double noisy_signal_acc_z[MAX_SIGNAL_SIZE];
 // Initialise to zero
 for (unsigned i = 0; i < MAX_SIGNAL_SIZE; i++)
  {
   noisy_signal_gyro_x[i] = 0.0;
   noisy_signal_gyro_y[i] = 0.0;
   noisy_signal_gyro_z[i] = 0.0;
   noisy_signal_acc_x[i] = 0.0;
   noisy_signal_acc_y[i] = 0.0;
   noisy_signal_acc_z[i] = 0.0;
  }
 // A counter to indicate the number of values for gyro and
 // accelerometers already processed in the signal buffer
 unsigned n_processed_data_in_gyro_buffer = 0;
 unsigned n_processed_data_in_acc_buffer = 0;
 
 // ----------------------------------------------------------------
 // Filter stage [END]
 // ----------------------------------------------------------------
 
#ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 // Used to compute the acceleration or derivative of the speed given
 // by the GPS
 double previous_speed_in_m_per_sec_from_gps = 0;
#endif // #ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 
 // Main LOOP (continue looping until all data in the input file is
 // processed)
 while (LOOP)
  {
   // Retrieve data from sensors
   LOOP = odes.get_sensors_lectures();
   // Check if there are data to process, otherwise end the LOOP
   if (!LOOP)
    {
     break;
    }
   
   // Get the number of gyro data
   const unsigned n_gyro_data = odes.ngyro_data();
   // Get the number of acceleration data
   const unsigned n_acc_data = odes.nacceleration_data();
   
   // Get the raw data from gyro
   std::vector<std::vector<double> > raw_gyro_t = odes.get_angular_velocities();
   // Get the raw data from accelerometers
   std::vector<std::vector<double> > raw_acc_t = odes.get_accelerations();
   
   // ==========================================================================
   // Rotate sensors data to match ASIKI's reference frame
   // ==========================================================================
   // Store the rotated data for gyro and accelerometers
   std::vector<std::vector<double> > rotated_raw_gyro(n_gyro_data);
   for (unsigned i = 0; i < n_gyro_data; i++)
    {
     rotated_raw_gyro[i].resize(DIM);
    }
   std::vector<std::vector<double> > rotated_raw_acc(n_acc_data);
   for (unsigned i = 0; i < n_acc_data; i++)
    {
     rotated_raw_acc[i].resize(DIM);
    }
   
   // Perform the actual rotatations
   rotate_sensors_to_ASIKIs_reference_frame(raw_gyro_t,
                                            raw_acc_t,
                                            rotated_raw_gyro,
                                            rotated_raw_acc);
   
#ifdef OUTPUT_RAW_AND_ROTATED_SENSORS_DATA
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [BEGIN]
   // --------------------------------------------------------------------------
   {
    // --------------------------------------------------
    // Output the raw and rotated data for gyro
    for (unsigned i = 0; i < n_gyro_data; i++)
     {
      // Raw gyro
      outfile_raw_gyro << raw_gyro_t[i][0]
                       << " " << raw_gyro_t[i][1]
                       << " " << raw_gyro_t[i][2]
                       << " " << raw_gyro_t[i][3] << std::endl;
      
      // Rotated raw gyro
      outfile_rotated_raw_gyro << raw_gyro_t[i][0]
                               << " " << rotated_raw_gyro[i][0]
                               << " " << rotated_raw_gyro[i][1]
                               << " " << rotated_raw_gyro[i][2] << std::endl;
     }
    
    // --------------------------------------------------
    // Output the raw and rotated data for accelerometers
    for (unsigned i = 0; i < n_acc_data; i++)
     {
      // Raw accelerometers
      outfile_raw_acc << raw_acc_t[i][0]
                      << " " << raw_acc_t[i][1]
                      << " " << raw_acc_t[i][2]
                      << " " << raw_acc_t[i][3] << std::endl;
      
      // Rotated raw accelerometers
      outfile_rotated_raw_acc << raw_acc_t[i][0]
                              << " " << rotated_raw_acc[i][0]
                              << " " << rotated_raw_acc[i][1]
                              << " " << rotated_raw_acc[i][2] << std::endl;
     }
    
   }
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [END]
   // --------------------------------------------------------------------------
#endif // #ifdef OUTPUT_RAW_AND_ROTATED_SENSORS_DATA
   
   // ==========================================================================
   // Apply low-pass filter via convolution
   // ==========================================================================
   // Copy the data into the corresponding structure
   for (unsigned i = 0 ; i < n_gyro_data; i++)
    {
     noisy_signal_gyro_x[i+n_processed_data_in_gyro_buffer] = rotated_raw_gyro[i][0];
     noisy_signal_gyro_y[i+n_processed_data_in_gyro_buffer] = rotated_raw_gyro[i][1];
     noisy_signal_gyro_z[i+n_processed_data_in_gyro_buffer] = rotated_raw_gyro[i][2];
    }
   
   // Copy the data into the corresponding structure
   for (unsigned i = 0 ; i < n_acc_data; i++)
    {
     noisy_signal_acc_x[i+n_processed_data_in_acc_buffer] = rotated_raw_acc[i][0];
     noisy_signal_acc_y[i+n_processed_data_in_acc_buffer] = rotated_raw_acc[i][1];
     noisy_signal_acc_z[i+n_processed_data_in_acc_buffer] = rotated_raw_acc[i][2];
    }
   
   // The data structure where to store the filtered gyro signal
   double *filtered_gyro_signal_t = new double[n_gyro_data];
   double *filtered_gyro_signal_x = new double[n_gyro_data];
   double *filtered_gyro_signal_y = new double[n_gyro_data];
   double *filtered_gyro_signal_z = new double[n_gyro_data];
   
   // The data structure where to store the filtered acc signal
   double *filtered_acc_signal_t = new double[n_acc_data];
   double *filtered_acc_signal_x = new double[n_acc_data];
   double *filtered_acc_signal_y = new double[n_acc_data];
   double *filtered_acc_signal_z = new double[n_acc_data];
   
   // Copy the time stamps for gyro
   for (unsigned i = 0; i < n_gyro_data; i++)
    {
     filtered_gyro_signal_t[i] = raw_gyro_t[i][0];
    }
   
   // Copy the time stamps for acc
   for (unsigned i = 0; i < n_acc_data; i++)
    {
     filtered_acc_signal_t[i] = raw_acc_t[i][0];
    }
   
   // The coefficients of the kernel signal to convolve with the gyro
   // data
   const unsigned n_kernel_gyro = 15;
   double kernel_gyro[] = {0.0102773244275157,	0.0162263834264182,	0.0328881753317823,	0.0570814837334001,	0.0840520641122108,	0.108434325903213,	0.125345958994944,	0.131388568141032,	0.125345958994944,	0.108434325903213,	0.0840520641122108,	0.0570814837334001,	0.0328881753317823,	0.0162263834264182,	0.0102773244275157};
   
   // The coefficients of the kernel signal to convolve with the
   // accelerometer data
   const unsigned n_kernel_acc = 15;
   double kernel_acc[] = {0.0104226000635011,	0.0163818874099687,	0.0330775506149548,	0.0572325417966930,	0.0840719974006429,	0.108274081298100,	0.125032039259642,	0.131014604312996,	0.125032039259642,	0.108274081298100,	0.0840719974006429,	0.0572325417966930,	0.0330775506149548,	0.0163818874099687,	0.0104226000635011};
   
   // Perform the actual convolution
   filter_signal_by_convolution(noisy_signal_gyro_x,
                                n_processed_data_in_gyro_buffer,
                                kernel_gyro, n_kernel_gyro,
                                filtered_gyro_signal_x,
                                n_gyro_data);
   filter_signal_by_convolution(noisy_signal_gyro_y,
                                n_processed_data_in_gyro_buffer,
                                kernel_gyro, n_kernel_gyro,
                                filtered_gyro_signal_y,
                                n_gyro_data);
   filter_signal_by_convolution(noisy_signal_gyro_z,
                                n_processed_data_in_gyro_buffer,
                                kernel_gyro, n_kernel_gyro,
                                filtered_gyro_signal_z,
                                n_gyro_data);
   filter_signal_by_convolution(noisy_signal_acc_x,
                                n_processed_data_in_acc_buffer,
                                kernel_acc, n_kernel_acc,
                                filtered_acc_signal_x,
                                n_acc_data);
   filter_signal_by_convolution(noisy_signal_acc_y,
                                n_processed_data_in_acc_buffer,
                                kernel_acc, n_kernel_acc,
                                filtered_acc_signal_y,
                                n_acc_data);
   filter_signal_by_convolution(noisy_signal_acc_z,
                                n_processed_data_in_acc_buffer,
                                kernel_acc, n_kernel_acc,
                                filtered_acc_signal_z,
                                n_acc_data);
   
   // Add the number of data to the processed data
   n_processed_data_in_gyro_buffer+=n_gyro_data;
   n_processed_data_in_acc_buffer+=n_acc_data;
   
   // If the number of processed data is larger than the kernel size
   // then shift the data to have just enough data for the next
   // filtering step (n_kernel)
   if (n_processed_data_in_gyro_buffer >= n_kernel_gyro)
    {
     // Get the number of elements that we should shift to the left
     const unsigned n_shift_gyro_data = n_processed_data_in_gyro_buffer - n_kernel_gyro + 1;
     for (unsigned i = 0; i < n_kernel_gyro; i++)
      {
       noisy_signal_gyro_x[i] = noisy_signal_gyro_x[i+n_shift_gyro_data];
       noisy_signal_gyro_y[i] = noisy_signal_gyro_y[i+n_shift_gyro_data];
       noisy_signal_gyro_z[i] = noisy_signal_gyro_z[i+n_shift_gyro_data];
      }
     // Reset the number of data processed in the gyro buffer
     n_processed_data_in_gyro_buffer=n_kernel_gyro-1;
    }
   
   if (n_processed_data_in_acc_buffer >= n_kernel_acc)
    {
     // Get the number of elements that we should shift to the left
     const unsigned n_shift_acc_data = n_processed_data_in_acc_buffer - n_kernel_acc + 1;
     for (unsigned i = 0; i < n_kernel_acc; i++)
      {
       noisy_signal_acc_x[i] = noisy_signal_acc_x[i+n_shift_acc_data];
       noisy_signal_acc_y[i] = noisy_signal_acc_y[i+n_shift_acc_data];
       noisy_signal_acc_z[i] = noisy_signal_acc_z[i+n_shift_acc_data];
      }
     // Reset the number of data processed in the gyro buffer
     n_processed_data_in_acc_buffer=n_kernel_acc-1;
    }
   
#ifdef OUTPUT_FILTERED_SENSORS_DATA
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [BEGIN]
   // --------------------------------------------------------------------------
   {
    // --------------------------------------------------
    // Output the filtered data for gyro
    for (unsigned i = 0; i < n_gyro_data; i++)
     {
      // Filtered gyro
      outfile_filtered_gyro << filtered_gyro_signal_t[i]
                            << " " << filtered_gyro_signal_x[i]
                            << " " << filtered_gyro_signal_y[i]
                            << " " << filtered_gyro_signal_z[i] << std::endl;
     }
    
    // Output the filtered data for accelerometers
    for (unsigned i = 0; i < n_acc_data; i++)
     {      
      // Filtered acceleration
      outfile_filtered_acc << filtered_acc_signal_t[i]
                           << " " << filtered_acc_signal_x[i]
                           << " " << filtered_acc_signal_y[i]
                           << " " << filtered_acc_signal_z[i] << std::endl;
     }
    
   }
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [END]
   // --------------------------------------------------------------------------
#endif // #ifdef OUTPUT_FILTERED_SENSORS_DATA
   
   // ==========================================================================
   // Align time stamps for Gyro and Accelerometers
   // ==========================================================================
   // We always have data in the following pattern
   // A G A G A G ...
   // where A represents an acceleration data, and G a gyroscope data
   
   // We use the time stamp of the gyro as the base time and
   // interpolate the accelerometer's data using gyros time stamp
   const unsigned n_data = std::min(n_gyro_data, n_acc_data);
   double *aligned_time = new double[n_data];
   double *aligned_gyro_signal_x = new double[n_data];
   double *aligned_gyro_signal_y = new double[n_data];
   double *aligned_gyro_signal_z = new double[n_data];
   double *aligned_acc_signal_x = new double[n_data];
   double *aligned_acc_signal_y = new double[n_data];
   double *aligned_acc_signal_z = new double[n_data];
   
   // Perform the actual alignment
   align_sensors_time_stamps(n_data,
                             aligned_time,
                             n_gyro_data,
                             filtered_gyro_signal_t,
                             filtered_gyro_signal_x,
                             filtered_gyro_signal_y,
                             filtered_gyro_signal_z,
                             aligned_gyro_signal_x,
                             aligned_gyro_signal_y,
                             aligned_gyro_signal_z,
                             n_acc_data,
                             filtered_acc_signal_t,
                             filtered_acc_signal_x,
                             filtered_acc_signal_y,
                             filtered_acc_signal_z,
                             aligned_acc_signal_x,
                             aligned_acc_signal_y,
                             aligned_acc_signal_z);
   
#ifdef OUTPUT_ALIGNED_SENSORS_DATA
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [BEGIN]
   // --------------------------------------------------------------------------
   {
    // --------------------------------------------------
    // Output aligned time stamps data for gyro and acceleration
    for (unsigned i = 0; i < n_data; i++)
     {
      // Aligned gyro
      outfile_aligned_gyro << aligned_time[i]
                           << " " << aligned_gyro_signal_x[i]
                           << " " << aligned_gyro_signal_y[i]
                           << " " << aligned_gyro_signal_z[i] << std::endl;
      
      // Aligned acceleration
      outfile_aligned_acc << aligned_time[i]
                          << " " << aligned_acc_signal_x[i]
                          << " " << aligned_acc_signal_y[i]
                          << " " << aligned_acc_signal_z[i] << std::endl;
      
     }
    
   }
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [END]
   // --------------------------------------------------------------------------
#endif // #ifdef OUTPUT_ALIGNED_SENSORS_DATA

   // Set the initial time for this set of data
   time = aligned_time[0];
   
#ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
   const double speed_in_m_per_sec_from_gps = odes.speed_in_knots()*0.514444;
   outfile_speed_in_m_per_sec_from_GPS << time
                                       << " " << speed_in_m_per_sec_from_gps << std::endl;
   const double acc_in_m_per_sec_from_speed_from_gps =
    (speed_in_m_per_sec_from_gps - previous_speed_in_m_per_sec_from_gps) / (time - (time - 1));
   previous_speed_in_m_per_sec_from_gps = speed_in_m_per_sec_from_gps;
   outfile_acc_in_m_per_sec_from_speed_from_GPS << time
                                                << " " << acc_in_m_per_sec_from_speed_from_gps << std::endl;
#endif // #ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
   
  } // while (LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 outfile_raw_gyro.close();
 outfile_raw_acc.close();
 outfile_rotated_raw_gyro.close();
 outfile_rotated_raw_acc.close();
 outfile_filtered_gyro.close();
 outfile_filtered_acc.close();
 outfile_aligned_gyro.close();
 outfile_aligned_acc.close();
 
#ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 outfile_speed_in_m_per_sec_from_GPS.close();
 outfile_acc_in_m_per_sec_from_speed_from_GPS.close();
#endif // #ifdef DEBUG_SPEED_AND_ACCELERATION_FROM_GPS
 
#if 0
 outfile_position.close();
 outfile_velocity.close();
 outfile_north_east_velocity.close();

 outfile_euler_angles_rates.close();

 outfile_inertial_acc.close();
 outfile_roll_pitch_yaw.close();
 // GPS DATA [BEGIN] --------------------------------------------
 outfile_true_course_in_degrees.close();
 outfile_speed_in_knots.close();
 // GPS DATA [END] ----------------------------------------------
 outfile_roll_pitch_yaw_from_acc.close();
#endif

#ifdef OLD_IMPLEMENTATION
 // Free memory
 delete integrator;
 integrator = 0;
#endif // #ifdef OLD_IMPLEMENTATION
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

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
// Odes from GEOFOG3D
#include "cc_odes_from_sensors_UBLOX.h"
// The nmea decoder
#include "cc_nmea_decoder.h"
// Matrices
#include "../../../src/matrices/cc_matrix.h"

//#define OLD_IMPLEMENTATION
// -------------------------------------------------
// Output data
// -------------------------------------------------
#define OUTPUT_RAW_AND_ROTATED_SENSORS_DATA
#define OUTPUT_FILTERED_SENSORS_DATA
#define OUTPUT_ALIGNED_SENSORS_DATA
#define OUTPUT_GRAVITY_IN_BODY_FRAME
#define OUTPUT_ACCELERATIONS
#define OUTPUT_VELOCITIES
#define OUTPUT_EULER_ANGLES
//#define OUTPUT_EULER_ANGLES_FROM_GYRO_AND_ACCELEROMETER // TODO, when
                                                        // ENABLE this
                                                        // remember to
                                                        // disable the
                                                        // complementary
                                                        // filter
#define OUTPUT_EULER_ANGLES_RATES

// Data to evaluation
#define NAVIGATION_DATA_TO_EVALUATION
//#define FORCE_USING_EULER_ANGLES_RATES_FROM_GEOFOG3D
//#define FORCE_USING_EULER_ANGLES_FROM_GEOFOG3D
//#define FORCE_USING_LINEAR_ACCELERATIONS_FROM_GEOFOG3D

//#define APPLY_LINEAR_ACCELERATIONS_OFFSET
//#define APPLY_EULER_ANGLES_OFFSET

//#define USE_COURSE_FROM_GPS

// -------------------------------------------------
// Constants
// -------------------------------------------------
#define MAX_SIGNAL_SIZE 140
#define GRAVITY 9.81
//#define AZGADS_CONSTANT 1.1285
//#define GYRO_THRESHOLD_Z 1.0 * TO_RADIANS // One degree threshold

using namespace chapchom;

// ===================================================================
// Performs a rotation indicated by the rotation matrix R
// ===================================================================
void rotate(CCMatrix<double> &R,
            double *original_data,
            double *rotated_data)
{
 // Create a vector representation of the original data
 CCVector<double> b(original_data, DIM);
 // A vector representation of the rotated data
 CCVector<double> r(DIM);
 // Apply rotation
 multiply_matrix_times_vector(R, b, r);
 // Copy back result in output structure
 rotated_data[0]=r(0);
 rotated_data[1]=r(1);
 rotated_data[2]=r(2);
}

// ===================================================================
// Rotate sensors data to match ASIKI's reference frame
// ===================================================================
void rotate_sensors_to_ASIKIs_reference_frame(std::vector<std::vector<double> > &raw_gyro_t,
                                              std::vector<std::vector<double> > &raw_acc_t,
                                              std::vector<std::vector<double> > &rotated_raw_gyro,
                                              std::vector<std::vector<double> > &rotated_raw_acc,
                                              std::vector<double> &Euler_angles_for_gyro,
                                              std::vector<double> &Euler_angles_for_acc)
{ 
 // -----------------------------------------------------------
 // Rotation matrices to rotate the gyro's and accelerometer's
 // reference frame to the ASIKI's reference frame
 // -----------------------------------------------------------

 {
  // Get the number of data for gyro
  const unsigned n_gyro = raw_gyro_t.size();
  
  // Rotation matrix for gyro data
  CCMatrix<double> R_g(DIM, DIM);
  R_g.allocate_memory();
  
  const double sin_theta_x = sin(Euler_angles_for_gyro[0]);
  const double sin_theta_y = sin(Euler_angles_for_gyro[1]);
  const double sin_theta_z = sin(Euler_angles_for_gyro[2]);
  const double cos_theta_x = cos(Euler_angles_for_gyro[0]);
  const double cos_theta_y = cos(Euler_angles_for_gyro[1]);
  const double cos_theta_z = cos(Euler_angles_for_gyro[2]);
  
  R_g(0,0) = cos_theta_y*cos_theta_z;
  R_g(0,1) = cos_theta_y*sin_theta_z;
  R_g(0,2) = -sin_theta_y;
  
  R_g(1,0) = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
  R_g(1,1) = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
  R_g(1,2) = sin_theta_x*cos_theta_y;
  
  R_g(2,0) = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
  R_g(2,1) = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
  R_g(2,2) = cos_theta_x*cos_theta_y;
  
  // Compute the transpose (body to inertial -- acc measurements are
  // in the inertial frame --)
  R_g.transpose();
  
  // Rotate each of the set of data of te gyro
  for (unsigned i = 0; i < n_gyro; i++)
   {
    // Copy the date in temporary structures
    double r[DIM];
    r[0]=raw_gyro_t[i][1]; // gyro_x
    r[1]=raw_gyro_t[i][2]; // gyro_y
    r[2]=raw_gyro_t[i][3]; // gyro_z
    double r_g[DIM];
    
    // Perform the actual transformation
    rotate(R_g, r, r_g);
    
    rotated_raw_gyro[i][0]=r_g[0];
    rotated_raw_gyro[i][1]=r_g[1];
    rotated_raw_gyro[i][2]=r_g[2];
   
   } // for (i < n_gyro)
  
 }
 
 {
  // Get the number of data for acc
  const unsigned n_acc = raw_acc_t.size();
  CCMatrix<double> R_a(DIM, DIM);
  R_a.allocate_memory();
  
  const double sin_theta_x = sin(Euler_angles_for_acc[0]);
  const double sin_theta_y = sin(Euler_angles_for_acc[1]);
  const double sin_theta_z = sin(Euler_angles_for_acc[2]);
  const double cos_theta_x = cos(Euler_angles_for_acc[0]);
  const double cos_theta_y = cos(Euler_angles_for_acc[1]);
  const double cos_theta_z = cos(Euler_angles_for_acc[2]);
  
  R_a(0,0) = cos_theta_y*cos_theta_z;
  R_a(0,1) = cos_theta_y*sin_theta_z;
  R_a(0,2) = -sin_theta_y;
  
  R_a(1,0) = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
  R_a(1,1) = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
  R_a(1,2) = sin_theta_x*cos_theta_y;
  
  R_a(2,0) = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
  R_a(2,1) = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
  R_a(2,2) = cos_theta_x*cos_theta_y;
  
  // Compute the transpose (body to inertial -- acc measurements are
  // in the inertial frame --)
  R_a.transpose();
  
  // Rotate each of the set of data of te gyro
  for (unsigned i = 0; i < n_acc; i++)
   {
    // Copy the date in temporary structures
    double r[DIM];
    r[0]=raw_acc_t[i][1]; // acc_x
    r[1]=raw_acc_t[i][2]; // acc_y
    r[2]=raw_acc_t[i][3]; // acc_z
    double r_a[DIM];
    
    // Perform the actual transformation
    rotate(R_a, r, r_a);
    
    rotated_raw_acc[i][0]=r_a[0];
    rotated_raw_acc[i][1]=r_a[1];
    rotated_raw_acc[i][2]=r_a[2];
    
   } // for (i < n_acc)
  
 }
 
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
// In charge of applying a transformation to get euler angles rates
// from angular velocities (the lectures from the gyro)
// ===================================================================
void transform_angular_velocities_into_euler_angles_rates(double *angular_velocities,
                                                          double *Euler_angles,
                                                          double *Euler_angles_rates,
                                                          double *Euler_angles_rates_thresholded)
{
 // Re-name variable
 const double phi = Euler_angles[0];
 const double theta = Euler_angles[1];
 // Cache trigonometric function values
 const double sin_phi = sin(phi);
 const double cos_phi = cos(phi);
 const double sec_theta = 1.0/cos(theta);
 const double tan_theta = tan(theta);
 
 // Create a matrix that transforms from angular velocities to
 // Euler angles rates
 CCMatrix<double> A(DIM, DIM);
 A.allocate_memory();
 A(0,0)=1.0;  A(0,1)=sin_phi*tan_theta; A(0,2)=cos_phi*tan_theta;
 A(1,0)=0.0;  A(1,1)=cos_phi;           A(1,2)=-sin_phi;
 A(2,0)=0.0;  A(2,1)=sin_phi*sec_theta; A(2,2)=cos_phi*sec_theta;
 
 CCVector<double> v(angular_velocities, DIM);
 CCVector<double> e(DIM);
 // --------------------------------------------------------------------------
 // Apply transformation to get Euler angles rates
 // --------------------------------------------------------------------------
 multiply_matrix_times_vector(A, v, e);
 // Copy back into output vector
 Euler_angles_rates[0]=e(0);
 Euler_angles_rates[1]=e(1);
 Euler_angles_rates[2]=e(2);
 
#ifdef GYRO_THRESHOLD_Z
 if (fabs(v(2)) < GYRO_THRESHOLD_Z)
  {
   v(2) = 0.0;
  }
 CCVector<double> e_th(DIM);
 // --------------------------------------------------------------------------
 // Apply transformation (with thresholded data)
 // --------------------------------------------------------------------------
 multiply_matrix_times_vector(A, v, e_th);
 // Copy back into output vector (thresholded)
 Euler_angles_rates_thresholded[0]=e_th(0);
 Euler_angles_rates_thresholded[1]=e_th(1);
 Euler_angles_rates_thresholded[2]=e_th(2);
#endif // #ifdef GYRO_THRESHOLD_Z
 
}

// ===================================================================
// Performs a rotation/transformation from the inertial reference
// frame to the body reference frame using Euler angles
// ===================================================================
void transform_inertial_to_body(double *Euler_angles,
                                double *inertial_frame_data,
                                double *body_frame_data)
{
 // Create the rotation matrix
 CCMatrix<double> R(DIM, DIM);
 R.allocate_memory();
 
 const double sin_theta_x = sin(Euler_angles[0]);
 const double sin_theta_y = sin(Euler_angles[1]);
 const double sin_theta_z = sin(Euler_angles[2]);
 const double cos_theta_x = cos(Euler_angles[0]);
 const double cos_theta_y = cos(Euler_angles[1]);
 const double cos_theta_z = cos(Euler_angles[2]);
 
 R(0,0) = cos_theta_y*cos_theta_z;
 R(0,1) = cos_theta_y*sin_theta_z;
 R(0,2) = -sin_theta_y;
 
 R(1,0) = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
 R(1,1) = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
 R(1,2) = sin_theta_x*cos_theta_y;
 
 R(2,0) = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
 R(2,1) = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
 R(2,2) = cos_theta_x*cos_theta_y;
 
 // Perform the actual transformation
 rotate(R, inertial_frame_data, body_frame_data);
 
}

// ===================================================================
// Performs a rotation/transformation from the body reference frame to
// the inertial reference frame using Euler angles
// ===================================================================
void transform_body_to_inertial(double *Euler_angles,
                                double *body_frame_data,
                                double *inertial_frame_data)
{
 // Create the rotation matrix
 CCMatrix<double> R(DIM, DIM);
 R.allocate_memory();
 
 const double sin_theta_x = sin(Euler_angles[0]);
 const double sin_theta_y = sin(Euler_angles[1]);
 const double sin_theta_z = sin(Euler_angles[2]);
 const double cos_theta_x = cos(Euler_angles[0]);
 const double cos_theta_y = cos(Euler_angles[1]);
 const double cos_theta_z = cos(Euler_angles[2]);
 
 R(0,0) = cos_theta_y*cos_theta_z;
 R(0,1) = cos_theta_y*sin_theta_z;
 R(0,2) = -sin_theta_y;
 
 R(1,0) = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
 R(1,1) = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
 R(1,2) = sin_theta_x*cos_theta_y;
 
 R(2,0) = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
 R(2,1) = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
 R(2,2) = cos_theta_x*cos_theta_y;
 
 // Transpose the matrix (to perform the inverse operation -- body to
 // inertial --)
 R.transpose();
 
 // Perform the actual transformation
 rotate(R, body_frame_data, inertial_frame_data);
  
}

void compute_current_latitude_and_longitude(const double instantaneous_travelled_distance,
                                            const double earth_referenced_course_in_radians,
                                            double &current_latitude, double &current_longitude)
{
 // The radius of the earth
 const double r = 6378137.0;
 //const double r = 6371000.0; // Mean earth radius

 // The angle to the north
 const double alpha = earth_referenced_course_in_radians;

 // The distance between the previous and the current (latitute, longitude) point
 const double dA = instantaneous_travelled_distance;

 const double new_latitude =
  asin(sin(current_latitude) * cos(dA/r) + cos(current_latitude) * sin(dA/r) * cos(alpha));
 
 const double new_longitude =
  current_longitude + atan2(sin(alpha)*sin(dA/r) * cos(current_latitude), cos(dA/r)- sin(current_latitude) * sin(new_latitude));

 // Return values
 current_latitude = new_latitude;
 current_longitude = new_longitude;
 
}

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
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
 
 // Euler-angles from gyro
 char file_euler_angles_from_gyro_name[100];
 sprintf(file_euler_angles_from_gyro_name, "./RESLT/euler_angles_from_gyro.dat");
 std::ofstream outfile_euler_angles_from_gyro;
 outfile_euler_angles_from_gyro.open(file_euler_angles_from_gyro_name, std::ios::out);
 if (outfile_euler_angles_from_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_euler_angles_from_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Euler-angles from accelerometer
 char file_euler_angles_from_accelerometer_name[100];
 sprintf(file_euler_angles_from_accelerometer_name, "./RESLT/euler_angles_from_accelerometer.dat");
 std::ofstream outfile_euler_angles_from_accelerometer;
 outfile_euler_angles_from_accelerometer.open(file_euler_angles_from_accelerometer_name, std::ios::out);
 if (outfile_euler_angles_from_accelerometer.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_euler_angles_from_accelerometer_name << "]"
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
 
 // Gravity in body frame
 char file_gravity_in_body_frame_name[100];
 sprintf(file_gravity_in_body_frame_name, "./RESLT/gravity_in_body_frame.dat");
 std::ofstream outfile_gravity_in_body_frame;
 outfile_gravity_in_body_frame.open(file_gravity_in_body_frame_name, std::ios::out);
 if (outfile_gravity_in_body_frame.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_gravity_in_body_frame_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Body frame accelerations
 char file_body_accelerations_name[100];
 sprintf(file_body_accelerations_name, "./RESLT/body_accelerations.dat");
 std::ofstream outfile_body_acc;
 outfile_body_acc.open(file_body_accelerations_name, std::ios::out);
 if (outfile_body_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_body_accelerations_name << "]"
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
 
 // Linear accelerations
 char file_linear_accelerations_name[100];
 sprintf(file_linear_accelerations_name, "./RESLT/linear_accelerations.dat");
 std::ofstream outfile_linear_acc;
 outfile_linear_acc.open(file_linear_accelerations_name, std::ios::out);
 if (outfile_linear_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_linear_accelerations_name << "]"
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
 
 // Velocity (North-East)
 char file_velocity_north_east_name[100];
 sprintf(file_velocity_north_east_name, "./RESLT/velocity_north_east.dat");
 std::ofstream outfile_velocity_north_east;
 outfile_velocity_north_east.open(file_velocity_north_east_name, std::ios::out);
 if (outfile_velocity_north_east.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_velocity_north_east_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
#ifdef NAVIGATION_DATA_TO_EVALUATION
 // Navigation data (for evaluation)
 char file_navigation_data_for_evaluation_name[100];
 sprintf(file_navigation_data_for_evaluation_name, "./RESLT/navigation_data_for_evaluation.dat");
 std::ofstream outfile_navigation_data_for_evaluation;
 outfile_navigation_data_for_evaluation.open(file_navigation_data_for_evaluation_name, std::ios::out);
 if (outfile_navigation_data_for_evaluation.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_navigation_data_for_evaluation_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Navigation data (latitude and longitude)
 char file_latitude_and_longitude_name[100];
 sprintf(file_latitude_and_longitude_name, "./RESLT/latitude_and_longitude.dat");
 std::ofstream outfile_latitude_and_longitude;
 outfile_latitude_and_longitude.open(file_latitude_and_longitude_name, std::ios::out);
 if (outfile_latitude_and_longitude.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_latitude_and_longitude_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef NAVIGATION_DATA_TO_EVALUATION
 
 // ----------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 // Odes from UBLOX
#ifdef IDA_40KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/40kmph_ida1.ubx");
#endif // #ifdef IDA_40KMPH_1

#ifdef IDA_40KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/40kmph_ida2.ubx");
#endif // #ifdef IDA_40KMPH_2

#ifdef REGRESO_40KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/40kmph_regreso1.ubx");
#endif // #ifdef REGRESO_40KMPH_1
 
#ifdef REGRESO_40KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/40kmph_regreso2.ubx");
#endif // #ifdef REGRESO_40KMPH_2

#ifdef IDA_50KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/50kmph_ida1.ubx");
#endif // #ifdef IDA_50KMPH_1

#ifdef IDA_50KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/50kmph_ida2.ubx");
#endif // #ifdef IDA_50KMPH_2

#ifdef REGRESO_50KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/50kmph_regreso1.ubx");
#endif // #ifdef REGRESO_50KMPH_1
 
#ifdef REGRESO_50KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/50kmph_regreso2.ubx");
#endif // #ifdef REGRESO_50KMPH_2

#ifdef IDA_60KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/60kmph_ida1.ubx");
#endif // #ifdef IDA_60KMPH_1

#ifdef IDA_60KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/60kmph_ida2.ubx");
#endif // #ifdef IDA_60KMPH_2

#ifdef REGRESO_60KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/60kmph_regreso1.ubx");
#endif // #ifdef REGRESO_60KMPH_1
 
#ifdef REGRESO_60KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/60kmph_regreso2.ubx");
#endif // #ifdef REGRESO_60KMPH_2

#ifdef IDA_70KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/70kmph_ida1.ubx");
#endif // #ifdef IDA_70KMPH_1

#ifdef IDA_70KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/70kmph_ida2.ubx");
#endif // #ifdef IDA_70KMPH_2

#ifdef REGRESO_70KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/70kmph_regreso1.ubx");
#endif // #ifdef REGRESO_70KMPH_1
 
#ifdef REGRESO_70KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/70kmph_regreso2.ubx");
#endif // #ifdef REGRESO_70KMPH_2

#ifdef IDA_80KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/80kmph_ida1.ubx");
#endif // #ifdef IDA_80KMPH_1

#ifdef IDA_80KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/80kmph_ida2.ubx");
#endif // #ifdef IDA_80KMPH_2

#ifdef REGRESO_80KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/80kmph_regreso1.ubx");
#endif // #ifdef REGRESO_80KMPH_1
 
#ifdef REGRESO_80KMPH_2
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/80kmph_regreso2.ubx");
#endif // #ifdef REGRESO_80KMPH_2

#ifdef IDA_90KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/90kmph_ida1.ubx");
#endif // #ifdef IDA_90KMPH_1

#ifdef REGRESO_90KMPH_1
 CCODEsFromSensorsUBLOX odes("./UBLOX/data_atlixco/90kmph_regreso1.ubx");
#endif // #ifdef REGRESO_90KMPH_1 
 
 // ----------------------------------------------------------------
 // Filter data [BEGIN]
 // ----------------------------------------------------------------
 //#define APPLY_FILTER
#ifdef APPLY_FILTER
 
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
 
#endif // #ifdef APPLY_FILTER
 
 // ----------------------------------------------------------------
 // Filter data [END]
 // ----------------------------------------------------------------
 
 // ----------------------------------------------------------------
 // Integrator initialisation [BEGIN]
 // ----------------------------------------------------------------
 // Create the factory for the integration methods
 CCFactoryIntegrationMethod *factory_integration_methods =
  new CCFactoryIntegrationMethod();
 // Create an instance of the integration method
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("Euler");
 //ACIntegrationMethod *integrator =
 // factory_integration_methods->create_integration_method("RK4");
 // Get the number of history values required by the integration
 // method
 const unsigned n_history_values = integrator->n_history_values();
 // Get the number of odes from the problem
 const unsigned n_odes = odes.nodes();
 // Storage for the values of the integrated functions
 std::vector<std::vector<double> > y(n_odes);
 // For each ode we allocate space for the histoy values + 1 (to store
 // the history values and the current one)
 for (unsigned i = 0; i < n_odes; i++)
  {
   y[i].resize(n_history_values+1);
  }
 
 // Iniatilise
 y[0][0] = 0.0; // Initial x-position
 y[1][0] = 0.0; // Initial x-velocity
 y[2][0] = 0.0; // Initial y-position
 y[3][0] = 0.0; // Initial y-velocity
 y[4][0] = 0.0; // Initial z-position
 y[5][0] = 0.0; // Initial z-velocity
 y[6][0] = 0.0; // Initial roll
 y[7][0] = 0.0; // Initial pitch
 y[8][0] = 0.0; // Initial yaw
 y[9][0] = 0.0; // Initial yaw-threshold
 
 odes.set_initial_conditions(y);
 
 // Discretised time
 double current_time = 0;
 double previous_step = 0.0;
 
 // Output the initial data to screen
 std::cout.precision(8);
 std::cout << "t: " << current_time
           << " x-pos: " << y[0][0] << " x-vel: " << y[1][0]
           << " y-pos: " << y[2][0] << " y-vel: " << y[3][0]
           << " z-pos: " << y[4][0] << " z-vel: " << y[5][0]
           << " roll: " << y[6][0] << " pitch: " << y[7][0] << " yaw: " << y[8][0] << std::endl;
 
 // ----------------------------------------------------------------
 // Integrator initialisation [END]
 // ----------------------------------------------------------------

#ifdef NAVIGATION_DATA_TO_EVALUATION
 // ----------------------------------------------------------------
 // Latitude and longitude initialisation [BEGIN]
 // ----------------------------------------------------------------
 bool initialised_navigation_reference_data = false;
 double initial_latitude = 0.0;
 double initial_longitude = 0.0;
 double initial_course_in_radians = 0.0;
 
 double current_latitude = 0.0;
 double current_longitude = 0.0;
 double instantaneous_travelled_distance = 0.0;
 double current_local_course_in_radians = 0.0;
 // ----------------------------------------------------------------
 // Latitude and longitude initialisation [END]
 // ----------------------------------------------------------------
 
 // Previous time
 double previous_time = 0.0;
 // Position x and y from GPS computed from radial position
 double X_POS = 0.0;
 double Y_POS = 0.0;
#endif //  #ifdef NAVIGATION_DATA_TO_EVALUATION
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (continue looping until all data in the input file is
 // processed)
 while(LOOP)
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
   
#ifdef NAVIGATION_DATA_TO_EVALUATION
   // Get latitude and longitude
   std::vector<std::vector<double> > latitude_longitude_from_table = odes.get_latitude_longitude_from_table();
#endif // #ifdef NAVIGATION_DATA_TO_EVALUATION
   
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // PRE-PROCESSING STAGE BLOCK [BEGIN]
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   
   // ==========================================================================
   // Rotate sensors data to match ASIKI's reference frame [BEGIN]
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
   
#if 0
   // Perform the actual rotatations
   rotate_sensors_to_ASIKIs_reference_frame(raw_gyro_t,
                                            raw_acc_t,
                                            rotated_raw_gyro,
                                            rotated_raw_acc);
#endif // #if 0
   
   std::vector<double> Euler_angles_to_rotate_raw_gyro(DIM);
   Euler_angles_to_rotate_raw_gyro[0]=0.0;//y[6][0];
   Euler_angles_to_rotate_raw_gyro[1]=0.0;//y[7][0];
   Euler_angles_to_rotate_raw_gyro[2]=0.0;//y[8][0];
   
   std::vector<double> Euler_angles_to_rotate_raw_acc(DIM);
   Euler_angles_to_rotate_raw_acc[0]=0.0;
   Euler_angles_to_rotate_raw_acc[1]=0.0;
   Euler_angles_to_rotate_raw_acc[2]=0.0;
   
   // Perform the actual rotatations
   rotate_sensors_to_ASIKIs_reference_frame(raw_gyro_t,
                                            raw_acc_t,
                                            rotated_raw_gyro,
                                            rotated_raw_acc,
                                            Euler_angles_to_rotate_raw_gyro,
                                            Euler_angles_to_rotate_raw_acc);
   
   // TODO Check Euler angles difference without abs in MatLab to
   // check "the direction" of the error
   
#ifdef OUTPUT_RAW_AND_ROTATED_SENSORS_DATA
   // --------------------------------------------------------------------------
   // OUTPUT DATA BLOCK [BEGIN]
   // --------------------------------------------------------------------------
   {
    // --------------------------------------------------
    // Output the raw and rotated data for gyro
    for (unsigned i = 0; i < n_gyro_data; i+=10) 
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
    for (unsigned i = 0; i < n_acc_data; i+=10)
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
   // Rotate sensors data to match ASIKI's reference frame [END]
   // ==========================================================================
   
   // ==========================================================================
   // Apply low-pass filter via convolution [BEGIN]
   // ==========================================================================
   
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
   
#ifdef APPLY_FILTER
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
      
#if 1
   // The coefficients of the kernel signal to convolve with the gyro
   // data
   const unsigned n_kernel_gyro = 15;
   double kernel_gyro[] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   
   // The coefficients of the kernel signal to convolve with the
   // accelerometer data
   const unsigned n_kernel_acc = 15;
   double kernel_acc[] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};   
#endif // #if 1
   
#if 0
   // The coefficients of the kernel signal to convolve with the gyro
   // data
   const unsigned n_kernel_gyro = 29;
   double kernel_gyro[] = {0.0049166, 0.0056897, 0.0078865, 0.0114381, 0.0161981, 0.0219499, 0.0284179, \
                           0.0352818, 0.0421945, 0.0488006, 0.0547570, 0.0597516, 0.0635210, 0.0658659, \
                           0.0666616, 0.0658659, 0.0635210, 0.0597516, 0.0547570, 0.0488006, 0.0421945, \
                           0.0352818, 0.0284179, 0.0219499, 0.0161981, 0.0114381, 0.0078865, 0.0056897, \
                           0.0049166};
   
   // The coefficients of the kernel signal to convolve with the
   // accelerometer data
   const unsigned n_kernel_acc = 29;
   double kernel_acc[] = {0.0051848, 0.0059470, 0.0081761, 0.0117697, 0.0165547, 0.0222962, 0.0287089, \
                          0.0354723, 0.0422464, 0.0486897, 0.0544764, 0.0593134, 0.0629553, 0.0652172, \
                          0.0659841, 0.0652172, 0.0629553, 0.0593134, 0.0544764, 0.0486897, 0.0422464, \
                          0.0354723, 0.0287089, 0.0222962, 0.0165547, 0.0117697, 0.0081761, 0.0059470, \
                          0.0051848};
#endif // #if 0
   
#if 0
   // The coefficients of the kernel signal to convolve with the gyro
   // data
   const unsigned n_kernel_gyro = 8;
   double kernel_gyro[] = {0.020640, 0.065486, 0.166411, 0.247463, 0.247463, 0.166411, 0.065486, 0.020640};
   
   // The coefficients of the kernel signal to convolve with the
   // accelerometer data
   const unsigned n_kernel_acc = 8;
   double kernel_acc[] = {0.020706, 0.065570, 0.166414, 0.247310, 0.247310, 0.166414, 0.065570, 0.020706};
#endif // if 0
   
#if 0 // TODO
   // The coefficients of the kernel signal to convolve with the gyro
   // data
   const unsigned n_kernel_gyro = 61;
   double kernel_gyro[] = {0.0017541, 0.0018614, 0.0020869, 0.0024376, 0.0029187, 0.0035331, 0.0042814, \
                           0.0051623, 0.0061718, 0.0073039, 0.0085502, 0.0099002, 0.0113413, 0.0128591, \
                           0.0144373, 0.0160586, 0.0177041, 0.0193543, 0.0209890, 0.0225877, 0.0241301, \
                           0.0255962, 0.0269667, 0.0282234, 0.0293496, 0.0303299, 0.0311510, 0.0318016, \
                           0.0322729, 0.0325583, 0.0326539, 0.0325583, 0.0322729, 0.0318016, 0.0311510, \
                           0.0303299, 0.0293496, 0.0282234, 0.0269667, 0.0255962, 0.0241301, 0.0225877, \
                           0.0209890, 0.0193543, 0.0177041, 0.0160586, 0.0144373, 0.0128591, 0.0113413, \
                           0.0099002, 0.0085502, 0.0073039, 0.0061718, 0.0051623, 0.0042814, 0.0035331, \
                           0.0029187, 0.0024376, 0.0020869, 0.0018614, 0.0017541};
   
   // The coefficients of the kernel signal to convolve with the
   // accelerometer data
   const unsigned n_kernel_acc = 61;
   double kernel_acc[] = {0.0022962, 0.0023817, 0.0026131, 0.0029901, 0.0035107, 0.0041713, 0.0049663, \
                          0.0058885, 0.0069292, 0.0080780, 0.0093232, 0.0106518, 0.0120497, 0.0135018, \
                          0.0149923, 0.0165048, 0.0180224, 0.0195282, 0.0210052, 0.0224366, 0.0238062, \
                          0.0250983, 0.0262981, 0.0273917, 0.0283666, 0.0292115, 0.0299166, 0.0304736, \
                          0.0308762, 0.0311197, 0.0312012, 0.0311197, 0.0308762, 0.0304736, 0.0299166, \
                          0.0292115, 0.0283666, 0.0273917, 0.0262981, 0.0250983, 0.0238062, 0.0224366, \
                          0.0210052, 0.0195282, 0.0180224, 0.0165048, 0.0149923, 0.0135018, 0.0120497, \
                          0.0106518, 0.0093232, 0.0080780, 0.0069292, 0.0058885, 0.0049663, 0.0041713, \
                          0.0035107, 0.0029901, 0.0026131, 0.0023817, 0.0022962};   
#endif // #if 0
   
   // TODO Do not apply filter
   
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

#else
   // Copy the data
   for (unsigned i = 0; i < n_gyro_data; i++)
    {
     filtered_gyro_signal_x[i] = rotated_raw_gyro[i][0];
     filtered_gyro_signal_y[i] = rotated_raw_gyro[i][1];
     filtered_gyro_signal_z[i] = rotated_raw_gyro[i][2];
    }
   
   // Copy the data
   for (unsigned i = 0; i < n_acc_data; i++)
    {
     filtered_acc_signal_x[i] = rotated_raw_acc[i][0];
     filtered_acc_signal_y[i] = rotated_raw_acc[i][1];
     filtered_acc_signal_z[i] = rotated_raw_acc[i][2];
    }
   
#endif // #ifdef APPLY_FILTER
   
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
   // Apply low-pass filter via convolution [END]
   // ==========================================================================
   
   // ==========================================================================
   // Align time stamps for Gyro and Accelerometers [BEGIN]
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
   
   //#define APPLY_TIME_STAMPS_ALIGNMENT
#ifdef APPLY_TIME_STAMPS_ALIGNMENT
   
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

#else
   
   // Copy the data
   for (unsigned i = 0; i < n_data; i++)
    {
     aligned_time[i] = filtered_gyro_signal_t[i];
     aligned_gyro_signal_x[i] = filtered_gyro_signal_x[i];
     aligned_gyro_signal_y[i] = filtered_gyro_signal_y[i];
     aligned_gyro_signal_z[i] = filtered_gyro_signal_z[i];
     aligned_acc_signal_x[i] = filtered_acc_signal_x[i];
     aligned_acc_signal_y[i] = filtered_acc_signal_y[i];
     aligned_acc_signal_z[i] = filtered_acc_signal_z[i];
    }
   
#endif // #ifde APPLY_TIME_STAMPS_ALIGNMENT
   
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
   
   // ==========================================================================
   // Align time stamps for Gyro and Accelerometers [BEGIN]
   // ==========================================================================
   
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // PRE-PROCESSING STAGE BLOCK [END]
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ALGORITHM CORE STAGE BLOCK [BEGIN]
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   
   // Loop over the data and process each pair of gyro-accelerometers
   // data (main processing)
   for (unsigned i = 0; i < n_data; i++)
    {
     // Get the discretised time for this set of data
     current_time = aligned_time[i];
     
     // Get Euler angles at current time
     double Euler_angles[DIM];
     Euler_angles[0] = y[6][0];
     Euler_angles[1] = y[7][0];
     Euler_angles[2] = y[8][0];
     
#ifdef OUTPUT_EULER_ANGLES
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [BEGIN]
     // --------------------------------------------------------------------------
     {
      // Euler angles
      outfile_roll_pitch_yaw << current_time
                             << " " << Euler_angles[0]
                             << " " << Euler_angles[1]
                             << " " << Euler_angles[2] << std::endl;
     }
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [END]
     // --------------------------------------------------------------------------
#endif //#ifdef OUTPUT_EULER_ANGLES
     
     // ==========================================================================
     // Process gyro's data [BEGIN]
     // ==========================================================================
     
#ifdef AZGADS_CONSTANT
     aligned_gyro_signal_x[i]*= AZGADS_CONSTANT;
     aligned_gyro_signal_y[i]*= AZGADS_CONSTANT;
     aligned_gyro_signal_z[i]*= AZGADS_CONSTANT;
#endif
     
     // ----------------------------------------------------------
     // Transform from angular velocities to Euler angles rates
     // ----------------------------------------------------------
     
     // Current time angular velocities
     double angular_velocities[DIM];
     angular_velocities[0] = aligned_gyro_signal_x[i];
     angular_velocities[1] = aligned_gyro_signal_y[i];
     angular_velocities[2] = aligned_gyro_signal_z[i];
     
     // The resulting Euler angles rates
     double Euler_angles_rates[DIM];
     // The thresholded Euler angles rates
     double Euler_angles_rates_thresholded[DIM];
     
     transform_angular_velocities_into_euler_angles_rates(angular_velocities,
                                                          Euler_angles,
                                                          Euler_angles_rates,
                                                          Euler_angles_rates_thresholded);
     
#ifdef FORCE_USING_EULER_ANGLES_RATES_FROM_GEOFOG3D
     Euler_angles_rates[0]=second_gyro_from_table[i][1];
     Euler_angles_rates[1]=second_gyro_from_table[i][2];
     Euler_angles_rates[2]=second_gyro_from_table[i][3];
#endif // #ifdef FORCE_USING_EULER_ANGLES_RATES_FROM_GEOFOG3D
     
     // Set Euler into the odes such that they are integrated later
     odes.euler_angles_rates() = Euler_angles_rates;
     
#ifdef OUTPUT_EULER_ANGLES_RATES
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [BEGIN]
     // --------------------------------------------------------------------------
     {
      // Euler angles rates
      outfile_euler_angles_rates << current_time
                                 << " " << Euler_angles_rates[0]
                                 << " " << Euler_angles_rates[1]
                                 << " " << Euler_angles_rates[2] << std::endl;
     }
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [END]
     // --------------------------------------------------------------------------
#endif //#ifdef OUTPUT_EULER_ANGLES_RATES
     
#ifdef GYRO_THRESHOLD_Z
     // Set Yaw obtained from thresholded gyro angular rates (this
     // sets the value dy[9] to later compute y[0][9])
     odes.yaw_change_rate_with_threshold() = Euler_angles_rates_thresholded[2];
#endif // #ifdef GYRO_THRESHOLD_Z
     // ==========================================================================
     // Process gyro's data [END]
     // ==========================================================================
     
     
     // ==========================================================================
     // Process acceleration data [BEGIN]
     // ==========================================================================
     
     // Pre-process aligned acceleration data
     //aligned_acc_signal_x[i]-=0.26;
     //aligned_acc_signal_y[i]-=0.01;
     //aligned_acc_signal_z[i]+=0.16;
     
     // Get Euler angles approximation from accelerations (we will use
     // this data after integration when applying a complementary
     // filter)
     double Euler_angles_from_acc[DIM];
     //Euler_angles_from_acc[0]=atan2(aligned_acc_signal_y[i], -aligned_acc_signal_z[i]);
     Euler_angles_from_acc[0]=atan2(-aligned_acc_signal_y[i], -aligned_acc_signal_z[i]);
     //Euler_angles_from_acc[1]=atan2(-aligned_acc_signal_x[i],
     //                               sqrt(aligned_acc_signal_y[i]*aligned_acc_signal_y[i]+
     //                                    aligned_acc_signal_z[i]*aligned_acc_signal_z[i]));
     Euler_angles_from_acc[1]=atan2(aligned_acc_signal_x[i],
                                    sqrt(aligned_acc_signal_y[i]*aligned_acc_signal_y[i]+
                                         aligned_acc_signal_z[i]*aligned_acc_signal_z[i]));
     Euler_angles_from_acc[2]=atan2(sqrt(aligned_acc_signal_x[i]*aligned_acc_signal_x[i]+
                                         aligned_acc_signal_y[i]*aligned_acc_signal_y[i]),
                                    aligned_acc_signal_x[i]);
     
     // ==========================================================================
     // Process acceleration data [END]
     // ==========================================================================
     
#ifdef OUTPUT_EULER_ANGLES_FROM_GYRO_AND_ACCELEROMETER
     outfile_euler_angles_from_gyro << current_time
                                    << " " << Euler_angles[0]
                                    << " " << Euler_angles[1]
                                    << " " << Euler_angles[2] << std::endl;
     
     outfile_euler_angles_from_accelerometer << current_time
                                             << " " << Euler_angles_from_acc[0]
                                             << " " << Euler_angles_from_acc[1]
                                             << " " << Euler_angles_from_acc[2] << std::endl;
#endif // #ifdef OUTPUT_EULER_ANGLES_FROM_GYRO_AND_ACCELEROMETER
     
     // ==========================================================================
     // Gravity compensation [BEGIN]
     // ==========================================================================
     
     // Store body frame accelerations
     double body_accelerations[DIM];
     body_accelerations[0]=aligned_acc_signal_x[i];
     body_accelerations[1]=aligned_acc_signal_y[i];
     body_accelerations[2]=aligned_acc_signal_z[i];
          
     // -------------------------------------------
     // Gravity compensation
     // -------------------------------------------
     
     // Store the gravity in the inertial frame (negative because we
     // want to subtract it later)
     double gravity_in_inertial_frame[DIM];
     gravity_in_inertial_frame[0]=0.0;
     gravity_in_inertial_frame[1]=0.0;
     gravity_in_inertial_frame[2]=-GRAVITY;
     //gravity_in_inertial_frame[2]=1.0; // TODO
     // Store the gravity in the body frame
     double gravity_in_body_frame[DIM];
     
     // Transform gravity into body frame
     transform_inertial_to_body(Euler_angles, gravity_in_inertial_frame, gravity_in_body_frame);
     
#ifdef OUTPUT_GRAVITY_IN_BODY_FRAME
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [BEGIN]
     // --------------------------------------------------------------------------
     {
      // Gravity in body frame
      outfile_gravity_in_body_frame << current_time
                                    << " " << gravity_in_body_frame[0]
                                    << " " << gravity_in_body_frame[1]
                                    << " " << gravity_in_body_frame[2] << std::endl;
     }
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [END]
     // --------------------------------------------------------------------------
#endif //#ifdef OUTPUT_GRAVITY_IN_BODY_FRAME
     
     // -------------------------------------------------------
     // Subtract gravity (in body frame) to generate linear
     // acceleration (in body frame)
     // -------------------------------------------------------
      
     // Linear acceleration storage
     double linear_accelerations[DIM];
     // Subtract gravity (gravity compensation)
     //linear_accelerations[0]=body_accelerations[0] - 0.4942;
     //linear_accelerations[0]=body_accelerations[0] * 1.3298;
     //linear_accelerations[0]=body_accelerations[0]-gravity_in_body_frame[0] + 0.06;
     //     linear_accelerations[0]=body_accelerations[0]-gravity_in_body_frame[0]+0.1589;
     //     linear_accelerations[1]=body_accelerations[1]-gravity_in_body_frame[1]-0.0816;
     //     linear_accelerations[2]=body_accelerations[2]-gravity_in_body_frame[2]-0.0041;
     
     // The shift of the acceleartions is computed from the average
     // errro of each acceleration axis
     //linear_accelerations[0]=body_accelerations[0]-gravity_in_body_frame[0]-0.0022;//+0.1589;
     //linear_accelerations[1]=body_accelerations[1]-gravity_in_body_frame[1]-0.1156;//-0.0816;//-0.12;//TODO shift
     //linear_accelerations[2]=body_accelerations[2]-gravity_in_body_frame[2]-0.0084;
     
     linear_accelerations[0]=body_accelerations[0]-gravity_in_body_frame[0];
     linear_accelerations[1]=body_accelerations[1]-gravity_in_body_frame[1];
     linear_accelerations[2]=body_accelerations[2]-gravity_in_body_frame[2];
#if 0
     for (unsigned j = 0; j < DIM; j++)
      {
       if (linear_accelerations[i] < 0.0)
        {
         linear_accelerations[i]*=1.01;//-1.67;
        }
       
       if (linear_accelerations[i] > 0.0)
        {
         linear_accelerations[i]=0.0;
        }
      }
#endif // #if 0
     
#ifdef APPLY_LINEAR_ACCELERATIONS_OFFSET
     linear_accelerations[0]-=0.0022;//+0.1589;
     linear_accelerations[1]-=0.1156;//-0.0816;//-0.12;//TODO shift
     linear_accelerations[2]-=0.0084;
#endif // #ifdef APPLY_LINEAR_ACCELERATIONS_OFFSET
     
#ifdef FORCE_USING_LINEAR_ACCELERATIONS_FROM_GEOFOG3D
     linear_accelerations[0]=linear_acceleration_from_table[i][1];
     linear_accelerations[1]=linear_acceleration_from_table[i][2];
     linear_accelerations[2]=linear_acceleration_from_table[i][3];
#endif // #ifdef FORCE_USING_LINEAR_ACCELERATIONS_FROM_GEOFOG3D
     
     // Set the values for linear acceleration into the odes to
     // integrate later
     odes.linear_acceleration() = linear_accelerations;
     
     // ----------------------------------------------------------
     // Transform linear acceleration from body frame to inertial
     // frame
     // ----------------------------------------------------------
     
     // Store inertial frame accelerations
     double inertial_accelerations[DIM];
     transform_body_to_inertial(Euler_angles, linear_accelerations, inertial_accelerations);
     
#ifdef OUTPUT_ACCELERATIONS
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [BEGIN]
     // --------------------------------------------------------------------------
     {
      // Body frame accelerations
      outfile_body_acc << current_time
                       << " " << body_accelerations[0]
                       << " " << body_accelerations[1]
                       << " " << body_accelerations[2] << std::endl;
      
      // Linear accelerations
      outfile_linear_acc << current_time
                         << " " << linear_accelerations[0]
                         << " " << linear_accelerations[1]
                         << " " << linear_accelerations[2] << std::endl;
      
      // Inertial frame accelerations
      outfile_inertial_acc << current_time
                           << " " << inertial_accelerations[0]
                           << " " << inertial_accelerations[1]
                           << " " << inertial_accelerations[2] << std::endl;
     }
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [END]
     // --------------------------------------------------------------------------
#endif //#ifdef OUTPUT_ACCELERATIONS
     
     // ==========================================================================
     // Gravity compensation [END]
     // ==========================================================================

     // ==========================================================================
     // Velocity processing [BEGIN]
     // ==========================================================================
     
#ifdef OUTPUT_VELOCITIES
     // --------------------------------------------------------------------------
     // OUTPUT DATA BLOCK [BEGIN]
     // --------------------------------------------------------------------------
     {
      // Linear velocity
      outfile_velocity << current_time
                       << " " << y[1][0]
                       << " " << y[3][0]
                       << " " << y[5][0]
                       << std::endl;
      
      // North-east velocities
      const double course_angle = y[8][0];
      //const double north_velocity = y[1][0]*sin(course_angle);// + y[3][0]*cos(course_angle);
      //const double east_velocity = y[1][0]*cos(course_angle);// + y[3][0]*sin(course_angle);
      //const double down_velocity = 0.0;
      const double north_velocity = y[1][0]*sin(M_PI/2.0 - course_angle);// + y[3][0]*sin(course_angle);
      const double east_velocity = y[1][0]*cos(M_PI/2.0 - course_angle);// - y[3][0]*cos(course_angle);
      const double down_velocity = 0.0;
      outfile_velocity_north_east << current_time
                                  << " " << north_velocity
                                  << " " << east_velocity
                                  << " " << down_velocity
                                  << std::endl;
     }
#endif // #ifdef OUTPUT_VELOCITIES
     
     // ==========================================================================
     // Velocity processing [END]
     // ==========================================================================
     
     // ==========================================================================
     // Integrate the ODE's [BEGIN]
     // ==========================================================================
     // Compute the step size
     double step = previous_step;
     if (i < n_data - 1)
      {
        step = aligned_time[i+1] - aligned_time[i];
      }
     previous_step = step;
     
     integrator->integrate_step(odes, step, current_time, y);
     
     // Update data (shift the history values)
     for (unsigned j = 0; j < n_odes; j++)
      {
       for (unsigned k = 0; k < n_history_values; k++)
        {
         y[j][k] = y[j][k+1];
        }
      }
     // Update time
     current_time+=step;
     
     // ==========================================================================
     // Integrate the ODE's [END]
     // ==========================================================================
     
     // ==========================================================================
     // Complementary filter [BEGIN]
     // ==========================================================================
     // Complementary filter parameter
     //const double alpha = 0.9995;
     //const double alpha = 0.1;
     const double alpha = 0.5; // 70kmph_ida1
     
#ifndef OUTPUT_EULER_ANGLES_FROM_GYRO_AND_ACCELEROMETER // Complementary
                                                        // filter is
                                                        // applied if
                                                        // no Euler
                                                        // angles from
                                                        // gyro and
                                                        // accelerometers
                                                        // are
                                                        // required
     
     // Update Euler angles
     y[6][0] = alpha * y[6][0] + (1.0 - alpha) * Euler_angles_from_acc[0];
     y[7][0] = alpha * y[7][0] + (1.0 - alpha) * Euler_angles_from_acc[1];
     //y[6][0]-=0.0374;
     //y[7][0]-=0.0891;
#ifdef GYRO_THRESHOLD_Z
     // Complementary filter of Yaw with Yaw threshold
     y[8][0] = alpha * y[8][0] + (1.0 - alpha) * y[9][0];
#endif // #ifdef GYRO_THRESHOLD_Z
     
#ifdef FORCE_USING_EULER_ANGLES_FROM_GEOFOG3D
     // FORCE the use of Euler angles from table
     y[6][0]=Euler_angles_from_table[i][1];
     y[7][0]=Euler_angles_from_table[i][2];
     y[8][0]=Euler_angles_from_table[i][3];
#endif // #ifdef FORCE_USING_EULER_ANGLES_FROM_GEOFOG3D
     
#ifdef APPLY_EULER_ANGLES_OFFSET
     y[6][0]+=0.0012;
     y[7][0]+=0.0091;
     y[8][0]+=0.0752;
#endif // #ifdef APPLY_EULER_ANGLES_OFFSET
     
     //const double alpha_vel = 0.90;
     //y[1][0] = y[1][0] * alpha_vel + (1.0 - alpha_vel) * previous_speed_in_m_per_sec_from_gps;
     //y[1][0] = y[1][0] * alpha_vel + (1.0 - alpha_vel) * 5.2274;
     //y[1][0] = y[1][0] * alpha_vel + (1.0 - alpha_vel) * 10.4548;
     
#endif // #ifndef OUTPUT_EULER_ANGLES_FROM_GYRO_AND_ACCELEROMETER
     
     // ==========================================================================
     // Complementary filter [END]
     // ==========================================================================
     
#ifdef NAVIGATION_DATA_TO_EVALUATION
     const double dt = current_time - previous_time;
     const double x_speed_in_m_per_sec = y[1][0];
     const double y_speed_in_m_per_sec = y[3][0];
     const double z_speed_in_m_per_sec = y[5][0];
     //     const double total_speed_in_m_per_sec = sqrt(x_speed_in_m_per_sec*x_speed_in_m_per_sec)+
     //      (y_speed_in_m_per_sec*y_speed_in_m_per_sec);
     const double total_speed_in_m_per_sec = x_speed_in_m_per_sec+y_speed_in_m_per_sec;
#ifdef USE_COURSE_FROM_GPS
     const double course_angle = latitude_longitude_from_table[0][3];
#else
     const double course_angle = y[8][0];
#endif // #ifdef USE_COURSE_FROM_GPS
     
     // Set the current course_angle
     current_local_course_in_radians = course_angle;
     // Set the current travelled distance
     instantaneous_travelled_distance = x_speed_in_m_per_sec * dt;
     
     // Compute x and y position from angle and radial position
     X_POS+= x_speed_in_m_per_sec*dt*cos(course_angle);
     Y_POS+= y_speed_in_m_per_sec*dt*sin(course_angle);
     
     // Set initial latitude and longitude
     if (!initialised_navigation_reference_data)
      {
       initial_latitude = latitude_longitude_from_table[0][1];
       initial_longitude = latitude_longitude_from_table[0][2];
#ifdef USE_COURSE_FROM_GPS
       // do nothing
#else 
       initial_course_in_radians = latitude_longitude_from_table[0][3]; // Get the initial course
#endif
       
       // Initialise current latitude and longitude data
       current_latitude = initial_latitude * TO_RADIANS;
       current_longitude = initial_longitude * TO_RADIANS;
       
       initialised_navigation_reference_data = true;
      }
     
     // Compute the current earth referenced course
     const double earth_referenced_course_in_radians =
      initial_course_in_radians + current_local_course_in_radians;
     
     // Get the latitude and longitude
     compute_current_latitude_and_longitude(instantaneous_travelled_distance,
                                            earth_referenced_course_in_radians,
                                            current_latitude, current_longitude);

     // -----------------------------------------------------------------------------------
     outfile_latitude_and_longitude << current_time << " "
                                    << current_latitude * TO_DEGREES << " "
                                    << current_longitude * TO_DEGREES << std::endl;
     
     // -----------------------------------------------------------------------------------
     outfile_navigation_data_for_evaluation << current_time << " "
                                            << latitude_longitude_from_table[0][2] << " "
                                            << latitude_longitude_from_table[0][1] << " "
                                            << x_speed_in_m_per_sec*3.6 << " "
                                            << X_POS << " " << Y_POS << " "
      //<< y[0][0] << " " << y[2][0] << " "
      //<< total_speed_in_m_per_sec * dt << " " // TODO
                                            << instantaneous_travelled_distance << " "
      //                                            << current_local_course_in_radians*TO_DEGREES << std::endl;
                                            << earth_referenced_course_in_radians*TO_DEGREES << std::endl;
          
     // Update previous time
     previous_time=current_time;
#endif //  #ifdef NAVIGATION_DATA_TO_EVALUATION
     
    } // for (i < n_data-1)
   
   std::cout.precision(8);
   std::cout << "t: " << current_time
             << " x-pos: " << y[0][0] << " x-vel: " << y[1][0]
             << " y-pos: " << y[2][0] << " y-vel: " << y[3][0]
             << " z-pos: " << y[4][0] << " z-vel: " << y[5][0]
             << " roll: " << y[6][0] << " pitch: " << y[7][0] << " yaw: " << y[8][0] << std::endl;
   
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ALGORITHM CORE STAGE BLOCK [END]
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   
  } // while(LOOP)
 
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
 outfile_euler_angles_rates.close();
 outfile_euler_angles_from_gyro.close();
 outfile_euler_angles_from_accelerometer.close();
 
 outfile_roll_pitch_yaw.close();
 outfile_gravity_in_body_frame.close();
 outfile_body_acc.close();
 outfile_inertial_acc.close();
 outfile_linear_acc.close();
 outfile_velocity.close();
 outfile_velocity_north_east.close();
 
#ifdef NAVIGATION_DATA_TO_EVALUATION
 outfile_navigation_data_for_evaluation.close();
 outfile_latitude_and_longitude.close();
#endif // #ifdef NAVIGATION_DATA_TO_EVALUATION
 
 // Free memory
 delete integrator;
 integrator = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

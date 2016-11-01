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

#define CORRECT_ACCELEROMETER_MISALIGNMENT
#define LOWER_THRESHOLD 1.0
//#define LOWER_THRESHOLD 9.81 * 0.1
#define GRAVITY 9.81
//#define GRAVITY_TO_BODY_FRAME
//#define INERTIAL_ACCELERATION_THRESHOLD GRAVITY

using namespace chapchom;

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

int main(int argc, char *argv[])
{
 // Initialise chapchom
 initialise_chapchom();
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 // The ode's
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/Cadenas_GNSS.txt");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_1_espera.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_2_sin_espera_basura.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_3_sin_espera_sin_basura.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_4_sin_espera_sin_basura_final.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_5_espera_large.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_6_espera_large.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_7_espera_large.log");
 //CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_8_car_ride_square_wait_large.log");
 CCODEsFromSensorsTelitSL869DR odes("./TelitSL869-DR/putty_9_car_ride_tona_acatepec_inaoe_wait_large.log");
 // Create the factory for the methods
 CCFactoryIntegrationMethod *factory_integration_methods =
  new CCFactoryIntegrationMethod();
 // Create an instance of the integrator method
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("Euler");
 // ACIntegrationMethod *integrator =
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
 std::ofstream outfile_intertial_acc;
 outfile_intertial_acc.open(file_inertial_accelerations_name, std::ios::out);
 if (outfile_intertial_acc.fail())
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
 
 // ----------------------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------------------
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (steps, h, initial
 // values)
 // -----------------------------------------------------------------
 // The step size is given by the number of data we have in a second
 // (15Hz)
 double h = 0.0;
 
 // Current time
 double time = 0.0;
 
 // Matrix that relates the angular velocities with the Euler rates
 std::vector<std::vector<double> >A(DIM);
 for (unsigned i = 0; i < DIM; i++)
  {
   A[i].resize(DIM);
  }
 
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
 y[0][8] = 0.0; // Initial yaw
 
 // Output the initial data to screen
 std::cout << "t: " << time
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
           << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;

 bool LOOP = true;

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
   // The step size is given by the number of data reported in a second
   h = 1.0 / n_acc_data;
   for (unsigned i = 0; i < n_acc_data; i++)
    {
     // ----------------------------------------------------------
     // ----------------------------------------------------------
     // Process the gyros data
     // ----------------------------------------------------------
     // ----------------------------------------------------------     
     
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
     
     // --------------------------
     // Get the Euler angles
     // --------------------------
     // Store the Euler-angles
     std::vector<double> euler_angles(DIM);
     euler_angles[0] = y[0][6];
     euler_angles[1] = y[0][7];
     euler_angles[2] = y[0][8];
     
     // Fill the matrix that transforms from angular velocities to
     // Euler-rates
     fill_angular_velocities_to_euler_rates_matrix(A, euler_angles);
     
     // Get the current reading from sensors
     // Gyro
     std::vector<double> gyro_t = odes.get_angular_rates(i);
     // Copy the data into a 3x3 vector
     std::vector<double> gyro(DIM);
     for (unsigned j = 0; j < DIM; j++)
      {
       gyro[j] = gyro_t[j+1];
       //gyro[j] = 0.0;
# if 0 // TODO: tachidok, what if we set the yaw data to 0.0 dps
       if (j == 2)
        {
         gyro[j] = 0.0;
        }
#endif
      }
     
     // Store the Euler-angles rates
     std::vector<double> euler_angular_rates(DIM);
     multiply_matrix_times_vector(A, gyro, euler_angular_rates);
     //euler_angular_rates[0] = 0.0;
     //euler_angular_rates[1] = 0.0;
     //euler_angular_rates[2] = 0.0;
     // Set the Euler angular rates
     odes.euler_angular_rates() = euler_angular_rates;
     
     // ----------------------------------------------------------
     // ----------------------------------------------------------
     // Process the acceleration data
     // ----------------------------------------------------------
     // ----------------------------------------------------------     
     // Get the readings from sensors
     // Accelerations
     std::vector<double> acc_t = odes.get_accelerations(i);
     // Copy the data into a 3x3 vector
     std::vector<double> acc(DIM);
     // ... and multiply by 9.81 since the data from the gyro are
     // given in 'g' units
     for (unsigned j = 0; j < DIM; j++)
      {
       acc[j] = acc_t[j+1] * GRAVITY;
      }
     
#ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     // Correct accelerations due to misalignment on device
     {
      double tmp = acc[0];
      acc[0] = acc[1];
      acc[1] = tmp*(-1.0);
     }
#endif // #ifdef CORRECT_ACCELEROMETER_MISALIGNMENT
     
#if 0 // TODO
     // Filter accelerations data?
     for (unsigned j = 0; j < DIM; j++)
      {
       if (fabs(acc[j] - LOWER_THRESHOLD) < 0.0)
        {
         acc[j] = 0.0;
        }
      }
#endif // #if 0
     
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
     const double alpha = 1.0;
     //const double alpha_yaw = 1.0;
     
     // Transform accelerations to angles
     std::vector<double> acc_angles(3, 0.0);
     //acc_angles[0] = atan2(acc_inertial[2], acc_inertial[1]);
     //acc_angles[1] = atan2(acc_inertial[0], acc_inertial[2]);
     //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
     
     //acc_angles[0] = atan2(acc_inertial[1], acc_inertial[2]);
     //acc_angles[1] = atan2(-acc_inertial[0], sqrt(acc_inertial[1]*acc_inertial[1]+acc_inertial[2]*acc_inertial[2]));
     //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
   
     acc_angles[0] = atan2(acc[1], acc[2]);
     acc_angles[1] = atan2(-acc[0], sqrt(acc[1]*acc[1]+acc[2]*acc[2]));
     //acc_angles[2] = atan2(acc[2], sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
     acc_angles[2] = atan2(sqrt(acc[0]*acc[0]+acc[1]*acc[1]), acc[0]); // HERE
   
     //acc_angles[2] = atan2(acc[1], acc[0]);
     //acc_angles[2] = atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
     //acc_angles[2] = (atan2(acc[1], acc[0]) + atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]))) / 2.0;
   
     // Update filtered Euler angles
     y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
     y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
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
     for (unsigned i = 0; i < DIM; i++)
      {
       R[i].resize(DIM);
       R_t[i].resize(DIM);
      }
     
     // Fill rotation matrices
     fill_rotation_matrices(R, R_t, y[0][6], y[0][7], y[0][8]); // tachidok
     
     // Transform from the body reference frame to the inertial
     // reference frame
     std::vector<double> acc_inertial(3, 0.0);
#ifdef GRAVITY_TO_BODY_FRAME
     std::vector<double> gravity(3, 0.0);
     gravity[2] = GRAVITY;
     std::vector<double> body_frame_gravity(3, 0.0);
     multiply_matrix_times_vector(R, gravity, body_frame_gravity);//tachidok
     for (unsigned i = 0; i < DIM; i++)
      {
       acc_inertial[i] = acc[i] - body_frame_gravity[i];
      }
#else
     multiply_matrix_times_vector(R_t, acc, acc_inertial);//tachidok
     // Substract gravity
     acc_inertial[2]-=GRAVITY;     
#endif // #ifdef GRAVITY_TO_BODY_FRAME
     
#if 0
     // Check whether inertial acceleration is meaningless
     for (unsigned i = 0; i < DIM; i++)
      {
       if (fabs(acc_inertial[i]) < INERTIAL_ACCELERATION_THRESHOLD)
        {
         acc_inertial[i] = 0.0;
        }
      }
#endif // #if 0
     
     // Set linear acceleration
     odes.linear_acceleration() = acc_inertial;
     
     // -----------------------------------------------------------------
     // Integrate
     // -----------------------------------------------------------------
     integrator->integrate_step(odes, h, time, y);
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
     // Velocity
     outfile_velocity << time
                      << " " << y[0][1]
                      << " " << y[0][3]
                      << " " << y[0][5]
      //                      << " " << std::sqrt(y[0][1] * y[0][1] + y[0][3] * y[0][3] + y[0][5] * y[0][5])
                      << " " << std::sqrt(y[0][1] * y[0][1] + y[0][3] * y[0][3])
                      << std::endl;
     // Raw gyro
     outfile_raw_gyro << time
                      << " " << gyro[0]
                      << " " << gyro[1]
                      << " " << gyro[2] << std::endl;
     // Euler angles rates
     outfile_euler_angles_rates << time
                                << " " << euler_angular_rates[0]
                                << " " << euler_angular_rates[1]
                                << " " << euler_angular_rates[2] << std::endl;     
     // Raw accelerations
     outfile_raw_acc << time
                     << " " << acc[0]
                     << " " << acc[1]
                     << " " << acc[2] << std::endl;
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
     // Inertial accelerations
     outfile_intertial_acc << time
                           << " " << acc_inertial[0]
                           << " " << acc_inertial[1]
                           << " " << acc_inertial[2] << std::endl;
     // Euler angles
     outfile_roll_pitch_yaw << time
                            << " " << y[0][6]
                            << " " << y[0][7]
                            << " " << y[0][8] << std::endl;
   
     // Euler angles from accelerations
     outfile_roll_pitch_yaw_from_acc << time
                                     << " " << acc_angles[0]
                                     << " " << acc_angles[1]
                                     << " " << acc_angles[2] << std::endl;
   
     std::cout << "t: " << time
               << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
               << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
               << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
               << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
   
    }
   
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 outfile_position.close();
 outfile_velocity.close();
 outfile_raw_gyro.close();
 outfile_euler_angles_rates.close();
 outfile_raw_acc.close();
#ifdef GRAVITY_TO_BODY_FRAME
 outfile_body_frame_gravity.close();
#endif // #ifdef GRAVITY_TO_BODY_FRAME
 outfile_intertial_acc.close();
 outfile_roll_pitch_yaw.close();
 outfile_roll_pitch_yaw_from_acc.close();
 
 // Free memory
 delete integrator;
 integrator = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

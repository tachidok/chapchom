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
// The nmea decoder
#include "cc_nmea_decoder.h"

using namespace chapchom;

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
 CCODEsFromSensorsTelitSL869DR odes("./bin/Cadenas_GNSS.txt");
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
 // The step size is variable and depends on the number of data
 // received from the sensors
 double h = 0.0;
 
 // Current time (this will be given by the first reading from the
 // sensors)
 std::vector<double> t;
 
 // -----------------------------------------------------------------------------
 // Initialise
 // -----------------------------------------------------------------------------
  
 // Get the readings from sensores
 // Accelerations
 std::vector<std::vector<double> > acc(DIM);
 // Gyro data
 std::vector<std::vector<double> > dtheta(DIM);
 // Retrieve data from sensors
 odes.get_sensors_lecture(t, acc, dtheta, euler_angles); // tachidok
 
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
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
           << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
 
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
 const double alpha = 0.98;
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
 acc_angles[2] = atan2(acc[2], sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
 //acc_angles[2] = atan2(sqrt(acc[0]*acc[0]+acc[1]*acc[1]), acc[0]); // HERE
 
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
 // Extract gravity and output the raw and the modified accelerations
 
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
 
 // Transform from the body reference frame to the inertial reference
 // frame
 std::vector<double> acc_inertial(3, 0.0);
 multiply_matrix_times_vector(R_t, acc, acc_inertial);//tachidok
 // Substract gravity
 acc_inertial[2]-=9.81;
 
 // Set linear acceleration
 odes.linear_acceleration() = acc_inertial;
 
 // -----------------
 // Output data
 // -----------------
 // Position
 outfile_position << t << " " << y[0][0] << " " << y[0][2] << " " << y[0][4] << std::endl; 
 // Velocity
 outfile_velocity << t << " " << y[0][1] << " " << y[0][3] << " " << y[0][5] << std::endl;
 // Raw accelerations
 outfile_raw_acc << t << " " << acc[0] << " " << acc[1] << " " << acc[2] << std::endl;
 // Inertial accelerations
 outfile_intertial_acc << t << " " << acc_inertial[0] << " "
                       << acc_inertial[1] << " " << acc_inertial[2] << std::endl;
 // Euler angles
 outfile_roll_pitch_yaw << t << " " << y[0][6] << " " << y[0][7] << " " << y[0][8] << std::endl;
 // Euler angles from accelerations
 outfile_roll_pitch_yaw_from_acc << t << " " << acc_angles[0] << " "
                                 << acc_angles[1] << " " << acc_angles[2] << std::endl;
 
 // -----------------------------------------------------------------
 // Integrate
 // -----------------------------------------------------------------
 //integrator->integrate(*odes, h, t_initial, t_final, y);
 for (unsigned i = 0; i < n_steps; i++)
  {
   integrator->integrate_step(*odes, h, t, y);
   // Update data
   for (unsigned j = 0; j < n_odes; j++)
    {
     y[0][j] = y[1][j];
    }
   // Update time
   t+=h;
   
   std::cout << "t: " << t
             << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
             << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
             << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
             << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
   
   // Get the accelerometers readings from the Table
   odes.get_sensors_lecture(t, acc, dtheta, magnetometer, euler_angles);
   
   // -------------------------------------------------------------------
   // Apply complementary filter
   // -------------------------------------------------------------------
   // Transform accelerations to angles
   //acc_angles[0] = atan2(acc_inertial[2], acc_inertial[1]);
   //acc_angles[1] = atan2(acc_inertial[0], acc_inertial[2]);
   //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
   
   //acc_angles[0] = atan2(acc_inertial[1], acc_inertial[2]);
   //acc_angles[1] = atan2(-acc_inertial[0], sqrt(acc_inertial[1]*acc_inertial[1]+acc_inertial[2]*acc_inertial[2]));
   //acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
   
   acc_angles[0] = atan2(acc[1], acc[2]);
   acc_angles[1] = atan2(-acc[0], sqrt(acc[1]*acc[1]+acc[2]*acc[2]));
   acc_angles[2] = atan2(acc[2], sqrt(acc[0]*acc[0]+acc[2]*acc[2]));
   
   //acc_angles[2] = atan2(sqrt(acc[0]*acc[0]+acc[1]*acc[1]), acc[0]); // HERE
   
   //acc_angles[2] = atan2(acc[1], acc[0]);
   //acc_angles[2] = atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
   //acc_angles[2] = (atan2(acc[1], acc[0]) + atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]))) / 2.0;
   
   mag_proc[0] = atan2(magnetometer[1], magnetometer[2]);
   mag_proc[1] = atan2(-magnetometer[0], sqrt(magnetometer[1]*magnetometer[1]+magnetometer[2]*magnetometer[2]));
   mag_proc[2] = atan2(magnetometer[2], sqrt(magnetometer[0]*magnetometer[0]+magnetometer[2]*magnetometer[2]));
   
   // Update yaw correcion
   yaw_correction = odes.get_yaw_correction(t, n_steps_per_second);
   
   // Update filtered Euler angles
   y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
   y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
   //y[0][8]+= yaw_correction;
   //y[0][8] = alpha_yaw * y[0][8];// + (1.0 - alpha) * yaw_correction;
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * (y[0][8] + yaw_correction);
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * yaw_correction;
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * magnetometer[1];
      
   // --------------------------------------------------
   // Gravity compensation
   // --------------------------------------------------
   // Extract gravity and output the raw and the modified accelerations
   
   // Fill rotation matrices
   fill_rotation_matrices(R, R_t, y[0][6], y[0][7], y[0][8]); // tachidok
   
   // Transform from the body reference frame to the inertial reference
   // frame
   multiply_matrix_times_vector(R_t, acc, acc_inertial);//tachidok
   // Substract gravity
   acc_inertial[2]-=9.81;
   
   // Set linear acceleration
   odes.linear_acceleration() = acc_inertial;
   
   // -----------------
   // Output data
   // -----------------
   // Position
   outfile_position << t << " " << y[0][0] << " " << y[0][2] << " " << y[0][4] << std::endl; 
   // Velocity
   outfile_velocity << t << " " << y[0][1] << " " << y[0][3] << " " << y[0][5] << std::endl;
   // Raw accelerations
   outfile_raw_acc << t << " " << acc[0] << " " << acc[1] << " " << acc[2] << std::endl;
   // Inertial accelerations
   outfile_intertial_acc << t << " " << acc_inertial[0] << " "
                         << acc_inertial[1] << " " << acc_inertial[2] << std::endl;
   // Euler angles
   outfile_roll_pitch_yaw << t << " " << y[0][6] << " " << y[0][7] << " " << y[0][8] << std::endl;
   // Euler angles from accelerations
   outfile_roll_pitch_yaw_from_acc << t << " " << acc_angles[0] << " "
                                   << acc_angles[1] << " " << acc_angles[2] << std::endl;   
   
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 outfile_position.close();
 outfile_velocity.close();
 outfile_raw_acc.close();
 outfile_intertial_acc.close();
 outfile_roll_pitch_yaw.close();
 outfile_roll_pitch_yaw_from_acc.close();
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}
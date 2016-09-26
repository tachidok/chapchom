#include <iostream>
#include <cmath>

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
#include "cc_odes_from_table_from_xsensMT9B.h"

using namespace chapchom;

//#define DEBUG

#define T_NO_MOVEMENT
//#define T_CHARACTERISE_YAW
//#define T_CHARACTERISE_YAW2
//#define T_ELLIPSE_MOVEMENT
//#define T_CHARACTERISE_YAW_HALF_HOUR
//#define T_CHARACTERISE_TWO_HOURS

//#define T_GET_YAW_DRIFT

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
 // Initialise chapcom
 initialise_chapchom();
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 
 // Create an instance of the ODEs to solve
#ifdef T_NO_MOVEMENT
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/01_no_movement/MT9_euler_00007154_000.log",
                                   "./xsensMT9B/01_no_movement/MT9_cal_00007154_000.log");
#endif // #ifdef T_NO_MOVEMENT

#ifdef T_CHARACTERISE_YAW
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/03_characterise_yaw_drift/MT9_euler_00007154_000.log",
                                   "./xsensMT9B/03_characterise_yaw_drift/MT9_cal_00007154_000.log");
#endif // #ifdef T_CHARACTERISE_YAW

#ifdef T_CHARACTERISE_YAW2
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/04_characterise_yaw_drift2/MT9_euler_00007154_000.log",
                                   "./xsensMT9B/04_characterise_yaw_drift2/MT9_cal_00007154_000.log");
#endif // #ifdef T_CHARACTERISE_YAW2
 
#ifdef T_ELLIPSE_MOVEMENT
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/02_test_ellipse_movement/MT9_euler_00007154_000.log",
                                   "./xsensMT9B/02_test_ellipse_movement/MT9_cal_00007154_000.log");
#endif // #ifdef T_ELLIPSE_MOVEMENT
 
#ifdef T_CHARACTERISE_YAW_HALF_HOUR
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_euler_00007154_001.log",
                                   "./xsensMT9B/06_characterise_yaw_drift_0.5hrs/MT9_cal_00007154_001.log");
#endif // #ifdef T_CHARACTERISE_YAW_HALF_HOUR

#ifdef T_CHARACTERISE_TWO_HOURS
 CCODEsFromTableFromXSENSMT9B *odes =
  new CCODEsFromTableFromXSENSMT9B("./xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_euler_00007154_000.log",
                                   "./xsensMT9B/07_characterise_yaw_drift_2hrs/MT9_cal_00007154_000.log");
#endif // #ifdef T_CHARACTERISE_TWO_HOURS
 
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
 const unsigned n_odes = odes->nodes();
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
 char file_raw_accelerations_name[100];
 sprintf(file_raw_accelerations_name, "./RESLT/raw_accelerations.dat");
 FILE *file_raw_accelerations_pt = fopen(file_raw_accelerations_name, "w");
 if (file_raw_accelerations_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_accelerations_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_inertial_accelerations_name[100];
 sprintf(file_inertial_accelerations_name, "./RESLT/inertial_accelerations.dat");
 FILE *file_inertial_accelerations_pt = fopen(file_inertial_accelerations_name, "w");
 if (file_inertial_accelerations_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_inertial_accelerations_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_roll_pitch_yaw_name[100];
 sprintf(file_roll_pitch_yaw_name, "./RESLT/roll_pitch_yaw.dat");
 FILE *file_roll_pitch_yaw_pt = fopen(file_roll_pitch_yaw_name, "w");
 if (file_roll_pitch_yaw_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_roll_pitch_yaw_from_acc_name[100];
 sprintf(file_roll_pitch_yaw_from_acc_name, "./RESLT/roll_pitch_yaw_from_acc.dat");
 FILE *file_roll_pitch_yaw_from_acc_pt = fopen(file_roll_pitch_yaw_from_acc_name, "w");
 if (file_roll_pitch_yaw_from_acc_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_from_acc_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_raw_magnetometers_name[100];
 sprintf(file_raw_magnetometers_name, "./RESLT/raw_magnetometers.dat");
 FILE *file_raw_magnetometers_pt = fopen(file_raw_magnetometers_name, "w");
 if (file_raw_magnetometers_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_magnetometers_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_drift_yaw_name[100];
 sprintf(file_drift_yaw_name, "./RESLT/ddrift_yaw.dat");
 FILE *file_drift_yaw_pt = fopen(file_drift_yaw_name, "w");
 if (file_drift_yaw_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_drift_yaw_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_velocity_name[100];
 sprintf(file_velocity_name, "./RESLT/velocity.dat");
 FILE *file_velocity_pt = fopen(file_velocity_name, "w");
 if (file_velocity_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_velocity_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_position_name[100];
 sprintf(file_position_name, "./RESLT/position.dat");
 FILE *file_position_pt = fopen(file_position_name, "w");
 if (file_position_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_position_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }

#ifdef T_GET_YAW_DRIFT
 char file_get_yaw_name[100];
 sprintf(file_get_yaw_name, "./RESLT/get_yaw.dat");
 FILE *file_get_yaw_pt = fopen(file_get_yaw_name, "w");
 if (file_get_yaw_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_get_yaw_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef T_GET_YAW_DRIFT

 char file_yaw_error[100];
 sprintf(file_yaw_error, "./RESLT/yaw_error.dat");
 FILE *file_yaw_error_pt = fopen(file_yaw_error, "w");
 if (file_yaw_error_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_yaw_error << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
#ifdef DEBUG
 char file_DEBUG_name[100];
 sprintf(file_DEBUG_name, "./RESLT/DEBUG.dat");
 FILE *file_DEBUG_pt = fopen(file_DEBUG_name, "w");
 if (file_DEBUG_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_DEBUG_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef DEBUG
 
 // ----------------------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------------------
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (steps, h,
 // initial values)
 // -----------------------------------------------------------------
 // Set the initial and final interval values (got from the number of data in Table)
#ifdef T_NO_MOVEMENT
 const double t_initial = 5.113;
 const double t_final = 76.0;
#endif // #ifdef T_NO_MOVEMENT
 
#ifdef T_CHARACTERISE_YAW
 const double t_initial = 8.54;
 const double t_final = 82.0;
#endif // #ifdef T_CHARACTERISE_YAW

#ifdef T_CHARACTERISE_YAW2
 const double t_initial = 22.195;
 const double t_final = 1065.0;
#endif // #ifdef T_CHARACTERISE_YAW2
 
#ifdef T_ELLIPSE_MOVEMENT
 const double t_initial = 25.0;
 const double t_final = 103.0;
#endif // #ifdef T_ELLIPSE_MOVEMENT
 
#ifdef T_CHARACTERISE_YAW_HALF_HOUR
 const double t_initial = 3.52;
 const double t_final = 2053.0;
#endif // #ifdef T_CHARACTERISE_YAW_HALF_HOUR
 
#ifdef T_CHARACTERISE_TWO_HOURS
 const double t_initial = 5.617;
 //const double t_test_final = 1.0;
 //const double t_test_final = 60.0 * 60.0 + 60.0 * 60.0;
 //const double t_final = t_initial + t_test_final;
 const double t_final = 7070.0;
#endif // #ifdef T_CHARACTERISE_TWO_HOURS
 
 //const double t_final = 100;
 // Set the number of steps per second
 const double n_steps_per_second = 257.0; // 257 measeurements per second (original number of measurements)
 // Set the number of steps we want to take
 const double n_steps = n_steps_per_second * t_final;
 //const double n_steps = 18273;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Initial time
 double t = t_initial;
 
 // -----------------------------------------------------------------------------
 // Initialise
 // -----------------------------------------------------------------------------
 
 // Dimension of the problem
 const unsigned dim = 3;
 
 // Get the readings from sensores
 // Accelerations
 std::vector<double> acc(dim);
 // Gyro data
 std::vector<double> dtheta(dim);
 // Magnetometer
 std::vector<double> magnetometer(dim);
 // Dummy data
 std::vector<double> euler_angles(dim);
 // Retrieve data from table
 odes->get_sensors_lecture(t, acc, dtheta, magnetometer, euler_angles); // tachidok
 
 // Initial conditions
 y[0][0] = 0.0; // Initial x-position
 y[0][1] = 0.0; // Initial x-velocity
 y[0][2] = 0.0; // Initial y-position
 y[0][3] = 0.0; // Initial y-velocity
 y[0][4] = 0.0; // Initial z-position
 y[0][5] = 0.0; // Initial z-velocity
 // Transform to radians since the data are given in angles
 y[0][6] = 0.0 * M_PI / 180.0; // Initial roll
 y[0][7] = 0.0 * M_PI / 180.0; // Initial pitch
 y[0][8] = 0.0 * M_PI / 180.0; // Initial yaw
 
 // Get the error in yaw
 double yaw_error = euler_angles[2] - y[0][8];
 
 // Output the initial data to screen
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
           << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8]
           << " yaw-error: " << yaw_error << std::endl;
 
 double ddrift_yaw = 0.0;
 
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
 double yaw_correction = odes->get_yaw_correction(t, n_steps_per_second);
 
 // -------------------------------------------------------------------
 // Apply complementary filter
 // -------------------------------------------------------------------
 // Complementary filter parameter
 const double alpha = 0.98;
 const double alpha_yaw = 1.0;
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
 
 std::vector<double> mag_proc(3, 0.0);
 mag_proc[0] = atan2(magnetometer[1], magnetometer[2]);
 mag_proc[1] = atan2(-magnetometer[0], sqrt(magnetometer[1]*magnetometer[1]+magnetometer[2]*magnetometer[2]));
 mag_proc[2] = atan2(magnetometer[2], sqrt(magnetometer[0]*magnetometer[0]+magnetometer[2]*magnetometer[2]));
 
 // Correction for yaw
 //yaw_correction = ddrift_yaw;
 
 // Update filtered Euler angles
 y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
 y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
 y[0][8]+= yaw_correction;
 //y[0][8] = alpha_yaw * y[0][8];// + (1.0 - alpha) * yaw_correction;
 //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * (y[0][8] + yaw_correction);
 //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
 //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * magnetometer[1];
 
#ifdef T_GET_YAW_DRIFT
 double yaw_error = euler_angles[2] - y[0][8];
 // Add the error to correct
 y[0][8]+=yaw_error;
 // Register the error
 fprintf(file_get_yaw_pt, "%lf %lf\n", t, yaw_error);
#endif // #ifdef T_GET_YAW_DRIFT
 
 // --------------------------------------------------
 // Gravity compensation
 // --------------------------------------------------
 // Extract gravity and output the raw and the modified accelerations
 
 // Create the rotation matrices
 std::vector<std::vector<double> > R(dim);
 std::vector<std::vector<double> > R_t(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   R[i].resize(dim);
   R_t[i].resize(dim);
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
 odes->linear_acceleration() = acc_inertial;
 
 // -----------------
 // Output data
 // -----------------
 // Raw accelerations
 fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc[0], acc[1], acc[2]);
 // Proccessed accelerations
 fprintf(file_inertial_accelerations_pt, "%lf %lf %lf %lf\n",
         t, acc_inertial[0], acc_inertial[1], acc_inertial[2]);
 // Euler angles
 fprintf(file_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n",
         t, y[0][6], y[0][7], y[0][8]);
 // Euler angles from accelerations
 fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n",
         t, acc_angles[0], acc_angles[1], acc_angles[2]);
 // Raw magnetometers
 fprintf(file_raw_magnetometers_pt, "%lf %lf %lf %lf\n", t, magnetometer[0], magnetometer[1], magnetometer[2]);
 //fprintf(file_raw_magnetometers_pt, "%lf %lf %lf %lf\n", t, mag_proc[0], mag_proc[1], mag_proc[2]);
 
 // ddrift yaw
 fprintf(file_drift_yaw_pt, "%lf 0.0 0.0 %lf\n", t, ddrift_yaw);
 
 // yaw error
 fprintf(file_yaw_error_pt, "%lf %lf\n", t, yaw_error);
 
 // Velocity
 fprintf(file_velocity_pt, "%lf %lf %lf %lf\n", t, y[0][1], y[0][3], y[0][5]);
 // Position
 fprintf(file_position_pt, "%lf %lf %lf %lf\n", t, y[0][0], y[0][2], y[0][4]);
 
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
     ddrift_yaw = (y[1][j] - y[0][j]) / h;
     y[0][j] = y[1][j];
    }
   // Update time
   t+=h;
   
   yaw_error = euler_angles[2] - y[0][8];
   
   std::cout << "t: " << t
             << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
             << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
             << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
             << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8]
             << " yaw-error: " << yaw_error << std::endl;
   
   // Get the accelerometers readings from the Table
   odes->get_sensors_lecture(t, acc, dtheta, magnetometer, euler_angles);
   
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
   
   // Correction for yaw
   //yaw_correction = ddrift_yaw;
   
   // Update yaw correcion
   yaw_correction = odes->get_yaw_correction(t, n_steps_per_second);
   
   // Update filtered Euler angles
   y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
   y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
   y[0][8]+= yaw_correction;
   //y[0][8] = alpha_yaw * y[0][8];// + (1.0 - alpha) * yaw_correction;
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * (y[0][8] + yaw_correction);
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * yaw_correction;
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * magnetometer[1];
   
#ifdef T_GET_YAW_DRIFT
   yaw_error = euler_angles[2] - y[0][8];
   // Add the error to correct
   y[0][8]+=yaw_error;
   // Register the error
   fprintf(file_get_yaw_pt, "%lf %lf\n", t, yaw_error);
#endif // #ifdef T_GET_YAW_DRIFT
   
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
   odes->linear_acceleration() = acc_inertial;
   
   // -----------------
   // Output data
   // -----------------
   // Raw accelerations
   fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc[0], acc[1], acc[2]);
   // Proccessed accelerations
   fprintf(file_inertial_accelerations_pt, "%lf %lf %lf %lf\n",
           t, acc_inertial[0], acc_inertial[1], acc_inertial[2]);
   // Euler angles
   fprintf(file_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n",
           t, y[0][6], y[0][7], y[0][8]);
   // Euler angles from accelerations
   fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n",
           t, acc_angles[0], acc_angles[1], acc_angles[2]);
   // Raw magnetometers
   fprintf(file_raw_magnetometers_pt, "%lf %lf %lf %lf\n", t, magnetometer[0], magnetometer[1], magnetometer[2]);
   //fprintf(file_raw_magnetometers_pt, "%lf %lf %lf %lf\n", t, mag_proc[0], mag_proc[1], mag_proc[2]);
   
   // ddrift yaw
   fprintf(file_drift_yaw_pt, "%lf 0.0 0.0 %lf\n", t, ddrift_yaw);
   
   // yaw error
   fprintf(file_yaw_error_pt, "%lf %lf\n", t, yaw_error);
   
   // Velocity
   fprintf(file_velocity_pt, "%lf %lf %lf %lf\n", t, y[0][1], y[0][3], y[0][5]);
   // Position
   fprintf(file_position_pt, "%lf %lf %lf %lf\n", t, y[0][0], y[0][2], y[0][4]);
   
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 fclose(file_raw_accelerations_pt);
 fclose(file_inertial_accelerations_pt);
 fclose(file_roll_pitch_yaw_pt);
 fclose(file_roll_pitch_yaw_from_acc_pt);
 fclose(file_raw_magnetometers_pt);
 fclose(file_drift_yaw_pt);
 fclose(file_velocity_pt);
 fclose(file_position_pt);

#ifdef T_GET_YAW_DRIFT
 fclose(file_get_yaw_pt);
#endif // #ifdef T_GET_YAW_DRIFT
 
 fclose(file_yaw_error_pt);
 
#ifdef DEBUG
 fclose(file_DEBUG_pt);
#endif // #ifdef DEBUG
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

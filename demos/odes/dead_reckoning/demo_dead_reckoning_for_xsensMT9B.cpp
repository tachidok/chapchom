#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
#include "../../../src/integration/ca_integration_method.h"
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_table_from_xsensMT9B.h"

#define DEBUG
#define THIRD_ALGORITHM

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
   error_message << "We can not muliply, the input matrix has dimension ("
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
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 
 // Create an instance of the ODEs to solve
 CCODEsFromTableFromXSENSMT9B *odes = new CCODEsFromTableFromXSENSMT9B();
 
 // Create an instance of the integrator method
 CAIntegrationMethod *integrator = new CCEulerMethod();
 //CAIntegrationMethod *integrator = new CCRK4Method();
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
 const double t_initial = 5.113;
 const double t_final = 76.0;
 //const double t_final = 100;
 // Set the number of steps we want to take
 const double n_steps = 257.0 * t_final;  // 257 measeurements per second (original number of measurements)
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
 // Dummy data
 std::vector<double> dummy(dim);
 // Retrieve data from table
 odes->get_sensors_lecture(t, acc, dtheta, dummy); // tachidok
 
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
 
 // Output the initial data to screen
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " z-pos: " << y[0][4] << " z-vel: " << y[0][5]
           << " roll: " << y[0][6] << " pitch: " << y[0][7] << " yaw: " << y[0][8] << std::endl;
 
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
 
 // -------------------------------------------------------------------
 // Apply complementary filter
 // -------------------------------------------------------------------
 // Complementary filter parameter
 const double alpha = 0.98;
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
 acc_angles[2] = atan2(acc[1], acc[0]);
 //acc_angles[2] = atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
 //acc_angles[2] = (atan2(acc[1], acc[0]) + atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]))) / 2.0;
 
 // Update filtered Euler angles
 y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
 y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
 //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
 
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
   odes->get_sensors_lecture(t, acc, dtheta, dummy);
   
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
   acc_angles[2] = atan2(acc[1], acc[0]);
   //acc_angles[2] = atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]));
   //acc_angles[2] = (atan2(acc[1], acc[0]) + atan2(-acc[0], sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]))) / 2.0;
   
   // Update filtered Euler angles
   y[0][6] = alpha * y[0][6] + (1.0 - alpha) * acc_angles[0];
   y[0][7] = alpha * y[0][7] + (1.0 - alpha) * acc_angles[1];
   //y[0][8] = alpha * y[0][8] + (1.0 - alpha) * acc_angles[2];
   
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
   
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 fclose(file_raw_accelerations_pt);
 fclose(file_inertial_accelerations_pt);
 fclose(file_roll_pitch_yaw_pt);
 fclose(file_roll_pitch_yaw_from_acc_pt);
 
#ifdef DEBUG
 fclose(file_DEBUG_pt);
#endif // #ifdef DEBUG
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 std::cout << "[DONE]" << std::endl;
 
}

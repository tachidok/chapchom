#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
#include "../../../src/integration/ca_integration_method.h"
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_table_based_on_acceleration.h"

#define DEBUG
//#define FIRST_ALGORITHM
//#define SECOND_ALGORITHM
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

#ifdef SECOND_ALGORITHM
void update_rotation_matrices(std::vector<std::vector<double> > &R0,
                              std::vector<std::vector<double> > &R1,
                              std::vector<std::vector<double> > &R0_t,
                              std::vector<double> &dr)
{
 const unsigned dim = 3;
 // Get values for first row of rotation matrix (CROSS-PRODUCT)
 // r_x[t+1] = r_x[t] + r_x[t] x dr
 R0[0][0] = R1[0][0] + (R1[0][1] * dr[2] - R1[0][2] * dr[1]);
 R0[0][1] = R1[0][1] + (R1[0][2] * dr[0] - R1[0][0] * dr[2]);
 R0[0][2] = R1[0][2] + (R1[0][0] * dr[1] - R1[0][1] * dr[0]);
 // Get values for second row of rotation matrix
 // r_y[t+1] = r_y[t] + r_y[t] x dr
 R0[1][0] = R1[1][0] + (R1[1][1] * dr[2] - R1[1][2] * dr[1]);
 R0[1][1] = R1[1][1] + (R1[1][2] * dr[0] - R1[1][0] * dr[2]);
 R0[1][2] = R1[1][2] + (R1[1][0] * dr[1] - R1[1][1] * dr[0]);
 // Get values for third row of rotation matrix
 // r_z[t+1] = r_z[t] + r_z[t] x dr
 R0[2][0] = R1[2][0] + (R1[2][1] * dr[2] - R1[2][2] * dr[1]);
 R0[2][1] = R1[2][1] + (R1[2][2] * dr[0] - R1[2][0] * dr[2]);
 R0[2][2] = R1[2][2] + (R1[2][0] * dr[1] - R1[2][1] * dr[0]);
 
 // Copy values from current time step to the previous one
 for (unsigned i = 0; i < dim; i++)
  {
   for (unsigned j = 0; j < dim; j++)
    {
     R1[i][j] = R0[i][j];
    }
  }
 
 // Transpose matrix
 R0_t[0][0] = R0[0][0];
 R0_t[0][1] = R0[1][0];
 R0_t[0][2] = R0[2][0];
 
 R0_t[1][0] = R0[0][1];
 R0_t[1][1] = R0[1][1];
 R0_t[1][2] = R0[2][1];
 
 R0_t[2][0] = R0[0][2];
 R0_t[2][1] = R0[1][2];
 R0_t[2][2] = R0[2][2];
 
}
#endif // #ifdef SECOND_ALGORITHM

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
 CCODEsFromTableBasedOnAcceleration *odes = new CCODEsFromTableBasedOnAcceleration();
 
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
 char file_roll_pitch_yaw_from_gyro_name[100];
 sprintf(file_roll_pitch_yaw_from_gyro_name, "./RESLT/roll_pitch_yaw_from_gyro.dat");
 FILE *file_roll_pitch_yaw_from_gyro_pt = fopen(file_roll_pitch_yaw_from_gyro_name, "w");
 if (file_roll_pitch_yaw_from_gyro_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_from_gyro_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
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
 
#ifdef FIRST_ALGORITHM
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
 
 char file_modified_accelerations_name[100];
 sprintf(file_modified_accelerations_name, "./RESLT/modified_accelerations.dat");
 FILE *file_modified_accelerations_pt = fopen(file_modified_accelerations_name, "w");
 if (file_modified_accelerations_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_modified_accelerations_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_filtered_roll_pitch_yaw_name[100];
 sprintf(file_filtered_roll_pitch_yaw_name, "./RESLT/filtered_roll_pitch_yaw.dat");
 FILE *file_filtered_roll_pitch_yaw_pt = fopen(file_filtered_roll_pitch_yaw_name, "w");
 if (file_filtered_roll_pitch_yaw_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_filtered_roll_pitch_yaw_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef FIRST_ALGORITHM

#ifdef SECOND_ALGORITHM
 char file_roll_pitch_yaw_from_acc2_name[100];
 sprintf(file_roll_pitch_yaw_from_acc2_name, "./RESLT/roll_pitch_yaw_from_acc2.dat");
 FILE *file_roll_pitch_yaw_from_acc2_pt = fopen(file_roll_pitch_yaw_from_acc2_name, "w");
 if (file_roll_pitch_yaw_from_acc2_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_roll_pitch_yaw_from_acc2_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_modified_accelerations2_name[100];
 sprintf(file_modified_accelerations2_name, "./RESLT/modified_accelerations2.dat");
 FILE *file_modified_accelerations2_pt = fopen(file_modified_accelerations2_name, "w");
 if (file_modified_accelerations2_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_modified_accelerations2_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_filtered_roll_pitch_yaw2_name[100];
 sprintf(file_filtered_roll_pitch_yaw2_name, "./RESLT/filtered_roll_pitch_yaw2.dat");
 FILE *file_filtered_roll_pitch_yaw2_pt = fopen(file_filtered_roll_pitch_yaw2_name, "w");
 if (file_filtered_roll_pitch_yaw2_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_filtered_roll_pitch_yaw2_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
#endif // #ifdef SECOND_ALGORITHM
 
#ifdef THIRD_ALGORITHM 
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
 
 char file_inertial_gyro_name[100];
 sprintf(file_inertial_gyro_name, "./RESLT/inertial_gyro.dat");
 FILE *file_inertial_gyro_pt = fopen(file_inertial_gyro_name, "w");
 if (file_inertial_gyro_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_inertial_gyro_name << "]"
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
#endif // #ifdef THIRD_ALGORITHM
 
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
 const double t_initial = 0.0;
 const double t_final = 4108;
 //const double t_final = 100;
 // Set the number of steps we want to take
 const double n_steps = 10000 * 5.0;
 //const double n_steps = 10000 * 9.0; // to have an approximately same number of steps than data
 //const double n_steps = 100;
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
 // Velocities
 std::vector<double> vel(dim);
 // Accelerations
 std::vector<double> acc(dim);
 // Gyro data
 std::vector<double> dtheta(dim);
 // Dummy data
 std::vector<double> dummy(dim);
 // Retrieve data from table
 odes->get_sensors_lecture(t, vel, acc, dtheta, dummy); // tachidok
 
 // Initial conditions
 y[0][0] = 0.0;         // Initial x-position
 y[0][1] = -0.05994836; // Initial x-velocity
 y[0][2] = 0.0;         // Initial y-position
 y[0][3] = 0.033224355; // Initial y-velocity
 y[0][4] = 0.7377110497 * M_PI / 180.0;// Initial roll
 y[0][5] = 1.8484771659 * M_PI / 180.0;// Initial pitch
 y[0][6] = (360.0 - 300.9750142095) * M_PI / 180.0;// Initial yaw
 y[0][7] = y[0][4];  // Initial roll
 y[0][8] = y[0][5];  // Initial pitch
 y[0][9] = y[0][6];  // Initial yaw
 y[0][10] = 1.7023341886 * M_PI / 180.0;  // Initial roll
 y[0][11] = 0.9397878122 * M_PI / 180.0;  // Initial pitch
 y[0][12] = 40.823029194 * M_PI / 180.0;  // Initial yaw
 
 // Output the initial data to screen
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " roll: " << y[0][4] << " pitch: " << y[0][5] << " yaw: " << y[0][6]
           << " roll2: " << y[0][7] << " pitch2: " << y[0][8] << " yaw2: " << y[0][9]
           << " roll3: " << y[0][10] << " pitch3: " << y[0][11] << " yaw3: " << y[0][12] << std::endl;
 
 fprintf(file_roll_pitch_yaw_from_gyro_pt, "%lf %lf %lf %lf\n", t, y[0][4], y[0][5], y[0][6]);
 
 // --------------------------------------------------
 // Gravity compensation
 // --------------------------------------------------
 
#ifdef FIRST_ALGORITHM
 // Create the rotations matrix
 std::vector<std::vector<double> > R(dim);
 std::vector<std::vector<double> > R_t(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   R[i].resize(dim);
   R_t[i].resize(dim);
  }
 
 // Fill rotation matrices
 fill_rotation_matrices(R, R_t, y[0][4], y[0][5], y[0][6]);
 
 // Modified acceleration
 std::vector<double> acc_prime(3, 0.0);
 // Transform from the body reference frame to the global reference
 // frame
 multiply_matrix_times_vector(R_t, acc, acc_prime);
 
#ifdef DEBUG
 // We should be able to recover the original vector from acc_prime
 std::vector<double> test(dim, 0.0);
 // Transform from the body reference frame to the global reference
 // frame
 multiply_matrix_times_vector(R, acc_prime, test);
 
 // Get the distance between the two vectors
 double dist = 0.0;
 for (unsigned i = 0; i < dim; i++)
  {
   dist+=(acc[i]-test[i])*(acc[i]-test[i]);
  }
 dist = sqrt(dist);
 // Output the raw and the modified accelerations
 fprintf(file_DEBUG_pt, "%lf %lf\n", t, dist);
#endif // #ifdef DEBUG
 
#endif // #ifdef FIRST_ALGORITHM

#ifdef SECOND_ALGORITHM
 // Another gravity compensation
 
 // The rotation matrix (roll, pitch and yaw)
 std::vector<std::vector<double> > R0(dim);
 std::vector<std::vector<double> > R1(dim);
 std::vector<std::vector<double> > R0_t(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   R0[i].resize(dim);
   R1[i].resize(dim);
   R0_t[i].resize(dim);
   for (unsigned j = 0; j < dim; j++)
    {
     // at current time step
     R0[i][j] = 0.0;
     // at previous time step
     R1[i][j] = 0.0;
     // at current time step
     R0_t[i][j] = 0.0;
    }
  }
 
 // Set initial roll, pitch and yaw
 R1[0][0] = y[0][7];
 R1[1][1] = y[0][8];
 R1[2][2] = y[0][9];
 
 // Update rotation matrices with the lectures from gyro
 update_rotation_matrices(R0, R1, R0_t, dtheta);
 
 // Gravity compensation [2]
 std::vector<double> acc_prime2(3, 0.0);
 // Transform from the body reference frame to the global reference
 // frame
 multiply_matrix_times_vector(R0_t, acc, acc_prime2);
 
#endif // #ifdef SECOND_ALGORITHM
 
 // Extract gravity and output the raw and the modified accelerations
 fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc[0], acc[1], acc[2]);
#ifdef FIRST_ALGORITHM
 acc_prime[2]+=9.81;
 fprintf(file_modified_accelerations_pt, "%lf %lf %lf %lf\n", t, acc_prime[0], acc_prime[1], acc_prime[2]);
#endif // #ifdef FIRST_ALGORITHM
#ifdef SECOND_ALGORITHM
 acc_prime2[2]+=9.81;
 fprintf(file_modified_accelerations2_pt, "%lf %lf %lf %lf\n", t, acc_prime2[0], acc_prime2[1], acc_prime2[2]);
#endif // #ifdef SECOND_ALGORITHM
 
 // Get roll, pitch and yaw from accelerations
 // euler_angles_from_acc_prime[0] - Roll
 // euler_angles_from_acc_prime[1] - Pitch
 // euler_angles_from_acc_prime[2] - Yaw 
#ifdef FIRST_ALGORITHM
 std::vector<double> euler_angles_from_acc_prime(dim, 0.0);
 
 euler_angles_from_acc_prime[0] = atan2(acc_prime[2], acc_prime[1]);
 euler_angles_from_acc_prime[1] = atan2(acc_prime[0], acc_prime[2]);
 euler_angles_from_acc_prime[2] = atan2(acc_prime[1], acc_prime[0]);
 
 fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n", t,
         euler_angles_from_acc_prime[0],
         euler_angles_from_acc_prime[1],
         euler_angles_from_acc_prime[2]);
#endif // #ifdef FIRST_ALGORITHM
 
#ifdef SECOND_ALGORITHM
 std::vector<double> euler_angles_from_acc_prime2(dim, 0.0);
 
 euler_angles_from_acc_prime2[0] = atan2(acc_prime2[2], acc_prime2[1]);
 euler_angles_from_acc_prime2[1] = atan2(acc_prime2[0], acc_prime2[2]);
 euler_angles_from_acc_prime2[2] = atan2(acc_prime2[1], acc_prime2[0]);
 
 fprintf(file_roll_pitch_yaw_from_acc2_pt, "%lf %lf %lf %lf\n", t,
         euler_angles_from_acc_prime2[0],
         euler_angles_from_acc_prime2[1],
         euler_angles_from_acc_prime2[2]);
#endif // #ifdef SECOND_ALGORITHM
 
 // Use complementary filter to get better estimates for roll, pitch
 // and yaw
 // euler_angles_filtered[0] - Filtered roll
 // euler_angles_filtered[1] - Filtered pitch
 // euler_angles_filtered[2] - Filtered yaw
 
 // Complementary filter
 const double alpha = 0.98;
 
 // Update the value of the function with the new values
#ifdef FIRST_ALGORITHM
 std::vector<double> euler_angles_filtered(dim, 0.0);
 
 euler_angles_filtered[0] = alpha * y[0][4] + (1.0 - alpha) * euler_angles_from_acc_prime[0];
 euler_angles_filtered[1] = alpha * y[0][5] + (1.0 - alpha) * euler_angles_from_acc_prime[1];
 euler_angles_filtered[2] = alpha * y[0][6] + (1.0 - alpha) * euler_angles_from_acc_prime[2];
 
 y[0][4] = euler_angles_filtered[0];
 y[0][5] = euler_angles_filtered[1];
 y[0][6] = euler_angles_filtered[2];
 
 fprintf(file_filtered_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n", t,
         euler_angles_filtered[0], euler_angles_filtered[1], euler_angles_filtered[2]);
#endif // #ifdef FIRST_ALGORITHM
 
#ifdef SECOND_ALGORITHM
 std::vector<double> euler_angles_filtered2(dim, 0.0);
 
 euler_angles_filtered2[0] = alpha * y[0][7] + (1.0 - alpha) * euler_angles_from_acc_prime2[0];
 euler_angles_filtered2[1] = alpha * y[0][8] + (1.0 - alpha) * euler_angles_from_acc_prime2[1];
 euler_angles_filtered2[2] = alpha * y[0][9] + (1.0 - alpha) * euler_angles_from_acc_prime2[2];
 
 y[0][7] = euler_angles_filtered2[0];
 y[0][8] = euler_angles_filtered2[1];
 y[0][9] = euler_angles_filtered2[2];
 
 fprintf(file_filtered_roll_pitch_yaw2_pt, "%lf %lf %lf %lf\n", t,
         euler_angles_filtered2[0], euler_angles_filtered2[1], euler_angles_filtered2[2]);
#endif // #ifdef SECOND_ALGORITHM
  
#ifdef THIRD_ALGORITHM
 
 // Create the rotation matrices
 std::vector<std::vector<double> > R(dim);
 std::vector<std::vector<double> > R_t(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   R[i].resize(dim);
   R_t[i].resize(dim);
  }
 
 // Fill rotation matrices
 // fill_rotation_matrices(R, R_t, y[0][10], y[0][11], y[0][12]); // tachidok
 fill_rotation_matrices(R, R_t, dummy[0], dummy[1], dummy[2]);
 
 // Transform from the body reference frame to the global reference
 // frame
 std::vector<double> acc_inertial(3, 0.0);
 multiply_matrix_times_vector(R_t, acc, acc_inertial);//tachidok
 acc_inertial[2]+=9.81;
 //std::vector<double> gyro_inertial(3, 0.0);
 //multiply_matrix_times_vector(R, dtheta, gyro_inertial);
 
 // Output data
 fprintf(file_inertial_accelerations_pt, "%lf %lf %lf %lf\n",
         t, acc_inertial[0], acc_inertial[1], acc_inertial[2]);
 //fprintf(file_inertial_gyro_pt, "%lf %lf %lf %lf\n",
 //        t, gyro_inertial[0], gyro_inertial[1], gyro_inertial[2]);
 
 // Another one gravity compensation 
 // -------------------------------------------------------------------
 // Apply complementary filter
 // -------------------------------------------------------------------
 // Transform accelerations to angles
 std::vector<double> acc_angles(3, 0.0);
 acc_angles[0] = atan2(acc_inertial[2], acc_inertial[1]);
 acc_angles[1] = atan2(acc_inertial[0], acc_inertial[2]);
 acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
 
 // Update filtered Euler angles
 //y[0][10] = alpha * y[0][10] + (1.0 - alpha) * acc_inertial[0];
 //y[0][11] = alpha * y[0][11] + (1.0 - alpha) * acc_inertial[1];
 //y[0][12] = alpha * y[0][12] + (1.0 - alpha) * acc_inertial[2];
 
 // Output data
 fprintf(file_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n",
         t, y[0][10], y[0][11], y[0][12]);
#endif // #ifdef THIRD_ALGORITHM
 
 // Integrate
 //integrator->integrate(*odes, h, t_initial, t_final, y);
 for (unsigned i = 0; i < n_steps && t < 100.0; i++)
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
             << " roll: " << y[0][4] << " pitch: " << y[0][5] << " yaw: " << y[0][6]
             << " roll2: " << y[0][7] << " pitch2: " << y[0][8] << " yaw2: " << y[0][9] << std::endl;
   
   fprintf(file_roll_pitch_yaw_from_gyro_pt, "%lf %lf %lf %lf\n", t, y[0][4], y[0][5], y[0][6]);
   
   // Get the accelerometers readings from the Table
   odes->get_sensors_lecture(t, vel, acc, dtheta, dummy);
   
   // ----------------------
   // Gravity compensation
   
#ifdef FIRST_ALGORITHM
   // Fill rotation matrices
   fill_rotation_matrices(R, R_t, y[0][4], y[0][5], y[0][6]);
   //fill_rotation_matrices(R, R_t, roll_filtered, pitch_filtered, yaw_filtered);
   
   // Transform from the body frame to the global frame
   multiply_matrix_times_vector(R_t, acc, acc_prime);
   
#ifdef DEBUG
   // We should be able to recover the original vector from acc_prime
   std::vector<double> test(dim, 0.0);
   // Transform from the body reference frame to the global reference
   // frame
   multiply_matrix_times_vector(R, acc_prime, test);
   
   // Get the distance between the two vectors
   double dist = 0.0;
   for (unsigned i = 0; i < dim; i++)
    {
     dist+=(acc[i]-test[i])*(acc[i]-test[i]);
    }
   dist = sqrt(dist);
   // Output the raw and the modified accelerations
   fprintf(file_DEBUG_pt, "%lf %lf\n", t, dist);
#endif // #ifdef DEBUG
   
#endif // #ifdef FIRST_ALGORITHM
   
#ifdef SECOND_ALGORITHM
   // Another gravity compensation
   
   // Update rotation matrices with the lectures from gyro
   update_rotation_matrices(R0, R1, R0_t, dtheta);
   
   // Transform from the body reference frame to the global reference
   // frame
   multiply_matrix_times_vector(R0_t, acc, acc_prime2);
#endif // #ifdef SECOND_ALGORITHM
   
   // Extract gravity and output the raw and the modified
   // accelerations
   fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc[0], acc[1], acc[2]);
#ifdef FIRST_ALGORITHM
   acc_prime[2]+=9.81;
   fprintf(file_modified_accelerations_pt, "%lf %lf %lf %lf\n", t,
           acc_prime[0], acc_prime[1], acc_prime[2]);
#endif // #ifdef FIRST_ALGORITHM
#ifdef SECOND_ALGORITHM
   acc_prime2[2]+=9.81;
   fprintf(file_modified_accelerations2_pt, "%lf %lf %lf %lf\n", t, acc_prime2[0], acc_prime2[1], acc_prime2[2]);
#endif // #ifdef SECOND_ALGORITHM
   
   // Use complementary filter to get better estimates for roll, pitch
   // and yaw, and update the value of the function with the new
   // values
#ifdef FIRST_ALGORITHM
   euler_angles_from_acc_prime[0] = atan2(acc_prime[2], acc_prime[1]);
   euler_angles_from_acc_prime[1] = atan2(acc_prime[0], acc_prime[2]);
   euler_angles_from_acc_prime[2] = atan2(acc_prime[1], acc_prime[0]);
   
   fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n", t,
           euler_angles_from_acc_prime[0],
           euler_angles_from_acc_prime[1],
           euler_angles_from_acc_prime[2]);
   
   euler_angles_filtered[0] = alpha * y[0][4] + (1.0 - alpha) * euler_angles_from_acc_prime[0];
   euler_angles_filtered[1] = alpha * y[0][5] + (1.0 - alpha) * euler_angles_from_acc_prime[1];
   euler_angles_filtered[2] = alpha * y[0][6] + (1.0 - alpha) * euler_angles_from_acc_prime[2];
   
   y[0][4] = euler_angles_filtered[0];
   y[0][5] = euler_angles_filtered[1];
   y[0][6] = euler_angles_filtered[2];
   fprintf(file_filtered_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n", t,
           euler_angles_filtered[0], euler_angles_filtered[1], euler_angles_filtered[2]);
#endif // #ifdef FIRST_ALGORITHM

#ifdef SECOND_ALGORITHM
   euler_angles_from_acc_prime2[0] = atan2(acc_prime2[2], acc_prime2[1]);
   euler_angles_from_acc_prime2[1] = atan2(acc_prime2[0], acc_prime2[2]);
   euler_angles_from_acc_prime2[2] = atan2(acc_prime2[1], acc_prime2[0]);
   
   fprintf(file_roll_pitch_yaw_from_acc2_pt, "%lf %lf %lf %lf\n", t,
           euler_angles_from_acc_prime2[0],
           euler_angles_from_acc_prime2[1],
           euler_angles_from_acc_prime2[2]);
   
   euler_angles_filtered2[0] = alpha * y[0][7] + (1.0 - alpha) * euler_angles_from_acc_prime2[0];
   euler_angles_filtered2[1] = alpha * y[0][8] + (1.0 - alpha) * euler_angles_from_acc_prime2[1];
   euler_angles_filtered2[2] = alpha * y[0][9] + (1.0 - alpha) * euler_angles_from_acc_prime2[2];
   
   y[0][7] = euler_angles_filtered2[0];
   y[0][8] = euler_angles_filtered2[1];
   y[0][9] = euler_angles_filtered2[2];
   fprintf(file_filtered_roll_pitch_yaw2_pt, "%lf %lf %lf %lf\n", t,
           euler_angles_filtered2[0], euler_angles_filtered2[1], euler_angles_filtered2[2]);
   
#endif // #ifdef SECOND_ALGORITHM
   
#ifdef THIRD_ALGORITHM
   // Fill rotation matrices
   // fill_rotation_matrices(R, R_t, y[0][10], y[0][11], y[0][12]); // tachidok
   fill_rotation_matrices(R, R_t, dummy[0], dummy[1], dummy[2]);
   
   // Transform from the body reference frame to the global reference
   // frame
   multiply_matrix_times_vector(R_t, acc, acc_inertial);//tachidok
   acc_inertial[2]+=9.81;
   //multiply_matrix_times_vector(R, dtheta, gyro_inertial);
   
   // Output data
   fprintf(file_inertial_accelerations_pt, "%lf %lf %lf %lf\n",
           t, acc_inertial[0], acc_inertial[1], acc_inertial[2]);
   //fprintf(file_inertial_gyro_pt, "%lf %lf %lf %lf\n",
   //        t, gyro_inertial[0], gyro_inertial[1], gyro_inertial[2]);
   
   // -------------------------------------------------------------------
   // Apply complementary filter
   // -------------------------------------------------------------------
   // Transform accelerations to angles
   acc_angles[0] = atan2(acc_inertial[2], acc_inertial[1]);
   acc_angles[1] = atan2(acc_inertial[0], acc_inertial[2]);
   acc_angles[2] = atan2(acc_inertial[1], acc_inertial[0]);
   
   // Update filtered Euler angles
   //y[0][10] = alpha * y[0][10] + (1.0 - alpha) * acc_inertial[0];
   //y[0][11] = alpha * y[0][11] + (1.0 - alpha) * acc_inertial[1];
   //y[0][12] = alpha * y[0][12] + (1.0 - alpha) * acc_inertial[2];
   
   // Output data
   fprintf(file_roll_pitch_yaw_pt, "%lf %lf %lf %lf\n",
           t, y[0][10], y[0][11], y[0][12]);
#endif // #ifdef THIRD_ALGORITHM
   
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output file
 fclose(file_roll_pitch_yaw_from_gyro_pt);
 fclose(file_raw_accelerations_pt);
  
#ifdef FIRST_ALGORITHM
 fclose(file_roll_pitch_yaw_from_acc_pt);
 fclose(file_modified_accelerations_pt);
 fclose(file_filtered_roll_pitch_yaw_pt);
#endif // #ifdef FIRST_ALGORITHM
 
#ifdef SECOND_ALGORITHM
 fclose(file_roll_pitch_yaw_from_acc2_pt);
 fclose(file_modified_accelerations2_pt);
 fclose(file_filtered_roll_pitch_yaw2_pt);
#endif // #ifdef SECOND_ALGORITHM
 
#ifdef THIRD_ALGORITHM
 fclose(file_inertial_accelerations_pt);
 fclose(file_inertial_gyro_pt);
#endif // #ifdef THIRD_ALGORITHM
 
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

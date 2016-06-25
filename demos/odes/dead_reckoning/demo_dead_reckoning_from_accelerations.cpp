#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
#include "../../../src/integration/ca_integration_method.h"
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_table_based_on_acceleration.h"

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
 R[0][1] = sin_theta_x*sin_theta_y*cos_theta_z - cos_theta_x*sin_theta_z;
 R[0][2] = cos_theta_x*sin_theta_y*cos_theta_z + sin_theta_x*sin_theta_z;
 
 R[1][0] = cos_theta_y*sin_theta_z;
 R[1][1] = sin_theta_x*sin_theta_y*sin_theta_z+cos_theta_x*cos_theta_z;
 R[1][2] = cos_theta_x*sin_theta_y*sin_theta_z-sin_theta_x*cos_theta_z;
 
 R[2][0] = -sin_theta_y;
 R[2][1] = sin_theta_x*cos_theta_y;
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
 
 // ----------------------------------------------------------------------------
 // FILES (END)
 // ----------------------------------------------------------------------------
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (steps, h,
 // initial values)
 // -----------------------------------------------------------------
 // Set the initial and final interval values (got from the number of data in Table)
 const double t_initial = 0.0;
 const double t_final = 4144;
 //const double t_final = 10;
 // Set the number of steps we want to take
 const double n_steps = 10000 * 2.0;
 //const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Initial time
 double t = t_initial;
 
 // Initial conditions
 y[0][0] = 0.0;         // Initial x-position
 y[0][1] = -0.05994836; // Initial x-velocity
 y[0][2] = 0.0;         // Initial y-position
 y[0][3] = 0.033224355; // Initial y-velocity
 y[0][4] = 0.0;         // Initial roll from gyro
 y[0][5] = 0.0;         // Initial pitch from gyro
 y[0][6] = 0.0;         // Initial yaw from gyro
 
 // Output the initial data to screen
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " x-vel: " << y[0][1]
           << " y-pos: " << y[0][2] << " y-vel: " << y[0][3]
           << " roll: " << y[0][4] << " pitch: " << y[0][5] << " yaw: " << y[0][6]<< std::endl;
 
 fprintf(file_roll_pitch_yaw_from_gyro_pt, "%lf %lf %lf %lf\n", t, y[0][4], y[0][5], y[0][6]);
 
 // Create the rotations matrix
 const unsigned dim = 3;
 std::vector<std::vector<double> > R(dim);
 std::vector<std::vector<double> > R_t(dim);
 for (unsigned i = 0; i < dim; i++)
  {
   R[i].resize(dim);
   R_t[i].resize(dim);
  }
 
 // Fill rotation matrices
 fill_rotation_matrices(R, R_t, y[0][4], y[0][5], y[0][6]);
 
 // Get the accelerometers readings from the Table
 double dummy_data;
 // Accelerations
 double acc_x, acc_y, acc_z;
 // Retrieve data from table
 odes->get_sensors_lecture(t, dummy_data, dummy_data, dummy_data,
                           acc_x, acc_y, acc_z,
                           dummy_data, dummy_data, dummy_data);
 
 // Create an accelerations vector
 std::vector<double> w(3, 0.0);
 w[0] = acc_x; w[1] = acc_y; w[2] = acc_z;
 // Gravity compensation
 std::vector<double> w_prime(3, 0.0);
 // Transform from the body frame to the global frame
 multiply_matrix_times_vector(R_t, w, w_prime);
 // Extract gravity
 w_prime[2]+=9.81;

 // Output the raw and the modified accelerations
 fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc_x, acc_y, acc_z);
 fprintf(file_modified_accelerations_pt, "%lf %lf %lf %lf\n", t, w_prime[0], w_prime[1], w_prime[2]);
 
 // Get roll and pitch from accelerations
 double roll_from_acc = atan2(w_prime[1], w_prime[2]);
 double pitch_from_acc = atan2(w_prime[0], w_prime[2]);
 double yaw_from_acc = atan2(w_prime[1], w_prime[0]);
 
 fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n", t,
         roll_from_acc, pitch_from_acc, yaw_from_acc);
 
 // Integrate
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
             << " roll: " << y[0][4] << " pitch: " << y[0][5] << " yaw: " << y[0][6]<< std::endl;
   
   fprintf(file_roll_pitch_yaw_from_gyro_pt, "%lf %lf %lf %lf\n", t, y[0][4], y[0][5], y[0][6]);
   
   // Fill rotation matrices
   fill_rotation_matrices(R, R_t, y[0][4], y[0][5], y[0][6]);
   
   // Get the accelerometers readings from the Table
   odes->get_sensors_lecture(t, dummy_data, dummy_data, dummy_data,
                             acc_x, acc_y, acc_z,
                             dummy_data, dummy_data, dummy_data);
   
   // Gravity compensation
   
   // Create an accelerations vector
   w[0] = acc_x; w[1] = acc_y; w[2] = acc_z;
   
   // Transform from the body frame to the global frame
   multiply_matrix_times_vector(R_t, w, w_prime);
   // Extract gravity
   w_prime[2]+=9.81;
   
   // Output the raw and the modified accelerations
   fprintf(file_raw_accelerations_pt, "%lf %lf %lf %lf\n", t, acc_x, acc_y, acc_z);
   fprintf(file_modified_accelerations_pt, "%lf %lf %lf %lf\n", t,
           w_prime[0], w_prime[1], w_prime[2]);
   
   // Get roll and pitch from accelerations   
   roll_from_acc = atan2(w_prime[1], w_prime[2]);
   pitch_from_acc = atan2(w_prime[0], w_prime[2]);
   yaw_from_acc = atan2(w_prime[1], w_prime[0]);
   
   fprintf(file_roll_pitch_yaw_from_acc_pt, "%lf %lf %lf %lf\n", t,
           roll_from_acc, pitch_from_acc, yaw_from_acc);
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Close the output files
 fclose(file_roll_pitch_yaw_from_acc_pt);
 fclose(file_roll_pitch_yaw_from_gyro_pt);
 fclose(file_raw_accelerations_pt);
 fclose(file_modified_accelerations_pt);
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 std::cout << "[DONE]" << std::endl;
 
}

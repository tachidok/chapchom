/** \file This file implements the CCODEsFromTableBasedOnAcceleration class
 */
#include "cc_odes_from_table_from_xsensMT9B.h"

namespace chapchom
{

 // ===================================================================
 // Constructor, sets the number of odes. We currently have two odes,
 // one for the velocity and the other for the acceleration
 // ===================================================================
 CCODEsFromTableFromXSENSMT9B::CCODEsFromTableFromXSENSMT9B(const char *euler_angles_filename,
                                                            const char *raw_sensors_data_filename)
  : ACODEs(9), DIM(3)
 {
  // The values have not been loaded into a table 
  Loaded_table = false;
  // Initialise the number of data in the Table
  //N_data_in_table = 0;
  //N_data_in_table = 18273; // no movement
  //N_data_in_table = 21162; // characterise yaw drift
  //N_data_in_table = 266959; // characterise yaw drift2
  //N_data_in_table = 20076; // ellipse movement
  N_data_in_table = 524668; // characterise yaw drift half hour
  //N_data_in_table = 1808483; // characterise yaw two hours
 
  // Create the interpolator
  interpolator_pt = new CCNewtonInterpolator();
 
  // Read the data from file
  //load_table("./xsensMT9B/no_movement/MT9_euler_00007154_000.log", "./xsensMT9B/no_movement/MT9_cal_00007154_000.log");
  load_table(euler_angles_filename, raw_sensors_data_filename);
 
  // Create storage for the matrix that relates the angular velocities
  // with the Euler rates
  A.resize(DIM);
  for (unsigned i = 0; i < DIM; i++)
   {
    A[i].resize(DIM);
   }
 
 }

 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsFromTableFromXSENSMT9B::~CCODEsFromTableFromXSENSMT9B()
 { 
  // Free memory for interpolator
  delete interpolator_pt;
  interpolator_pt = 0;
 }

 // ===================================================================
 // Loads the data from an input file to generate a table from which
 // the ode takes its values
 // ===================================================================
 void CCODEsFromTableFromXSENSMT9B::load_table(const char *euler_angles_filename,
                                               const char *raw_data_filename)
 {
  // Open the file with the euler angles data
  FILE *file_euler_angles_pt = fopen(euler_angles_filename, "r");
  if (file_euler_angles_pt == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The data file [" << euler_angles_filename << "] was not opened"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Open the file with the raw data
  FILE *file_raw_pt = fopen(raw_data_filename, "r");
  if (file_raw_pt == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The data file [" << raw_data_filename << "] was not opened"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
 
  // Resize the containers based on the Table size
  Table_time.resize(N_data_in_table);
  Table_acc_x.resize(N_data_in_table);
  Table_acc_y.resize(N_data_in_table);
  Table_acc_z.resize(N_data_in_table);
  Table_gyro_x.resize(N_data_in_table);
  Table_gyro_y.resize(N_data_in_table);
  Table_gyro_z.resize(N_data_in_table);
  Table_mag_x.resize(N_data_in_table);
  Table_mag_y.resize(N_data_in_table);
  Table_mag_z.resize(N_data_in_table);
  Table_roll.resize(N_data_in_table);
  Table_pitch.resize(N_data_in_table);
  Table_yaw.resize(N_data_in_table);
 
  // Read the data
  for (unsigned i = 0; i < N_data_in_table; i++)
   {
    double time;
    double acc_x;
    double acc_y;
    double acc_z;
    double gyro_x;
    double gyro_y;
    double gyro_z;
    double magnet_x;
    double magnet_y;
    double magnet_z;
    double roll;
    double pitch;
    double yaw;
    double temperature;
   
    // Read euler angles
    int n_read = fscanf(file_euler_angles_pt, "%lf\t%lf\t%lf\t%lf\n",
                        &time, &roll, &pitch, &yaw);
    if (n_read != 4)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Number of read values (" << n_read << ") in euler angles file" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
   
    // Read raw data
    n_read = fscanf(file_raw_pt, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
                    &time,
                    &acc_x, &acc_y, &acc_z,
                    &gyro_x, &gyro_y, &gyro_z,
                    &magnet_x, &magnet_y, &magnet_z,
                    &temperature);
    if (n_read != 11)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Number of read values (" << n_read << ") in raw data file" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
   
    Table_time[i] = time;
    Table_acc_x[i] = acc_x;
    Table_acc_y[i] = acc_y;
    Table_acc_z[i] = acc_z;
    Table_gyro_x[i] = gyro_x;
    Table_gyro_y[i] = gyro_y;
    Table_gyro_z[i] = gyro_z;
    Table_mag_x[i] = magnet_x;
    Table_mag_y[i] = magnet_y;
    Table_mag_z[i] = magnet_z;
    Table_roll[i] = roll;
    Table_pitch[i] = pitch;
    Table_yaw[i] = yaw;
   }
 
  // Close the files
  fclose(file_euler_angles_pt);
  fclose(file_raw_pt);
 
  Loaded_table = true;
 
 }

 // ======================================================================
 /// Get the values of the sensors at specific time (computed from table)
 // ======================================================================
 void CCODEsFromTableFromXSENSMT9B::get_sensors_lecture(const double t,
                                                        std::vector<double> &acc,
                                                        std::vector<double> &gyro,
                                                        std::vector<double> &mag,
                                                        std::vector<double> &euler_angles)
 {
  // Do linear interpolation
  unsigned interpolation_order = 1;
  // Do interpolation if the exact value was not found in the table
  bool do_interpolation = true;
  // In case of not using interpolation then use this index as the
  // entry of the table having the exact value
  unsigned i_exact = 0;
 
  // Search for the greater value smaller than "t", and the smaller
  // value larger than "t" to use them as the "x"s points for
  // interpolation
  int i_left = 0;
  int i_right = N_data_in_table - 1;
  bool loop = true;
  bool found_value = false;
  unsigned found_index = 0;
  while(loop)
   {
    if (i_left > i_right)
     {
      // Failure to find the value
      loop = false;
     }
   
    if (Table_time[i_left] == t)
     {
      do_interpolation = false;
      loop = false;
      found_value = true;
      i_exact = i_left;
     }
    else if (Table_time[i_right] == t)
     {
      do_interpolation = false;
      loop = false;
      found_value = true;
      i_exact = i_right;
     }
    else
     {
      // Compute the middle index in the current range
      const unsigned i_middle = std::floor(i_left + (i_right - i_left)/ 2);
#if 0
      std::cout << "T: (" << t << ")" << std::endl;
      std::cout << "i_left: (" << i_left << ") i_middle: ("
                << i_middle << ") i_right: ("
                << i_right << ")" << std::endl;
      std::cout << "[i_left]: (" << Table_time[i_left] << ") [i_middle]: ("
                << Table_time[i_middle] << ") [i_right]: ("
                << Table_time[i_right] << ")" << std::endl;
#endif // #if 0
      if (i_middle == i_left || i_middle == i_right &&
          (i_right - i_left) == 1)
       {
        //std::cout << "[END]" << std::endl;
        // Found data
        loop = false;
        found_value = true;
       }
      else if (Table_time[i_middle] < t)
       {
        //std::cout << "[MOVE LEFT TO MIDDLE]" << std::endl;
        i_left = i_middle;
       }
      else if (Table_time[i_middle] > t)
       {
        //std::cout << "[MOVE RIGHT TO MIDDLE]" << std::endl;
        i_right = i_middle;
       }
      else
       {
        // Error message
        std::ostringstream error_message;
        error_message << "The requested 't' value is not in the table"
                      << std::endl;
        throw ChapchomLibError(error_message.str(),
                               CHAPCHOM_CURRENT_FUNCTION,
                               CHAPCHOM_EXCEPTION_LOCATION);
       }
     
     } // The searched value is not exactly in the table
   
   } // while(loop)
 
  if (do_interpolation)
   {
    // Store the data used to interpolate in the correponding data structures
    std::vector<double> time(interpolation_order + 1);
    std::vector<double> acc_x(interpolation_order + 1);
    std::vector<double> acc_y(interpolation_order + 1);
    std::vector<double> acc_z(interpolation_order + 1);
    std::vector<double> gyro_x(interpolation_order + 1);
    std::vector<double> gyro_y(interpolation_order + 1);
    std::vector<double> gyro_z(interpolation_order + 1);
    std::vector<double> mag_x(interpolation_order + 1);
    std::vector<double> mag_y(interpolation_order + 1);
    std::vector<double> mag_z(interpolation_order + 1);
    std::vector<double> roll(interpolation_order + 1);
    std::vector<double> pitch(interpolation_order + 1);
    std::vector<double> yaw(interpolation_order + 1);
   
    // Copy the data
    time[0] = Table_time[i_left];
    time[1] = Table_time[i_right];
    acc_x[0]= Table_acc_x[i_left];
    acc_x[1]= Table_acc_x[i_right];
    acc_y[0]= Table_acc_y[i_left];
    acc_y[1]= Table_acc_y[i_right];
    acc_z[0]= Table_acc_z[i_left];
    acc_z[1]= Table_acc_z[i_right];
    gyro_x[0]= Table_gyro_x[i_left];
    gyro_x[1]= Table_gyro_x[i_right];
    gyro_y[0]= Table_gyro_y[i_left];
    gyro_y[1]= Table_gyro_y[i_right];
    gyro_z[0]= Table_gyro_z[i_left];
    gyro_z[1]= Table_gyro_z[i_right];
    mag_x[0]= Table_mag_x[i_left];
    mag_x[1]= Table_mag_x[i_right];
    mag_y[0]= Table_mag_y[i_left];
    mag_y[1]= Table_mag_y[i_right];
    mag_z[0]= Table_mag_z[i_left];
    mag_z[1]= Table_mag_z[i_right];
    roll[0]= Table_roll[i_left];
    roll[1]= Table_roll[i_right];
    pitch[0]= Table_pitch[i_left];
    pitch[1]= Table_pitch[i_right];
    yaw[0]= Table_yaw[i_left];
    yaw[1]= Table_yaw[i_right];
   
    acc[0] = interpolator_pt->interpolate_1D(time, acc_x, t, interpolation_order);
    acc[1] = interpolator_pt->interpolate_1D(time, acc_y, t, interpolation_order);
    acc[2] = interpolator_pt->interpolate_1D(time, acc_z, t, interpolation_order);
    gyro[0] = interpolator_pt->interpolate_1D(time, gyro_x, t, interpolation_order);
    gyro[1] = interpolator_pt->interpolate_1D(time, gyro_y, t, interpolation_order);
    gyro[2] = interpolator_pt->interpolate_1D(time, gyro_z, t, interpolation_order);
    mag[0] = interpolator_pt->interpolate_1D(time, mag_x, t, interpolation_order);
    mag[1] = interpolator_pt->interpolate_1D(time, mag_y, t, interpolation_order);
    mag[2] = interpolator_pt->interpolate_1D(time, mag_z, t, interpolation_order);
    // Transform to radians because the lectures are given in degress
    euler_angles[0] = interpolator_pt->interpolate_1D(time, roll, t, interpolation_order) * (M_PI / 180.0);
    euler_angles[1] = interpolator_pt->interpolate_1D(time, pitch, t, interpolation_order) * (M_PI / 180.0);
    euler_angles[2] = interpolator_pt->interpolate_1D(time, yaw, t, interpolation_order) * (M_PI / 180.0);
   }
  else // Do not do interpolation, the exact values are in the table
   {
    acc[0] = Table_acc_x[i_exact];
    acc[1] = Table_acc_y[i_exact];
    acc[2] = Table_acc_z[i_exact];
    gyro[0] = Table_gyro_x[i_exact];
    gyro[1] = Table_gyro_y[i_exact];
    gyro[2] = Table_gyro_z[i_exact];
    mag[0] = Table_gyro_x[i_exact];
    mag[1] = Table_gyro_y[i_exact];
    mag[2] = Table_gyro_z[i_exact];
    // Transform to radians because the lectures are given in degress
    euler_angles[0] = Table_roll[i_exact] * (M_PI / 180.0);
    euler_angles[1] = Table_pitch[i_exact] * (M_PI / 180.0);
    euler_angles[2] = Table_yaw[i_exact] * (M_PI / 180.0);
   }
  
 }
 
 // ===================================================================
 // Get yaw correction as a function of time and the number of steps
 // per second
 // ===================================================================
 const double CCODEsFromTableFromXSENSMT9B::get_yaw_correction(const double t,
                                                               const double n_steps_per_second)
 {
  // Check in which interval is "t"
  if (t >= 0 && t < 30.0)
   {
    return 2.0 * 0.006544985/n_steps_per_second; // 0.75 degreess per second
    //0.013089969/n_steps_per_second;
   }
  else if (t >= 30.0 && t < 60.0)
   {
    return 2.2 * 0.006544985/n_steps_per_second; // 0.75 degreess per second
    //0.013089969/n_steps_per_second;
   }
  else
   {
    return 2.5 * 0.006544985/n_steps_per_second; // 0.75 degreess per second
   }
 }
 
#if 0
 // ===================================================================
 // Get yaw correction as a function of time and the number of steps
 // per second
 // ===================================================================
 const double CCODEsFromTableFromXSENSMT9B::get_yaw_correction(const double t,
                                                               const double n_steps_per_second)
 {
  // Check in which interval is "t"
  if (t >= 0 && t < 10.0)
   {
    return 0.006544985/n_steps_per_second; // 0.00011 degreess per second
   }
  else if (t >= 10.0 && t < 30.0)
   {
    return 1.2 * 0.006544985/n_steps_per_second; // 0.00013 degreess per second
   }
  else if (t >= 30.0 && t < 60.0)
   {
    return 1.6 * 0.006544985/n_steps_per_second; // 0.00018 degreess per second
   }
  //else if (t >= 60.0 && t < 60.0*10.0)
  // {
  //  return 0.5 * 0.006544985/n_steps_per_second; // 0.00018 degreess per second
  // }
  else
   {
    return 2.0 * 0.006544985/n_steps_per_second; // 0.75 degreess per second
    //0.013089969/n_steps_per_second;
   }
  //   {
  //    return 0.013089969/n_steps_per_second; // 0.75 degreess per second
  //   }
 }
#endif // #if 0
 
 // ===================================================================
 /// Fills the matrix that performs the transformation from angular
 /// velocities to Euler-rates
 // ===================================================================
 void CCODEsFromTableFromXSENSMT9B::
 fill_angular_velocities_to_euler_rates_matrix(std::vector<std::vector<double> > &A,
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
 /// Multiplies a matrix times a vector
 // ===================================================================
 void CCODEsFromTableFromXSENSMT9B::multiply_matrix_times_vector(std::vector<std::vector<double> > &A,
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

 // ===================================================================
 // Evaluates the system of odes at the given time "t" and the values
 // of the function in "y". The evaluation produces results in the dy
 // vector
 // ===================================================================
 void CCODEsFromTableFromXSENSMT9B::evaluate(const double t,
                                             const std::vector<double> &y,
                                             std::vector<double> &dy)
 {
  // Velocities
  std::vector<double> vel(DIM);
  // Accelerations
  std::vector<double> acc(DIM);
  // Angle rates (gyro data)
  std::vector<double> gyro(DIM);
  // Angle rates (gyro data)
  std::vector<double> mag(DIM);
  // Dummy data
  std::vector<double> dummy(DIM);
  // Retrieve data from table
  get_sensors_lecture(t, acc, gyro, mag, dummy);
 
  // Zero velocities
  vel[0] = 0.0;
  vel[1] = 0.0;
  vel[2] = 0.0;
  // -------------------------------------------------------------------
  // Get the Euler angles
  // -------------------------------------------------------------------
  // Store the Euler-angles
  std::vector<double> euler_angles(DIM);
  euler_angles[0] = y[6];
  euler_angles[1] = y[7];
  euler_angles[2] = y[8];
 
  // Fill the matrix that transforms from angular velocities to
  // Euler-rates
  fill_angular_velocities_to_euler_rates_matrix(A, euler_angles);
 
  // Store the Euler-angles rates
  std::vector<double> euler_angles_rates(DIM);
  multiply_matrix_times_vector(A, gyro, euler_angles_rates);
 
  // -----------------
  // y[0] x-position
  // y[1] x-velocity
  // y[2] y-position
  // y[3] y-velocity
  // y[4] z-position
  // y[5] z-velocity
  // y[6] roll
  // y[7] pitch
  // y[8] yaw
  // -----------------
  // dy[0] x-velocity
  // dy[1] x-acceleration
  // dy[2] y-velocity
  // dy[3] y-acceleration
  // dy[4] z-velocity
  // dy[5] z-acceleration
  // dy[6] droll
  // dy[7] dpitch
  // dy[8] dyaw
 
  //dy[0] = vel[0];
  //dy[1] = acc[0];
  //dy[2] = vel[1];
  //dy[3] = acc[1];
  //dy[4] = vel[2];
  //dy[5] = acc[2];
  dy[0] = y[1];
  dy[1] = Linear_acceleration[0];
  dy[2] = y[3];
  dy[3] = Linear_acceleration[1];
  dy[4] = y[5];
  dy[5] = Linear_acceleration[2];
  dy[6] = euler_angles_rates[0];
  dy[7] = euler_angles_rates[1];
  dy[8] = euler_angles_rates[2];
 
 }

 // ===================================================================
 // Evaluates the specified ode by "i" of the system of odes at the
 // given time "t" and the values of the function in "y". The
 // evaluation produces results in the dy vector at the dy[i] position
 // ===================================================================
 void CCODEsFromTableFromXSENSMT9B::evaluate(const unsigned i, const double t,
                                             const std::vector<double> &y,
                                             std::vector<double> &dy)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "This method is not implemented for this class"
                << std::endl;
  throw ChapchomLibError(error_message.str(),
                         CHAPCHOM_CURRENT_FUNCTION,
                         CHAPCHOM_EXCEPTION_LOCATION);
 }

}

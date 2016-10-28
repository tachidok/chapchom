/** \file This file implements the CCODEsFromSensorsTelitSL869DR class
 */
#include "cc_odes_from_sensors_TelitSL869-DR.h"

namespace chapchom
{

 // ===================================================================
 // In charge of mapping the input value to the new scale (used by the
 // class CCODEsFromSensorsTelitSL869DR to transform the data read from
 // the NMEA strings to 'real')
 // ===================================================================
 double scale(double x_min, double x_max, double fx_min, double fx_max, double x);
 {
  const double s = (fx_max - fx_min) / (x_max - x_min);
  return ((x - x_min) * s) + fx_min;
 }
 
 // ===================================================================
 // Constructor, sets the number of odes. We currently have two odes,
 // one for the velocity and the other for the acceleration
 // ===================================================================
 CCODEsFromSensorsTelitSL869DR::
 CCODEsFromSensorsTelitSL869DR(const char *input_filename)
  : ACODEs(9), Current_data_index(0)
 {
  // Open the file
  Input_file.open(input_filename, std::ios::in);
  if (Input_file.fail())
   {
    // Error message
   std::ostringstream error_message;
   error_message << "We could not open the NMEA strings - sensors file:["
                 << input_filename << "]" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }  
  
  // Initialise nmea parser
  nmea_decoder = new CCNMEADecoder(20);
  
  // Create storage for the matrix that relates the angular velocities
  // with the Euler rates
  A.resize(DIM);
  for (unsigned i = 0; i < DIM; i++)
   {
    A[i].resize(DIM);
   }
 
 }

 // ===================================================================
 // Destructor
 // ===================================================================
 CCODEsFromSensorsTelitSL869DR::~CCODEsFromSensorsTelitSL869DR()
 { 
  // Close the file
  Input_file.close();

  // Free memory for nmea
  delete nmea_decoder;
 }
 
 // ======================================================================
 /// Get the values of the sensors at specific time (computed from table)
 // ======================================================================
 bool CCODEsFromSensorsTelitSL869DR::get_sensors_lectures()
 {
  // Initialise current data index (used to indicate which sensor data
  // is currently beeing processed)
  Current_data_index = 0;
  // Read data from the file/sensors. We proceed as follow:
  // -------------------------------------------------------------------
  // - State 1: Read a block of SIZE_BLOCK_DATA(15) PSTM3DACC data
  // -------------------------------------------------------------------
  // - State 2: Read a block of SIZE_BLOCK_DATA(15) PSTM3DGYRO data
  // -------------------------------------------------------------------
  
  // Extracted character
  char character;
  unsigned n_PSTM3DACC = 0;
  unsigned n_PSTM3DGYRO = 0;
  unsigned state = 1;
  // Flag to indicate whether GPRMC data has been read
  bool read_GPRMC_data = false;
  // Flag to indicate whether Euler angles data has been read
  bool read_Euler_angles_data = false;
  // Flag to continue looping
  bool LOOP = true;
  // Clear the input vectors
  Acceleration_data.clear();
  Gyro_data.clear();
  Euler_angles_data.clear();
  // Loop until eof
  while(LOOP && !Input_file.eof())
   {
    Input_file.get(character);
    //std::cerr << character;
    nmea_decoder->parse(character);
    // Check whether any of the data structures has new information
    if (nmea_decoder->is_accelerometer_data_ready())
     {
      if (state == 1)
       {
        // Get the data structure
        struct PSTM3DACC pstm3dacc = nmea_decoder->get_pstm3dacc();
        std::vector<double> read_acc(DIM+1);
        read_acc[0] = pstm3dacc.time;
        read_acc[1] = scale(X_MIN, X_MAX, FX_MIN_ACC, FX_MAX_ACC, pstm3dacc.acc_x);
        read_acc[2] = scale(X_MIN, X_MAX, FX_MIN_ACC, FX_MAX_ACC, pstm3dacc.acc_y);
        read_acc[3] = scale(X_MIN, X_MAX, FX_MIN_ACC, FX_MAX_ACC, pstm3dacc.acc_z);
        // Consume accelerometer data
        nmea_decoder->consume_accelerometer_data();
        // Add the reading to the acceleration data
        Acceleration_data.push_back(read_acc);
        // Increase the counter of the number of read acceleration data
        n_PSTM3DACC++;
        std::cout << "Time:" << read_acc[0]
                  << "Accelerometer:(" << read_acc[1] << ", " << read_acc[2] << ", " <<  read_acc[3] << ")"
                  << std::endl;
        
        // Have we reached the number of data
        if (n_PSTM3DACC == SIZE_BLOCK_DATA)
         {
          state = 2;
         }
        
       }
      else
       {
        // Something was wrong, clear all previously stored data and
        // start again
        state = 1;
        // Clear the input vectors
        Acceleration_data.clear();
        Gyro_data.clear();
        Euler_angles_data.clear();
        n_PSTM3DACC = 0;
        n_PSTM3DGYRO = 0;        
       }
      
     }
    
    if (nmea_decoder->is_gyro_data_ready())
     {      
      if (state == 2)
       {
        // Get the data structure
        struct PSTM3DGYRO pstm3dgyro = nmea_decoder->get_pstm3dgyro();
        std::vector<double> read_gyro(DIM+1);
        read_gyro[0] = pstm3dgyro.time;
        read_gyro[1] = scale(X_MIN, X_MAX, FX_MIN_GYRO, FX_MAX_GYRO, pstm3dgyro.raw_x);
        read_gyro[2] = scale(X_MIN, X_MAX, FX_MIN_GYRO, FX_MAX_GYRO, pstm3dgyro.raw_y);
        read_gyro[3] = scale(X_MIN, X_MAX, FX_MIN_GYRO, FX_MAX_GYRO, pstm3dgyro.raw_z);
        // Consume gyro data
        nmea_decoder->consume_gyro_data();
        // Add the reading to the gyro data
        Gyro_data.push_back(read_gyro);
        // Increase the counter of the number of read acceleration data
        n_PSTM3DGYRO++;
        std::cout << "Time:" << read_gyro[0]
                  << "Gyro:(" << read_gyro[1] << ", " << read_gyro[2] << ", " <<  read_gyro[3] << ")" << std::endl;

        // Have we reached the number of data
        if (n_PSTM3DGYRO == SIZE_BLOCK_DATA)
         {
          state = 3;
         }
        
       }
      else
       {
        // Something was wrong, clear all previously stored data and
        // start again
        state = 1;
        // Clear the input vectors
        Acceleration_data.clear();
        Gyro_data.clear();
        Euler_angles_data.clear();
        n_PSTM3DACC = 0;
        n_PSTM3DGYRO = 0;
       }
      
     }
    
    // TODO: GPRMC data
    read_GPRMC_data = true;
    
    if (nmea_decoder->is_GPRMC_data_ready())
     {
      // Get the data structure
      struct GPRMC gprmc = nmea_decoder->get_gprmc();
      const double latitude = gprmc.latitude;
      const double longitude = gprmc.longitude;
      const double course_degrees = gprmc.course_degrees;
      // Consume GPRMC data
      nmea_decoder->consume_GPRMC_data();
      // Indicate GPRMC data has been read
      read_GPRMC_data = true;
      std::cout << "GPRMC:(" << latitude << ", " << longitude << ", " <<  course_degrees << ")" << std::endl;
     }
    
    // TODO: Read Euler angles data
    read_Euler_angles_data = true;
    
    // If we have read the corresponding accelerometer, gyro, GPRMC
    // and Euler angles data then break the cycle
    if (state == 3 && read_GPRMC_data && read_Euler_angles_data)
     {
      LOOP = false;
     }
    
   }
  
  // If we finished the loop because there is no more data return
  // false to stop execution
  if (LOOP)
   {
    return false;
   }
  
  // Align/pair lectures such that accelerometers and gyro data
  // are given at the same time
  pair_lectures();
  
  return true;
  
 }
 
 // ===================================================================
 // Get yaw correction as a function of time and the number of steps
 // per second
 // ===================================================================
 const double CCODEsFromSensorsTelitSL869DR::get_yaw_correction(const double t,
                                                                const double n_steps_per_second)
 {
  // Error message
  std::ostringstream error_message;
  error_message << "Implement this" << std::endl;
  throw ChapchomLibError(error_message.str(),
                         CHAPCHOM_CURRENT_FUNCTION,
                         CHAPCHOM_EXCEPTION_LOCATION);
  
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
  
 // ===================================================================
 /// Fills the matrix that performs the transformation from angular
 /// velocities to Euler-rates
 // ===================================================================
 void CCODEsFromSensorsTelitSL869DR::
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
 void CCODEsFromSensorsTelitSL869DR::
 multiply_matrix_times_vector(std::vector<std::vector<double> > &A,
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
 void CCODEsFromSensorsTelitSL869DR::evaluate(const double t,
                                              const std::vector<double> &y,
                                              std::vector<double> &dy)
 {
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
  
  // Get the current reading from sensors
  // Gyro
  std::vector<double> gyro_t = get_angular_rates(Current_data_index);
  // Copy the data into a 3x3 vector
  std::vector<double> gyro(DIM);
  for (unsigned j = 0; j < DIM; j++)
   {
    gyro[j] = gyro_t[j+1];
   }
  
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
 void CCODEsFromSensorsTelitSL869DR::evaluate(const unsigned i, const double t,
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

 // ===================================================================
 // In charge of "pairing/align" the data obtained from the sensors
 // (accelerometers and gyro) via nearest value or interpolation such
 // that both lectures correspond to the same time
 // ===================================================================
 void CCODEsFromSensorsTelitSL869DR::pair_lectures()
 {
  // Get the number of lectures for accelerometer and gyro
  const unsigned n_acc_data = Acceleration_data.size();
  const unsigned n_gyro_data = Gyro_data.size();
  // Get the minimum number of lectures
  double n_min_data = 0.0;
  if (n_acc_data <= n_gyro_data)
   {
    n_min_data = n_acc_data;
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "There are more acceleration data [" << n_acc_data
                  << "] than gyro data [" << n_gyro_data << "]."
                  << std::endl << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Indicates the strategy followed to match the data
  // strategy = 0, nearest value
  // strategy = 1, linear interpolation
  
  // These strategies are based on the knowledge that the
  // accelerometers are read before the gyro's data
  const unsigned strategy = 0;
  // Create temporary arrays to process the data
  std::vector<std::vector<double> > tmp_acc_data;
  // Match the values based on the selected strategy
  if (strategy == 0)
   {
    // Do nothing since the data are already sorted following a
    // nearest strategy
   }
  else if (strategy == 1)
   {
    // We use the gyro's time to interpolate the accelerometers data
    for (unsigned i = 0; i < n_min_data - 1; i++)
     {
      const double t = Gyro_data[i][0];      
      // We know that gyro's readings come after one reading of the
      // accelerometers, thus we can use the previous and the next
      // data from the accelerometers to interpolate
      const double t_acc0 = Acceleration_data[i][0];
      const double t_acc1 = Acceleration_data[i+1][0];
      if (t >= t_acc0 && t <= t_acc1)
       {
        std::vector<double> interpolated_data(DIM+1);
        interpolated_data[0] = t;
        const double dt = t_acc1 - t_acc0;
        // Linear interpolation (for each dimension)
        for (unsigned j = 0; j < DIM; j++)
         {
          // Using divided differences notation
          const double a0 = Acceleration_data[i][j];
          const double a1 =
           (Acceleration_data[i+1][j] - Acceleration_data[i][j]) / dt;
          // Do interpolation
          interpolated_data[j+1] = a0 + a1 * (t - t_acc0);
         }
        // Add to the vector
        tmp_acc_data.push_back(interpolated_data);
        
       } // if (t >= t_acc0 && t <= t_acc1)
      else
       {
        // Error message
        std::ostringstream error_message;
        error_message << "Interpolation error, the time of reading the gyro"
                      << "\nis not between two readings of the accelerometer"
                      << "\nGyro["<<i<<"][0]:" << t
                      << "\nAcceleration["<<i<<"][0]:"<<Acceleration_data[i][0]
                      << "\nAcceleration["<<i+1<<"][0]:"<<Acceleration_data[i+1][0]
                      << std::endl << std::endl;
        throw ChapchomLibError(error_message.str(),
                               CHAPCHOM_CURRENT_FUNCTION,
                               CHAPCHOM_EXCEPTION_LOCATION);
       }
      
      
     } // for (i < n_min_data)

    // Copy back the information to the "Acceleration_data" structure
    Acceleration_data.clear();
    Acceleration_data.resize(n_min_data);
    for (unsigned i = 0; i < n_min_data; i++)
     {
      Acceleration_data.push_back(tmp_acc_data[i]);
     }
    
   }
  else
   {
    // Do nothing
   }
  
 }
 
}

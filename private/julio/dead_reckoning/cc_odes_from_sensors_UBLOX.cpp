/** \file This file implements the CCODEsFromSensorsUBLOX class
 */
#include "cc_odes_from_sensors_UBLOX.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes. We currently have 10 odes
 // ===================================================================
 CCODEsFromSensorsUBLOX::CCODEsFromSensorsUBLOX(const char *input_filename)
  : ACODEs(10)
 {
  
  // Data have not been load from table
  Loaded_data_from_table = false;
  
  // Read the data from file
  load_table(input_filename);
  
  // Initialise the number of data in the Table
  N_data_in_table = // TODO
   //N_data_in_table = 11592;
   //N_data_in_table = 78748;
  
   // Initialise index data
  Index_data = 0;
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsFromSensorsUBLOX::~CCODEsFromSensorsUBLOX()
 { }

 // ===================================================================
 // Loads the data from an input file to generate a table from which
 // the ode takes its values
 // ===================================================================
 void CCODEsFromSensorsUBLOX::load_table(const char *input_filename)
 {
  // Create the UBLOX decoder
  CCUBLOXDecoder ublox_decoder;
  
  // Create the nmea decoder
  CCNMEADecoder nmea_decoder(NFIELDS_NMEA_DECODER);
  
  // Create the object to deal with a file
  std::ifstream infile;
  infile.open(input_filename, std::ios::in | std::ios::binary);
  if (infile.fail())
   {
    // Error message
    std::ostringstream error_message;
    error_message << "We could not open the UBLOX bin file" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Extracted byte
  char byte;
  // Loop until eof
  while(!infile.eof())
   {
    infile.get(byte);
    
    // NMEA decoding
    {
     nmea_decoder.parse(byte);
    
     if (nmea_decoder.is_GPRMC_data_ready())
      {
       // Get the data structure
       struct GPRMC gprmc = nmea_decoder.get_gprmc();
       
       double utc_time = 0.0;
       if (gprmc.valid_data_UTC_time)
        {
         utc_time = gprmc.UTC_time;
        }
       
       char status = '0';
       if (gprmc.valid_data_status)
        {
         status = gprmc.status;
        }
       
       double latitude = 0.0;
       if (gprmc.valid_data_latitude)
          {
           latitude = gprmc.latitude;
          }
       
        // Change sign in latitude data if required
       if (gprmc.valid_data_latitude && gprmc.valid_data_NS && gprmc.NS == 'S')
          {
           latitude = -latitude;
          }
       
       double longitude = 0.0;
       if (gprmc.valid_data_longitude)
        {
         longitude = gprmc.longitude;
        }
       
       // Change sign in longitude data if required
       if (gprmc.valid_data_longitude && gprmc.valid_data_EW && gprmc.EW == 'W')
        {
         longitude = -longitude;
        }
       
       double course_degrees = 0.0;
       if (gprmc.valid_data_course_degrees)
        {
         course_degrees = gprmc.course_degrees;
        }
       
       // Create a package of data to push into
       std::vector<double> utc_lat_lon_course_valid(5);
       utc_lat_lon_course_valid[0] = utc_time;
       utc_lat_lon_course_valid[1] = latitude;
       utc_lat_lon_course_valid[2] = longitude;
       utc_lat_lon_course_valid[3] = course_degrees * TO_RADIANS;
       if (status == 'A')
        {
         utc_lat_lon_course_valid[4] = 1.0;
        }
       else
        {
         utc_lat_lon_course_valid[4] = 0.0;
        }
       
       // Push data into Table
       Table_latitude_longitude_course_valid.push_back(utc_lat_lon_course_valid);
       
       // Consume GPRMC data
       nmea_decoder.consume_GPRMC_data();
       
       std::cout << "GPRMC:(" << utc_time << " " << status << " " << latitude << ", " << longitude << ", " <<  course_degrees << ")" << std::endl;
      }
     
    } // NMEA decoding
    
    // UBLOX decoding
    {
     ublox_decoder.parse(byte);
     // Check whether any of the data structures has new information
     if (ublox_decoder.is_UBX_ESF_RAW_data_ready())
      {
       // Get the data structure
       struct UBX_ESF_RAW ubx_esf_raw = ublox_decoder.get_UBX_ESF_RAW();
      
       // Package the gyroscope data
       std::vector<double> gyro_data(4);
       gyro_data[0] = ubx_esf_raw.time_gyroscope_temperature;
       gyro_data[1] = ubx_esf_raw.gyroscope_x;
       gyro_data[2] = ubx_esf_raw.gyroscope_y;
       gyro_data[3] = ubx_esf_raw.gyroscope_z;
      
       // Package the acceleration data
       std::vector<double> acc_data(4);
       acc_data[0] = ubx_esf_raw.time_gyroscope_temperature;
       acc_data[1] = ubx_esf_raw.accelerometer_x;
       acc_data[2] = ubx_esf_raw.accelerometer_y;
       acc_data[3] = ubx_esf_raw.accelerometer_z;

       // Push data into Table
       Table_gyro.push_back(gyro_data);
       Table_acc.push_back(acc_data);
       
#if 0
       // Print the read data
       std::cout << ubx_esf_raw.time_gyroscope_temperature << " " << ubx_esf_raw.gyroscope_temperature << " " << ubx_esf_raw.gyroscope_x << " " << ubx_esf_raw.gyroscope_y << " " << ubx_esf_raw.gyroscope_z << " " << ubx_esf_raw.accelerometer_x << " " << ubx_esf_raw.accelerometer_y << " " << ubx_esf_raw.accelerometer_z << std::endl;
#endif // #if 0
      
       // Consume UBX-ESF-RAW
       ublox_decoder.consume_UBX_ESF_RAW_data();     
      }

    } // UBLOX decoding
    
   } // while(!infile.eof())
  
  // Close the files
  infile.close();

 }




  

  
 // Open the file with the data
 FILE *file_pt = fopen(input_filename, "r");
 if (file_pt == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The data file [" << input_filename << "] was not opened"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Resize the containers based on the Table size
  Table_acc.resize(N_data_in_table);
  Table_gyro.resize(N_data_in_table);
  Table_linear_acc.resize(N_data_in_table);
  Table_g_force.resize(N_data_in_table);
  Table_second_gyro.resize(N_data_in_table);
  Table_Euler_angles.resize(N_data_in_table);
  Table_velocity.resize(N_data_in_table);
  Table_velocity.resize(N_data_in_table);
  Table_latitude_longitude.resize(N_data_in_table);
  
  // Get rid of the first line where headers are stored
  char *headers=NULL;
  size_t length = 0;
  getline(&headers, &length, file_pt);
  
  // Skip data until reaching the Initial_index
  for (unsigned i = 0; i < Initial_index; i++)
   {
    getline(&headers, &length, file_pt);
   }
  
  double fixed_time = 0.0;
  double previous_read_time = 0.0;
  
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
    double lacc_x;
    double lacc_y;
    double lacc_z;
    double g_force;
    double sgyro_x;
    double sgyro_y;
    double sgyro_z;
    double roll;
    double pitch;
    double yaw;
    double north_vel;
    double east_vel;
    double down_vel;
    double latitude;
    double longitude;
    
    const int n_read =
     fscanf(file_pt, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
            &time, &acc_x, &acc_y, &acc_z,
            &gyro_x, &gyro_y, &gyro_z,
            &lacc_x, &lacc_y, &lacc_z,
            &g_force,
            &sgyro_x, &sgyro_y, &sgyro_z,
            &roll, &pitch, &yaw,
            &north_vel, &east_vel, &down_vel,
            &latitude, &longitude);
    if (n_read != 22)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Number of read values (" << n_read << ")" << std::endl
                    << "After reading (" << i << ") data rows" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
   
    if (time < previous_read_time)
     {
      fixed_time+=1.0;
     }
    
    const double this_time = fixed_time + time * 1.0e-6;
    
    Table_acc[i].resize(4);
    Table_acc[i][0] = this_time;
    Table_acc[i][1] = acc_x;
    Table_acc[i][2] = acc_y;
    Table_acc[i][3] = acc_z;
    
    Table_gyro[i].resize(4);
    Table_gyro[i][0] = this_time;
    Table_gyro[i][1] = gyro_x*TO_RADIANS;
    Table_gyro[i][2] = gyro_y*TO_RADIANS;
    Table_gyro[i][3] = gyro_z*TO_RADIANS;
    
    Table_linear_acc[i].resize(4);
    Table_linear_acc[i][0] = this_time;
    Table_linear_acc[i][1] = lacc_x;
    Table_linear_acc[i][2] = lacc_y;
    Table_linear_acc[i][3] = lacc_z;

    Table_g_force[i].resize(2);
    Table_g_force[i][0] = this_time;
    Table_g_force[i][1] = g_force;
    
    Table_second_gyro[i].resize(4);
    Table_second_gyro[i][0] = this_time;
    Table_second_gyro[i][1] = sgyro_x*TO_RADIANS;
    Table_second_gyro[i][2] = sgyro_y*TO_RADIANS;
    Table_second_gyro[i][3] = sgyro_z*TO_RADIANS;
    
    Table_Euler_angles[i].resize(4);
    Table_Euler_angles[i][0] = this_time;
    Table_Euler_angles[i][1] = roll*TO_RADIANS;
    Table_Euler_angles[i][2] = pitch*TO_RADIANS;
    Table_Euler_angles[i][3] = yaw*TO_RADIANS;
    
    Table_velocity[i].resize(4);
    Table_velocity[i][0] = this_time;
    Table_velocity[i][1] = north_vel;
    Table_velocity[i][2] = east_vel;
    Table_velocity[i][3] = down_vel;

    Table_latitude_longitude[i].resize(3);
    Table_latitude_longitude[i][0] = this_time;
    Table_latitude_longitude[i][1] = latitude;
    Table_latitude_longitude[i][2] = longitude;
    
    previous_read_time = time;
    
   }
  
  // Close the file
  fclose(file_pt);
  
  // Indicates that data have been loaded from table
  Loaded_data_from_table = true;
  
 }
 
 // ======================================================================
 /// Store the values of the sensors in arrays
 // ======================================================================
 bool CCODEsFromSensorsUBLOX::get_sensors_lectures()
 {
  // If we have read all the data then stop
  if (Index_data >= N_data_in_table)
   {
    return false;
   }
  
  // Return a block of data corresponding to one second of data
  
  // Backup the index data
  unsigned long Local_index_data = Index_data;
  // Get the initial time from the block of data
  const double initial_block_time = Table_gyro[Local_index_data][0];
  // Count the number of data to return
  unsigned counter = 0;
  
  while(Local_index_data < N_data_in_table &&
        (Table_gyro[Local_index_data++][0] - initial_block_time) < 1.0)
   {
    counter++;
   }
  
  // Clean return data
  Current_acc_from_table.resize(counter);
  Current_gyro_from_table.resize(counter);
  Current_linear_acc_from_table.resize(counter);
  Current_g_force_from_table.resize(counter);
  Current_second_gyro_from_table.resize(counter);
  Current_Euler_angles_from_table.resize(counter);
  Current_velocity_from_table.resize(counter);
  Current_latitude_longitude_from_table.resize(counter);
  
  for (unsigned i = 0; i < counter; i++)
   {
    // Resize to store the data block
    Current_acc_from_table[i].resize(DIM+1);
    Current_gyro_from_table[i].resize(DIM+1);
    
    Current_linear_acc_from_table[i].resize(DIM+1);
    Current_g_force_from_table[i].resize(2);
    Current_second_gyro_from_table[i].resize(DIM+1);
    Current_Euler_angles_from_table[i].resize(DIM+1);
    Current_velocity_from_table[i].resize(DIM+1);
    Current_latitude_longitude_from_table[i].resize(3);
    
    // Copy data block
    Current_acc_from_table[i][0] = Table_acc[Index_data+i][0];
    Current_acc_from_table[i][1] = Table_acc[Index_data+i][1];
    Current_acc_from_table[i][2] = Table_acc[Index_data+i][2];
    Current_acc_from_table[i][3] = Table_acc[Index_data+i][3];
    
    Current_gyro_from_table[i][0] = Table_gyro[Index_data+i][0];
    Current_gyro_from_table[i][1] = Table_gyro[Index_data+i][1];
    Current_gyro_from_table[i][2] = Table_gyro[Index_data+i][2];
    Current_gyro_from_table[i][3] = Table_gyro[Index_data+i][3];

    Current_linear_acc_from_table[i][0] = Table_linear_acc[Index_data+i][0];
    Current_linear_acc_from_table[i][1] = Table_linear_acc[Index_data+i][1];
    Current_linear_acc_from_table[i][2] = Table_linear_acc[Index_data+i][2];
    Current_linear_acc_from_table[i][3] = Table_linear_acc[Index_data+i][3];
    
    Current_g_force_from_table[i][0] = Table_g_force[Index_data+i][0];
    Current_g_force_from_table[i][1] = Table_g_force[Index_data+i][1];
    
    Current_second_gyro_from_table[i][0] = Table_second_gyro[Index_data+i][0];
    Current_second_gyro_from_table[i][1] = Table_second_gyro[Index_data+i][1];
    Current_second_gyro_from_table[i][2] = Table_second_gyro[Index_data+i][2];
    Current_second_gyro_from_table[i][3] = Table_second_gyro[Index_data+i][3];
    
    Current_Euler_angles_from_table[i][0] = Table_Euler_angles[Index_data+i][0];
    Current_Euler_angles_from_table[i][1] = Table_Euler_angles[Index_data+i][1];
    Current_Euler_angles_from_table[i][2] = Table_Euler_angles[Index_data+i][2];
    Current_Euler_angles_from_table[i][3] = Table_Euler_angles[Index_data+i][3];
    
    Current_velocity_from_table[i][0] = Table_velocity[Index_data+i][0];
    Current_velocity_from_table[i][1] = Table_velocity[Index_data+i][1];
    Current_velocity_from_table[i][2] = Table_velocity[Index_data+i][2];
    Current_velocity_from_table[i][3] = Table_velocity[Index_data+i][3];
    
    Current_latitude_longitude_from_table[i][0] = Table_latitude_longitude[Index_data+i][0];
    Current_latitude_longitude_from_table[i][1] = Table_latitude_longitude[Index_data+i][1];
    Current_latitude_longitude_from_table[i][2] = Table_latitude_longitude[Index_data+i][2];
    
   }
  
  // Increase the Index_data to point to the first data of the new
  // data block
  Index_data+=counter;
  
  return true;
 }
 
 // ======================================================================
 /// Set initial conditions
 // ======================================================================
 void CCODEsFromSensorsUBLOX::set_initial_conditions(std::vector<std::vector<double> > &y)
 {
  // Only assing initial conditions if data have been loadad from table
  if (Loaded_data_from_table)
   {
    // Set initial conditions
#ifdef TONANTZINTLA_TO_CHOLULA
    y[1][0] = 7.729281075; // Initial x-velocity
    y[6][0] = 0.03174143; // Initial roll (radians)
    y[7][0] = 0.044491584; // Initial pitch (radians)
    y[8][0] = 0.646752591;//0.924043736;//0.646752591; // Initial yaw (radians)
    y[9][0] = 0.646752591;//0.0 // Initial yaw with threshold (radians)
#endif // #ifdef TONANTZINTLA_TO_CHOLULA
    
#ifdef TLAXCALANCINGO_TO_ACATEPEC_ZERO_INITIAL_VELOCITY
    y[1][0] = 0.017278609; // Initial x-velocity
    y[6][0] = 0.018566813; // Initial roll (radians)
    y[7][0] = 0.079363612; // Initial pitch (radians)
    y[8][0] = -2.017426082; //4.404219685;//0.924043736;//0.646752591; // Initial yaw (radians)
    y[9][0] = -2.017426082; // Initial yaw with threshold (radians)
#endif // #ifdef TLAXCALANCINGO_TO_ACATEPEC_ZERO_INITIAL_VELOCITY
 
#ifdef TLAXCALANCINGO_TO_ACATEPEC
    y[1][0] = 9.47332405; // Initial x-velocity
    y[6][0] = 0.063093652; // Initial roll (radians)
    y[7][0] = 0.048420669; // Initial pitch (radians)
    y[8][0] = -1.82427573; //4.404219685;//0.924043736;//0.646752591; // Initial yaw (radians)
    y[9][0] = -1.82427573; // Initial yaw with threshold (radians)
#endif // #ifdef TLAXCALANCINGO_TO_ACATEPEC
 
#ifdef ACATEPEC_TO_TONANTZINTLA
    y[1][0] = 9.928759692; // Initial x-velocity
    y[6][0] = 0.020158553; // Initial roll (radians)
    y[7][0] = 0.016275195; // Initial pitch (radians)
    y[8][0] = -1.031505296; // Initial yaw (radians)
    y[9][0] = -1.031505296; // Initial yaw with threshold (radians)
#endif // #ifdef ACATEPEC_TO_TONANTZINTLA

#ifdef UDLAP_PERIFERICO
    y[1][0] = 11.422295071; // Initial x-velocity
    y[6][0] = 0.04549096; // Initial roll (radians)
    y[7][0] = 0.008888264; // Initial pitch (radians)
    y[8][0] = 2.923349999; // Initial yaw (radians)
    y[9][0] = 2.923349999; // Initial yaw with threshold (radians)
#endif // #ifdef UDLAP_PERIFERICO
 
#ifdef PERIFERICO_TO_11SUR
    y[1][0] = 16.06923009; // Initial x-velocity
    y[6][0] = -0.050907938; // Initial roll (radians)
    y[7][0] = 0.062309127; // Initial pitch (radians)
    y[8][0] = 2.777109996; // Initial yaw (radians)
    y[9][0] = 2.777109996; // Initial yaw with threshold (radians)
#endif// #ifdef PERIFERICO_TO_11SUR
 
#ifdef _11SUR_TO_TLAXCALANCINGO
    y[1][0] = 14.630887714; // Initial x-velocity
    y[6][0] = -0.033215536; // Initial roll (radians)
    y[7][0] = 0.026363547; // Initial pitch (radians)
    y[8][0] = -1.465565365; // Initial yaw (radians)
    y[9][0] = -1.465565365; // Initial yaw with threshold (radians)
#endif// #ifdef _11SUR_TO_TLAXCALANCINGO 
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Data have not been loaded from table thus we can not set\n"
                  << "initial conditions" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
  
 }

 // ======================================================================
 /// Reset initial contidions
 // ======================================================================
 void CCODEsFromSensorsUBLOX::reset_initial_conditions_at_current_time(std::vector<std::vector<double> > &y)
 {
  // Only assing initial conditions if data have been loadad from table
  if (Loaded_data_from_table)
   {
    // Reset initial conditions
    y[6][0] = Table_Euler_angles[Index_data][1]; // Roll (radians)
    y[7][0] = Table_Euler_angles[Index_data][2]; // Pitch (radians)
    y[8][0] = Table_Euler_angles[Index_data][3]; // Yaw (radians)
    y[9][0] = y[8][0]; // Yaw with threshold (radians)
   }
  else
   {
    // Error message
    std::ostringstream error_message;
    error_message << "Data have not been loaded from table thus we can not reset\n"
                  << "initial conditions" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
   
 }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t". The values of the i-th
 /// function at previous times are accessible via y[i][1], y[i][2]
 /// and so on. The evaluation produces results in the vector dy.
 // ===================================================================
 void CCODEsFromSensorsUBLOX::evaluate(const double t,
                                       const std::vector<std::vector<double> > &y,
                                          std::vector<double> &dy)
 {
  // -----------------
  // y[0][0] Current x-position
  // y[1][0] Current x-velocity
  // y[2][0] Current y-position
  // y[3][0] Current y-velocity
  // y[4][0] Current z-position
  // y[5][0] Current z-velocity
  // y[6][0] Current roll
  // y[7][0] Current pitch
  // y[8][0] Current yaw
  // y[9][0] Current yaw with threshold
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
  // dy[9] dyaw with threshold
 
  dy[0] = y[1][0];
  //dy[0] = North_velocity;
  dy[1] = Linear_acceleration[0];
  dy[2] = y[3][0];
  //dy[2] = East_velocity;
  dy[3] = Linear_acceleration[1];
  dy[4] = y[5][0];
  dy[5] = Linear_acceleration[2];
  dy[6] = Euler_angles_rates[0];
  dy[7] = Euler_angles_rates[1];
  dy[8] = Euler_angles_rates[2];
  dy[9] = Yaw_change_rate_with_threshold;
  
 }
 
 // ===================================================================
 /// Evaluates the i-th ode at time "t". The values of the function
 /// at previous times are stores at y[1], y[2] and so on. The
 /// evaluation stores the result in dy.
 // ===================================================================
 void CCODEsFromSensorsUBLOX::evaluate(const unsigned i, const double t,
                                       const std::vector<double> &y, double &dy)
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

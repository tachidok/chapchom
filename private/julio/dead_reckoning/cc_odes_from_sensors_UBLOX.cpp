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
  N_data_in_table = Table_acc.size();
  //N_data_in_table = 11592;
  //N_data_in_table = 78748;
  
  // Initialise index data
  Index_data = 0;
  Index_data_for_lat_lon = 0;
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
  CCNMEADecoder nmea_decoder(NFIELDS_NMEA_DECODER, 50);
  
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

  //  unsigned my_counter_RMC = 0;
  //  unsigned my_counter_inertial = 0;
  double time_counter = 0.0;
  // Extracted byte
  char byte;
  // Loop until eof
  while(!infile.eof())
   {
    infile.get(byte);
    
    //std::cerr << byte;
    
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
       
        // Transform from degress to decimal
       latitude = degress_to_decimal_helper(latitude);
       longitude = degress_to_decimal_helper(longitude);
       
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
       
       //       std::cout << "GNRMC:(" << my_counter_RMC++ << " " << utc_time << " " << status << " " << latitude << ", " << longitude << ", " <<  course_degrees << ")" << std::endl;
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
       //gyro_data[0] = ubx_esf_raw.time_gyroscope_temperature;
       gyro_data[0] = time_counter;
       gyro_data[1] = ubx_esf_raw.gyroscope_x * TO_RADIANS;
       gyro_data[2] = ubx_esf_raw.gyroscope_y * TO_RADIANS;
       gyro_data[3] = ubx_esf_raw.gyroscope_z * TO_RADIANS;
       
       // Package the acceleration data
       std::vector<double> acc_data(4);
       //acc_data[0] = ubx_esf_raw.time_gyroscope_temperature;
       acc_data[0] = time_counter;
       acc_data[1] = ubx_esf_raw.accelerometer_x;
       acc_data[2] = ubx_esf_raw.accelerometer_y;
       acc_data[3] = -ubx_esf_raw.accelerometer_z; // Negative 

       // Push data into Table
       Table_gyro.push_back(gyro_data);
       Table_acc.push_back(acc_data);
       
       time_counter+=FIXED_STEP_SIZE;
       
       // Print the read data
       //       std::cout << my_counter_inertial++ << " " << gyro_data[0] << " " << gyro_data[1] << " " << gyro_data[2] << " " << gyro_data[3] << " " << acc_data[1] << " " << acc_data[2] << " " << acc_data[3] << " " << std::endl;
       
       // Consume UBX-ESF-RAW
       ublox_decoder.consume_UBX_ESF_RAW_data();     
      }
     
    } // UBLOX decoding
    
   } // while(!infile.eof())
  
  // Close the files
  infile.close();

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
  
  for (unsigned i = 0; i < counter; i++)
   {
    // Resize to store the data block
    Current_acc_from_table[i].resize(DIM+1);
    Current_gyro_from_table[i].resize(DIM+1);
        
    // Copy data block
    Current_acc_from_table[i][0] = Table_acc[Index_data+i][0];
    Current_acc_from_table[i][1] = Table_acc[Index_data+i][1];
    Current_acc_from_table[i][2] = Table_acc[Index_data+i][2];
    Current_acc_from_table[i][3] = Table_acc[Index_data+i][3];
    
    Current_gyro_from_table[i][0] = Table_gyro[Index_data+i][0];
    Current_gyro_from_table[i][1] = Table_gyro[Index_data+i][1];
    Current_gyro_from_table[i][2] = Table_gyro[Index_data+i][2];
    Current_gyro_from_table[i][3] = Table_gyro[Index_data+i][3]; 
   }
  
  // Increase the Index_data to point to the first data of the new
  // data block
  Index_data+=counter;
  
  // Add the data for latitude and longitude
  Current_latitude_longitude_from_table.resize(1);
  
  Current_latitude_longitude_from_table[0].resize(5);
  
  Current_latitude_longitude_from_table[0][0] = Table_latitude_longitude_course_valid[Index_data_for_lat_lon][0];
  Current_latitude_longitude_from_table[0][1] = Table_latitude_longitude_course_valid[Index_data_for_lat_lon][1];
  Current_latitude_longitude_from_table[0][2] = Table_latitude_longitude_course_valid[Index_data_for_lat_lon][2];
  Current_latitude_longitude_from_table[0][3] = Table_latitude_longitude_course_valid[Index_data_for_lat_lon][3];
  Current_latitude_longitude_from_table[0][4] = Table_latitude_longitude_course_valid[Index_data_for_lat_lon][4];
  
  
  Index_data_for_lat_lon++;
  
  return true;
 }
 
 // ===================================================================
 // Convert degrees, minutes and seconds to decimal degrees
 // ===================================================================
 double CCODEsFromSensorsUBLOX::degress_to_decimal_helper(double dm)
 {
  double decimal_degrees = 0;
  double mind = 0;
  int deg = 0;
 
  // Get the degress, they are in the 3rd and 4th digit to the left
  // after the decimal point
  deg = (int)(dm / 100);
 
  // Get the minutes, they include all the digits to the right after
  // the decimal point, and the 1st and 2nd digit to the left after the
  // decimal point
  mind = (dm - deg*100);
  // The final data is the number of degrees plus the number degrees
  // made from minutes
  decimal_degrees = deg + (mind / 60.0);
  
  // Return the decimal format
  return decimal_degrees;
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
#ifdef IDA_40KMPH_1
    y[1][0] = 40.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_40KMPH_1

#ifdef IDA_40KMPH_2
    y[1][0] = 40.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_40KMPH_2

#ifdef REGRESO_40KMPH_1
    y[1][0] = 40.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_40KMPH_1

#ifdef REGRESO_40KMPH_2
    y[1][0] = 40.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_40KMPH_2

#ifdef IDA_50KMPH_1
    y[1][0] = 50.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_50KMPH_1

#ifdef IDA_50KMPH_2
    y[1][0] = 50.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_50KMPH_2

#ifdef REGRESO_50KMPH_1
    y[1][0] = 50.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_50KMPH_1

#ifdef REGRESO_50KMPH_2
    y[1][0] = 50.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_50KMPH_2

#ifdef IDA_60KMPH_1
    y[1][0] = 60.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_60KMPH_1

#ifdef IDA_60KMPH_2
    y[1][0] = 60.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_60KMPH_2

#ifdef REGRESO_60KMPH_1
    y[1][0] = 60.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_60KMPH_1

#ifdef REGRESO_60KMPH_2
    y[1][0] = 60.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_60KMPH_2

#ifdef IDA_70KMPH_1
    y[1][0] = 70.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_70KMPH_1

#ifdef IDA_70KMPH_2
    y[1][0] = 70.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_70MPH_2

#ifdef REGRESO_70KMPH_1
    y[1][0] = 70.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_70KMPH_1

#ifdef REGRESO_70KMPH_2
    y[1][0] = 70.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_70KMPH_2

#ifdef IDA_80KMPH_1
    y[1][0] = 80.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_80KMPH_1

#ifdef IDA_80KMPH_2
    y[1][0] = 80.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_80KMPH_2

#ifdef REGRESO_80KMPH_1
    y[1][0] = 80.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_80KMPH_1

#ifdef REGRESO_80KMPH_2
    y[1][0] = 80.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_80KMPH_2

#ifdef IDA_90KMPH_1
    y[1][0] = 90.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef IDA_90KMPH_1

#ifdef REGRESO_90KMPH_1
    y[1][0] = 90.0*0.277777777777; // Initial x-velocity
    y[6][0] = 0.0; // Initial roll (radians)
    y[7][0] = 0.0; // Initial pitch (radians)
    y[8][0] = 0.0; // Initial yaw (radians)
    y[9][0] = 0.0; // Initial yaw with threshold (radians)
#endif // #ifdef REGRESO_90KMPH_1
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

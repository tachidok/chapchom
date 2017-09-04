/** \file This file implements the CCODEsFromSensorsMoreData class
 */
#include "cc_odes_from_sensors_more_data.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes. We currently have two odes,
 // one for the velocity and the other for the acceleration
 // ===================================================================
 CCODEsFromSensorsMoreData::CCODEsFromSensorsMoreData(const char *input_filename,
                                                      const unsigned initial_index,
                                                      const unsigned final_index)
  : ACODEs(10)
 {
  
  Initial_index=initial_index;
  Final_index=final_index;
  
  // Initialise the number of data in the Table
  N_data_in_table=Final_index - Initial_index + 1;
  //N_data_in_table=N_data_in_table/8+1;
  
  //N_data_in_table = 11592;
  //N_data_in_table = 78748;
  
  // Read the data from file
  load_table(input_filename);
  
  // Initialise index data
  Index_data = 0;
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsFromSensorsMoreData::~CCODEsFromSensorsMoreData()
 { }

 // ===================================================================
 // Loads the data from an input file to generate a table from which
 // the ode takes its values
 // ===================================================================
 void CCODEsFromSensorsMoreData::load_table(const char *input_filename)
 {
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
  Table_Euler_angles.resize(N_data_in_table);
  Table_velocity.resize(N_data_in_table);
  Table_inertial_velocity.resize(N_data_in_table);
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
    double vel_x;
    double vel_y;
    double vel_z;
    double latitude;
    double altitude;
    double longitude;
    double roll;
    double pitch;
    double yaw;
    double north_vel;
    double east_vel;
    double down_vel;
    double total_vel;
    double inertial_vel;
    double distance_AGL;
    
    const int n_read =
     fscanf(file_pt, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
            &time,
            &acc_x, &acc_y, &acc_z,
            &gyro_x, &gyro_y, &gyro_z,
            &vel_x, &vel_y, &vel_z,
            &latitude, &altitude, &longitude,
            &roll, &pitch, &yaw,
            &total_vel, &inertial_vel,
            &north_vel, &east_vel, &down_vel,
            &distance_AGL);
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
    
    Table_acc[i].resize(4);
    Table_acc[i][0] = time;
    Table_acc[i][1] = acc_x * FEETS_TO_METERS;
    Table_acc[i][2] = acc_y * FEETS_TO_METERS;
    Table_acc[i][3] = acc_z * FEETS_TO_METERS;
    
    Table_gyro[i].resize(4);
    Table_gyro[i][0] = time;
    Table_gyro[i][1] = gyro_x*TO_RADIANS;
    Table_gyro[i][2] = gyro_y*TO_RADIANS;
    Table_gyro[i][3] = gyro_z*TO_RADIANS;

    Table_latitude_longitude[i].resize(3);
    Table_latitude_longitude[i][0] = time;
    Table_latitude_longitude[i][1] = latitude;
    Table_latitude_longitude[i][2] = longitude;
    
    Table_Euler_angles[i].resize(4);
    Table_Euler_angles[i][0] = time;
    Table_Euler_angles[i][1] = roll*TO_RADIANS;
    Table_Euler_angles[i][2] = pitch*TO_RADIANS;
    Table_Euler_angles[i][3] = yaw*TO_RADIANS;

    Table_inertial_velocity[i].resize(3);
    Table_inertial_velocity[i][0] = time;
    Table_inertial_velocity[i][1] = total_vel * FEETS_TO_METERS;
    Table_inertial_velocity[i][2] = inertial_vel * FEETS_TO_METERS;
    
    Table_body_velocity[i].resize(4);
    Table_body_velocity[i][0] = time;
    Table_body_velocity[i][1] = vel_x * FEETS_TO_METERS;
    Table_body_velocity[i][2] = vel_y * FEETS_TO_METERS;
    Table_body_velocity[i][3] = vel_z * FEETS_TO_METERS; 
    
    Table_velocity[i].resize(4);
    Table_velocity[i][0] = time;
    Table_velocity[i][1] = north_vel * FEETS_TO_METERS;
    Table_velocity[i][2] = east_vel * FEETS_TO_METERS;
    Table_velocity[i][3] = down_vel * FEETS_TO_METERS;

#if 1
    // Skip data
    const unsigned n_skip = 8;
    for (unsigned j = 0; j < n_skip; j++)
     {
      const int n_read =
       fscanf(file_pt, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
              &time,
              &acc_x, &acc_y, &acc_z,
              &gyro_x, &gyro_y, &gyro_z,
              &latitude, &altitude, &longitude,
              &roll, &pitch, &yaw,
              &total_vel, &inertial_vel,
              &north_vel, &east_vel, &down_vel,
              &distance_AGL);
      if (n_read != 19)
       {
        // Error message
        std::ostringstream error_message;
        error_message << "Number of read values (" << n_read << ")" << std::endl
                      << "After reading (" << i << ") data rows" << std::endl;
        throw ChapchomLibError(error_message.str(),
                               CHAPCHOM_CURRENT_FUNCTION,
                               CHAPCHOM_EXCEPTION_LOCATION);
        
       }
      
     } // for (j < n_skip)
#endif // #if 1
    
   }
 
  // Close the file
  fclose(file_pt);
 
 }

 // ======================================================================
 /// Store the values of the sensors in arrays
 // ======================================================================
 bool CCODEsFromSensorsMoreData::get_sensors_lectures()
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
  
  // Get a block of data with measures corresponding to one second
  while(Local_index_data < N_data_in_table &&
        (Table_gyro[Local_index_data++][0] - initial_block_time) < 1.0)
   {
    counter++;
   }
  
  // Clean return data
  Current_acc_from_table.resize(counter);
  Current_gyro_from_table.resize(counter);
  Current_Euler_angles_from_table.resize(counter);
  Current_velocity_from_table.resize(counter);
  Current_body_velocity_from_table.resize(counter);
  Current_inertial_velocity_from_table.resize(counter);
  Current_latitude_longitude_from_table.resize(counter);
  
  for (unsigned i = 0; i < counter; i++)
   {
    // Resize to store the data block
    Current_acc_from_table[i].resize(DIM+1);
    Current_gyro_from_table[i].resize(DIM+1);
    
    Current_Euler_angles_from_table[i].resize(DIM+1);
    Current_velocity_from_table[i].resize(DIM+1);
    Current_inertial_velocity_from_table[i].resize(3);
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
    
    Current_Euler_angles_from_table[i][0] = Table_Euler_angles[Index_data+i][0];
    Current_Euler_angles_from_table[i][1] = Table_Euler_angles[Index_data+i][1];
    Current_Euler_angles_from_table[i][2] = Table_Euler_angles[Index_data+i][2];
    Current_Euler_angles_from_table[i][3] = Table_Euler_angles[Index_data+i][3];
    
    Current_velocity_from_table[i][0] = Table_velocity[Index_data+i][0];
    Current_velocity_from_table[i][1] = Table_velocity[Index_data+i][1];
    Current_velocity_from_table[i][2] = Table_velocity[Index_data+i][2];
    Current_velocity_from_table[i][3] = Table_velocity[Index_data+i][3];
    
    Current_body_velocity_from_table[i][0] = Table_body_velocity[Index_data+i][0];
    Current_body_velocity_from_table[i][1] = Table_body_velocity[Index_data+i][1];
    Current_body_velocity_from_table[i][2] = Table_body_velocity[Index_data+i][2];
    Current_body_velocity_from_table[i][3] = Table_body_velocity[Index_data+i][3];
    
    Current_inertial_velocity_from_table[i][0] = Table_inertial_velocity[Index_data+i][0];
    Current_inertial_velocity_from_table[i][1] = Table_inertial_velocity[Index_data+i][1];
    Current_inertial_velocity_from_table[i][2] = Table_inertial_velocity[Index_data+i][2];
    
    Current_latitude_longitude_from_table[i][0] = Table_latitude_longitude[Index_data+i][0];
    Current_latitude_longitude_from_table[i][1] = Table_latitude_longitude[Index_data+i][1];
    Current_latitude_longitude_from_table[i][2] = Table_latitude_longitude[Index_data+i][2];
    
   }
  
  // Increase the Index_data to point to the first data of the new
  // data block
  Index_data+=counter;
  
  return true;
 }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t". The values of the i-th
 /// function at previous times are accessible via y[i][1], y[i][2]
 /// and so on. The evaluation produces results in the vector dy.
 // ===================================================================
 void CCODEsFromSensorsMoreData::evaluate(const double t,
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
 void CCODEsFromSensorsMoreData::evaluate(const unsigned i, const double t,
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

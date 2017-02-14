/** \file This file implements the CCODEsFromSensorsGEOFOG3D class
 */
#include "cc_odes_from_sensors_GEOFOG3D.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes. We currently have two odes,
 // one for the velocity and the other for the acceleration
 // ===================================================================
 CCODEsFromSensorsGEOFOG3D::CCODEsFromSensorsGEOFOG3D(const char *input_filename)
  : ACODEs(10)
 {
  // Initialise the number of data in the Table
  N_data_in_table = 78748;
  
  // Read the data from file
  load_table(input_filename);
  
  // Initialise index data
  Index_data = 0;
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCODEsFromSensorsGEOFOG3D::~CCODEsFromSensorsGEOFOG3D()
 { }

 // ===================================================================
 // Loads the data from an input file to generate a table from which
 // the ode takes its values
 // ===================================================================
 void CCODEsFromSensorsGEOFOG3D::load_table(const char *input_filename)
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
    int n_read = fscanf(file_pt, "%lf %lf %lf %lf %lf %lf %lf",
                        &time, &acc_x, &acc_y, &acc_z,
                        &gyro_x, &gyro_y, &gyro_z);
    if (n_read != 7)
     {
      // Error message
      std::ostringstream error_message;
      error_message << "Number of read values (" << n_read << ")" << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
   
    if (time < previous_read_time)
     {
      fixed_time+=1.0;
     }
    
    Table_acc[i].resize(4);
    Table_acc[i][0] = fixed_time + time * 1.0e-6;
    Table_acc[i][1] = acc_x;
    Table_acc[i][2] = acc_y;
    Table_acc[i][3] = acc_z;
    Table_gyro[i].resize(4);
    Table_gyro[i][0] = fixed_time + time * 1.0e-6;
    Table_gyro[i][1] = gyro_x;
    Table_gyro[i][2] = gyro_y;
    Table_gyro[i][3] = gyro_z;
    
    previous_read_time = time;
    
   }
 
  // Close the file
  fclose(file_pt);
 
 }

 // ======================================================================
 /// Store the values of the sensors in arrays
 // ======================================================================
 bool CCODEsFromSensorsGEOFOG3D::get_sensors_lectures()
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
  Current_acc.resize(counter);
  Current_gyro.resize(counter);
  
  for (unsigned i = 0; i < counter; i++)
   {
    // Resize to store the data block
    Current_acc[i].resize(DIM+1);
    Current_gyro[i].resize(DIM+1);
    
    // Copy data block
    Current_acc[i][0] = Table_acc[Index_data+i][0];
    Current_acc[i][1] = Table_acc[Index_data+i][1];
    Current_acc[i][2] = Table_acc[Index_data+i][2];
    Current_acc[i][3] = Table_acc[Index_data+i][3];
    
    Current_gyro[i][0] = Table_gyro[Index_data+i][0];
    Current_gyro[i][1] = Table_gyro[Index_data+i][1];
    Current_gyro[i][2] = Table_gyro[Index_data+i][2];
    Current_gyro[i][3] = Table_gyro[Index_data+i][3];
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
 void CCODEsFromSensorsGEOFOG3D::evaluate(const double t,
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
 void CCODEsFromSensorsGEOFOG3D::evaluate(const unsigned i, const double t,
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

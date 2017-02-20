/** \file This file implements the CCODEsFromSensorsGEOFOG3D class
 */
#include "cc_odes_from_sensors_GEOFOG3D.h"

// ===================================================================
// Constructor, sets the number of odes. We currently have two odes,
// one for the velocity and the other for the acceleration
// ===================================================================
CCODEsFromSensorsGEOFOG3D::CCODEsFromSensorsGEOFOG3D()
 : ACODEs(10)
{
 // Initialise the number of data in the Table
 N_data_in_table = 78748; 
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
void CCODEsFromSensorsGEOFOG3D::load_table(const char *filename)
{
 // Open the file with the data
 FILE *file_pt = fopen(filename, "r");
 if (file_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "The data file [" << filename << "] was not opened"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Resize the containers based on the Table size
 Table_time.resize(N_data_in_table);
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
   
   Table_time[i] = fixed_time + time * 1.0e-6;
   Table_acc[i].resize(3);
   Table_acc[i][0] = acc_x;
   Table_acc[i][1] = acc_y;
   Table_acc[i][2] = acc_z;
   Table_gyro[i].resize(3);
   Table_gyro[i][0] = gyro_x;
   Table_gyro[i][1] = gyro_y;
   Table_gyro[i][2] = gyro_z;
   
  }
 
 // Close the file
 fclose(file_pt);
 
}

// ======================================================================
/// Store the values of the sensors in arrays
// ======================================================================
bool CCODEsFromSensorsGEOFOG3D::get_sensors_lecture()
{
 // Read the data from file
 load_table("./GEOFOG3D/GEOFOG3D.dat");
 return true;
}

// ===================================================================
// Evaluates the system of odes at the given time "t" and the values
// of the function in "y". The evaluation produces results in the dy
// vector
// ===================================================================
void CCODEsFromSensorsGEOFOG3D::evaluate(const double t,
                                         const std::vector<double> &y,
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
// Evaluates the specified ode by "i" of the system of odes at the
// given time "t" and the values of the function in "y". The
// evaluation produces results in the dy vector at the dy[i] position
// ===================================================================
void CCODEsFromSensorsGEOFOG3D::evaluate(const unsigned i, const double t,
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

/** \file This file implements the CCODEsFromTableBasedOnAcceleration class
 */
#include "cc_odes_from_table_based_on_acceleration.h"

// ===================================================================
// Constructor, sets the number of odes. We currently have two odes,
// one for the velocity and the other for the acceleration
// ===================================================================
CCODEsFromTableBasedOnAcceleration::CCODEsFromTableBasedOnAcceleration()
 : CAODEs(10)
{
 // The values have not been loaded into a table 
 Loaded_table = false;
 // Initialise the number of data in the Table
 //N_data_in_table = 0;
 N_data_in_table = 78748;
 
 // Create the interpolator
 interpolator_pt = new CCNewtonInterpolator();
 
 // Read the data from file
 load_table("./data.dat");
 
}
// ===================================================================
// Empty destructor
// ===================================================================
CCODEsFromTableBasedOnAcceleration::~CCODEsFromTableBasedOnAcceleration()
{ 
 // Free memory for interpolator
 delete interpolator_pt;
 interpolator_pt = 0;
}

// ===================================================================
// Loads the data from an input file to generate a table from which
// the ode takes its values
// ===================================================================
void CCODEsFromTableBasedOnAcceleration::load_table(const char *filename)
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
 Table_vel_north.resize(N_data_in_table);
 Table_vel_east.resize(N_data_in_table);
 Table_vel_height.resize(N_data_in_table);
 Table_acc_x.resize(N_data_in_table);
 Table_acc_y.resize(N_data_in_table);
 Table_acc_z.resize(N_data_in_table);
 Table_gyro_x.resize(N_data_in_table);
 Table_gyro_y.resize(N_data_in_table);
 Table_gyro_z.resize(N_data_in_table);
 
 // Get rid of the first line where the headers are stored
 char *headers=NULL;
 size_t length = 0;
 getline(&headers, &length, file_pt);
 // Read the data
 for (unsigned i = 0; i < N_data_in_table; i++)
  {
   int index;
   double time;
   double latitude;
   double longitude;
   double height;
   double vel_north;
   double vel_east;
   double vel_down;
   double acc_x;
   double acc_y;
   double acc_z;
   double gyro_x;
   double gyro_y;
   double gyro_z;
   double magnet_x;
   double magnet_y;
   double magnet_z;
   int n_read = fscanf(file_pt, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
		       &index, &time, &latitude, &longitude, &height,
		       &vel_north, &vel_east, &vel_down,
		       &acc_x, &acc_y, &acc_z,
                       &gyro_x, &gyro_y, &gyro_z,
                       &magnet_x, &magnet_y, &magnet_z);
   if (n_read != 17)
    {
     // Error message
     std::ostringstream error_message;
     error_message << "Number of read values (" << n_read << ")" << std::endl;
     throw ChapchomLibError(error_message.str(),
			    CHAPCHOM_CURRENT_FUNCTION,
			    CHAPCHOM_EXCEPTION_LOCATION);
    }
   
   Table_time[i] = time;
   Table_vel_north[i] = vel_north;
   Table_vel_east[i] = vel_east;
   Table_vel_height[i] = vel_down;
   Table_acc_x[i] = acc_x;
   Table_acc_y[i] = acc_y;
   Table_acc_z[i] = acc_z;
   Table_gyro_x[i] = gyro_x;
   Table_gyro_y[i] = gyro_y;
   Table_gyro_z[i] = gyro_z;
  }
 

 // Close the file
 fclose(file_pt);
 
}

// ===================================================================
/// Get the values of the sensors at specific time (computed from table)
// ===================================================================
void CCODEsFromTableBasedOnAcceleration::get_sensors_lecture(const double t,
                                                             std::vector<double> &vel, 
                                                             std::vector<double> &acc,
                                                             std::vector<double> &gyro)
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
   std::vector<double> vel_x(interpolation_order + 1);
   std::vector<double> vel_y(interpolation_order + 1);
   std::vector<double> vel_z(interpolation_order + 1);
   std::vector<double> acc_x(interpolation_order + 1);
   std::vector<double> acc_y(interpolation_order + 1);
   std::vector<double> acc_z(interpolation_order + 1);
   std::vector<double> gyro_x(interpolation_order + 1);
   std::vector<double> gyro_y(interpolation_order + 1);
   std::vector<double> gyro_z(interpolation_order + 1);
   
   // Copy the data
   time[0] = Table_time[i_left];
   time[1] = Table_time[i_right];
   vel_x[0]= Table_vel_east[i_left];
   vel_x[1]= Table_vel_east[i_right];
   vel_y[0]= Table_vel_north[i_left];
   vel_y[1]= Table_vel_north[i_right];
   vel_z[0]= Table_vel_height[i_left];
   vel_z[1]= Table_vel_height[i_right];
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
   
   vel[0] = interpolator_pt->interpolate_1D(time, vel_x, t, interpolation_order);
   vel[1] = interpolator_pt->interpolate_1D(time, vel_y, t, interpolation_order);
   vel[2] = interpolator_pt->interpolate_1D(time, vel_z, t, interpolation_order);
   acc[0] = interpolator_pt->interpolate_1D(time, acc_x, t, interpolation_order);
   acc[1] = interpolator_pt->interpolate_1D(time, acc_y, t, interpolation_order);
   acc[2] = interpolator_pt->interpolate_1D(time, acc_z, t, interpolation_order);
   // Transform to radians because the lectures are given in degress
   gyro[0] = interpolator_pt->interpolate_1D(time, gyro_x, t, interpolation_order) * (M_PI / 180.0);
   gyro[1] = interpolator_pt->interpolate_1D(time, gyro_y, t, interpolation_order) * (M_PI / 180.0);
   gyro[2] = interpolator_pt->interpolate_1D(time, gyro_z, t, interpolation_order) * (M_PI / 180.0);
  }
 else // Do not do interpolation, the exact values are in the table
  {
   vel[0] = Table_vel_east[i_exact];
   vel[0] = Table_vel_north[i_exact];
   vel[0] = Table_vel_height[i_exact];
   acc[0] = Table_acc_x[i_exact];
   acc[0] = Table_acc_y[i_exact];
   acc[0] = Table_acc_z[i_exact];
   // Transform to radians because the lectures are given in degress
   gyro[0] = Table_gyro_x[i_exact] * (M_PI / 180.0);
   gyro[0] = Table_gyro_y[i_exact] * (M_PI / 180.0);
   gyro[0] = Table_gyro_z[i_exact] * (M_PI / 180.0);
  }
 
}

// ===================================================================
// Evaluates the system of odes at the given time "t" and the values
// of the function in "y". The evaluation produces results in the dy
// vector
// ===================================================================
void CCODEsFromTableBasedOnAcceleration::evaluate(const double t,
						  const std::vector<double> &y,
						  std::vector<double> &dy)
{
 const unsigned dim = 3;
 // Velocities
 std::vector<double> vel(dim);
 // Accelerations
 std::vector<double> acc(dim);
 // Angle rates (gyro data)
 std::vector<double> gyro(dim);
 // Retrieve data from table
 get_sensors_lecture(t, vel, acc, gyro);
 
 // -----------------
 // y[0] x-position
 // y[1] x-velocity
 // y[2] y-position
 // y[3] y-velocity
 // y[4] roll
 // y[5] pitch
 // y[6] yaw
 // -----------------   
 // dy[0] x-velocity
 // dy[1] x-acceleration
 // dy[2] y-velocity
 // dy[3] y-acceleration
 // dy[4] z-angle velocity (with respect to y)
 // dy[5] z-angle velocity (with respect to x)
 // dy[6] x-angle velocity (with respect to y)
 
 dy[0] = vel[0];
 dy[1] = acc[0];
 dy[2] = vel[1];
 dy[3] = acc[1];
 dy[4] = gyro[0];
 dy[5] = gyro[1];
 dy[6] = gyro[2];
 dy[7] = gyro[0];
 dy[8] = gyro[1];
 dy[9] = gyro[2];
 
}

// ===================================================================
// Evaluates the specified ode by "i" of the system of odes at the
// given time "t" and the values of the function in "y". The
// evaluation produces results in the dy vector at the dy[i] position
// ===================================================================
void CCODEsFromTableBasedOnAcceleration::evaluate(const unsigned i, const double t,
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

/** \file This file implements the CCODEsFromTableBasedOnVelocity class
 */

#include "cc_odes_from_table_based_on_velocity.h"

// ===================================================================
// Constructor, sets the number of odes. We currently have two odes,
// one for the velocity and the other for the acceleration
// ===================================================================
CCODEsFromTableBasedOnVelocity::CCODEsFromTableBasedOnVelocity()
 : CAODEs(2)
{
 // The values have not been loaded into a table 
 Loaded_table = false;
 // Initialise the number of data in the Table
 //N_data_in_table = 0;
 N_data_in_table = 78748;
 
 // Create the interpolator
 interpolator_pt = new CCNewtonInterpolator();
 
}

// ===================================================================
// Empty destructor
// ===================================================================
CCODEsFromTableBasedOnVelocity::~CCODEsFromTableBasedOnVelocity()
{ 
 // Free memory for interpolator
 delete interpolator_pt;
 interpolator_pt = 0;
}

// ===================================================================
// Loads the data from an input file to generate a table from which
// the ode takes its values
// ===================================================================
void CCODEsFromTableBasedOnVelocity::load_table(const char *filename)
{ 
 // Open the file with the data
 FILE *file_pt = fopen(filename, "r");
 if (file_pt == 0)
  {
   std::cout << "ERROR in CCODEsFromTableBasedOnVelocity::load_table() - The data file [" 
	     << filename << "] was not opened" << std::endl;
   throw(1);
   return;
  }
 
 // Resize the containers based on the Table size
 Table_time.resize(N_data_in_table);
 Table_vel_north.resize(N_data_in_table);
 Table_vel_east.resize(N_data_in_table);
 
 // Get rid of the first where the headers are stored
 char headers[200];
 fgets(headers, 200, file_pt);
 //std::cerr << headers;
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
   int n_read = fscanf(file_pt, "%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
		       &index, &time, &latitude, &longitude, &height,
		       &vel_north, &vel_east, &vel_down,
		       &acc_x, &acc_y, &acc_z);
   if (n_read != 11)
    {
     std::cout << "ERROR in CCODEsFromTableBasedOnVelocity::load_table() - Number of read values (" << n_read << ")" << std::endl;
     throw(1);
     return;
    }
   
   Table_time[i] = time;
   Table_vel_north[i] = vel_north;
   Table_vel_east[i] = vel_east;   
  }
 
 // Close the file
 fclose(file_pt);
 
}

// ===================================================================
// Evaluates the system of odes at the given time "t" and the values
// of the function in "y". The evaluation produces results in the dy
// vector
// ===================================================================
void CCODEsFromTableBasedOnVelocity::evaluate(const double t,
					      const std::vector<double> &y,
					      std::vector<double> &dy)
{
 // Do linear interpolation
 unsigned interpolation_order = 1;
 
 // Search for the greater value smaller than "t", and the smaller
 // value larger than "t" to use them for interpolation

#if 0
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
   
   // Compute the middle index in the current range
   const unsigned middle_index = std::floor((i_right - i_left)/ 2);
   if (Table_time[middle_index] < t)
    {
     i_left = middle_index;
    }
   else if (Table_time[middle_index] > t)
    {
     i_right = middle_index;
    }
   else if (Table_time[middle_index] == t)
    {
     // Found data
     loop = false;
     found_value = true;
     found_index = middle_index;
    }
   else
    {
     // Nothing happened ()
    }
   
  }
#endif // #if 0
 
 unsigned i = 0;
 bool loop = true;
 
 do
  {
   if (Table_time[i] < t && i < N_data_in_table)
    {
     i++;
    }
   else
    {
     loop = false;
    }
   
  }while(loop);

 if (i == N_data_in_table - 1)
  {
   std::cout << "ERROR in CCODEsFromTableBasedOnVelocity::evaluate - The requeste 't' value is out of the range of the current data" << std::endl;
   throw(1);
   return;
  }
 
 // Store the data used to interpolate in the correponding data structures
 std::vector<double> time(interpolation_order + 1);
 std::vector<double> vel_x(interpolation_order + 1);
 std::vector<double> vel_y(interpolation_order + 1);
 
 // Copy the data
 time[0] = Table_time[i];
 time[1] = Table_time[i+1];
 vel_x[0]= Table_vel_east[i];
 vel_x[1]= Table_vel_east[i+1];
 vel_y[0]= Table_vel_north[i];
 vel_y[1]= Table_vel_north[i+1];
 
 // y[0] represents the x-position
 dy[0] = interpolator_pt->interpolate_1D(time, vel_x, t, interpolation_order);
 // y[1] represents the y-position
 dy[1] = interpolator_pt->interpolate_1D(time, vel_y, t, interpolation_order);
}

// ===================================================================
// Evaluates the specified ode by "i" of the system of odes at the
// given time "t" and the values of the function in "y". The
// evaluation produces results in the dy vector at the dy[i] position
// ===================================================================
void CCODEsFromTableBasedOnVelocity::evaluate(const unsigned i, const double t,
					      const std::vector<double> &y,
					      std::vector<double> &dy)
{
 // TODO Julio: Implement a class to handle runtime errors and call
 // it here!!!
 std::cout << "ERROR in CCODEsFromTableBasedOnVelocity::evaluate() - This method is not implemented for this class" << std::endl;
 throw(1);
 return;
}

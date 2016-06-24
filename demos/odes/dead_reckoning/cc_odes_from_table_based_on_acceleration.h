#ifndef CCODESFROMTABLEBASEDONACCELERATION_H
#define CCODESFROMTABLEBASEDONACCELERATION_H

#include "../../../src/general/common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ca_odes.h"
#include "../../../src/interpolation/cc_newton_interpolator.h"

// Load data from FILE
#include <stdio.h>

/// \class CCOdesFromTableBasedOnVelocity cc_odes_from_table.h
    
/// This class implements a set of odes from a Table. It inherits the
/// interface to define ODEs from the CAODEs class
class CCODEsFromTableBasedOnAcceleration : public CAODEs
{
 
 public:

 /// Constructor, sets the number of odes
 CCODEsFromTableBasedOnAcceleration();
 
 /// Empty destructor
 virtual ~CCODEsFromTableBasedOnAcceleration();
 
 /// Loads the data from an input file to generate a table from which
 /// the ode takes its values
 void load_table(const char *filename);
 
 /// Get the values of the sensors at specific time (computed from table)
 void get_sensors_lecture(const double t,
                          double &vel_x, double &vel_y, double &vel_z,
                          double &acc_x, double &acc_y, double &acc_z,
                          double &gyro_x, double &gyro_y, double &gyro_z);
 
 /// Evaluates the system of odes at the given time "t" and the values
 /// of the function in "y". The evaluation produces results in the dy
 /// vector
 void evaluate(const double t,
	       const std::vector<double> &y, std::vector<double> &dy);
 
 /// Evaluates the specified ode by "i" of the system of odes at the
 /// given time "t" and the values of the function in "y". The
 /// evaluation produces results in the dy vector at the dy[i]
 /// position
 void evaluate(const unsigned i, const double t,
	       const std::vector<double> &y, std::vector<double> &dy);
 
 protected:
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCODEsFromTableBasedOnAcceleration(const CCODEsFromTableBasedOnAcceleration &copy)
  : CAODEs(copy)
  {
   BrokenCopy::broken_copy("CCODEsFromTableBasedOnAcceleration");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCODEsFromTableBasedOnAcceleration &copy)
  {
   BrokenCopy::broken_assign("CCODEsFromTableBasedOnAcceleration");
  }
 
 // Indicates whether the data have been loaded from the table or not
 bool Loaded_table;

 // Number of data in the loaded table
 unsigned N_data_in_table;
 
 // Storage for the loaded data
 std::vector<double> Table_time;
 std::vector<double> Table_vel_north;
 std::vector<double> Table_vel_east;
 std::vector<double> Table_vel_height;
 std::vector<double> Table_acc_x;
 std::vector<double> Table_acc_y;
 std::vector<double> Table_acc_z;
 std::vector<double> Table_gyro_x;
 std::vector<double> Table_gyro_y;
 std::vector<double> Table_gyro_z;
 
 // The interpolator
 CCNewtonInterpolator *interpolator_pt;
 
};

#endif // #ifndef CCODESFROMTABLEBASEDONACCELERATION_H

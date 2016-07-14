#ifndef CCODESFROMTABLEBASEDONVELOCITY_H
#define CCODESFROMTABLEBASEDONVELOCITY_H

#include "../../../src/general/common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ca_odes.h"
#include "../../../src/interpolation/cc_newton_interpolator.h"

// Load data from FILE
#include <stdio.h>

/// \class CCOdesFromTableBasedOnVelocity cc_odes_from_table_based_on_velocity.h
    
/// This class implements a set of odes from a Table. It inherits the
/// interface to define ODEs from the CAODEs class
class CCODEsFromTableBasedOnVelocity : public CAODEs
{
 
 public:

 /// Constructor, sets the number of odes
 CCODEsFromTableBasedOnVelocity();
 
 /// Empty destructor
 virtual ~CCODEsFromTableBasedOnVelocity();
 
 /// Loads the data from an input file to generate a table from which
 /// the ode takes its values
 void load_table(const char *filename);
 
 /// Get the values of the sensors at specific time (computed from table)
 void get_sensors_lecture(const double t, double &vel_x, double &vel_y);
 
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
 CCODEsFromTableBasedOnVelocity(const CCODEsFromTableBasedOnVelocity &copy)
  : CAODEs(copy)
  {
   BrokenCopy::broken_copy("CCODEsFromTableBasedOnVelocity");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCODEsFromTableBasedOnVelocity &copy)
 {
  BrokenCopy::broken_assign("CCODEsFromTableBasedOnVelocity");
 }
 
 // Indicates whether the data have been loaded from the table or not
 bool Loaded_table;

 // Number of data in the loaded table
 unsigned N_data_in_table;
 
 // Storage for the loaded data
 std::vector<double> Table_time;
 std::vector<double> Table_vel_north;
 std::vector<double> Table_vel_east;
 
 // The interpolator
 CCNewtonInterpolator *interpolator_pt;
 
};

#endif // #ifndef CCODESFROMTABLEBASEDONVELOCITY_H

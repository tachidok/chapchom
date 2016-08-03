#ifndef CCODESFROMTABLEFROMXSENSMT9B_H
#define CCODESFROMTABLEFROMXSENSMT9B_H

#include "../../../src/general/common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ca_odes.h"
#include "../../../src/interpolation/cc_newton_interpolator.h"

// Load data from FILE
#include <stdio.h>

/// \class CCOdesFromTableBasedOnVelocity cc_odes_from_table.h
    
/// This class implements a set of odes from a Table. It inherits the
/// interface to define ODEs from the CAODEs class
class CCODEsFromTableFromXSENSMT9B : public CAODEs
{
 
 public:

 /// Constructor, sets the number of odes
 CCODEsFromTableFromXSENSMT9B();
 
 /// Empty destructor
 virtual ~CCODEsFromTableFromXSENSMT9B();
 
 /// Loads the data from an input file to generate a table from which
 /// the ode takes its values
 void load_table(const char *euler_angles_filename, const char *raw_data_filename);
 
 /// Get the values of the sensors at specific time (computed from table)
 void get_sensors_lecture(const double t,
                          std::vector<double> &acc,
                          std::vector<double> &gyro,
                          std::vector<double> &euler_angles);
 
 /// Fills the matrix that performs the transformation from angular
 /// velocities to Euler-rates
 void fill_angular_velocities_to_euler_rates_matrix(std::vector<std::vector<double> > &A,
                                                    std::vector<double> &euler_angles);
 
 /// Multiplies a matrix times a vector
 void multiply_matrix_times_vector(std::vector<std::vector<double> > &A,
                                   std::vector<double> &b,
                                   std::vector<double> &x);
 
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
 CCODEsFromTableFromXSENSMT9B(const CCODEsFromTableFromXSENSMT9B &copy)
  : CAODEs(copy), DIM(0)
  {
   BrokenCopy::broken_copy("CCODEsFromTableFromXSENSMT9B");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCODEsFromTableFromXSENSMT9B &copy)
  {
   BrokenCopy::broken_assign("CCODEsFromTableFromXSENSMT9B");
  }
 
 // The dimension of the problem
 const unsigned DIM;
 
 // Indicates whether the data have been loaded from the table or not
 bool Loaded_table;
 
 // Number of data in the loaded table
 unsigned N_data_in_table;
 
 // Storage for the loaded data
 std::vector<double> Table_time;
 std::vector<double> Table_acc_x;
 std::vector<double> Table_acc_y;
 std::vector<double> Table_acc_z;
 std::vector<double> Table_gyro_x;
 std::vector<double> Table_gyro_y;
 std::vector<double> Table_gyro_z;
 std::vector<double> Table_roll;
 std::vector<double> Table_pitch;
 std::vector<double> Table_yaw;
 
 // The interpolator
 CCNewtonInterpolator *interpolator_pt;
 
 // A transformation matrix from angular velocities to Euler rates
 std::vector<std::vector<double> > A;
  
};

#endif // #ifndef CCODESFROMTABLEFROMXSENSMT9B_H

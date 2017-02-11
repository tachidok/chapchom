#ifndef CCODESFROMSENSORSGEOFOG3D_H
#define CCODESFROMSENSORSGEOFOG3D_H

#include "../../../src/general/common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ac_odes.h"
#include "../../../src/interpolation/cc_newton_interpolator.h"

// Load data from FILE
#include <stdio.h>

/// \class CCODEsFromSensorsGEOFOG3D cc_odes_from_sensors_GEOFOG3D.h
    
/// This class implements a set of odes from a Table. It inherits the
/// interface to define ODEs from the ACODEs class
class CCODEsFromSensorsGEOFOG3D : public virtual ACODEs
{
 
 public:

 /// Constructor, sets the number of odes
 CCODEsFromSensorsGEOFOG3D();
 
 /// Empty destructor
 virtual ~CCODEsFromSensorsGEOFOG3D();
 
 /// Loads the data from an input file to generate a table from which
 /// the ode takes its values
 void load_table(const char *filename);
 
 /// Get the values of the sensors
 bool get_sensors_lecture();
 
 // Get the number of acceleration data
 inline const unsigned nacceleration_data()
 {return Table_acc.size();}
 
 // Get acceleration data
 inline std::vector<double> &get_accelerations(const unsigned i)
 {return Table_acc[i];}
 
 // Get acceleration data
 inline std::vector<std::vector<double> > &get_accelerations()
 {return Table_acc;}
 
 // Get the number of gyro data
 inline const unsigned ngyro_data() {return Table_gyro.size();}
 
 // Get gyro's data
 inline std::vector<double> &get_angular_velocities(const unsigned i)
 {return Table_gyro[i];}
 
 // Get gyro's data
 inline std::vector<std::vector<double> > &get_angular_velocities()
 {return Table_gyro;}
 
 /// Set linear acceleration for current time
 inline double *&linear_acceleration() {return Linear_acceleration;}
 
 /// Set Euler angles rates for current time
 inline double *&euler_angles_rates() {return Euler_angles_rates;}
 
 // Set the rate of change of yaw at the current time obtained after
 // applying a threshold to the gyro-z lecture
 inline double &yaw_change_rate_with_threshold()
 {return Yaw_change_rate_with_threshold;}
 
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
 CCODEsFromSensorsGEOFOG3D(const CCODEsFromSensorsGEOFOG3D &copy)
  : ACODEs(copy), DIM(0)
  {
   BrokenCopy::broken_copy("CCODEsFromSensorsGEOFOG3D");
  }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCODEsFromSensorsGEOFOG3D &copy)
  {
   BrokenCopy::broken_assign("CCODEsFromSensorsGEOFOG3D");
  }
 
 // Number of data in the loaded table
 unsigned N_data_in_table;
 
 // Stores linear acceleration (to integrate)
 double *Linear_acceleration;
 
 // Stores Euler angles rates (to integrate)
 double *Euler_angles_rates;
 
 // Stores the rate of change of yaw obtained after applying a
 // threshold to the gyro-z lecture
 double Yaw_change_rate_with_threshold;
 
 // Storage for the loaded data
 std::vector<double> Table_time;
 std::vector<std::vector<double> > Table_acc;
 std::vector<std::vector<double> > Table_gyro;
 
};

#endif // #ifndef CCODESFROMSENSORSGEOFOG3D_H

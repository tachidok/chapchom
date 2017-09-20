#ifndef CCODESFROMSENSORSMOREDATA_H
#define CCODESFROMSENSORSMOREDATA_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ac_odes.h"

#define DIM 3

#define FEETS_TO_METERS 0.3048

namespace chapchom
{

 /// \class CCODEsFromSensorsMoreData cc_odes_from_sensors_GEOFOG3D.h
    
 /// This class implements a set of odes from a Table. It inherits the
 /// interface to define ODEs from the ACODEs class
 class CCODEsFromSensorsMoreData : public virtual ACODEs
 {
 
 public:

  /// Constructor, sets the number of odes and the indices to read the
  /// data from the input file
  CCODEsFromSensorsMoreData(const char *input_filename,
                            const unsigned initial_index,
                            const unsigned final_index);
  
  /// Empty destructor
  virtual ~CCODEsFromSensorsMoreData();
  
  /// Loads the data from an input file to generate a table from which
  /// the ode takes its values
  void load_table(const char *input_filename);
  
  /// Get the values of the sensors
  bool get_sensors_lectures();
  
  /// Set initial conditions
  void set_initial_conditions(std::vector<std::vector<double> > &y);
  
  /// Reset initial contidions
  void reset_initial_conditions_at_current_time(std::vector<std::vector<double> > &y);
  
  // Get the number of acceleration data
  inline const unsigned nacceleration_data()
  {return Current_acc_from_table.size();}
 
  // Get acceleration data
  inline std::vector<double> &get_accelerations(const unsigned i)
  {return Current_acc_from_table[i];}
 
  // Get acceleration data
  inline std::vector<std::vector<double> > &get_accelerations()
  {return Current_acc_from_table;}
 
  // Get the number of gyro data
  inline const unsigned ngyro_data() {return Current_gyro_from_table.size();}
 
  // Get gyro's data
  inline std::vector<double> &get_angular_velocities(const unsigned i)
  {return Current_gyro_from_table[i];}
 
  // Get gyro's data
  inline std::vector<std::vector<double> > &get_angular_velocities()
  {return Current_gyro_from_table;}
  
  // Euler angles from Table
  inline std::vector<std::vector<double> > &get_Euler_angles_from_table()
  {return Current_Euler_angles_from_table;}
  
  // Velocity from Table
  inline std::vector<std::vector<double> > &get_velocity_from_table()
  {return Current_velocity_from_table;}
  
  // Velocity from Table
  inline std::vector<std::vector<double> > &get_body_velocity_from_table()
  {return Current_body_velocity_from_table;}
  
  // Inertial velocity from Table
  inline std::vector<std::vector<double> > &get_inertial_velocity_from_table()
  {return Current_inertial_velocity_from_table;}
  
  // Latitude-longitude from Table
  inline std::vector<std::vector<double> > &get_latitude_longitude_from_table()
  {return Current_latitude_longitude_from_table;}
  
  /// Set linear acceleration for current time
  inline double *&linear_acceleration() {return Linear_acceleration;}
  
  /// Set Euler angles rates for current time
  inline double *&euler_angles_rates() {return Euler_angles_rates;}
 
  // Set the rate of change of yaw at the current time obtained after
  // applying a threshold to the gyro-z lecture
  inline double &yaw_change_rate_with_threshold()
  {return Yaw_change_rate_with_threshold;}
  
  /// Evaluates the system of odes at time "t". The values of the i-th
  /// function at previous times are accessible via y[i][1], y[i][2]
  /// and so on. The evaluation produces results in the vector dy.
  void evaluate(const double t,
                const std::vector<std::vector<double> > &y,
                std::vector<double> &dy);

  /// Evaluates the i-th ode at time "t". The values of the function
  /// at previous times are stores at y[1], y[2] and so on. The
  /// evaluation stores the result in dy.
  void evaluate(const unsigned i, const double t,
                const std::vector<double> &y, double &dy);
  
 protected:
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCODEsFromSensorsMoreData(const CCODEsFromSensorsMoreData &copy)
  : ACODEs(copy)
   {
    BrokenCopy::broken_copy("CCODEsFromSensorsMoreData");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCODEsFromSensorsMoreData &copy)
   {
    BrokenCopy::broken_assign("CCODEsFromSensorsMoreData");
   }
 
  // Number of data in the loaded table
  unsigned long N_data_in_table;

  // Indicates whether data have been load from table or not
  bool Loaded_data_from_table;
  
  // The initial index to read from data
  unsigned Initial_index;
  // The final index to read from data
  unsigned Final_index;
  
  // Stores linear acceleration (to integrate)
  double *Linear_acceleration;
  
  // Stores Euler angles rates (to integrate)
  double *Euler_angles_rates;
  
  // Stores the rate of change of yaw obtained after applying a
  // threshold to the gyro-z lecture
  double Yaw_change_rate_with_threshold;
  
  unsigned long Index_data;
  
  // Storage for the complete loaded data
  std::vector<std::vector<double> > Table_acc;
  std::vector<std::vector<double> > Table_gyro; 
  
  // Table_Euler_angles[1] - Roll, Table_Euler_angles[2] - Pitch, Table_Euler_angles[3] - Yaw
  std::vector<std::vector<double> > Table_Euler_angles;
    
  // Table_velocity[1] - North, Table_velocity[2] - East, Table_velocity[3] - Down
  std::vector<std::vector<double> > Table_velocity;
  
  // Table_body_velocity[1] - vel_x, Table_body_velocity[2] - vel_y, Table_body_velocity[3] - vel_z
  std::vector<std::vector<double> > Table_body_velocity;
  
  // Table_inertial_velocity[1] - Total velocity,
  // Table_inertial_velocity[2] - Inertial velocity
  std::vector<std::vector<double> > Table_inertial_velocity;
  
  // Table_lat_lon[1] - Latitude, Table_lat_lon[2] - Longitude
  std::vector<std::vector<double> > Table_latitude_longitude;
  
  // Used to store the data correspoding to the current second
  std::vector<std::vector<double> > Current_acc_from_table;
  std::vector<std::vector<double> > Current_gyro_from_table;
  
  std::vector<std::vector<double> > Current_Euler_angles_from_table;
  std::vector<std::vector<double> > Current_velocity_from_table;
  std::vector<std::vector<double> > Current_body_velocity_from_table;
  std::vector<std::vector<double> > Current_inertial_velocity_from_table;
  std::vector<std::vector<double> > Current_latitude_longitude_from_table;
  
 };
 
}

#endif // #ifndef CCODESFROMSENSORSGEOFOG3D_H

#ifndef CCODESFROMSENSORSUBLOX_H
#define CCODESFROMSENSORSUBLOX_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ac_odes.h"

// The UBLOX decoder
#include "cc_ublox_decoder.h"
// The nmea decoder
#include "cc_nmea_decoder.h"

#define NFIELDS_NMEA_DECODER 50

#define DIM 3

//#define TONANTZINTLA_TO_CHOLULA
//#define TLAXCALANCINGO_TO_ACATEPEC_ZERO_INITIAL_VELOCITY
//#define TLAXCALANCINGO_TO_ACATEPEC
//#define ACATEPEC_TO_TONANTZINTLA
//#define UDLAP_PERIFERICO
//#define PERIFERICO_TO_11SUR
#define _11SUR_TO_TLAXCALANCINGO

namespace chapchom
{

 /// \class CCODEsFromSensorsUBLOX cc_odes_from_sensors_UBLOX.h
    
 /// This class implements a set of odes from a Table. It inherits the
 /// interface to define ODEs from the ACODEs class
 class CCODEsFromSensorsUBLOX : public virtual ACODEs
 {
 
 public:
  
  /// Constructor, sets the number of odes and the indices to read the
  /// data from the input file
  CCODEsFromSensorsUBLOX(const char *input_filename);
  
  /// Empty destructor
  virtual ~CCODEsFromSensorsUBLOX();
  
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
 CCODEsFromSensorsUBLOX(const CCODEsFromSensorsUBLOX &copy)
  : ACODEs(copy)
   {
    BrokenCopy::broken_copy("CCODEsFromSensorsUBLOX");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCODEsFromSensorsUBLOX &copy)
   {
    BrokenCopy::broken_assign("CCODEsFromSensorsUBLOX");
   }
 
  // Number of data in the loaded table
  unsigned long N_data_in_table;
  
  // Indicates whether data have been load from table or not
  bool Loaded_data_from_table;
  
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
  
  // Table_latitude_longitude_course_valid[1] - Latitude,
  // Table_latitude_longitude_course_valid[2] - Longitude,
  // Table_latitude_longitude_course_valid[3] - Course,
  // Table_latitude_longitude_course_valid[4] - valid
  std::vector<std::vector<double> > Table_latitude_longitude_course_valid;
  
  // Used to store the data correspoding to the current second
  std::vector<std::vector<double> > Current_acc_from_table;
  std::vector<std::vector<double> > Current_gyro_from_table; 
  std::vector<std::vector<double> > Current_latitude_longitude_from_table;
  
 };
 

}

#endif // #ifndef CCODESFROMSENSORSUBLOX_H

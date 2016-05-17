/** \file A class implementing a set of ODEs from Tables
 */

// Check whether the class has been already defined
#ifndef CCODESFROMTABLE_H
#define CCODESFROMTABLE_H

#include "../../../src/general/h_common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ca_odes.h"
#include "../../../src/interpolators/cc_newton_interpolator.h"

// Load data from FILE
#include <stdio.h>

/** \class CCOdesFromTable cc_odes_from_table.h
    
    \brief This class implements a set of odes from a Table. It
    inherits the interface to define ODEs from the CAODEs class
 */
class CCODEsFromTable : public CAODEs
{
 
 public:

 /** 
     \brief Constructor, sets the number of odes
 */
 CCODEsFromTable();
 
 /** Empty destructor
  */
 virtual ~CCODEsFromTable();
 
 /** 
     \brief Loads the data from an input file to generate a table from
     which the ode takes its values
  */
 void load_table(const char *filename);
 
 /** \brief Evaluates the system of odes at the given time "t" and the
     values of the function in "y". The evaluation produces results in
     the dy vector
 */
 void evaluate(const double t,
	       const std::vector<double> &y, std::vector<double> &dy);
 
 /** \brief Evaluates the specified ode by "i" of the system of odes
     at the given time "t" and the values of the function in "y". The
     evaluation produces results in the dy vector at the dy[i]
     position
 */
 void evaluate(const unsigned i, const double t,
	       const std::vector<double> &y, std::vector<double> &dy);
 
 protected:
 
 /** \brief Copy constructor (we do not want this class to be
     copiable). Check
     http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCODEsFromTable(const CCODEsFromTable &copy);

 /** \brief Assignment operator (we do not want this class to be
  copiable. Check
  http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CCODEsFromTable& operator=(const CCODEsFromTable &copy);
 
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

#endif // #ifndef CCODESFROMTABLE_H

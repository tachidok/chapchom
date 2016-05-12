/** \file A class implementing a set of ODEs from Tables
 */

// Check whether the class has been already defined
#ifndef CCODESFROMTABLE_H
#define CCODESFROMTABLE_H

#include "../../../src/general/h_common_includes.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ca_odes.h"

/** \class CCOdesFromTable cc_odes_from_table.h
    
    \brief This class implements a set of odes from a Table. It
    inherints the interface to define ODEs from the CAODEs class
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
 
};

#endif // #ifndef CCODESFROMTABLE_H

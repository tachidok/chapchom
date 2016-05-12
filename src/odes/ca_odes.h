/** \file The definition of the interfaces to handle a system of ODEs
 */

// Check whether the class has been already defined
#ifndef CAODES_H
#define CAODES_H

#include "../general/h_common_includes.h"

/** \class CAODEs ca_odes.h
    
    \brief This class implements the interface to the odes to be
    solved by the integration methods
 */
class CAODEs
{

 public:
 
 /** 
     \brief Constructor, sets the number of odes
 */
 CAODEs(const unsigned n_odes);
 
 /** Empty destructor
  */
 virtual ~CAODEs();
 
 /** \brief Gets the number of odes
  */
 unsigned nodes() const
 {return N_odes;}
 
 /** \brief Gets the vector storing the number of calls to the odes
  */
 const std::vector<unsigned> &ncallsodes()
 {return N_calls_ode;}
 
 /** \brief Gets the number of calls to an specific ode
  */
 unsigned ncallsode(const unsigned i) const
 {return N_calls_ode[i];}
 
 /** \brief Evaluates the system of odes at the given time "t" and the
     values of the function in "y". The evaluation produces results in
     the dy vector
 */
 virtual void evaluate(const double t,
		       const std::vector<double> &y,
		       std::vector<double> &dy) = 0;
 
 /** \brief Evaluates the specified ode by "i" of the system of odes
     at the given time "t" and the values of the function in "y". The
     evaluation produces results in the dy vector at the dy[i]
     position
 */
 virtual void evaluate(const unsigned i, const double t,
		       const std::vector<double> &y,
		       std::vector<double> &dy) = 0;
 
 protected:
 
 /** \brief Copy constructor (we do not want this class to be
     copiable). Check
     http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CAODEs(const CAODEs &copy);

 /** \brief Assignment operator (we do not want this class to be
  copiable. Check
  http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 */
 CAODEs& operator=(const CAODEs &copy);

 // The number of odes
 unsigned N_odes;
 
 // The number of calls for each ode
 std::vector<unsigned> N_calls_ode;
 
};

#endif // #ifndef CAODES_H

#ifndef ACODES_H
#define ACODES_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{

 /// @class ACODEs ac_odes.h
    
 /// This class implements the interface to the odes to be solved by
 /// the integration methods
 class ACODEs
 {

 public:
 
  /// Constructor, sets the number of odes
  ACODEs(const unsigned n_odes);
 
  /// Empty destructor
  virtual ~ACODEs();
 
  /// Gets the number of odes
  unsigned nodes() const
  {return N_odes;}
 
  /// Gets the vector storing the number of calls to the odes
  const std::vector<unsigned> &ncallsodes()
  {return N_calls_ode;}
 
  /// Gets the number of calls to an specific ode
  unsigned ncallsode(const unsigned i) const
  {return N_calls_ode[i];}
 
  /// Evaluates the system of odes at the time given by "t" and the
  /// values of the function in "y". The evaluation produces results in
  /// the dy vector
  virtual void evaluate(const double t,
                        const std::vector<double> &y,
                        std::vector<double> &dy) = 0;
 
  /// Evaluates the specified ode by "i" of the system of odes at the
  /// given time "t" and the values of the function in "y". The
  /// evaluation produces results in the dy vector at the dy[i]
  /// position
  virtual void evaluate(const unsigned i, const double t,
                        const std::vector<double> &y,
                        std::vector<double> &dy) = 0;
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACODEs(const ACODEs &copy)
   {
    BrokenCopy::broken_copy("ACODEs");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACODEs &copy)
   {
    BrokenCopy::broken_assign("ACODEs");
   }

  /// The number of odes
  unsigned N_odes;
 
  /// The number of calls for each ode
  std::vector<unsigned> N_calls_ode;
 
 };

}
 
#endif // #ifndef ACODES_H

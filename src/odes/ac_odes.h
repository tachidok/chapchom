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
  const std::vector<unsigned> &ncalls_odes()
  {return N_calls_ode;}
  
  /// Gets the number of calls to an specific ode
  unsigned ncalls_ode(const unsigned i) const
  {return N_calls_ode[i];}
    
  /// Evaluates the system of odes at time "t". The values of the i-th
  /// function at previous times are accessible via y[i][t+1],
  /// y[i][t+2] and so on. The evaluation produces results in the
  /// vector dy.
  virtual void evaluate(const double t,
                        const std::vector<std::vector<double> > &y,
                        std::vector<double> &dy) = 0;
  
  /// Evaluates the i-th ode at time "t". The values of the function
  /// at previous times are stores at y[t+1], y[t+2] and so on. The
  /// evaluation stores the result in dy.
  virtual void evaluate(const unsigned i, const double t,
                        const std::vector<double> &y, double &dy) = 0;
  
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

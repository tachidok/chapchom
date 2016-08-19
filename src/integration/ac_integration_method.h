#ifndef ACINTEGRATIONMETHOD_H
#define ACINTEGRATIONMETHOD_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../odes/ac_odes.h"

/// @class ACIntegrationMethod ac_integration_method.h

/// This class implements the interfaces for integration methods to
/// solve ODE's
class ACIntegrationMethod
{
 
 public:
 
 /// Empty constructor
 ACIntegrationMethod();
 
 /// Empty destructor
 virtual ~ACIntegrationMethod();
 
 /// Applies the explicit method to the given odes from time
 /// "t_initial" to time "t_final" using a step given by "h". The
 /// output is stored in the vector "y" for each ode and each
 /// integration step. Warning: this may require a lot of memory if
 /// the number of h-steps is "large". If you want to keep track of
 /// "y" by yourself call the "integrate_step" method instead
 virtual void integrate(ACODEs &odes, const double h,
			const double t_initial, const double t_final,
			std::vector<std::vector<double> > &y) = 0;
 
 /// Applies the explicit method to the given odes from the current
 /// time "t" to the time "t+h".
 virtual void integrate_step(ACODEs &odes, const double h,
			     const double t,
			     std::vector<std::vector<double> >&y) = 0;
 
 /// Get the associated number of history values (each method is in
 /// charge of setting this value based on the number of history
 /// values it requires)
 unsigned n_history_values()
 {return N_history_values;}
 
 protected:
 
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 ACIntegrationMethod(const ACIntegrationMethod &copy)
  {
   BrokenCopy::broken_copy("ACIntegrationMethod");
  }

 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const ACIntegrationMethod &copy)
  {
   BrokenCopy::broken_assign("ACIntegrationMethod");
  }
 
 /// The number of history values
 unsigned N_history_values;
 
};

#endif // #ifndef ACEXPLICITINTEGRATIONMETHOD_H

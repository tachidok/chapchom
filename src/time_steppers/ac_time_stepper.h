#ifndef ACTIMESTEPPER_H
#define ACTIMESTEPPER_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

namespace chapchom
{

 /// @class ACTimeStepper ac_time_stepper.h

 /// This class implements the interfaces for integration methods to
 /// solve ODE's
 class ACTimeStepper
 {
 
 public:
 
  /// Empty constructor
  ACTimeStepper();
 
  /// Empty destructor
  virtual ~ACTimeStepper();
  
  /// Performs a time step applying a time integration method to the
  /// given odes from the current time "t" to the time "t+h".
  virtual void time_step(ACODEs &odes, const Real h,
                         const Real t,
                         CCData<Real> &u) = 0;
  
  /// Get the associated number of history values (each method is in
  /// charge of setting this value based on the number of history
  /// values it requires)
  unsigned n_history_values()
  {return N_history_values;}
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACTimeStepper(const ACTimeStepper &copy)
   {
    BrokenCopy::broken_copy("ACTimeStepper");
   }

  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACTimeStepper &copy)
   {
    BrokenCopy::broken_assign("ACTimeStepper");
   }
 
  /// The number of history values
  unsigned N_history_values;
 
 };

}
 
#endif // #ifndef ACTIMESTEPPER_H

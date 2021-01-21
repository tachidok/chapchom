#include "ac_ivp_for_odes.h"

namespace chapchom
{
 
 // ===================================================================
 /// Constructor, sets the ODEs and the time stepper
 // ===================================================================
 ACIVPForODEs::ACIVPForODEs(ACODEs *odes_pt,
                            ACTimeStepper *time_stepper_pt)
  : ACProblem(),
    ODEs_pt(odes_pt)
 {
  // Get the number of odes
  const unsigned n_odes = odes_pt->n_odes();
  const unsigned n_history_values = time_stepper_pt->n_history_values();
  U_pt = new CCData(n_odes, n_history_values);
  // Add the time stepper to the vector of time steppers
  add_time_stepper(time_stepper_pt);
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 ACIVPForODEs::~ACIVPForODEs()
 {
  // Free memory
  delete U_pt;
  // Set pointer to null
  U_pt = 0;
 }

 // ===================================================================
 /// We perform an unsteady solve by default, if you require a
 /// different solving strategy then override this method
 // ===================================================================
 void ACIVPForODEs::solve()
 {
  // Solve the ODEs
  unsteady_solve();
 }
 
 // ===================================================================
 /// Problem unsteady solve
 // ===================================================================
 void ACIVPForODEs::unsteady_solve()
 {
  // Call actions before time stepping
  actions_before_time_stepping();
  
  // Get the number of time steppers
  const unsigned n_time_steppers = this->n_time_steppers();
  
  // If there are more than one time stepper then throw an error since
  // this feature has not been tested and it possibly wont work at
  // all, please carefully implement any necessary changes
  if (n_time_steppers > 1)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "This feature has not been fully tested\n"
                  << "Please create a demo driver that uses more than one\n"
                  << "time stepper and implement the necessary changes to\n"
                  << "the code.\n"
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // Loop over all the time steppers
  for (unsigned i = 0; i < n_time_steppers; i++)
   {
    const Real t = time(i);
    const Real h = time_step(i);
    
    // Time step (apply the Time stepper to time integrate the ODEs)
    time_stepper_pt(i)->time_step((*ODEs_pt), h, t, (*U_pt));  
   }
  
  // Call actions after time stepping
  actions_after_time_stepping();
  
 }
 
}

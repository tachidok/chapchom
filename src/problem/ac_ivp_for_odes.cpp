#include "ac_ivp_for_odes.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor, in charge of initialising any stuff required for the
 // framework
 // ===================================================================
 ACIVPForODEs::ACIVPForODEs(ACODEs *odes_pt,
                            ACTimeStepper *time_stepper_pt)
  : ACProblem(),
    ODEs_pt(odes_pt), Time_stepper_pt(time_stepper_pt)
 {
  // Get the number of odes
  const unsigned n_odes = odes_pt->n_odes();
  const unsigned n_history_values = time_stepper_pt->n_history_values();
  U_pt = new CCData<Real>(n_odes, n_history_values);
  
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
 // Problem unsteady solve
 // ===================================================================
 void ACIVPForODEs::unsteady_solve()
 {
  // Call actions before time stepping
  actions_before_time_stepping();
  
  // Time step (apply the Time stepper to time integrate the ODEs)
  Time_stepper_pt->time_step((*ODEs_pt), Time_step, Time, (*U_pt));
  
  // Call actions after time stepping
  actions_after_time_stepping();
  
 }
 
}


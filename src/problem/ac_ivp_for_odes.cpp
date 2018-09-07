#include "ac_ivp_for_odes.h"

namespace chapchom
{

 // ===================================================================
 // Constructor, in charge of initialising any stuff required for the
 // framework
 // ===================================================================
 ACIVPForODEs::ACIVPForODEs(ACODEs *odes_pt,
                            ACTimeStepper *time_stepper_pt,
                            CCData<double> *u_pt)
  : ACProblem(),
    ODEs_pt(odes_pt), Time_stepper_pt(time_stepper_pt), U_pt(u_pt)
 { 
  
 }
 
 // ===================================================================
 // Problem unsteady solve
 // ===================================================================
 void ACIVPForODEs::unsteady_solve(bool shift_history_values)
 {
  // Call actions before time stepping
  actions_before_time_stepping();
  
  // Time step (apply the Time stepper to time integrate the ODEs)
  Time_stepper_pt->time_step((*ODEs_pt), Time_step, Time, (*U_pt));
  
  // Call actions after time stepping
  actions_after_time_stepping();

  if (shift_history_values)
   {
    // Update data (shift history values, one position only)
    U_pt->shift_history_values();
   }
  
 }
 
#if 0
 // ===================================================================
 // Problem unsteady solve
 // ===================================================================
 void ACIVPForODEs::unsteady_solve()
 {
  // Compute the time step size
  const double time_step_size = (Final_time - Initial_time) / N_time_steps;
  double current_time = Initial_time;
  
  // Set initial conditions
  set_initial_conditions();
  
  // Output the initial data to screen
  std::cout.precision(8);
  std::cout << "t: " << current_time
            << "\t" << u(0) << "\t" << u(6) << "\t" << u(12) << "\t" << u(18) << std::endl;
  
  // ----------------------------------------------------------------
  // Integrator initialisation [END]
  // ----------------------------------------------------------------
  
  unsigned output_file_index = 0;
  // Initial output
  std::ostringstream output_filename;
  output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << output_file_index++;
  output_particles(0.0, u, output_filename);
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (continue until reaching the final time)
  while(LOOP)
   {
    // Call actions before time stepping
    actions_before_time_stepping();
    
    // Time step (apply the Time stepper to time integrate the ODEs)
    Time_stepper.time_step(ODEs, time_step_size, current_time, U);
    
    // Call actions after time stepping
    actions_after_time_stepping();
    
    // Update data (shift history values, one position only)
    U.shift_history_values();
    
    // Update time
    current_time+=time_step_size;
    
    // Check whether we have reached the final time
    if (current_time >= Final_time)
     {
      LOOP = false;
     }
    
    // Output
    std::cout.precision(8);
    std::cout << "t: " << current_time
              << "\t" << u(0) << "\t" << u(6) << "\t" << u(12) << "\t" << u(18) << std::endl;
   
    // Output to file
    std::ostringstream output_filename;
    output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << output_file_index++;
    output_particles(current_time, u, output_filename);
   
   } // while(LOOP)
 
  std::cout << "[FINISHING UP] ... " << std::endl;
  
 }
#endif // #if 0
 
}


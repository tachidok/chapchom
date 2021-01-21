// Include the initialisation rutines headers
#include "initialise.h"

namespace chapchom
{
 /// Keep track of the total time spent in a program, since
 /// initilaisation up-to termination
 namespace Global_timings
 {
  // Initial time
  time_t Global_initial_wall_time=0;
  // Initial CPU clock time
  clock_t Global_initial_cpu_clock_time=0;
 }

 /// In charge of initialising time variables to keep track of execution time
 bool initialise_chapchom()
 {
  chapchom_output << "Initialising chapchom .." << std::endl;
  // These variables are defined in the header file
  // cmake_definitions.h, which is automatically generated from the
  // cmake_definitions.h.in file
  chapchom_output << "This is chapchom version "
                  << MAJOR_VERSION
                  << "."
                  << MINOR_VERSION
                  << "."
                  << PATCH_LEVEL
                  << std::endl;
  
  /// Setup terminate helper
  TerminateHelper::setup();
  
  // Initialise global wall time
  Global_timings::Global_initial_wall_time=Timing::wall_time();
  // Initialise CPU clock time
  Global_timings::Global_initial_cpu_clock_time=Timing::cpu_clock_time();
  
  chapchom_output << "[DONE]: SciCellxx initialisation" << std::endl;
  // Everything was alright
  return true;
  
 }
 
 /// In charge of finalising and reporting execution times
 bool finalise_chapchom()
 {
  chapchom_output << "Finalising chapchom ..." << std::endl;
  
  // Get the wall and cpu execution time of the program
  time_t final_wall_time = Timing::wall_time();
  clock_t final_cpu_clock_time = Timing::cpu_clock_time();
  double total_wall_time =
   Timing::diff_wall_time(Global_timings::Global_initial_wall_time,
                          final_wall_time);
  double total_cpu_clock_time =
   Timing::diff_cpu_clock_time(Global_timings::Global_initial_cpu_clock_time,
                               final_cpu_clock_time);
  
  chapchom_output << "Total wall time: " << total_wall_time << std::endl;
  chapchom_output << "Total cpu clock time: " << total_cpu_clock_time << std::endl; 
  
  chapchom_output << "[DONE]: SciCellxx termination" << std::endl;
  // Everything was alright
  return true;
 }
 
}

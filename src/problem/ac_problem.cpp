#include "ac_problem.h"

namespace chapchom
{

 // ===================================================================
 /// Constructor, in charge of initialising any stuff required for the
 /// framework
 // ===================================================================
 ACProblem::ACProblem()
  : Time(0.0), Time_step(0.0), Output_file_index(0)
 { 
  initialise_problem();
  
  // Create an empty time steppers vector
  Time_stepper_pt.clear();
  // Create an empty time vector
  Time.clear();
  // Create and empty time step vector
  Time_step.clear();
  
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 ACProblem::~ACProblem()
 {
  finalise_problem();
 }
 
 // ===================================================================
 /// Initialise problem (sets framework ready to work)
 // ===================================================================
 void ACProblem::initialise_problem()
 {
  // Initialise chapchom
  initialise_chapchom();
 }

 // =================================================================== 
 /// Finalise problem (performs operations to free resources)
 // ===================================================================
 void ACProblem::finalise_problem()
 {
  // Finalise chapcom
  finalise_chapchom();
 }

 // ===================================================================
 /// Write access to the current time
 // ===================================================================
 Real &ACProblem::time(const unsigned i)
 {
#ifdef CHAPCHOM_PANIC_MODE
  // Get the size of the time container
  const unsigned n_time = Time.size();
  if (i >= n_time)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to access to a time that is not\n"
                  << "available at the time container\n"
                  << "Maximum index of the time container: ["<<n_time<<"]\n"
                  << "The index on the container you want to access: ["<<i<<"]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Time[i];
 }
 
 // ===================================================================
 /// Read-only access to the current time
 // ===================================================================
 Real ACProblem::time(const unsigned i) const
 {
#ifdef CHAPCHOM_PANIC_MODE
  // Get the size of the time container
  const unsigned n_time = Time.size();
  if (i >= n_time)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to access to a time that is not\n"
                  << "available at the time container\n"
                  << "Maximum index of the time container: ["<<n_time<<"]\n"
                  << "The index on the container you want to access: ["<<i<<"]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Time[i];
 }
 
 // ===================================================================
 /// Write access to the current time step
 // ===================================================================
 Real &ACProblem::time_step(const unsigned i)
 {
#ifdef CHAPCHOM_PANIC_MODE
  // Get the size of the time step container
  const unsigned n_time_step = Time_step.size();
  if (i >= n_time_step)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to access to a time step that is not\n"
                  << "available at the time step container\n"
                  << "Maximum index of the time step container: ["<<n_time_step<<"]\n"
                  << "The index on the container you want to access: ["<<i<<"]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Time_step[i];
 }
 
 // ===================================================================
 /// Read-only access to the current time step
 // ===================================================================
 Real ACProblem::time_step(const unsigned i) const
 {
#ifdef CHAPCHOM_PANIC_MODE
  // Get the size of the time step container
  const unsigned n_time_step = Time_step.size();
  if (i >= n_time_step)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to access to a time step that is not\n"
                  << "available at the time step container\n"
                  << "Maximum index of the time step container: ["<<n_time_step<<"]\n"
                  << "The index on the container you want to access: ["<<i<<"]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Time_step[i];
 }
 
 // ===================================================================
 /// Add a time stepper
 //===================================================================
 void ACProblem::add_time_stepper(ACTimeStepper *time_stepper_pt,
                                  const Real initial_time,
                                  const Real time_step)
 {
  // Add the time stepper to the time stepper vector
  Time_stepper_pt.push_back(time_stepper_pt);
  // Add the initial time step for the time stepper
  Time.push_back(initial_time);
  // Add the time step for the time stepper
  Time_step.push_back(time_step);
 }
 
 /// Read-only access to the time i-th stepper pointer
 ACTimeStepper *ACProblem::time_stepper_pt(const unsigned i) const
 {
#ifdef CHAPCHOM_PANIC_MODE
  // Get the number of time steppers
  const unsigned n_time_steppers = Time_stepper_pt.size();
  if (i >= n_time_steppers)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You are trying to access to a time stepper that is not\n"
                  << "available at the time stepper container\n"
                  << "Maximum index of time steppers in the container: ["<<n_time_steppers<<"]\n"
                  << "The index of the time stepper you want to access: ["<<i<<"]\n"
                  << std::endl;
                     throw ChapchomLibError(error_message.str(),
                                            CHAPCHOM_CURRENT_FUNCTION,
                                            CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Time_stepper_pt[i];
 }
  
}

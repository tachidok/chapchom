#ifndef ACPROBLEM_H
#define ACPROBLEM_H

#include "../general/common_includes.h"
#include "../general/utilities.h"
#include "../general/initialise.h"

#include "../time_steppers/ac_time_stepper.h"

namespace scicellxx
{

 /// @class ACProblem ac_problem.h

 /// This class implements the interfaces for the problem class. It
 /// specifies a template for solving a problem thus one needs to
 /// create a class that inherents from this one to solve a particular
 /// problem
 class ACProblem
 {
  
 public:

  /// Constructor, in charge of initialising any stuff required for
  /// the framework
  ACProblem();
  
  /// Destructor
  virtual ~ACProblem();
  
  /// Every derived class must implement its own solve method (calling
  /// the corresponding steady_solve() and unsteady_solve() methods)
  virtual void solve() = 0;
  
  /// Add a time stepper
  void add_time_stepper(ACTimeStepper *time_stepper_pt,
                        const Real initial_time = 0,
                        const Real time_step = 0);
  
  /// Read-only access to the time i-th stepper pointer
  ACTimeStepper *time_stepper_pt(const unsigned i = 0) const;
  
  /// Get the number of time steppers
  inline const unsigned n_time_steppers() {return Time_stepper_pt.size();}
  
  /// Write access to the current time
  Real &time(const unsigned i = 0);
  
  /// Read-only access to the current time
  Real time(const unsigned i = 0) const;
  
  /// Write access to the current time step
  Real &time_step(const unsigned i = 0);
  
  /// Read-only access to the current time step
  Real time_step(const unsigned i = 0) const;
  
  /// Write access to the current time step
  inline unsigned &output_file_index() {return Output_file_index;}
  
  /// Read-only access to the current time step
  inline unsigned output_file_index() const {return Output_file_index;}
  
  /// Document solution
  virtual void document_solution()
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Virtual function in ACProblem class, you should implement\n"
                 << "it to document your solution" << std::endl;
   throw SciCellxxLibError(error_message.str(),
                          SCICELLXX_CURRENT_FUNCTION,
                          SCICELLXX_EXCEPTION_LOCATION);
  }
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACProblem(const ACProblem &copy)
   {
    BrokenCopy::broken_copy("ACProblem");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACProblem &copy)
   {
    BrokenCopy::broken_assign("ACProblem");
   }
  
  /// Initialise problem (sets framework ready to work)
  void initialise_problem();
  
  /// Finalise problem (performs operations to free resources)
  void finalise_problem();
  
  /// Problem steady solve
  virtual void steady_solve() = 0;
  
  /// Problem unsteady solve
  virtual void unsteady_solve() = 0;
  
  /// The set of actions to be performed before a time stepping
  virtual void actions_before_time_stepping() = 0;
  
  /// The set of actions to be performed after a time stepping
  virtual void actions_after_time_stepping() = 0; 
  
  /// The set of actions to be performed before newton solve
  virtual void actions_before_newton_solve() = 0;
  
  /// The set of actions to be performed after newton solve
  virtual void actions_after_newton_solve() = 0;
  
  /// A time steppers vector, possibly to solve a problem with
  /// different time scales
  std::vector<ACTimeStepper *> Time_stepper_pt;
  
  /// The current time vector (each time stepper has an associated
  /// time)
  std::vector<Real> Time;

  /// The time step vector (each time stepper has an associated time)
  std::vector<Real> Time_step;
  
  /// A counter to store the current output file index
  unsigned Output_file_index;
  
 };
 
}

#endif // #ifndef ACPROBLEM_H

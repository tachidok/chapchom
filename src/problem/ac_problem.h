#ifndef ACPROBLEM_H
#define ACPROBLEM_H

#include "../general/common_includes.h"
#include "../general/utilities.h"
#include "../general/initialise.h"

namespace chapchom
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
  
  // Problem steady solve
  virtual void steady_solve() = 0;
  
  // Problem unsteady solve
  virtual void unsteady_solve(bool shift_history_values = true) = 0;
  
  // Write access to the current time
  inline double &time() {return Time;}
  
  // Read-only access to the current time
  inline double time() const {return Time;}
  
  // Write access to the current time step
  inline double &time_step() {return Time_step;}
  
  // Read-only access to the current time step
  inline double time_step() const {return Time_step;}

  // Write access to the current time step
  inline unsigned &output_file_index() {return Output_file_index;}
  
  // Read-only access to the current time step
  inline unsigned output_file_index() const {return Output_file_index;}
  
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
  
  // Initialise problem (sets framework ready to work)
  void initialise_problem();
  
  // Finalise problem (performs operations to free resources)
  void finalise_problem();
  
  // The set of actions to be performed before a time stepping
  virtual void actions_before_time_stepping() = 0;
  
  // The set of actions to be performed after a time stepping
  virtual void actions_after_time_stepping() = 0; 
  
  // The set of actions to be performed before newton solve
  virtual void actions_before_newton_solve() = 0;
  
  // The set of actions to be performed after newton solve
  virtual void actions_after_newton_solve() = 0;
  
  // Document the solution
  virtual void document_solution(std::ostringstream &output_filename) = 0;
  
  // The current time
  double Time;
  
  // The time step
  double Time_step;
  
  // A counter to store the current output file index
  unsigned Output_file_index;
  
 };
 
}

#endif // #ifndef ACPROBLEM_H

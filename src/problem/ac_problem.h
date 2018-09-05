#ifndef ACPROBLEM_H
#define ACPROBLEM_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

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
  
  // Set initial conditions
  virtual void set_initial_conditions() = 0;
  
  // Set boundary conditions
  virtual void set_boundary_conditions() = 0;
  
  // Problem steady solve
  void steady_solve();
  
  // Problem unsteady solve
  void unsteady_solve();
  
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
  
  // The set of actions to be performed before a time stepping
  virtual void actions_before_time_stepping() { }
  
  // The set of actions to be performed after a time stepping
  virtual void actions_after_time_stepping() { }
  
  // The set of actions to be performed before a Newton solve,
  // e.g. setting boundary conditions
  virtual void actions_before_newton_solve() { }
  
  // The set of actions to be performed after a Newton solve,
  // e.g. update nodes/particules positions
 virtual void actions_after_newton_solve() { } 
  
 };

}
 
#endif // #ifndef ACPROBLEM_H

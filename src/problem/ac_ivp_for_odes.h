#ifndef CCIVPFORODES_H
#define CCIVPFORODES_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"
#include "../time_steppers/ac_time_stepper.h"
#include "ac_problem.h"

namespace chapchom
{

 /// @class ACIVPForODEs ac_ivp_for_odes.h

 /// This class implements the interfaces for an initial value problem
 /// for ODEs. It specifies a template for solving a problem thus one
 /// needs to create a class that inherents from this one to solve a
 /// particular initial value problem for ODEs
 class ACIVPForODEs : public virtual ACProblem
 {
  
 public:
  
  /// Constructor
  ACIVPForODEs(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt);
  
  /// Destructor
  virtual ~ACIVPForODEs();
  
  // Get access to the U vector
  CCData<Real> *u_pt() const {return U_pt;}
  
  // Read-only access to the vector U values
  inline const Real u(const unsigned i, const unsigned t = 0) const {return U_pt->value(i,t);}
  
  // Write access to the vector U values
  inline Real &u(const unsigned i, const unsigned t = 0) {return U_pt->value(i,t);}
  
  // -------------------------------------------------------------------------
  // THESE METHODS MUST BE IMPLEMENTED IN THE CONCRETE PROBLEM CLASS [BEGIN]
  // -------------------------------------------------------------------------
  // Set initial conditions
  virtual void set_initial_conditions() = 0;
  
  // Set boundary conditions
  virtual void set_boundary_conditions() = 0;
    
  // Document the solution
  virtual void document_solution(std::ostringstream &output_filename) { } 
  // -------------------------------------------------------------------------
  // THESE METHODS MUST BE IMPLEMENTED IN THE CONCRETE PROBLEM CLASS [END]
  // -------------------------------------------------------------------------
  
  // A helper function to complete the problem setup
  void complete_problem_setup() { }
  
  // Problem steady solve (empty)
  void steady_solve() { }
  
  // Problem unsteady solve
  void unsteady_solve();
  
 protected:
  
  /// Copy constructor (we do not want this class to be
   /// copiable). Check
   /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 ACIVPForODEs(const ACIVPForODEs &copy)
  : ACProblem()
   {
    
    BrokenCopy::broken_copy("ACIVPForODEs");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACIVPForODEs &copy)
   {
    BrokenCopy::broken_assign("ACIVPForODEs");
   } 
  
  // The set of actions to be performed before a time stepping
  virtual void actions_before_time_stepping() { }
  
  // The set of actions to be performed after a time stepping
  virtual void actions_after_time_stepping() { } 
  
  // The set of actions to be performed before newton solve
  virtual void actions_before_newton_solve() { }
  
  // The set of actions to be performed after newton solve
  virtual void actions_after_newton_solve() { }
  
  // The ODEs
  ACODEs *ODEs_pt;
  
  // The Time Stepper to approximate a solution to the ODEs
  ACTimeStepper *Time_stepper_pt;
  
  // The storage for the approximated solution of the time integration
  // of the ODEs
  CCData<Real> *U_pt;
  
 };
 
}

#endif // #ifndef CCIVPFORODES_H


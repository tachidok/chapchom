#include "ac_problem.h"

namespace chapchom
{

 // ===================================================================
 // Constructor, in charge of initialising any stuff required for the
 // framework
 // ===================================================================
 ACProblem::ACProblem()
  : Time(0.0), Time_step(0.0), Output_file_index(0)
 { 
  initialise_problem();
 }

 // ===================================================================
 // Destructor
 // ===================================================================
 ACProblem::~ACProblem()
 {
  finalise_problem();
 }
 
 // ===================================================================
 // Initialise problem (sets framework ready to work)
 // ===================================================================
 void ACProblem::initialise_problem()
 {
  // Initialise chapchom
  initialise_chapchom();
 }

 // =================================================================== 
 // Finalise problem (performs operations to free resources)
 // ===================================================================
 void ACProblem::finalise_problem()
 {
  // Finalise chapcom
  finalise_chapchom();
 }
 
}

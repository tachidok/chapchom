#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The required classes to solve Initial Value Problems (IVP)
// The factory to create the time stepper (integration method)
#include "../../../src/time_steppers/cc_factory_time_stepper.h"
// Integration methods
#include "../../../src/time_steppers/cc_euler_method.h"
#include "../../../src/time_steppers/cc_RK4_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"

#include "../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"
// Odes for Lotka-Volkaterra problem
#include "cc_lotka_volterra_odes.h"

using namespace chapchom;

/// This class implements inherits from the ACIVPForODEs class, we
/// implement specific functions to solve the Lotka-Volterra equations
class CCLotkaVolterraProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CCLotkaVolterraProblem(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
  // Name the outputfile and open it
  std::ostringstream output_filename;
  output_filename << "./RESLT/soln0.dat";
  output_filename.precision(8);
  Output_file.open((output_filename.str()).c_str());
 }
 
 /// Destructor
 ~CCLotkaVolterraProblem()
 {
  Output_file.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions
  u(0) = 2.0; // Initial number of prey
  u(1) = 1.0; // Initial number of predators
  
  // Document initial state
  complete_problem_setup();
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem setup (call
 // set_initial_conditions(), set_boundary_conditions() and document
 // the initial problem configuration)
 void complete_problem_setup()
 {
  // Initial problem configuration
  Output_file << Time << "\t" << u(0) << "\t" << u(1) << std::endl;
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename) { }
 
 // Document the solution
 void document_solution()
 {
  // Initial problem configuration
  Output_file << Time << "\t" << u(0) << "\t" << u(1) << std::endl;
 }
 
protected:

 // The output file
 std::ofstream Output_file;
 
}; // class CCLotkaVolterraProblem

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
 
 // ----------------------------------------------------------------
 // Time stepper
 // ----------------------------------------------------------------
 // Create the factory for the time steppers (integration methods)
 CCFactoryTimeStepper<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > factory_time_stepper;
 //CCFactoryTimeStepper<CCMatrix<Real>, CCVector<Real> > factory_time_stepper;
 // Create an instance of the integration method
 //ACTimeStepper *time_stepper_pt =
 // factory_time_stepper.create_time_stepper("Euler");
 //ACTimeStepper *time_stepper_pt =
 // factory_time_stepper.create_time_stepper("RK4");
 ACTimeStepper *time_stepper_pt =
  factory_time_stepper.create_time_stepper("BDF1");
 
 // Create an instance of the problem
 CCLotkaVolterraProblem lotka_volterra_problem(&odes, time_stepper_pt);
 
 // Prepare time integration data
 const Real initial_time = 0.0;
 const Real final_time = 40.0;
 //const unsigned n_time_steps = 1000;
 //const Real time_step = 0.0625;
 const Real time_step = 1.0;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 lotka_volterra_problem.time() = initial_time;
 
 // Initial time step
 lotka_volterra_problem.time_step() = time_step;
 
 // Set initial conditions
 lotka_volterra_problem.set_initial_conditions();
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   lotka_volterra_problem.unsteady_solve();
   
   // Update time of the problem
   lotka_volterra_problem.time()+=lotka_volterra_problem.time_step();
   
   // Check whether we have reached the final time
   if (lotka_volterra_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   lotka_volterra_problem.document_solution();
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


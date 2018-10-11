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
  
 }
 
 /// Destructor
 ~CCLotkaVolterraProblem()
 {
  
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions for 1st body
  u(0,0) = 0.0; // x-position
  u(1,0) = 0.0; // x-velocity
  u(2,0) = 0.0; // y-position
  u(3,0) = 0.0; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.0; // x-position
  u(7,0) = -5.0; // x-velocity
  u(8,0) = 5.2; // y-position
  u(9,0) = -2.5; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
#if 0
  // Initial conditions for 3rd body
  u(12,0) = -4.503; // x-position
  u(13,0) = -1.38; // x-velocity
  u(14,0) = 2.6; // y-position
  u(15,0) = -2.39; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
  // Initial conditions for 4th body
  u(18,0) = 4.503; // x-position
  u(19,0) = -1.38; // x-velocity
  u(20,0) = 2.6; // y-position
  u(21,0) = 2.39; // y-velocity
  u(22,0) = 0.0; // z-position
  u(23,0) = 0.0; // z-velocity
#endif // #if 0
#if 1
  // Initial conditions for 3rd body
  u(12,0) = -0.5; // x-position
  u(13,0) = -2.5; // x-velocity
  u(14,0) = 5.0; // y-position
  u(15,0) = -1.25; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
  // Initial conditions for 4th body
  u(18,0) = 0.5; // x-position
  u(19,0) = -2.5; // x-velocity
  u(20,0) = 5.4; // y-position
  u(21,0) = 1.25; // y-velocity
  u(22,0) = 0.0; // z-position
  u(23,0) = 0.0; // z-velocity 
#endif // #if 1
  
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
  std::ostringstream output_filename;
  output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << Output_file_index++;
  output_particles(Time, (*U_pt), output_filename);
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename)
 {
  output_particles(Time, (*U_pt), output_filename);
  
  // Output
  std::cout.precision(8);
  std::cout << "t: " << Time
            << "\t" << U_pt->value(0) << "\t" << U_pt->value(6) << "\t" << U_pt->value(12) << "\t" << U_pt->value(18) << std::endl;
  
 }
 
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
 CCLotkaVolterraProblem odes(4);
 
 odes.set_odes_parameters();
 
 // ----------------------------------------------------------------
 // Time stepper
 // ----------------------------------------------------------------
 // Create the factory for the time steppers (integration methods)
 CCFactoryTimeStepper<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > factory_time_stepper;
 //CCFactoryTimeStepper<CCMatrix<Real>, CCVector<Real> > factory_time_stepper;
 // Create an instance of the integration method
 //ACTimeStepper *time_stepper_pt =
 //  factory_time_stepper.create_time_stepper("Euler");
 //ACTimeStepper *time_stepper_pt =
 //  factory_time_stepper.create_time_stepper("RK4"); 
 ACTimeStepper *time_stepper_pt =
  factory_time_stepper.create_time_stepper("BDF1");
 
 // Create an instance of the problem
 CCNBodyProblem n_body_problem(&odes, time_stepper_pt);
 
 // Prepare time integration data
 const Real initial_time = 0.0; // years
 const Real final_time = 10.0; // years
 const unsigned n_time_steps = 1000;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 n_body_problem.time() = initial_time;
 
 // Initial time step
 n_body_problem.time_step() = (final_time - initial_time) / n_time_steps; // years
 
 // Set initial conditions
 n_body_problem.set_initial_conditions();
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   n_body_problem.unsteady_solve();
   
   // Update time of the problem
   n_body_problem.time()+=n_body_problem.time_step();
   
   // Check whether we have reached the final time
   if (n_body_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   // Output to file
   std::ostringstream output_filename;
   output_filename
    << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << n_body_problem.output_file_index()++;
   
   n_body_problem.document_solution(output_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


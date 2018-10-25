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
#include "../../../src/time_steppers/cc_runge_kutta_4_method.h"
#include "../../../src/time_steppers/cc_adams_moulton_2_predictor_corrector_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"
#include "../../../src/time_steppers/cc_adams_moulton_2_method.h"

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
 CCLotkaVolterraProblem(ACODEs *odes_pt,
                        ACTimeStepper *time_stepper_pt,
                        std::ostringstream &output_filename)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
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
  //u(0) = 0.9; // Initial number of prey
  //u(1) = 0.9; // Initial number of predators
  
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
 // Create the factory for the time steppers (integration methods)
#ifdef CHAPCHOM_USES_ARMADILLO
 CCFactoryTimeStepper<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > factory_time_stepper;
#else 
 CCFactoryTimeStepper<CCMatrix<Real>, CCVector<Real> > factory_time_stepper;
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
 
 // Euler method test
 {
  std::cout << "Euler test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
  //CCLotkaVolterraODEs odes(2.0/3.0, 4.0/3.0, 1.0, 1.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  // Create an instance of the integration method
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("Euler");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
   std::ostringstream output_filename;
   output_filename << "euler.dat";
   output_filename.precision(8);
  
   // Create an instance of the problem
   CCLotkaVolterraProblem lotka_volterra_problem(&odes,
                                                 time_stepper_pt,
                                                 output_filename);
  
   // Prepare time integration data
   const Real initial_time = 0.0;
   const Real final_time = 40.0;
   const Real time_step = 0.0625;
  
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
  
  }
 
 {
  std::cout << "Runge-Kutta 4 test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
  //CCLotkaVolterraODEs odes(2.0/3.0, 4.0/3.0, 1.0, 1.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("RK4");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "rk4.dat";
  output_filename.precision(8);
  
  // Create an instance of the problem
  CCLotkaVolterraProblem lotka_volterra_problem(&odes,
                                                time_stepper_pt,
                                                output_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 40.0;
  const Real time_step = 0.0625;
  
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
  
 }
 
 {
  std::cout << "Adams-Moulton 2 or Trapezoidal Rule - Predictor-Corrector test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
  //CCLotkaVolterraODEs odes(2.0/3.0, 4.0/3.0, 1.0, 1.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("AM2PC");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "am2pc.dat";
  output_filename.precision(8);
  
  // Create an instance of the problem
  CCLotkaVolterraProblem lotka_volterra_problem(&odes,
                                                time_stepper_pt,
                                                output_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 40.0;
  const Real time_step = 0.1;
  
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
  
 }
 
 {
  std::cout << "Backward Differentiation Formula 1 - Fully Implicit test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
  //CCLotkaVolterraODEs odes(2.0/3.0, 4.0/3.0, 1.0, 1.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("BDF1");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "bdf1.dat";
  output_filename.precision(8);
  
  // Create an instance of the problem
  CCLotkaVolterraProblem lotka_volterra_problem(&odes,
                                                time_stepper_pt,
                                                output_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 40.0;
  const Real time_step = 0.1;
  
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

 }
 
 {
  std::cout << "Adams-Moulton 2 or Trapezoidal Rule - Fully Implicit test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCLotkaVolterraODEs odes(1.2, 0.6, 0.8, 0.3);
  //CCLotkaVolterraODEs odes(2.0/3.0, 4.0/3.0, 1.0, 1.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("AM2");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "am2.dat";
  output_filename.precision(8);
  
  // Create an instance of the problem
  CCLotkaVolterraProblem lotka_volterra_problem(&odes,
                                                time_stepper_pt,
                                                output_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 40.0;
  const Real time_step = 0.1;
  
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

 }
 
 return 0;
 
}

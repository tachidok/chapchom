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
#include "../../../src/time_steppers/cc_backward_euler_predictor_corrector_method.h"
#include "../../../src/time_steppers/cc_adams_moulton_2_predictor_corrector_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"
#include "../../../src/time_steppers/cc_adams_moulton_2_method.h"
#include "../../../src/time_steppers/cc_bdf_2_method.h"

#include "../../../src/matrices/cc_matrix.h"

#ifdef SCICELLXX_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILLO

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"

// Odes for Chen problem
#include "cc_chen_odes.h"

using namespace scicellxx;

/// This class implements inherits from the ACIVPForODEs class, we
/// implement specific functions to solve the Lotka-Volterra equations
class CCChenProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CCChenProblem(ACODEs *odes_pt,
               ACTimeStepper *time_stepper_pt,
               std::ostringstream &output_filename1,
               std::ostringstream &output_filename2)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
  Output_file1.open((output_filename1.str()).c_str());
  Output_file2.open((output_filename2.str()).c_str());
  Counter = 0;
  //  Counter_output = 100;
 }
 
 /// Destructor
 ~CCChenProblem()
 {
  Output_file1.close();
  Output_file2.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions
  u(0) = -10.0;
  u(1) = 0.0;
  u(2) = 37.0;
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // Document the solution
 void document_solution()
 {
  const Real t = this->time();
  Counter++;
  if (Counter >= 5000000)
   {
    Counter = 0;
    std::cout << "Current time: " << t << std::endl;
   }
  
  //Counter_output++;
  //  if (Counter_output >= 100)
  {
   if (t >= 0 && t <= 200)
    {
     Output_file1 << t << "\t" << u(0) << "\t" << u(1) << "\t" << u(2) << std::endl;
    }
   else if (t >= 49800 && t <= 50000)
    {
     Output_file2 << t << "\t" << u(0) << "\t" << u(1) << "\t" << u(2) << std::endl;
    }
   //Counter_output = 0;
  }
 }
 
 protected:

  // The output files
  std::ofstream Output_file1;
  std::ofstream Output_file2;
 
 unsigned Counter;
 //unsigned Counter_output;
 
}; // class CCChenProblem

struct Args {
 argparse::ArgValue<bool> test;
};

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Instantiate parser
 Args args;
 auto parser = argparse::ArgumentParser(argv[0], "Description of application");
 
 // Add arguments
 
 // Optional
 parser.add_argument(args.test, "--test")
  .help("Boolean argument")
  .default_value("false")
  .action(argparse::Action::STORE_TRUE);
 
 // Parse the input arguments
 parser.parse_args(argc, argv);
 
 // Create the factory for the time steppers (integration methods)
 CCFactoryTimeStepper factory_time_stepper;

 // Number of prediction correction steps, if enabled it performs the
 // indicated number of prediction correction steps without checking
 // for local errors
 unsigned Fixed_number_of_prediction_correction_steps = 10;
 
 // Prepare time integration data
 const Real initial_time = 0.0;
 Real final_time = 50000.0;
 Real time_step = 0.002;
 
 // Check if we are in test mode
 if (args.test)
  {
   time_step = 0.02;
   Fixed_number_of_prediction_correction_steps = 2;
  }
 
 {
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Runge-Kutta 4 test" << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCChenODEs odes(35.0, 3.0, 28.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("RK4");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename0_200;
  output_filename0_200 << "RESLT/rk4_0_200.dat";
  std::ostringstream output_filename49800_50000;
  output_filename49800_50000 << "RESLT/rk4_49800_50000.dat";
  
  // Create an instance of the problem
  CCChenProblem chen_problem(&odes,
                             time_stepper_pt,
                             output_filename0_200,
                             output_filename49800_50000);
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  chen_problem.time() = initial_time;
  
  // Initial time step
  chen_problem.time_step() = time_step;
  
  // Set initial conditions
  chen_problem.set_initial_conditions();
  
  // Document intiial configuration
  chen_problem.document_solution();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    chen_problem.solve();
    
    // Update time of the problem
    chen_problem.time()+=chen_problem.time_step();
    
    // Check whether we have reached the final time
    if (chen_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    chen_problem.document_solution();
    
   } // while(LOOP)
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Backwards Euler - Predictor-Corrector test" << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCChenODEs odes(35.0, 3.0, 28.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("BEPC");
  
  // Dynamic cast to set a fixed number of corrections
  ACPredictorCorrectorTimeStepper *time_stepper_predictor_corrector_pt =
   dynamic_cast<ACPredictorCorrectorTimeStepper *>(time_stepper_pt);
  if (time_stepper_predictor_corrector_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dynamic cast was not succesfull."
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // Set a fixed number of prediction-correction steps
  time_stepper_predictor_corrector_pt->enable_fixed_number_of_corrections(Fixed_number_of_prediction_correction_steps);
  time_stepper_predictor_corrector_pt->enable_final_evaluation(); // P(EC)^k E , enables the last evaluation
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename0_200;
  output_filename0_200 << "RESLT/bepc_" << Fixed_number_of_prediction_correction_steps <<"_0_200.dat";
  std::ostringstream output_filename49800_50000;
  output_filename49800_50000 << "RESLT/bepc_" << Fixed_number_of_prediction_correction_steps << "_49800_50000.dat";
  
  // Create an instance of the problem
  CCChenProblem chen_problem(&odes,
                             time_stepper_pt,
                             output_filename0_200,
                             output_filename49800_50000); 
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  chen_problem.time() = initial_time;
  
  // Initial time step
  chen_problem.time_step() = time_step;
  
  // Set initial conditions
  chen_problem.set_initial_conditions();

  // Document intiial configuration
  chen_problem.document_solution();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    chen_problem.solve();
    
    // Update time of the problem
    chen_problem.time()+=chen_problem.time_step();
    
    // Check whether we have reached the final time
    if (chen_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    chen_problem.document_solution();
    
   } // while(LOOP)
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Adams-Moulton 2 - Predictor-Corrector test" << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCChenODEs odes(35.0, 3.0, 28.0);
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("AM2PC");

  // Dynamic cast to set a fixed number of corrections
  ACPredictorCorrectorTimeStepper *time_stepper_predictor_corrector_pt =
   dynamic_cast<ACPredictorCorrectorTimeStepper *>(time_stepper_pt);
  if (time_stepper_predictor_corrector_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dynamic cast was not succesfull."
                  << std::endl;
    throw SciCellxxLibError(error_message.str(),
                           SCICELLXX_CURRENT_FUNCTION,
                           SCICELLXX_EXCEPTION_LOCATION);
   }
  
  // Set a fixed number of prediction-correction steps
  time_stepper_predictor_corrector_pt->enable_fixed_number_of_corrections(Fixed_number_of_prediction_correction_steps);
  
  time_stepper_predictor_corrector_pt->enable_final_evaluation(); // P(EC)^k E , enables the last evaluation
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename0_200;
  output_filename0_200 << "RESLT/am2pc_" << Fixed_number_of_prediction_correction_steps << "_0_200.dat";
  std::ostringstream output_filename49800_50000;
  output_filename49800_50000 << "RESLT/am2pc_" << Fixed_number_of_prediction_correction_steps << "_49800_50000.dat";
  
  // Create an instance of the problem
  CCChenProblem chen_problem(&odes,
                             time_stepper_pt,
                             output_filename0_200,
                             output_filename49800_50000);
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  chen_problem.time() = initial_time;
  
  // Initial time step
  chen_problem.time_step() = time_step;
  
  // Set initial conditions
  chen_problem.set_initial_conditions();

  // Document intiial configuration
  chen_problem.document_solution();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    chen_problem.solve();
    
    // Update time of the problem
    chen_problem.time()+=chen_problem.time_step();
    
    // Check whether we have reached the final time
    if (chen_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    chen_problem.document_solution();
    
   } // while(LOOP)
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 return 0;
 
}

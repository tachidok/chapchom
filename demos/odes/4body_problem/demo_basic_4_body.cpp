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
// Time-stepper methods
#include "../../../src/time_steppers/cc_euler_method.h"
#include "../../../src/time_steppers/cc_runge_kutta_4_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"

// Matrices representations
#include "../../../src/matrices/cc_matrix.h"

#ifdef SCICELLXX_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILLO

#ifdef SCICELLXX_USES_VTK
#include "../../../src/vtk/cc_chapchom2vtk.h"
#endif // #ifdef SCICELLXX_USES_VTK

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"
// Odes for 4 body problem
#include "cc_odes_basic_4_body.h"

using namespace chapchom;

/// This class implements inherits from the ACIVPForODEs class, we
/// implement specific functions to solve the 4 body problem
class CC4BodyProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CC4BodyProblem(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt, std::ostringstream &output_filename)
  : ACIVPForODEs(odes_pt, time_stepper_pt),
    Output_filename(output_filename.str())
 {
  std::ostringstream output_complete_filename;
  output_complete_filename << Output_filename.str() << ".dat";
  Output_file.open((output_complete_filename.str()).c_str());
 }
 
 /// Destructor
 ~CC4BodyProblem()
 {
  Output_file.close();
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
  u(7,0) = -2.75674; // x-velocity
  u(8,0) = 5.2; // y-position
  u(9,0) = 0.0; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
#if 1
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
#endif // #if 1
#if 0
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
  u(3,0) = 0.0; // z-velocity 
#endif // #if 0
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem setup
 void complete_problem_setup()
 {
  
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename)
 {
  // Document animation
  const Real t = this->time();
  const unsigned n_data_per_particle = 6;
  CCSciCellxx2VTK::get_instance().output_particles(t, (*U_pt), output_filename, n_data_per_particle);
  
  // Output
  std::cout.precision(8);
  std::cout.precision(8);
  std::cout << "t: " << t
            << "\t" << U_pt->value(0) << "\t" << U_pt->value(2) << "\t" << U_pt->value(6) << "\t" << U_pt->value(8) << "\t" << U_pt->value(12) << "\t" << U_pt->value(14) << "\t" << U_pt->value(18) << "\t" << U_pt->value(20) << std::endl;
  
  // Document raw data
  // t,
  // x_1, vx_1, y_1, vy_1, z_1, vz_1,
  // x_2, vx_2, y_2, vy_2, z_2, vz_2,
  // x_3, vx_3, y_3, vy_3, z_3, vz_3,
  // x_4, vx_4, y_4, vy_4, z_4, vz_4
  Output_file << t << "\t"
              << u(0) << "\t" << u(1) << "\t" << u(2) << "\t" << u(3) << "\t" << u(4) << "\t" << u(5) << "\t"
              << u(6) << "\t" << u(7) << "\t" << u(8) << "\t" << u(9) << "\t" << u(10) << "\t" << u(11) << "\t"
              << u(12) << "\t" << u(13) << "\t" << u(14) << "\t" << u(15) << "\t" << u(16) << "\t" << u(17) << "\t"
              << u(18) << "\t" << u(19) << "\t" << u(20) << "\t" << u(21) << "\t" << u(22) << "\t" << u(23) << std::endl;
  
 }
 
protected:
 
 // The output file
 std::ostringstream Output_filename;
 
 // The output file
 std::ofstream Output_file;
 
}; // class CC4BodyProblem

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
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 CCODEsBasic4Body odes(4);
 
 odes.set_odes_parameters();
 
 // ----------------------------------------------------------------
 // Time stepper
 // ----------------------------------------------------------------
 // Create the factory for the time steppers (integration methods)
 CCFactoryTimeStepper factory_time_stepper;
 
 // Create an instance of the integration method
 //ACTimeStepper *time_stepper_pt =
 //  factory_time_stepper.create_time_stepper("Euler");
 ACTimeStepper *time_stepper_pt =
  factory_time_stepper.create_time_stepper("RK4"); 
 //ACTimeStepper *time_stepper_pt =
 //factory_time_stepper.create_time_stepper("BDF1");
 
 // ----------------------------------------------------------------
 // Prepare the output file
 // ----------------------------------------------------------------
 std::ostringstream raw_output_filename;
 raw_output_filename << "output_test";
 
 // Create an instance of the problem
 CC4BodyProblem four_body_problem(&odes, time_stepper_pt, raw_output_filename);
 
 // Prepare time integration data
 const Real initial_time = 0.0; // years
 const Real final_time = 30.0; // years
 const unsigned n_time_steps = 3000;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 four_body_problem.time() = initial_time;
 
 // Initial time step
 four_body_problem.time_step() = (final_time - initial_time) / n_time_steps; // years
 
 // Set initial conditions
 four_body_problem.set_initial_conditions();
 
 // Complete setup
 four_body_problem.complete_problem_setup();
 
 // Output to file
 std::ostringstream output_filename;
 if (!args.test)
  {
   output_filename
    << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << four_body_problem.output_file_index()++;
  }
 
 // Document initial configuration
 four_body_problem.document_solution(output_filename);
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   four_body_problem.solve();
   
   // Update time of the problem
   four_body_problem.time()+=four_body_problem.time_step();
   
   // Check whether we have reached the final time
   if (four_body_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   // Output to file
   std::ostringstream ioutput_filename;
   if (!args.test)
    {
     ioutput_filename
      << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << four_body_problem.output_file_index()++;
    }
   
   four_body_problem.document_solution(ioutput_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


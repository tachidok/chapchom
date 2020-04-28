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

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

#ifdef CHAPCHOM_USES_VTK
#include "../../../src/vtk/cc_chapchom2vtk.h"
#endif // #ifdef CHAPCHOM_USES_VTK

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"
// Odes for N body problem
#include "cc_odes_basic_3_body.h"

//#define EIGHT_SHAPE_SOLUTION
//#define BODY_AT_CENTER_SOLUTION
#define FLOWER_IN_CIRCLE_SOLUTION
//#define TRIPLE_RINGS_SOLUTION
//#define TRIANGLES_INSIDE_OVAL_SOLUTION

using namespace chapchom;

// The VTK output object
//CCChapchom2VTK VTK_helper = CCChapchom2VTK::get_instance();

/// This class inherits from the ACIVPForODEs class, we implement
/// specific functions to solve the 3 body problem
class CC3BodyProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CC3BodyProblem(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt, std::ostringstream &output_filename)
  : ACIVPForODEs(odes_pt, time_stepper_pt),
    Output_filename(output_filename.str())
 {
  std::ostringstream output_complete_filename;
  output_complete_filename << Output_filename.str() << ".dat";
  Output_file.open((output_complete_filename.str()).c_str()); 
 }
 
 /// Destructor
 ~CC3BodyProblem()
 {
  Output_file.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {  
#ifdef EIGHT_SHAPE_SOLUTION
  // An infinity/eight shape movement
  
  // r1(0) = - r3(0) = (-0.97000436, 0.24308753); r2(0) = (0,0); v1(0) = v3(0) = (0.4662036850, 0.4323657300); v2(0) = (-0.93240737, -0.86473146).
  
  // The values are obtained from Chenciner & Montgomery (2000). Check
  // the Wikipedia page for the initial conditions in the references
  // https://en.wikipedia.org/wiki/Three-body_problem
  
  // Initial conditions for 1st body
  u(0,0) = -0.97000436; // x-position
  u(1,0) = 0.4662036850; // x-velocity
  u(2,0) = 0.24308753; // y-position
  u(3,0) = 0.4323657300; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.0; // x-position
  u(7,0) = -0.93240737; // x-velocity
  u(8,0) = 0.0; // y-position
  u(9,0) = -0.86473146; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = 0.97000436; // x-position
  u(13,0) = 0.4662036850; // x-velocity
  u(14,0) = -0.24308753; // y-position
  u(15,0) = 0.4323657300; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity 
#endif // #ifdef EIGHT_SHAPE_SOLUTION

#ifdef BODY_AT_CENTER_SOLUTION 
  // Body at the center and two others in elliptic orbitis
  
  // Initial conditions for 1st body
  u(0,0) = 0.0; // x-position
  u(1,0) = 0.0 ; // x-velocity
  u(2,0) = 0.0; // y-position
  u(3,0) = 0.0; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = -5.0; // x-position
  u(7,0) = 0.0; // x-velocity
  u(8,0) = 0.0; // y-position
  u(9,0) = -1.0; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = 5.0; // x-position
  u(13,0) = 0.0; // x-velocity
  u(14,0) = 0.0; // y-position
  u(15,0) = 1.0; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
#endif // #ifdef BODY_AT_CENTER_SOLUTION 
  
#ifdef FLOWER_IN_CIRCLE_SOLUTION
  // Flower in circle
  
  // Initial conditions for 1st body
  u(0,0) = -0.602885898116520; // x-position
  u(1,0) = 0.122913546623784; // x-velocity
  u(2,0) = 1.059162128863347-1; // y-position
  u(3,0) = 0.747443868604908; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.252709795391000; // x-position
  u(7,0) = -0.019325586404545; // x-velocity
  u(8,0) = 1.058254872224370-1; // y-position
  u(9,0) = 1.369241993562101; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = -0.355389016941814; // x-position
  u(13,0) = -0.103587960218793; // x-velocity
  u(14,0) = 1.038323764315145-1; // y-position
  u(15,0) = -2.116685862168820; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity 
#endif // #ifdef FLOWER_IN_CIRCLE_SOLUTION

#ifdef TRIPLE_RINGS_SOLUTION
  // Triple rings
  
  // Initial conditions for 1st body
  u(0,0) = -0.0347; // x-position
  u(1,0) = 0.2495; // x-velocity
  u(2,0) = 1.1856; // y-position
  u(3,0) = -0.1076; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.2693; // x-position
  u(7,0) = 0.2059; // x-velocity
  u(8,0) = -1.0020; // y-position
  u(9,0) = -0.9396; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = -0.2328; // x-position
  u(13,0) = -0.4553; // x-velocity
  u(14,0) = -0.5978; // y-position
  u(15,0) = 1.0471; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity 
#endif // #ifdef TRIPLE_RINGS_SOLUTION
  
#ifdef TRIANGLES_INSIDE_OVAL_SOLUTION
  // Nested ovals
  
  // Initial conditions for 1st body
  u(0,0) = 1.666163752077218-1; // x-position
  u(1,0) = 0.841202975403070; // x-velocity
  u(2,0) = -1.081921852656887+1; // y-position
  u(3,0) = 0.029746212757039; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.974807336315507-1; // x-position
  u(7,0) = 0.142642469612081; // x-velocity
  u(8,0) = -0.545551424117481+1; // y-position
  u(9,0) = -0.492315648524683; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = 0.896986706257760-1; // x-position
  u(13,0) = -0.983845445011510; // x-velocity
  u(14,0) = -1.765806200083609+1; // y-position
  u(15,0) = 0.462569435774018; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity 
#endif // #ifdef TRIANGLES_INSIDE_OVAL_SOLUTION
  
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem setup
 void complete_problem_setup()
 {
  CCODEsBasic3Body *odes_pt = dynamic_cast<CCODEsBasic3Body *>(ODEs_pt);
  if (odes_pt==NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "It was not possible to dynamic cast the ODEs to the CCODEsBasic3Body ODEs class\n"
                  << "and residual computation."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
#ifdef EIGHT_SHAPE_SOLUTION
  // Set masses and gravity
  odes_pt->m(0) = 1.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef EIGHT_SHAPE_SOLUTION
  
#ifdef BODY_AT_CENTER_SOLUTION 
  // Set masses and gravity
  odes_pt->m(0) = 10.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef BODY_AT_CENTER_SOLUTION
  
#ifdef FLOWER_IN_CIRCLE_SOLUTION
  // Flower in circle
  // Set masses and gravity
  odes_pt->m(0) = 1.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef FLOWER_IN_CIRCLE_SOLUTION

#ifdef TRIPLE_RINGS_SOLUTION
  // Triple rings
  // Set masses and gravity
  odes_pt->m(0) = 1.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef TRIPLE_RINGS_SOLUTION

#ifdef TRIANGLES_INSIDE_OVAL_SOLUTION
  // Nested oval
  // Set masses and gravity
  odes_pt->m(0) = 1.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef TRIANGLES_INSIDE_OVAL_SOLUTION
  
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename)
 {
  const unsigned n_data_per_particle = 6;
  const Real t = this->time();
  CCChapchom2VTK::get_instance().output_particles(t, (*U_pt), output_filename, n_data_per_particle);
  
  // Output
  std::cout.precision(8);
  std::cout << "t: " << t
            << "\t" << U_pt->value(0) << "\t" << U_pt->value(2) << "\t" << U_pt->value(6) << "\t" << U_pt->value(8) << "\t" << U_pt->value(12) << "\t" << U_pt->value(14) << std::endl;
  
  // Document raw data
  // t,
  // x_1, vx_1, y_1, vy_1, z_1, vz_1,
  // x_2, vx_2, y_2, vy_2, z_2, vz_2,
  // x_3, vx_3, y_3, vy_3, z_3, vz_3
  Output_file << t << "\t"
              << u(0) << "\t" << u(1) << "\t" << u(2) << "\t" << u(3) << "\t" << u(4) << "\t" << u(5) << "\t"
              << u(6) << "\t" << u(7) << "\t" << u(8) << "\t" << u(9) << "\t" << u(10) << "\t" << u(11) << "\t"
              << u(12) << "\t" << u(13) << "\t" << u(14) << "\t" << u(15) << "\t" << u(16) << "\t" << u(17) <<  std::endl;
  
 }
 
protected:
 
 // The output file
 std::ostringstream Output_filename;
 
 // The output file
 std::ofstream Output_file;
  
}; // class CC3BodyProblem

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
 // Instantiation of the odes associated with the problem
 // -----------------------------------------------------------------
 CCODEsBasic3Body odes(3);
 
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
 // Prepare the output filename
 // ----------------------------------------------------------------
 std::ostringstream raw_output_filename;
 raw_output_filename << "output_test";
 
 // Create an instance of the problem
 CC3BodyProblem three_body_problem(&odes, time_stepper_pt, raw_output_filename);
 
 // Prepare time integration data
 const Real initial_time = 0.0;
 const Real final_time = 10.0;
 const Real time_step = 0.01;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 three_body_problem.time() = initial_time;
 
 // Initial time step
 three_body_problem.time_step() = time_step;
 
 // Set initial conditions
 three_body_problem.set_initial_conditions();
 
 // Complete setup
 three_body_problem.complete_problem_setup();
 
 // Output to file
 std::ostringstream output_filename;
 if (!args.test)
  {
   output_filename
    << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << three_body_problem.output_file_index()++;
  }
 
 // Document initial configuration
 three_body_problem.document_solution(output_filename);
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   three_body_problem.solve();
   
   // Update time of the problem
   three_body_problem.time()+=three_body_problem.time_step();
   
   // Check whether we have reached the final time
   if (three_body_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   // Output to file
   std::ostringstream ioutput_filename;
   if (!args.test)
    {
     ioutput_filename
      << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << three_body_problem.output_file_index()++;
    }
   
   three_body_problem.document_solution(ioutput_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


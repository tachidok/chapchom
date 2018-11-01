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
#include "../../../src/time_steppers/cc_bdf_2_method.h"

#include "../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// The class used to store the values of u and dudt
#include "../../../src/data_structures/cc_data.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/data_structures/ac_odes.h"

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"

using namespace chapchom;
// =================================================================
// =================================================================
// =================================================================
/// This class implements the system of ODEs to be solved
///
/// \frac{du}{dt} = -u^{2}, with initial values u(0) = 1
// =================================================================
// =================================================================
// =================================================================
class CCBasicODEs : public virtual ACODEs
{
 
public:
 
 /// Constructor
 CCBasicODEs()
  :ACODEs(1) // The number of equations
 {
  
 }
 
 /// Empty destructor
 virtual ~CCBasicODEs()
 {
  
 }
 
 /// Evaluates the system of odes at time 't', using the history
 /// values of u at index k
 void evaluate(const Real t, CCData<Real> &u, CCData<Real> &dudt, const unsigned k = 0)
 {
  // \frac{du}{dt} = -u^{2}
  dudt(0) = -(u(0,k)*u(0,k));
 }
 
protected:
 
 /// Copy constructor (we do not want this class to be
 /// copiable). Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCBasicODEs(const CCBasicODEs &copy)
  : ACODEs(copy)
 {
  BrokenCopy::broken_copy("CCBasicODEs");
 }
 
 /// Assignment operator (we do not want this class to be
 /// copiable. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCBasicODEs &copy)
 {
  BrokenCopy::broken_assign("CCBasicODEs");
 }
 
};

// =================================================================
// =================================================================
// =================================================================
// This class inherits from the ACIVPForODEs class and solves the
// system of ODEs from above
// =================================================================
// =================================================================
// =================================================================
class CCBasicODEsProblem : public virtual ACIVPForODEs
{
 
public:
 
 /// Constructor
 CCBasicODEsProblem(ACODEs *odes_pt,
                    ACTimeStepper *time_stepper_pt,
                    std::ostringstream &output_filename,
                    std::ostringstream &output_filename_error)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
  Output_file.open((output_filename.str()).c_str());
  Output_error_file.open((output_filename_error.str()).c_str());
 }
 
 /// Destructor
 ~CCBasicODEsProblem()
 {
  Output_file.close();
  Output_error_file.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions
  u(0) = 1.0;
  
  // Document initial state
  complete_problem_setup();
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem
 // setup (calls set_boundary_conditions() and document the initial problem
 // configuration)
 void complete_problem_setup()
 {
  // Initial problem configuration
  Output_file << Time << "\t" << u(0) << std::endl;
  output_error();
 }
 
 // Document the solution
 void document_solution()
 {
  // Initial problem configuration
  Output_file << Time << "\t" << u(0) << std::endl;
  output_error();
 }

 // Output error
 void output_error()
 {
  // Compute the error 
  const Real t = this->time();
  const Real u_analytical = 1.0/(1.0+t);
  const Real error = std::fabs(u(0)-u_analytical);
  Output_error_file << Time << "\t" << error << std::endl;
 }
 
protected:
 
 // The output file
 std::ofstream Output_file;
 // The error output file
 std::ofstream Output_error_file;
 
}; // class CCBasicODEsProblem

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
  CCBasicODEs odes;
  
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
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "euler_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
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
  CCBasicODEs odes;
  
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

  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "rk4_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
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
  CCBasicODEs odes;
  
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

  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "am2pc_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
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
  CCBasicODEs odes;
  
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

  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "bdf1_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
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
  CCBasicODEs odes;
  
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

  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "am2_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
   } // while(LOOP)
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "Backward Differentiation Formula 2 - Fully Implicit test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCBasicODEs odes;
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("BDF2");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "bdf2.dat";
  output_filename.precision(8);

  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "bdf2_error.dat";
  output_error_filename.precision(8);
  
  // Create an instance of the problem
  CCBasicODEsProblem basic_ode_problem(&odes,
                                       time_stepper_pt,
                                       output_filename,
                                       output_error_filename);
  
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 2.0;
  const Real time_step = 0.1;
  
  // ----------------------------------------------------------------
  // Configure problem
  // ----------------------------------------------------------------
  // Initial time
  basic_ode_problem.time() = initial_time;
  
  // Initial time step
  basic_ode_problem.time_step() = time_step;
  
  // Set initial conditions
  basic_ode_problem.set_initial_conditions();
  
  // Flag to indicate whether to continue processing
  bool LOOP = true;
  
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    // Check whether we have reached the final time
    if (basic_ode_problem.time() >= final_time)
     {
      LOOP = false;
     }
    
    basic_ode_problem.document_solution();
    
   } // while(LOOP)
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 return 0;
 
}

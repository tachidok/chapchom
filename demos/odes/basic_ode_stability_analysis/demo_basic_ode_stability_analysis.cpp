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

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// The class used to store the values of u and dudt
#include "../../../src/data_structures/cc_data.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/data_structures/ac_odes.h"

// The base class for the specification of the Jacobian of the ODEs
#include "../../../src/time_steppers/ac_jacobian_and_residual_for_implicit_time_stepper.h"

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
 void evaluate_derivatives(const Real t, CCData &u, CCData &dudt, const unsigned k = 0)
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
class CCStabilityAnalysisProblem : public virtual ACIVPForODEs
{
 
public:
 
 /// Constructor
 CCStabilityAnalysisProblem(ACODEs *odes_pt,
                            ACTimeStepper *time_stepper_pt,
                            std::ostringstream &output_filename_prefix,
                            std::ostringstream &output_filename_error_prefix,
                            std::ostringstream &output_filename_stability,
                            const Real initial_time,
                            const Real final_time)
  : ACIVPForODEs(odes_pt, time_stepper_pt),
    Output_filename_prefix(output_filename_prefix.str()),
    Output_error_filename_prefix(output_filename_error_prefix.str()),
    Output_stability_filename(output_filename_stability.str()),
    Initial_time(initial_time),
    Final_time(final_time)
 {
  std::ostringstream output_stability_filename;
  output_stability_filename << Output_stability_filename.str() << ".dat";
  Output_stability_file.open((output_stability_filename.str()).c_str());
 }
 
 /// Destructor
 ~CCStabilityAnalysisProblem()
 {
  // Close open files
  Output_file.close();
  Output_error_file.close();
  Output_stability_file.close();
 }
 
 // Prepare the filenames for new output
 void prepare_files_for_output()
 {
  // Close previouly open files
  Output_file.close();
  Output_error_file.close();
  
  // Generate the new files names
  std::ostringstream output_filename;
  std::ostringstream output_filename_error;
  
  output_filename << Output_filename_prefix.str() << "_h_" << this->time_step() << ".dat";
  output_filename_error << Output_error_filename_prefix.str() << "_h_" << this->time_step() << ".dat";
  
  Output_file.open((output_filename.str()).c_str());
  Output_error_file.open((output_filename_error.str()).c_str());
 }
 
 // Solve the problem with a new time step
 void solve()
 {
  // Open files
  prepare_files_for_output();
  
  // Reset problem current time
  this->time() = 0.0;
  
  // Reset initial conditions
  set_initial_conditions();
  
  // Document initial solution
  this->document_solution();
     
  // Flag to indicate whether to continue processing
  bool LOOP = true;
   
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Solve (unsteady solve) - PARENT VERSION
    ACIVPForODEs::solve();
    
    // Update time of the problem
    this->time()+=this->time_step();
    
    // Check whether we have reached the final time
    if (this->time() >= Final_time)
     {
      LOOP = false;
     }
     
    this->document_solution();
     
   } // while(LOOP)
  
  // Document error at $u = Final_time$
  const Real u_analytical = 1.0/(1.0+Final_time);
  Output_stability_file << this->time_step() << "\t" << fabs(u(0)- u_analytical) << std::endl;
  
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions
  u(0) = 1.0; 
 }
 
 // Document the solution
 void document_solution()
 {
  // Initial problem configuration
  Output_file << this->time() << "\t" << u(0) << std::endl;
  output_error();
 }

 // Output error
 void output_error()
 {
  // Compute the error 
  const Real t = this->time();
  const Real u_analytical = 1.0/(1.0+t);
  const Real error = std::fabs(u(0)-u_analytical);
  Output_error_file << t << "\t" << error << std::endl;
 }
 
protected:
 
 // The output file prefix
 std::ostringstream Output_filename_prefix;
 // The error output file prefix
 std::ostringstream Output_error_filename_prefix; 
 // The stability output file prefix
 std::ostringstream Output_stability_filename;
 
 // The initial time
 const Real Initial_time; 
 // The final time
 const Real Final_time;
  
 // The output file
 std::ofstream Output_file;
 // The error output file
 std::ofstream Output_error_file;
 // The stability output file
 std::ofstream Output_stability_file;
  
}; // class CCStabilityAnalysisProblem

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
  
 // Euler stability analysis
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Euler - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/euler";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/euler_error";
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/euler_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
    
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Runge-Kutta 4 - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/rk4";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/rk4_error";
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/rk4_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
      
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Backward Euler - Predictor-Corrector - Stability analysis" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCBasicODEs odes;
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("BEPC");
  
  // ----------------------------------------------------------------
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/bepc";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/bepc_error"; 
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/bepc_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();

  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
    
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Adams-Moulton 2 or Trapezoidal Rule - Predictor-Corrector - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/am2pc";
   
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/am2pc_error"; 
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/am2pc_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();

  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
    
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
  
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Backward Differentiation Formula 1 - Fully Implicit - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/bdf1";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/bdf1_error";
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/bdf1_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
    
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
  
 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Adams-Moulton 2 or Trapezoidal Rule - Fully Implicit - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/am2";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/am2_error";
  
  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/am2_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.1;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 } 

 {
  std::cout << "--------------------------" << std::endl;
  std::cout << "Backward Differentiation Formula 2 - Fully Implicit - Stability analysis" << std::endl;
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
  // Prepare the output file name prefix
  // ----------------------------------------------------------------
  std::ostringstream output_filename_prefix;
  output_filename_prefix << "RESLT/bdf2";
  
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename_prefix;
  output_error_filename_prefix << "RESLT/bdf2_error";

  // ----------------------------------------------------------------
  // Prepare the output stability file name
  // ----------------------------------------------------------------
  std::ostringstream output_stability_filename_prefix;
  output_stability_filename_prefix << "RESLT/bdf2_stability";
  
  // Time interval for solving
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
  
  // Create an instance of the problem
  CCStabilityAnalysisProblem stability_analysis_problem(&odes,
                                                        time_stepper_pt,
                                                        output_filename_prefix,
                                                        output_error_filename_prefix,
                                                        output_stability_filename_prefix,
                                                        initial_time,
                                                        final_time);
  
  // ----------------------------------------------------------------
  // Configure the problem with different time steps to perform
  // stability analisys
  // ----------------------------------------------------------------
  Real time_step = 1.0;
  // Resets time stepper
  //time_stepper_pt->reset();
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.1;
  // Resets time stepper
  time_stepper_pt->reset();
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.01;
  // Resets time stepper
  time_stepper_pt->reset();
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  time_step = 0.001;
    // Resets time stepper
  time_stepper_pt->reset();
  stability_analysis_problem.time_step() = time_step;
  // Solve
  stability_analysis_problem.solve();
  
  std::cout << "[FINISHING UP] ... " << std::endl;
  
  // Free memory
  delete time_stepper_pt;
  time_stepper_pt = 0;
  
 }
 
 return 0;
 
}

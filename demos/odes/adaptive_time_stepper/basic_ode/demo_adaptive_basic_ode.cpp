#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../../src/general/common_includes.h"
#include "../../../../src/general/utilities.h"
#include "../../../../src/general/initialise.h"

// The required classes to solve Initial Value Problems (IVP)
// The factory to create the time stepper (integration method)
#include "../../../../src/time_steppers/cc_factory_time_stepper.h"
// Integration methods
#include "../../../../src/time_steppers/ac_adaptive_time_stepper.h"
#include "../../../../src/time_steppers/cc_adaptive_runge_kutta_45F_method.h"
#include "../../../../src/time_steppers/cc_adaptive_runge_kutta_45DP_method.h"

#include "../../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// The class used to store the values of u and dudt
#include "../../../../src/data_structures/cc_data.h"
// The class implementing the interfaces for the ODEs
#include "../../../../src/data_structures/ac_odes.h"

// Base class for the concrete problem
#include "../../../../src/problem/ac_ivp_for_odes.h"

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
 void evaluate_derivatives(const Real t, CCData<Real> &u, CCData<Real> &dudt, const unsigned k = 0)
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
// system of ODEs from above. It implements additional processing for
// the adaptive time step method
// =================================================================
// =================================================================
// =================================================================
class CCAdaptiveBasicODEsProblem : public virtual ACIVPForODEs
{
 
public:
 
 /// Constructor
 CCAdaptiveBasicODEsProblem(ACODEs *odes_pt,
                            ACTimeStepper *time_stepper_pt,
                            std::ostringstream &output_filename,
                            std::ostringstream &output_filename_error)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
  Output_file.open((output_filename.str()).c_str());
  Output_error_file.open((output_filename_error.str()).c_str());

  // Cast the time stepper to get a pointer to the adaptive version of
  // the time stepper
  Adaptive_time_stepper_pt = dynamic_cast<ACAdaptiveTimeStepper*>(time_stepper_pt);
  if (Adaptive_time_stepper_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The time stepper is not adaptive or of type ACAdaptiveTimeStepper*\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 /// Destructor
 ~CCAdaptiveBasicODEsProblem()
 {
  Output_file.close();
  Output_error_file.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions
  u(0) = 1.0; 
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // The set of actions to be performed after a time stepping
 void actions_after_time_stepping()
 {
  // Update the time step as that really used for the time step method
  this->time_step() = Adaptive_time_stepper_pt->current_auto_step_size();
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
 
 // Keep track of the adaptive version of the time stepper
 ACAdaptiveTimeStepper *Adaptive_time_stepper_pt;
 
}; // class CCAdaptiveBasicODEsProblem

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
  
 {
  std::cout << "Adaptive Runge-Kutta 4(5) Fehlberg test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCBasicODEs odes;
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("RK45F");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "RESLT/rk45f.dat";
   
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "RESLT/rk45f_error.dat";
   
  // Create an instance of the problem
  CCAdaptiveBasicODEsProblem basic_ode_problem(&odes,
                                               time_stepper_pt,
                                               output_filename,
                                               output_error_filename);
   
  // Prepare time integration data
  const Real initial_time = 0.0;
  const Real final_time = 20.0;
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

  // Document initial configuration
  basic_ode_problem.document_solution();
   
  // Flag to indicate whether to continue processing
  bool LOOP = true;
   
  // Main LOOP (loop until reaching final time)
  while(LOOP)
   {
    // Performs an unsteady solve
    basic_ode_problem.unsteady_solve();
    
    // Update time of the problem
    basic_ode_problem.time()+=basic_ode_problem.time_step();
    
    std::cerr << "t: " << basic_ode_problem.time() << " h: " << basic_ode_problem.time_step() << std::endl;
    
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

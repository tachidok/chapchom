#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../../src/general/common_includes.h"
#include "../../../../src/general/utilities.h"
#include "../../../../src/general/initialise.h"

// An interpolator
#include "../../../../src/problem/cc_newton_interpolator.h"

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
  
  // Disable fixed ouptut by default
  disable_fixed_output();
  
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
  
  // Add the intiial conditions to the interpolation vectors
  T_values_for_interpolator.push_back(0.0);
  U_values_for_interpolator.push_back(u(0));
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // The set of actions to be performed after a time stepping
 void actions_after_time_stepping()
 {
  // Update the time step as that really used for the time step method
  this->time_step() = Adaptive_time_stepper_pt->taken_auto_step_size();
  
  // Check whether fixed output is enabled
  if (Fixed_output)
   {
    // Compute the new time
    const Real t = time() + time_step();
    // Shift the data and leave those more recent if there are three
    // values already
    const unsigned n_data = T_values_for_interpolator.size();
    if (n_data >= 3)
     {
      // Erase the first element of the vector
      T_values_for_interpolator.erase(T_values_for_interpolator.begin());
      U_values_for_interpolator.erase(U_values_for_interpolator.begin());
      // Add the current values
      T_values_for_interpolator.push_back(t);
      U_values_for_interpolator.push_back(u(0));
     }
    else
     {
      // Add the current values to the interpolation vectors
      T_values_for_interpolator.push_back(t);
      U_values_for_interpolator.push_back(u(0));
     }
   }
  
 }
 
 // Document the solution
 void document_solution()
 {
  // Check whether fixed output is enabled
  if (!Fixed_output)
   {
    // Output the current values of u
    Output_file << time() << "\t" << u(0) << std::endl;
    output_error();
   }
  else
   {
    document_solution_at_fixed_output();
   } // else if (!Fixed_output)
  
 }
 
 void document_solution_at_fixed_output()
 {
  // Check how many data do we have to perform interpolation 
  if (T_values_for_interpolator.size() == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "There are no data to perform interpolation\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  else if (T_values_for_interpolator.size() == 1)
   {
    // Output the current values of u
    Output_file << T_values_for_interpolator[0] << "\t" << U_values_for_interpolator[0] << std::endl;
    output_error(T_values_for_interpolator[0], U_values_for_interpolator[0]);
    Previous_fixed_output_time = T_values_for_interpolator[0];
   }
  else if (T_values_for_interpolator.size() == 2)
   {
    const unsigned interpolation_order = 1;
    const Real fixed_output_time = Previous_fixed_output_time + Fixed_output_step;
    // Check whether the current values of U allow to compute a
    // value for the fixed output time
    if (T_values_for_interpolator[1] >= fixed_output_time)
     {
      const Real U_interpolated = Interpolator.interpolate_1D(T_values_for_interpolator, U_values_for_interpolator, fixed_output_time, interpolation_order);
      // Output the current values of u
      Output_file << fixed_output_time << "\t" << U_interpolated << std::endl;
      output_error(fixed_output_time, U_interpolated);
      // Update the last fixed output
      Previous_fixed_output_time+=Fixed_output_step;
     }
   }
  else
   {
    const unsigned interpolation_order = 2;
    // Output as many data as able using the approximations of U
    bool LOOP = true;
    while(LOOP)
     {
      Real fixed_output_time = Previous_fixed_output_time + Fixed_output_step;
      // Check whether the current values of U allow to compute a
      // value for the fixed output time
      if (!(T_values_for_interpolator[2] > fixed_output_time))
       {
        // Set loop to false but break the loop
        LOOP = false;
        break;
       }
      // Interpolate
      const Real U_interpolated = Interpolator.interpolate_1D(T_values_for_interpolator, U_values_for_interpolator, fixed_output_time, interpolation_order);
      // Output the current values of u
      Output_file << fixed_output_time << "\t" << U_interpolated << std::endl;
      output_error(fixed_output_time, U_interpolated);
      // Update the last fixed output
      Previous_fixed_output_time+=Fixed_output_step;
     } // while(LOOP);
      
   }
  
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
 
 // Output error for fixed output
 void output_error(const Real fixed_time, const Real fixed_u)
 {
  // Compute the error
  const Real u_analytical = 1.0/(1.0+fixed_time);
  const Real error = std::fabs(fixed_u-u_analytical);
  Output_error_file << fixed_time << "\t" << error << std::endl;
 }
 
 // Write access
 inline Real &fixed_output_step() {return Fixed_output_step;}
 
 inline void enable_fixed_output()
 {Fixed_output = true;}
 
 inline void disable_fixed_output()
 {Fixed_output = false;}
 
protected:
 
 // The output file
 std::ofstream Output_file;
 // The error output file
 std::ofstream Output_error_file;
 
 // Keep track of the adaptive version of the time stepper
 ACAdaptiveTimeStepper *Adaptive_time_stepper_pt;
 
 // Indicates whether to perform fixed output
 bool Fixed_output;
 
 // The fixed output step
 Real Fixed_output_step;
 
 // An interpolator
 CCNewtonInterpolator Interpolator;
 
 // Storage for t and u values
 std::vector<Real> T_values_for_interpolator;
 std::vector<Real> U_values_for_interpolator;
 
 // Keep track of the previous fixed output time
 Real Previous_fixed_output_time;
 
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
  
  // Enable/disable fixed output
  //basic_ode_problem.disable_fixed_output();
  basic_ode_problem.enable_fixed_output();
  
  // Set the fixed output step size
  basic_ode_problem.fixed_output_step() = 1.0;
   
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
 
 {
  std::cout << "Adaptive Runge-Kutta 4(5) Dormand-Prince test" << std::endl;
  // -----------------------------------------------------------------
  // Instantiation of the ODEs
  // -----------------------------------------------------------------
  CCBasicODEs odes;
  
  // ----------------------------------------------------------------
  // Time stepper
  // ----------------------------------------------------------------
  ACTimeStepper *time_stepper_pt =
   factory_time_stepper.create_time_stepper("RK45DP");
  
  // ----------------------------------------------------------------
  // Prepare the output file name
  // ----------------------------------------------------------------
  std::ostringstream output_filename;
  output_filename << "RESLT/rk45dp.dat";
   
  // ----------------------------------------------------------------
  // Prepare the output error file name
  // ----------------------------------------------------------------
  std::ostringstream output_error_filename;
  output_error_filename << "RESLT/rk45dp_error.dat";
  
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
  
  // Enable/disable fixed output
  basic_ode_problem.disable_fixed_output();
  //basic_ode_problem.enable_fixed_output();
  
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

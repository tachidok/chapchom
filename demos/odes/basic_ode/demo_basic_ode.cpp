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
// This class implements the strategy for the computation of the
// Jacobian of the system of ODEs to be solved (it is optional to
// implement it for your specific problem, but if you know the
// Jacobian the specification of this class may reduce the
// computational cost)
//
// \frac{dF}{du} = -2u
// =================================================================
// =================================================================
// =================================================================
template<class MAT_TYPE, class VEC_TYPE>
class CCJacobianStrategyForMyODEs : public virtual ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE,VEC_TYPE>
{
 
public:
 
 // Empty constructor
 CCJacobianStrategyForMyODEs()
  : ACJacobianAndResidualForImplicitTimeStepper<MAT_TYPE, VEC_TYPE>()
 {
  
 }
 
 // Empty destructor
 ~CCJacobianStrategyForMyODEs()
 {
  
 }
 
 // In charge of computing the Jacobian
 void compute_jacobian()
 {
  // Get a pointer to the ODEs
  ACODEs *odes_pt = this->odes_pt();
  
  // Get a pointer to the u values
  CCData<Real> *u_pt = this->u_pt();
  
  // Check whether the data for the computation of the jacobian has
  // been set
  if (!this->data_for_jacobian_and_residual_has_been_set() || odes_pt == NULL || u_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You have not established the data required for\n"
                  << "the computation of the Jacobian\n"
                  << "You need to call the method\n"
                  << "set_data_for_jacobian_and_residual()\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of ODEs
  const unsigned n_dof = odes_pt->n_odes();
  
  // Double check that the number of odes is correct
  if (n_dof != 1)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The number of odes is not correct (ehhh!!!!)\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Allocate memory for the Jacobian (delete previous data)
  this->Jacobian.allocate_memory(n_dof, n_dof);
  
  // Get the index of history values of the u vector at time 't+h'
  // that should be used to compute the values of the Jacobian
  const unsigned k = this->history_index();
  
  // Fill in the Jacobian
  this->Jacobian(0, 0) = -(2*u_pt->value(0,k));
  
 }
 
 // No residual computation
 void compute_residual()
 {
  
 }
 
private:
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCJacobianStrategyForMyODEs(const CCJacobianStrategyForMyODEs <MAT_TYPE,VEC_TYPE> &copy)
 {
  BrokenCopy::broken_copy("CCJacobianStrategyForMyODEs");
 }
 
 // Copy constructor (we do not want this class to be copiable because
 // it contains dynamically allocated variables, A in this
 // case). Check
 // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 void operator=(const CCJacobianStrategyForMyODEs<MAT_TYPE,VEC_TYPE> &copy)
 {
  BrokenCopy::broken_assign("CCJacobianStrategyForMyODEs");
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
  }
  
  // Document the solution
  void document_solution()
  {
   // Get the inital time
   const Real t = this->time();
   // Initial problem configuration
   Output_file << t << "\t" << u(0) << std::endl;
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
   output_filename << "RESLT/euler.dat";
   output_filename.precision(8);
   
   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/euler_error.dat";
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
   
   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
   
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
     
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
   output_filename << "RESLT/rk4.dat";
   output_filename.precision(8);

   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/rk4_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
    
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
   std::cout << "Backward-Euler - Predictor-Corrector test" << std::endl;
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
   // Prepare the output file name
   // ----------------------------------------------------------------
   std::ostringstream output_filename;
   output_filename << "RESLT/bepc.dat";
   output_filename.precision(8);
   
   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/bepc_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
    
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
   output_filename << "RESLT/am2pc.dat";
   output_filename.precision(8);

   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/am2pc_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
     
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
   
   // Create an instance of the strategy to compute the Jacobian
#ifdef CHAPCHOM_USES_ARMADILLO
   CCJacobianStrategyForMyODEs<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > my_jacobian_strategy;
#else
   CCJacobianStrategyForMyODEs<CCMatrix<Real>, CCVector<Real> > my_jacobian_strategy;
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Get a pointer to the specific time stepper
#ifdef CHAPCHOM_USES_ARMADILLO
   CCBackwardEulerMethod<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *backward_euler_time_stepper_pt =
    dynamic_cast<CCBackwardEulerMethod<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *>(time_stepper_pt);
#else
   CCBackwardEulerMethod<CCMatrix<Real>, CCVector<Real> > *backward_euler_time_stepper_pt =
    dynamic_cast<CCBackwardEulerMethod<CCMatrix<Real>, CCVector<Real> > *>(time_stepper_pt);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Set the Jacobian strategy for the time stepper
   backward_euler_time_stepper_pt->set_strategy_for_odes_jacobian(&my_jacobian_strategy);
   
   // ----------------------------------------------------------------
   // Prepare the output file name
   // ----------------------------------------------------------------
   std::ostringstream output_filename;
   output_filename << "RESLT/bdf1.dat";
   output_filename.precision(8);

   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/bdf1_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
    
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
   
   // Create an instance of the strategy to compute the Jacobian 
#ifdef CHAPCHOM_USES_ARMADILLO
   CCJacobianStrategyForMyODEs<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > my_jacobian_strategy;
#else
   CCJacobianStrategyForMyODEs<CCMatrix<Real>, CCVector<Real> > my_jacobian_strategy;
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Get a pointer to the specific time stepper   
#ifdef CHAPCHOM_USES_ARMADILLO
   CCAdamsMoulton2Method<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *amd2_time_stepper_pt =
    dynamic_cast<CCAdamsMoulton2Method<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *>(time_stepper_pt);
#else
   CCAdamsMoulton2Method<CCMatrix<Real>, CCVector<Real> > *amd2_time_stepper_pt =
    dynamic_cast<CCAdamsMoulton2Method<CCMatrix<Real>, CCVector<Real> > *>(time_stepper_pt);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Set the Jacobian strategy for the time stepper
   amd2_time_stepper_pt->set_strategy_for_odes_jacobian(&my_jacobian_strategy);
   
   // ----------------------------------------------------------------
   // Prepare the output file name
   // ----------------------------------------------------------------
   std::ostringstream output_filename;
   output_filename << "RESLT/am2.dat";
   output_filename.precision(8);

   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/am2_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
    
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
   
   // Create an instance of the strategy to compute the Jacobian 
#ifdef CHAPCHOM_USES_ARMADILLO
   CCJacobianStrategyForMyODEs<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > my_jacobian_strategy;
#else
   CCJacobianStrategyForMyODEs<CCMatrix<Real>, CCVector<Real> > my_jacobian_strategy;
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Get a pointer to the specific time stepper
#ifdef CHAPCHOM_USES_ARMADILLO
   CCBDF2Method<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *bdf2_time_stepper_pt =
    dynamic_cast<CCBDF2Method<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > *>(time_stepper_pt);
#else
   CCBDF2Method<CCMatrix<Real>, CCVector<Real> > *bdf2_time_stepper_pt =
    dynamic_cast<CCBDF2Method<CCMatrix<Real>, CCVector<Real> > *>(time_stepper_pt);
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
   
   // Set the Jacobian strategy for the time stepper
   bdf2_time_stepper_pt->set_strategy_for_odes_jacobian(&my_jacobian_strategy);
   
   // ----------------------------------------------------------------
   // Prepare the output file name
   // ----------------------------------------------------------------
   std::ostringstream output_filename;
   output_filename << "RESLT/bdf2.dat";
   output_filename.precision(8);

   // ----------------------------------------------------------------
   // Prepare the output error file name
   // ----------------------------------------------------------------
   std::ostringstream output_error_filename;
   output_error_filename << "RESLT/bdf2_error.dat";
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

   // Document initial configuration
   basic_ode_problem.document_solution();
   
   // Flag to indicate whether to continue processing
   bool LOOP = true;
  
   // Main LOOP (loop until reaching final time)
   while(LOOP)
    {
     // Solve (unsteady solve)
     basic_ode_problem.solve();
    
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

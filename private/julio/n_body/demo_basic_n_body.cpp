#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The required classes to solve Initial Value Problems (IVP)
// The factory to create the integration method
#include "../../../src/integration/cc_factory_integration_method.h"
// Integration methods
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// Odes for N body problem
#include "cc_odes_basic_n_body.h"

// -------------------------------------------------
// Constants
// -------------------------------------------------
#define G 4*M_PI // Gravitational constant for problem

using namespace chapchom;

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 // Initialise chapchom
 initialise_chapchom();
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 CCODEsBasicNBody odes(G, 4);
 // Set the masses of the objects
 odes.m(0) = 1.0;
 odes.m(1) = 0.001;
 odes.m(2) = 0.0;
 odes.m(3) = 0.0;
 
 // ----------------------------------------------------------------
 // Integrator initialisation [BEGIN]
 // ----------------------------------------------------------------
 // Create the factory for the integration methods
 CCFactoryIntegrationMethod *factory_integration_methods =
  new CCFactoryIntegrationMethod();
 // Create an instance of the integration method
 //ACIntegrationMethod *integrator =
 //factory_integration_methods->create_integration_method("Euler");
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("RK4");
 // Get the number of history values required by the integration
 // method
 const unsigned n_history_values = integrator->n_history_values();
 // Get the number of odes from the problem
 const unsigned n_odes = odes.nodes();
 // Storage for the values of the integrated functions
 std::vector<std::vector<double> > y(n_odes);
 // For each ode we allocate space for the histoy values + 1 (to store
 // the history values and the current one)
 for (unsigned i = 0; i < n_odes; i++)
         {
          y[i].resize(n_history_values+1);
         }
 
        // Set initial conditions
 odes.set_initial_conditions(y);
 
 // Prepare time integration data
 double initial_time = 0.0; // years
 double final_time = 300.0; // years
 double time_step_size = 0.001; // years
 double current_time = initial_time; // years
 
 // Output the initial data to screen
 std::cout.precision(8);
 std::cout << "t: " << current_time
           << "\t" << y[0][0] << "\t" << y[6][0] << "\t" << y[12][0] << "\t" << y[18][0] << std::endl;
 
 // ----------------------------------------------------------------
 // Integrator initialisation [END]
 // ----------------------------------------------------------------
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (continue looping until all data in the input file is
 // processed)
 while(LOOP)
  {
   // ==========================================================================
   // Integrate the ODE's [BEGIN]
   // ==========================================================================     
   integrator->integrate_step(odes, time_step_size, current_time, y);
   
   // Update data (shift the history values)
   for (unsigned j = 0; j < n_odes; j++)
    {
     for (unsigned k = 0; k < n_history_values; k++)
      {
       y[j][k] = y[j][k+1];
      }
    }
   // Update time
   current_time+=time_step_size;
   
   // Check whether we have reached the final time
   if (current_time >= final_time)
    {
     LOOP = false;
    }
   
   // ==========================================================================
   // Integrate the ODE's [END]
   // ==========================================================================
   
   // Output
   std::cout.precision(8);
   std::cout << "t: " << current_time
             << "\t" << y[0][0] << "\t" << y[6][0] << "\t" << y[12][0] << "\t" << y[18][0] << std::endl;
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete integrator;
 integrator = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

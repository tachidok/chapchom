#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// The factory to create the integration method
#include "../../../src/integration/cc_factory_integration_method.h"
// Integration methods
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_table_based_on_velocity.h"

//#define T_EULER
#define T_RK4

int main(int argc, char *argv[])
{
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 
 // Create an instance of the ODEs to solve
 CCODEsFromTableBasedOnVelocity *odes = new CCODEsFromTableBasedOnVelocity();
 
 // Create the factory for the methods
 CCFactoryIntegrationMethod *factory_integration_methods =
  new CCFactoryIntegrationMethod();
 // Create an instance of the integrator method
#ifdef T_EULER
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("Euler");
#endif
#ifdef T_RK4
 ACIntegrationMethod *integrator =
  factory_integration_methods->create_integration_method("RK4");
#endif
 // Get the number of history values required by the integration
 // method
 const unsigned n_history_values = integrator->n_history_values();
 // Get the number of odes
 const unsigned n_odes = odes->nodes();
 // Storage for the values of the function (plus one history value to
 // store the current one)
 std::vector<std::vector<double> > y(n_history_values+1);
 // Resize container for the number of odes
 for (unsigned i = 0; i < n_history_values+1; i++)
  {
   y[i].resize(n_odes);
  }

 // Open two files to store the results 
 char file_longitude_name[100];
#ifdef T_EULER
 sprintf(file_longitude_name, "./RESLT/longitude_from_velocityEuler.dat");
#endif
#ifdef T_RK4
 sprintf(file_longitude_name, "./RESLT/longitude_from_velocityRK4.dat");
#endif
 FILE *file_longitude_pt = fopen(file_longitude_name, "w");
 if (file_longitude_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_longitude_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 char file_latitude_name[100];
#ifdef T_EULER
 sprintf(file_latitude_name, "./RESLT/latitude_from_velocityEuler.dat");
#endif
#ifdef T_RK4
 sprintf(file_latitude_name, "./RESLT/latitude_from_velocityRK4.dat");
#endif
 FILE *file_latitude_pt = fopen(file_latitude_name, "w");
 if (file_latitude_pt == 0)
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_latitude_name << "]"
		 << std::endl;
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (steps, h,
 // initial values)
 // -----------------------------------------------------------------
 // Set the initial and final interval values (got from the number of data in Table)
 const double t_initial = 0.0;
 const double t_final = 4108;
 //const double t_final = 10;
 // Set the number of steps
 const double n_steps = 10000;
 //const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Initial time
 double t = t_initial;
 
 // Initial conditions
 y[0][0] = 0.0;         // Initial x-position
 y[0][1] = 0.0;         // Initial y-position
 
 // Output the initial data to screen
 std::cout << "t: " << t
           << " x-pos: " << y[0][0] << " y-pos: " << y[0][1] << std::endl;
 fprintf(file_longitude_pt, "%lf %lf\n", t, y[0][0]);
 fprintf(file_latitude_pt, "%lf %lf\n", t, y[0][1]);
 
 // Integrate
 //integrator->integrate(*odes, h, t_initial, t_final, y);
 for (unsigned i = 0; i < n_steps; i++)
  {
   integrator->integrate_step(*odes, h, t, y);
   // Update data
   for (unsigned j = 0; j < n_odes; j++)
    {
     y[0][j] = y[1][j];
    }
   // Update time
   t+=h;
   std::cout << "t: " << t
             << " x-pos: " << y[0][0] << " y-pos: " << y[0][1] << std::endl;
   fprintf(file_longitude_pt, "%lf %lf\n", t, y[0][0]);
   fprintf(file_latitude_pt, "%lf %lf\n", t, y[0][1]);
   //getchar();
  }
    
 std::cout << "[FINISHING UP] ... " << std::endl;

 // Close the output files
 fclose(file_longitude_pt);
 fclose(file_latitude_pt);
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 std::cout << "[DONE]" << std::endl;
 
}

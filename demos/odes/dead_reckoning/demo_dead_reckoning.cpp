#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
//#include "../../src/odes/ca_explicit_method.h"
#include "../../../src/integration/ca_integration_method.h"
#include "../../../src/integration/cc_euler_method.h"
#include "../../../src/integration/cc_RK4_method.h"
// The odes
#include "cc_odes_from_table_based_on_velocity.h"
#include "cc_odes_from_table_based_on_acceleration.h"

int main(int argc, char *argv[])
{
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 
 // Create an instance of the ODEs to solve
 //CCODEsFromTableBasedOnVelocity *odes = new CCODEsFromTableBasedOnVelocity();
 CCODEsFromTableBasedOnAcceleration *odes = new CCODEsFromTableBasedOnAcceleration();
 odes->load_table("./extracted_data.dat");
 
 // Create an instance of the integrator method
 CAIntegrationMethod *integrator = new CCEulerMethod();
 //CAIntegrationMethod *integrator = new CCRK4Method();
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
 FILE *file_latitude_pt = fopen("./latitudeEuler.dat", "w");
 if (file_latitude_pt == 0)
  {
   std::cout << "ERROR in main() - Could not create the file [latitude.dat]"
	     << std::endl;
   throw(1);
   return 0;
  }
 
 FILE *file_longitude_pt = fopen("./longitudeEuler.dat", "w");
 if (file_longitude_pt == 0)
  {
   std::cout << "ERROR in main() - Could not create the file [longitude.dat]"
	     << std::endl;
   throw(1);
   return 0;
  }
 
 // -----------------------------------------------------------------
 // Configuration and initialisation of the problem (time, initial
 // values)
 // -----------------------------------------------------------------
 // Set the initial and final interval values
 const double t_initial = 0.0;
 const double t_final = 4144;
 //const double t_final = 10;
 // Set the number of steps we want to take
 const double n_steps = 100000;
 //const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Initial time
 double t = t_initial;
 
 // Initial conditions
 y[0][0] = 0.0;         // Initial x-position
 y[0][1] = -0.05994836; // Initial x-velocity
 y[0][2] = 0.0;         // Initial y-position
 y[0][3] = 0.033224355; // Initial y-velocity
 
 //y[0][0] = 0.0;         // Initial x-position
 //y[0][1] = 0.0;         // Initial y-position
 
 // The first data
 std::cout << "t: " << t << " y[0][0]: " << y[0][0] << std::endl;
 std::cout << "t: " << t << " y[0][1]: " << y[0][1] << std::endl;
 std::cout << "t: " << t << " y[0][2]: " << y[0][2] << std::endl;
 std::cout << "t: " << t << " y[0][3]: " << y[0][3] << std::endl;
 fprintf(file_longitude_pt, "%lf %lf\n", t, y[0][0]);
 fprintf(file_latitude_pt, "%lf %lf\n", t, y[0][2]);
 
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
   t+=h;
   std::cout << "t: " << t << " y[0][0]: " << y[0][0] << std::endl;
   std::cout << "t: " << t << " y[0][1]: " << y[0][1] << std::endl;
   std::cout << "t: " << t << " y[0][2]: " << y[0][2] << std::endl;
   std::cout << "t: " << t << " y[0][3]: " << y[0][3] << std::endl;
   fprintf(file_longitude_pt, "%lf %lf\n", t, y[0][0]);
   fprintf(file_latitude_pt, "%lf %lf\n", t, y[0][2);
   //getchar();
  }
 
 std::cout << "[FINISHING UP] ... " << std::endl;

 // Close the output files
 fclose(file_latitude_pt);
 fclose(file_longitude_pt);
 
 // Free memory
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;
 
 std::cout << "[DONE]" << std::endl;
 
}

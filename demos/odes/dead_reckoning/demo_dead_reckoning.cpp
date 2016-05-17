#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
//#include "../../src/odes/ca_explicit_method.h"
#include "../../../src/integration/ca_integration_method.h"
#include "../../../src/integration/cc_euler_method.h"
// The odes
#include "cc_odes_from_table.h"

int main(int argc, char *argv[])
{
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 
 // Create an instance of the ODEs to solve
 CCODEsFromTable *odes = new CCODEsFromTable();
 odes->load_table("./extracted_data.dat");
 
 // Create an instance of the integrator method
 CAIntegrationMethod *integrator = new CCEulerMethod();
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
 FILE *file_latitude_pt = fopen("./my_latitude.dat", "w");
 if (file_latitude_pt == 0)
  {
   std::cout << "ERROR in main() - Could not create the file [my_latitude.dat]"
	     << std::endl;
   throw(1);
   return 0;
  }
 
 FILE *file_longitude_pt = fopen("./my_longitude.dat", "w");
 if (file_longitude_pt == 0)
  {
   std::cout << "ERROR in main() - Could not create the file [my_longitude.dat]"
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
 const double t_final = 4145;
 //const double t_final = 10;
 // Set the number of steps we want to take
 const double n_steps = 100000;
 //const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Initial time
 double t = t_initial;
 
 // Initial conditions
 y[0][0] = -98.2285316455;
 y[0][1] = 19.0159704133;
 
 // The first data
 std::cout << "t: " << t << " y[0][0]: " << y[0][0] << std::endl;
 std::cout << "t: " << t << " y[0][1]: " << y[0][1] << std::endl;
 fprintf(file_longitude_pt, "%lf %lf\n", t, y[0][0]);
 fprintf(file_latitude_pt, "%lf %lf\n", t, y[0][1]);
 
#if 0
 // Evaluate ode
 for (unsigned i = 0; i < n_steps; i++)
  {
   std::vector<double> dy(2);
   odes->evaluate(t, y[0], dy);
   std::cout << "t: " << t << " y[0][0]: " << y[0]
	     << " dy[0]: " << dy[0] << std::endl;
   std::cout << "t: " << t << " y[0][1]: " << y[1]
	     << " dy[1]: " << dy[1] << std::endl;
   getchar();
   t+=h;
  }
#endif // #if 0
 
 // Integrate
 //integrator->integrate(*odes, h, t_initial, t_final, y);
 for (unsigned i = 0; i < n_steps; i++)
  {
   integrator->integrate_step(*odes, h, t, y);
   std::cout << "t: " << t << " y[1][0]: " << y[1][0] << std::endl;
   std::cout << "t: " << t << " y[1][1]: " << y[1][1] << std::endl;
   fprintf(file_longitude_pt, "%lf %lf\n", t, y[1][0]);
   fprintf(file_latitude_pt, "%lf %lf\n", t, y[1][1]);
   // Update data
   for (unsigned j = 0; j < n_odes; j++)
    {
     y[0][j] = y[1][j];
    }
   t+=h;
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

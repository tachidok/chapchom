#include <iostream>
#include <cmath>

// The required classes to solve Initial Value Problems (IVP)
// Integration methods
//#include "../../src/odes/ca_explicit_method.h"
#include "../../../src/odes/cc_euler_method.h"
// The odes
#include "cc_odes_from_table.h"

int main(int argc, char *argv[])
{
 // Create an instance of the ODEs to solve
 CCODEsFromTable *odes = new CCODEsFromTable();
 odes->load_table("./extracted_data.dat");
 
 // Set the initial and final interval values
 const double t_initial = 0;
 // const double t_final = 4145;
 const double t_final = 10;
 // Set the number of steps we want to take
 //const double n_steps = 100000;
 const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
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
 
 // Create an instance of the integrator methods
 CCEulerMethod *integrator = new CCEulerMethod();
 
 // The values of the function
 std::vector<double> y(2);
 
 // Initial time
 double t = 0.0;
 
 // Initial conditions
 y[0] = -98.2285316455;
 y[1] = 19.0159704133;
 
 // The first data
 std::cout << "t: " << t << " y[0]: " << y[0] << std::endl;
 std::cout << "t: " << t << " y[1]: " << y[1] << std::endl;
 fprintf(file_longitude_pt, "%lf %lf\n", t, y[0]);
 fprintf(file_latitude_pt, "%lf %lf\n", t, y[1]);

 
#if 0
 // Evaluate ode
 for (unsigned i = 0; i < n_steps; i++)
  {
   std::vector<double> dy(2);
   odes->evaluate(t, y, dy);
   std::cout << "t: " << t << " y[0]: " << y[0]
	     << " dy[0]: " << dy[0] << std::endl;
   std::cout << "t: " << t << " y[1]: " << y[1]
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
   std::cout << "t: " << t << " y[0]: " << y[0] << std::endl;
   std::cout << "t: " << t << " y[1]: " << y[1] << std::endl;
   fprintf(file_longitude_pt, "%lf %lf\n", t, y[0]);
   fprintf(file_latitude_pt, "%lf %lf\n", t, y[1]);
   t+=h;
  }
 
#if 0
 // Print got values
 t = 0;
 for (unsigned i = 0; i < n_steps; i++)
  {
   std::cout << "y(" << t << "): " << y[i] << std::endl;
   t+=h;
  }
#endif // #if 0
 
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

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
 
 // Set the initial and final interval values
 const double t_initial = 0;
 const double t_final = 100;
 // Set the number of steps we want to take
 const double n_steps = 100;
 // Get the step size
 const double h = (t_final - t_initial) / n_steps;
 
 // Create an instance of the integrator methods
 CCEulerMethod *integrator = new CCEulerMethod();
 
 // The values of the function
 std::vector<double> y(n_steps);
 
 // Integrate
 integrator->integrate(*odes, h, t_initial, t_final, y);
 
 double current_step = 0;
 for (unsigned i = 0; i < n_steps; i++)
  {
   std::cout << "y(" << current_step << "): " << y[i] << std::endl;
   current_step+=h;
  }
 
 delete integrator;
 integrator = 0;
 delete odes;
 odes = 0;

}

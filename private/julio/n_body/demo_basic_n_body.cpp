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

// Include the VTK libraries to generate the output
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>

#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkPointData.h>

// -------------------------------------------------
// Constants
// -------------------------------------------------
#define G 4*M_PI // Gravitational constant for problem

using namespace chapchom;

// ==================================================================
// Functions for VTK output
// ==================================================================
void add_time_to_vtk_data_set(double time,
                              vtkSmartPointer<vtkUnstructuredGrid> &data_set)
{
 // Add time stamp for the current file
 vtkSmartPointer<vtkDoubleArray> array = vtkSmartPointer<vtkDoubleArray>::New();
 array->SetName("TIME");
 array->SetNumberOfTuples(1);
 array->SetTuple1(0, time);
 data_set->GetFieldData()->AddArray(array);
}

void add_particles_to_vtk_data_set(const std::vector<std::vector <double> > &particles_data,
                                   vtkSmartPointer<vtkPoints> &data_points,
                                   vtkSmartPointer<vtkUnstructuredGrid> &data_set)
{
 const unsigned n_data_per_particle = 6;
 const int n_particles = particles_data.size()/n_data_per_particle;
 // An array to store the particles IDs
 vtkSmartPointer<vtkDoubleArray> ids = vtkSmartPointer<vtkDoubleArray>::New();
 ids->SetNumberOfComponents(1);
 ids->SetNumberOfTuples(n_particles);
 ids->SetName("ID");
#if 0
 // An array to store the particles radius
 vtkSmartPointer<vtkDoubleArray> radius = vtkSmartPointer<vtkDoubleArray>::New();
 radius->SetNumberOfComponents(3);
 radius->SetNumberOfTuples(n_particles);
 radius->SetName("Radius");
#endif // #if 0
 // An array to store the particles positions
 vtkSmartPointer<vtkDoubleArray> position = vtkSmartPointer<vtkDoubleArray>::New();
 position->SetNumberOfComponents(3);
 position->SetNumberOfTuples(n_particles);
 position->SetName("Position");
 // An array to store the particles velocity
 vtkSmartPointer<vtkDoubleArray> velocity = vtkSmartPointer<vtkDoubleArray>::New();
 velocity->SetNumberOfComponents(3);
 velocity->SetNumberOfTuples(n_particles);
 velocity->SetName("Velocity");

 // Temporal vector to extract data
 double pos[3];
 double vel[3];
 int global_id = 0;
 // Loop through particles data
 for (unsigned i = 0; i < n_particles*n_data_per_particle; i+=n_data_per_particle)
  {
   // Position
   pos[0] = particles_data[i][0];
   pos[1] = particles_data[i+2][0];
   pos[2] = particles_data[i+4][0];
   data_points->SetPoint(global_id, pos);
   
   // IDs
   ids->InsertValue(global_id, global_id);
   
   // Velocity
   vel[0] = particles_data[i+1][0];
   vel[1] = particles_data[i+3][0];
   vel[2] = particles_data[i+5][0];
   velocity->InsertTuple(global_id, vel);
   
   global_id++;
  }
 
 // Add particles data to data set
 data_set->GetPointData()->AddArray(ids);
 //data_set->GetPointData()->AddArray(radius);
 //data_set->GetPointData()->AddArray(position);
 data_set->GetPointData()->AddArray(velocity);
}

void output_particles(double time,
                      const std::vector<std::vector <double> > &particles_data,
                      std::ostringstream &file_name)
{
 // Create a VTK writer
 vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
  vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
 
 // Generate the filename with the proper extension
 file_name << "." << writer->GetDefaultFileExtension();
 writer->SetFileName((file_name.str()).c_str());
 
 // Create a pointer to a VTK Unstructured Grid data set
 vtkSmartPointer<vtkUnstructuredGrid> data_set =
  vtkSmartPointer<vtkUnstructuredGrid>::New();
 
 // Set up pointer to data point
 vtkSmartPointer<vtkPoints> data_points =
  vtkSmartPointer<vtkPoints>::New();
 
 // Get the total number of particles
 const int n_points = particles_data.size()/6;
 data_points->SetNumberOfPoints(n_points);
 
 // Add time
 add_time_to_vtk_data_set(time, data_set);
 
 // Add the particle data to the unstructured grid
 add_particles_to_vtk_data_set(particles_data, data_points, data_set);
 
 // Set the points
 data_set->SetPoints(data_points);
 // Remove unused memory
 data_set->Squeeze();
 
 // Set the writer's input data set
 writer->SetInputData(data_set);
 //writer->SetDataModelToBinary();
 writer->SetDataModeToAscii();
 writer->Write();
 
}


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
 //double time_step_size = 0.001; // years
 double time_step_size = 0.1; // years
 double current_time = initial_time; // years
 
 // Output the initial data to screen
 std::cout.precision(8);
 std::cout << "t: " << current_time
           << "\t" << y[0][0] << "\t" << y[6][0] << "\t" << y[12][0] << "\t" << y[18][0] << std::endl;
 
 // ----------------------------------------------------------------
 // Integrator initialisation [END]
 // ----------------------------------------------------------------

 unsigned output_file_index = 0;
 // Initial output
 std::ostringstream output_filename;
 output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << output_file_index++;
 output_particles(0.0, y, output_filename);
 
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
   
   // Output to file
   std::ostringstream output_filename;
   output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << output_file_index++;
   output_particles(current_time, y, output_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete integrator;
 integrator = 0;
 
 // Finalise chapcom
 finalise_chapchom();

 return 0;
 
}

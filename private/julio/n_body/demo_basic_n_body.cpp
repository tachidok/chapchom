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
#include "../../../src/time_steppers/cc_RK4_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"

#include "../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"
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

void add_particles_to_vtk_data_set(CCData<double> &particles_data,
                                   vtkSmartPointer<vtkPoints> &data_points,
                                   vtkSmartPointer<vtkUnstructuredGrid> &data_set)
{
 const unsigned n_data_per_particle = 6;
 const int n_particles = particles_data.n_values()/n_data_per_particle;
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
 // An array to store the particles masses
 vtkSmartPointer<vtkDoubleArray> masses = vtkSmartPointer<vtkDoubleArray>::New();
 masses->SetNumberOfComponents(1);
 masses->SetNumberOfTuples(n_particles);
 masses->SetName("Masses");

 // Temporal vector to extract data
 double pos[3];
 double vel[3];
 double mass[1];
 int global_id = 0;
 // Loop through particles data
 for (unsigned i = 0; i < n_particles*n_data_per_particle; i+=n_data_per_particle)
  {
   // Position
   pos[0] = particles_data(i,0);
   pos[1] = particles_data(i+2,0);
   pos[2] = particles_data(i+4,0);
   data_points->SetPoint(global_id, pos);
   
   // IDs
   ids->InsertValue(global_id, global_id);
   
   // Velocity
   vel[0] = particles_data(i+1,0);
   vel[1] = particles_data(i+3,0);
   vel[2] = particles_data(i+5,0);
   velocity->InsertTuple(global_id, vel);
   
   mass[0] = global_id;
   masses->InsertTuple(global_id, mass);
   
   global_id++;
  }
 
 // Add particles data to data set
 data_set->GetPointData()->AddArray(ids);
 //data_set->GetPointData()->AddArray(radius);
 //data_set->GetPointData()->AddArray(position);
 data_set->GetPointData()->AddArray(velocity);
 data_set->GetPointData()->AddArray(masses);
}

void output_particles(double time,
                      CCData<double> &particles_data,
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
 const int n_points = particles_data.n_values()/6;
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

/// This class implements inherits from the ACIVPForODEs class, we
/// implement specific functions to solve the n body problem
class CCNBodyProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CCNBodyProblem(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt)
  : ACIVPForODEs(odes_pt, time_stepper_pt)
 {
  
 }
 
 /// Destructor
 ~CCNBodyProblem()
 {
  
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
  // Initial conditions for 1st body
  u(0,0) = 0.0; // x-position
  u(1,0) = 0.0; // x-velocity
  u(2,0) = 0.0; // y-position
  u(3,0) = 0.0; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.0; // x-position
  u(7,0) = -5.0; // x-velocity
  u(8,0) = 5.2; // y-position
  u(9,0) = -2.5; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
#if 0
  // Initial conditions for 3rd body
  u(12,0) = -4.503; // x-position
  u(13,0) = -1.38; // x-velocity
  u(14,0) = 2.6; // y-position
  u(15,0) = -2.39; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
  // Initial conditions for 4th body
  u(18,0) = 4.503; // x-position
  u(19,0) = -1.38; // x-velocity
  u(20,0) = 2.6; // y-position
  u(21,0) = 2.39; // y-velocity
  u(22,0) = 0.0; // z-position
  u(23,0) = 0.0; // z-velocity
#endif // #if 0
#if 1
  // Initial conditions for 3rd body
  u(12,0) = -0.5; // x-position
  u(13,0) = -2.5; // x-velocity
  u(14,0) = 5.0; // y-position
  u(15,0) = -1.25; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
  // Initial conditions for 4th body
  u(18,0) = 0.5; // x-position
  u(19,0) = -2.5; // x-velocity
  u(20,0) = 5.4; // y-position
  u(21,0) = 1.25; // y-velocity
  u(22,0) = 0.0; // z-position
  u(23,0) = 0.0; // z-velocity 
#endif // #if 1
  
  // Document initial state
  complete_problem_setup();
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem setup (call
 // set_initial_conditions(), set_boundary_conditions() and document
 // the initial problem configuration)
 void complete_problem_setup()
 {
  std::ostringstream output_filename;
  output_filename << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << Output_file_index++;
  output_particles(Time, (*U_pt), output_filename);
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename)
 {
  output_particles(Time, (*U_pt), output_filename);
  
  // Output
  std::cout.precision(8);
  std::cout << "t: " << Time
            << "\t" << U_pt->value(0) << "\t" << U_pt->value(6) << "\t" << U_pt->value(12) << "\t" << U_pt->value(18) << std::endl;
  
 }
 
protected:
 
 // The set of actions to be performed after a time stepping
 void actions_after_time_stepping() { }
 
}; // class CCNBodyProblem

// ==================================================================
// ==================================================================
// ==================================================================
// Main function
// ==================================================================
// ==================================================================
// ==================================================================
int main(int argc, char *argv[])
{
 
 // -----------------------------------------------------------------
 // Instantiation of the problem
 // -----------------------------------------------------------------
 CCODEsBasicNBody odes(4);
 
 odes.set_odes_parameters();
 
 // ----------------------------------------------------------------
 // Time stepper
 // ----------------------------------------------------------------
 // Create the factory for the time steppers (integration methods)
 //CCFactoryTimeStepper<CCMatrixArmadillo<double>, CCVectorArmadillo<double> > factory_time_stepper;
 CCFactoryTimeStepper<CCMatrix<double>, CCVector<double> > factory_time_stepper;
 // Create an instance of the integration method
 //ACTimeStepper *time_stepper_pt =
 // factory_time_stepper.create_time_stepper("Euler");
 //ACTimeStepper *time_stepper_pt =
 //  factory_time_stepper.create_time_stepper("RK4"); 
 ACTimeStepper *time_stepper_pt =
  factory_time_stepper.create_time_stepper("BDF1");
 
 // Create an instance of the problem
 CCNBodyProblem n_body_problem(&odes, time_stepper_pt);
 
 // Prepare time integration data
 const double initial_time = 0.0; // years
 const double final_time = 10.0; // years
 const unsigned n_time_steps = 1000;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 n_body_problem.time() = initial_time;
 
 // Initial time step
 n_body_problem.time_step() = (final_time - initial_time) / n_time_steps; // years
 
 // Set initial conditions
 n_body_problem.set_initial_conditions();
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   n_body_problem.unsteady_solve();
   
   // Update time of the problem
   n_body_problem.time()+=n_body_problem.time_step();
   
   // Check whether we have reached the final time
   if (n_body_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   // Output to file
   std::ostringstream output_filename;
   output_filename
    << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << n_body_problem.output_file_index()++;
   
   n_body_problem.document_solution(output_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


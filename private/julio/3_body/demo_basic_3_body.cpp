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
// Time-stepper methods
#include "../../../src/time_steppers/cc_euler_method.h"
#include "../../../src/time_steppers/cc_runge_kutta_4_method.h"
#include "../../../src/time_steppers/cc_backward_euler_method.h"

// Matrices representations
#include "../../../src/matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../../../src/matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

// Base class for the concrete problem
#include "../../../src/problem/ac_ivp_for_odes.h"
// Odes for N body problem
#include "cc_odes_basic_3_body.h"

// Include the VTK libraries to generate the output
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>

#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkPointData.h>

//#define EIGHT_SHAPE_SOLUTION
#define BODY_AT_CENTER_SOLUTION

using namespace chapchom;

// ==================================================================
// Functions for VTK output
// ==================================================================
void add_time_to_vtk_data_set(Real time,
                              vtkSmartPointer<vtkUnstructuredGrid> &data_set)
{
 // Add time stamp for the current file
 vtkSmartPointer<vtkDoubleArray> array = vtkSmartPointer<vtkDoubleArray>::New();
 array->SetName("TIME");
 array->SetNumberOfTuples(1);
 array->SetTuple1(0, time);
 data_set->GetFieldData()->AddArray(array);
}

void add_particles_to_vtk_data_set(CCData<Real> &particles_data,
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
 Real pos[3];
 Real vel[3];
 Real mass[1];
 int global_id = 0;
 // Loop through particles data
 for (unsigned i = 0; i < n_particles*n_data_per_particle; i+=n_data_per_particle)
  {
   // Position
   pos[0] = particles_data(i,0);
   pos[1] = particles_data(i+2,0);
   pos[2] = particles_data(i+4,0);
   std::cout << "POS:" << pos[0] << "," << pos[1] << "," << pos[2] << std::endl;
   data_points->SetPoint(global_id, pos);
   
   // IDs
   ids->InsertValue(global_id, global_id);
   
   // Velocity
   vel[0] = particles_data(i+1,0);
   vel[1] = particles_data(i+3,0);
   vel[2] = particles_data(i+5,0);
   std::cout << "VEL:" << vel[0] << "," << vel[1] << "," << vel[2] << std::endl;
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

void output_particles(Real time,
                      CCData<Real> &particles_data,
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

/// This class inherits from the ACIVPForODEs class, we implement
/// specific functions to solve the 3 body problem
class CC3BodyProblem : public virtual ACIVPForODEs
{
  
public:
 
 /// Constructor
 CC3BodyProblem(ACODEs *odes_pt, ACTimeStepper *time_stepper_pt, std::ostringstream &output_filename)
  : ACIVPForODEs(odes_pt, time_stepper_pt),
    Output_filename(output_filename.str())
 {
  std::ostringstream output_complete_filename;
  output_complete_filename << Output_filename.str() << ".dat";
  Output_file.open((output_complete_filename.str()).c_str()); 
 }
 
 /// Destructor
 ~CC3BodyProblem()
 {
  Output_file.close();
 }
 
 // Set initial conditions
 void set_initial_conditions()
 {
#ifdef BODY_AT_CENTER_SOLUTION 
  // Body at the center and two others in elliptic orbitis
  
  // Initial conditions for 1st body
  u(0,0) = 0.0; // x-position
  u(1,0) = 0.0 ; // x-velocity
  u(2,0) = 0.0; // y-position
  u(3,0) = 0.0; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = -5.0; // x-position
  u(7,0) = 0.0; // x-velocity
  u(8,0) = 0.0; // y-position
  u(9,0) = -1.0; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = 5.0; // x-position
  u(13,0) = 0.0; // x-velocity
  u(14,0) = 0.0; // y-position
  u(15,0) = 1.0; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity
#endif // #ifdef BODY_AT_CENTER_SOLUTION 
  
#ifdef EIGHT_SHAPE_SOLUTION
  // An infinity/eight shape movement
  
  // r1(0) = - r3(0) = (-0.97000436, 0.24308753); r2(0) = (0,0); v1(0) = v3(0) = (0.4662036850, 0.4323657300); v2(0) = (-0.93240737, -0.86473146).
  
  // The values are obtained from Chenciner & Montgomery (2000). Check
  // the Wikipedia page for the initial conditions in the references
  // https://en.wikipedia.org/wiki/Three-body_problem
  
  // Initial conditions for 1st body
  u(0,0) = -0.97000436; // x-position
  u(1,0) = 0.4662036850; // x-velocity
  u(2,0) = 0.24308753; // y-position
  u(3,0) = 0.4323657300; // y-velocity
  u(4,0) = 0.0; // z-position
  u(5,0) = 0.0; // z-velocity
  // Initial conditions for 2nd body
  u(6,0) = 0.0; // x-position
  u(7,0) = -0.93240737; // x-velocity
  u(8,0) = 0.0; // y-position
  u(9,0) = -0.86473146; // y-velocity
  u(10,0) = 0.0; // z-position
  u(11,0) = 0.0; // z-velocity
  // Initial conditions for 3rd body
  u(12,0) = 0.97000436; // x-position
  u(13,0) = 0.4662036850; // x-velocity
  u(14,0) = -0.24308753; // y-position
  u(15,0) = 0.4323657300; // y-velocity
  u(16,0) = 0.0; // z-position
  u(17,0) = 0.0; // z-velocity 
#endif // #ifdef EIGHT_SHAPE_SOLUTION
 }
 
 // Set boundary conditions
 void set_boundary_conditions() { }
 
 // A helper function to complete the problem setup
 void complete_problem_setup()
 {
  CCODEsBasic3Body *odes_pt = dynamic_cast<CCODEsBasic3Body *>(ODEs_pt);
  if (odes_pt==NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "It was not possible to dynamic cast the ODEs to the CCODEsBasic3Body ODEs class\n"
                  << "and residual computation."
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
#ifdef BODY_AT_CENTER_SOLUTION 
  // Set masses and gravity
  odes_pt->m(0) = 10.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef BODY_AT_CENTER_SOLUTION
  
#ifdef EIGHT_SHAPE_SOLUTION
  // Set masses and gravity
  odes_pt->m(0) = 1.0;
  odes_pt->m(1) = 1.0;
  odes_pt->m(2) = 1.0;
  
  odes_pt->g(0) = -1.0;
  odes_pt->g(1) = -1.0;
  odes_pt->g(2) = -1.0;
#endif // #ifdef EIGHT_SHAPE_SOLUTION
 }
 
 // Document the solution
 void document_solution(std::ostringstream &output_filename)
 {
  output_particles(Time, (*U_pt), output_filename);
  
  // Output
  std::cout.precision(8);
  std::cout << "t: " << Time
            << "\t" << U_pt->value(0) << "\t" << U_pt->value(2) << "\t" << U_pt->value(6) << "\t" << U_pt->value(8) << "\t" << U_pt->value(12) << "\t" << U_pt->value(14) << std::endl;
  
  // Document raw data
  // t,
  // x_1, vx_1, y_1, vy_1, z_1, vz_1,
  // x_2, vx_2, y_2, vy_2, z_2, vz_2,
  // x_3, vx_3, y_3, vy_3, z_3, vz_3
  Output_file << Time << "\t"
              << u(0) << "\t" << u(1) << "\t" << u(2) << "\t" << u(3) << "\t" << u(4) << "\t" << u(5) << "\t"
              << u(6) << "\t" << u(7) << "\t" << u(8) << "\t" << u(9) << "\t" << u(10) << "\t" << u(11) << "\t"
              << u(12) << "\t" << u(13) << "\t" << u(14) << "\t" << u(15) << "\t" << u(16) << "\t" << u(17) <<  std::endl;
  
 }
 
protected:
 
 // The output file
 std::ostringstream Output_filename;
 
 // The output file
 std::ofstream Output_file;
 
}; // class CC3BodyProblem

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
 CCODEsBasic3Body odes(3);
 
 // ----------------------------------------------------------------
 // Time stepper
 // ----------------------------------------------------------------
 // Create the factory for the time steppers (integration methods)
 CCFactoryTimeStepper<CCMatrixArmadillo<Real>, CCVectorArmadillo<Real> > factory_time_stepper;
 //CCFactoryTimeStepper<CCMatrix<Real>, CCVector<Real> > factory_time_stepper;
 // Create an instance of the integration method
 //ACTimeStepper *time_stepper_pt =
 //  factory_time_stepper.create_time_stepper("Euler");
 ACTimeStepper *time_stepper_pt =
  factory_time_stepper.create_time_stepper("RK4"); 
 //ACTimeStepper *time_stepper_pt =
 //factory_time_stepper.create_time_stepper("BDF1");

 // ----------------------------------------------------------------
 // Prepare the output file
 // ----------------------------------------------------------------
 std::ostringstream raw_output_filename;
 raw_output_filename << "RESLT/raw_output";
 
 // Create an instance of the problem
 CC3BodyProblem three_body_problem(&odes, time_stepper_pt, raw_output_filename);
 
 // Prepare time integration data
 const Real initial_time = 0.0;
 const Real final_time = 10.0;
 const Real time_step = 0.01;
 
 // ----------------------------------------------------------------
 // Configure problem
 // ----------------------------------------------------------------
 // Initial time
 three_body_problem.time() = initial_time;
 
 // Initial time step
 three_body_problem.time_step() = time_step;
 
 // Set initial conditions
 three_body_problem.set_initial_conditions();
 
 // Complete setup
 three_body_problem.complete_problem_setup();
 
 // Output to file
 std::ostringstream output_filename;
 output_filename
  << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << three_body_problem.output_file_index()++;
 
 // Document initial configuration
 three_body_problem.document_solution(output_filename);
 
 // Flag to indicate whether to continue processing
 bool LOOP = true;
 
 // Main LOOP (loop until reaching final time)
 while(LOOP)
  {
   // Performs an unsteady solve
   three_body_problem.unsteady_solve();
   
   // Update time of the problem
   three_body_problem.time()+=three_body_problem.time_step();
   
   // Check whether we have reached the final time
   if (three_body_problem.time() >= final_time)
    {
     LOOP = false;
    }
   
   // Output to file
   std::ostringstream ioutput_filename;
   ioutput_filename
    << "./RESLT/soln" << "_" << std::setfill('0') << std::setw(5) << three_body_problem.output_file_index()++;
   
   three_body_problem.document_solution(ioutput_filename);
   
  } // while(LOOP)
 
 std::cout << "[FINISHING UP] ... " << std::endl;
 
 // Free memory
 delete time_stepper_pt;
 time_stepper_pt = 0;
 
 return 0;
 
}


#include "ac_mesh_free_problem.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor
 // ===================================================================
 ACMeshFreeProblem::ACMeshFreeProblem()
  : ACProblem(),
    Time_stepper_pt(NULL)
 {
  // TODO We need to allocate memory for U_pt /// JULIO
  
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 ACMeshFreeProblem::~ACMeshFreeProblem()
 {
  if (U_pt != NULL)
   {
    // Free memory
    delete U_pt;
    // Set pointer to null
    U_pt = NULL;
   }
  
 }
 
 // ===================================================================
 /// Problem steady solve
 // ===================================================================
 void ACMeshFreeProblem::steady_solve()
 {
  // Call actions before newton solve
  actions_before_newton_solve();
  
  newton_solve();
  
  while(NO_CONVERGENCE)
   {
    // Call the newton solver
    newton_solve();
    
   }
  
  // Call actions after newton solve
  actions_after_newton_solve();
 }
 
 // ===================================================================
 /// Problem unsteady solve
 // ===================================================================
 void ACMeshFreeProblem::unsteady_solve()
 {
  // We need to check whether a Time Stepper has been set for the
  // unsteady solveJacobian computation strategy has been set
  if (Time_stepper_pt == NULL)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "You need to specify a Time_stepper to approximate\n"
                  << "a solution for the time dependent problem.\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);  
   }
  
  // Perform an steady solve
  steady_solve();
  
  // Call actions before time stepping
  actions_before_time_stepping();
  
  // Advance solution in time
  Time_stepper_pt->time_step((*ODEs_pt), Time_step, Time, (*U_pt));
  
  // Call actions after time stepping
  actions_after_time_stepping();
  
 }
 
 // ===================================================================
 /// In charge of creating the nodes considering the geometry of the
 /// domain
 // ===================================================================
 void ACMeshFreeProblem::create_nodes()
 {
  // --------------------------------------------------------------
  // Domain specification
  // --------------------------------------------------------------
  // TODO: Create a DOMAIN/GEOMETRIC_DOMAIN (mesh?) type class JULIO
  
  // Dimension of the problem
  const unsigned dim = 2;
  
  // Specify the one-dimensional lenght of the domain
  const unsigned L = 1.0;
  
  // --------------------------------------------------------------
  // Create and give position to nodes
  // --------------------------------------------------------------
  // Nodes per dimension
  const unsigned n_nodes_per_dim = pow(2, 4);
  // The number of nodes
  const unsigned n_nodes = pow(n_nodes_per_dim, dim);
  // Distance between a pair of nodes
  const Real h = L / (Real)(n_nodes_per_dim - 1);
  
  // Create the vector of nodes/resize
  Nodes_pt.resize(n_nodes);
  
  // Number of variables stored in each node
  const unsigned n_variables = 1;
  
  // Create nodes
  for (unsigned i = 0; i < n_nodes; i++)
   {
    Nodes_pt[i] = new CCNode<Real>(dim, n_variables);
   }
  
  // Assign positions (internal nodes)
  unsigned kk = 0;
  for (unsigned i = 1; i < n_nodes_per_dim - 1; i++)
   {
    const Real position_i = i*h;
    for (unsigned j = 1; j < n_nodes_per_dim - 1; j++)
     {
      const Real position_j = j*h;
      Nodes_pt[kk]->set_position(position_i, 0);
      Nodes_pt[kk]->set_position(position_j, 1);
      kk++;
     }
   }
  
  // Create boundary nodes
  const unsigned n_nodes_per_boundary = n_nodes_per_dim;
  // Create total number of boundary nodes
  const unsigned n_boundary_nodes = (n_nodes_per_boundary * 4) - 4;
  
  // Check whether the number of boundary nodes is the same as the
  // rest of the nodes to be created
  if (n_boundary_nodes != n_nodes - kk)
   {
    std::ostringstream error_message;
    error_message << "The number of nodes leave for creation is not the same as\n"
                  << "the number of boundary nodes to create\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // A vector of boundary nodes
  Boundary_nodes_pt.resize(n_boundary_nodes);
  // The IDs for the boundaries
  const unsigned boundary_1_id = 1;
  const unsigned boundary_2_id = 2;
  
  // Create the boundary nodes
  for (unsigned i = 0; i < n_boundary_nodes; i++)
   {
    if (i < n_nodes_per_boundary)
     {
      Boundary_nodes_pt[i] = new CCBoundaryNode<Real>(boundary_1_id, dim, n_variables);
     }
    else
     {
      Boundary_nodes_pt[i] = new CCBoundaryNode<Real>(boundary_2_id, dim, n_variables);
     }
    
    // Add the pointer of the boundary node to the vector of nodes
    Nodes_pt[kk] = Boundary_nodes_pt[i];
    kk++;
    
   }
  
  // We have two boundaries and two nodes lying on both boundaries
  Boundary_nodes_pt[0]->add_to_boundary(boundary_2_id);
  Boundary_nodes_pt[n_nodes_per_boundary-1]->add_to_boundary(boundary_2_id);
  
  // Assign positions
  kk = 0;
  for (unsigned i = 0; i < n_nodes_per_dim; i++)
   {
    const Real position_i = i*h;
    // (x, 0)
    Boundary_nodes_pt[i]->set_position(position_i, 0);
    Boundary_nodes_pt[i]->set_position(0, 1);
    // (x, 1)
    Boundary_nodes_pt[i+n_nodes_per_dim]->set_position(position_i, 0);
    Boundary_nodes_pt[i+n_nodes_per_dim]->set_position(1, 1);
    // (1, y)
    Boundary_nodes_pt[i+n_nodes_per_dim*2]->set_position(1, 0);
    Boundary_nodes_pt[i+n_nodes_per_dim*2]->set_position(position_i, 1);
    // (0, y)
    Boundary_nodes_pt[i+n_nodes_per_dim*3]->set_position(0, 0);
    Boundary_nodes_pt[i+n_nodes_per_dim*3]->set_position(position_i, 1);
    
   }
  
 }
 
#ifdef CHAPCHOM_PANIC_MODE
 // ===================================================================
 /// Output nodes information (for debugging purposes)
 // ===================================================================
 void ACMeshFreeProblem::output_nodes_information(std::ostringstream &output_filename)
 {
  // --------------------------------------------------------------
  // Output nodes positions
  // --------------------------------------------------------------
  std::ofstream nodes_file((output_filename.str()).c_str());
  const unsigned n = n_nodes();
  for (unsigned i = 0; i < n; i++)
   {
    Nodes_pt[i]->output(nodes_file, true);
   }
  // Close interior nodes file
  nodes_file.close();
 }
 
 // ===================================================================
 /// Output boundary nodes information (for debugging purposes)
 // ===================================================================
 void ACMeshFreeProblem::output_boundary_nodes_information(std::ostringstream &output_filename)
 {
  // Boundary nodes
  std::ofstream boundary_nodes_file((output_filename.str()).c_str());
  const unsigned nb = n_boundary_nodes();
  for (unsigned i = 0; i < nb; i++)
   {
    Boundary_nodes_pt[i]->output_boundary_position_and_value(boundary_nodes_file);
   }
  // Close boundary nodes file
  boundary_nodes_file.close();
 }
#endif // #ifdef CHAPCHOM_PANIC_MODE
 
 // ===================================================================
 /// Get access to the specific node
 // ===================================================================
 CCNode<Real> *ACMeshFreeProblem::node(const unsigned i)
 {
  // We need to check whether the nodes vector has nodes in it
  const unsigned n = n_nodes();
  if (n == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The nodes_pt vector has zero nodes\n"
                  << "First you need to create the vector of nodes in order\n"
                  << "to access its components, to do so call or implement\n"
                  << "the method 'create_nodes()'.\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }

  if (i >= n)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The node number you are trying to access is out of the\n"
                  << "scope of the current vector of nodes.\n"
                  << "Number of nodes in the Nodes_pt vector: [" << n <<"]\n"
                  << "Node number you want to get access: [" << i << "]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }

  return Nodes_pt[i];
  
 }
 
}


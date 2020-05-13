#include "ac_mesh_free_problem.tpl.h"

namespace chapchom
{
 
 // ===================================================================
 /// Constructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::ACMeshFreeProblem()
  : ACProblem(),
    Time_stepper_pt(NULL),
    Free_memory_for_linear_solver(false)
 {
  // Set default linear solver
  set_default_linear_solver();  
  
  // TODO We need to allocate memory for U_pt /// JULIO???? Really,
  // why not to store the solution in the Nodes_pt
  
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::~ACMeshFreeProblem()
 {
  // Performs clean up of linear solver
  clean_up_linear_solver();
 }
 
 // ===================================================================
 /// Clean up linear solver
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::clean_up_linear_solver()
 {
  // Check whether we should free the memory associated for the linear
  // solver
  if (Free_memory_for_linear_solver)
   {
    // Free memory
    delete Linear_solver_pt;
    Linear_solver_pt = 0;
    
    // Memory has been already free
    Free_memory_for_linear_solver = false;
    
   }
  
 }
 
 // ===================================================================
 /// Sets default configuration
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::set_default_linear_solver()
 {
  // Cleans up linear solver
  clean_up_linear_solver();
  
  // Create a factor for the linear solver
  CCFactoryLinearSolver<MAT_TYPE, VEC_TYPE> factory_linear_solver;
  
  // Create the linear solver
  Linear_solver_pt = factory_linear_solver.create_linear_solver();
  
  // In charge of free the memory for linear solver
  Free_memory_for_linear_solver = true;
  
 }
 
 // ===================================================================
 /// Set the Linear solver
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::
 set_linear_solver(ACLinearSolver<MAT_TYPE, VEC_TYPE> *linear_solver_pt)
 {
  // Free memory for previous linear solver
  clean_up_linear_solver();
  
  // Assign the new linear solver
  Linear_solver_pt = linear_solver_pt;
  
  // An external new linear solver has been set, then we no longer
  // need to worry about freeing its allocated memory
  Free_memory_for_linear_solver = false;
 }
 
 // ===================================================================
 /// Problem steady solve
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::steady_solve()
 {
  // Call actions before newton solve
  actions_before_newton_solve();
  
  //compute_residual();
  
  while(NO_CONVERGENCE)
   {
    // Call newton solve
    newton_solve();
    
    // recompute_residual()
    
   }
  
  // Call actions after newton solve
  actions_after_newton_solve();
 }
 
 // ===================================================================
 /// Problem unsteady solve
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::unsteady_solve()
 {
#ifdef CHAPCHOM_PANIC_MODE
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
#endif // #ifdef CHAPCHOM_PANIC_MODE
  
  // This feature has not been tested and it possibly wont work at all, 
  // please carefully implement any necessary changes
  
  // Error message
  std::ostringstream error_message;
  error_message << "This feature has not been fully tested\n"
                << "Please create a demo driver that uses more than one\n"
                << "time stepper and implement the necessary changes to\n"
                << "the code.\n"
                << std::endl;
  throw ChapchomLibError(error_message.str(),
                         CHAPCHOM_CURRENT_FUNCTION,
                         CHAPCHOM_EXCEPTION_LOCATION);
  
  // Perform an steady solve
  steady_solve();
  
  // Call actions before time stepping
  actions_before_time_stepping();
  
  // We need to get a vector of the u variables in the nodes and then
  // send it as part of the vector where the informatino will be
  // stored

  // ****************************************************************
  // ****************************************************************
  // Advance solution in time
  // ****************************************************************
  // ****************************************************************
  //Time_stepper_pt->time_step((*ODEs_pt), Time_step, Time, (*U_pt));
  
  // Call actions after time stepping
  actions_after_time_stepping();
  
 }
 
 // ===================================================================
 /// In charge of creating the nodes considering the geometry of the
 /// domain
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::create_nodes()
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
 
 // ===================================================================
 /// Get access to i-th node
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 const CCNode<Real> *ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::node_pt(const unsigned i)
 {
#ifdef CHAPCHOM_PANIC_MODE
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
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Nodes_pt[i];
 }

 // ===================================================================
 /// Get access to i-th boundary node
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 const CCBoundaryNode<Real> *ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::boundary_node_pt(const unsigned i)
 {
#ifdef CHAPCHOM_PANIC_MODE
  // We need to check whether the nodes vector has nodes in it
  const unsigned n = n_boundary_nodes();
  if (n == 0)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The boundary_nodes_pt vector has zero nodes\n"
                  << "First you need to create the vector of boundary nodes in order\n"
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
    error_message << "The boundary node number you are trying to access is out of the\n"
                  << "scope of the current vector of boundary nodes.\n"
                  << "Number of boundary nodes in the Boundary_nodes_pt vector: [" << n <<"]\n"
                  << "Boundary node number you want to get access: [" << i << "]\n"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  return Boundary_nodes_pt[i];
 }
 
#ifdef CHAPCHOM_PANIC_MODE
 // ===================================================================
 /// Output nodes information (for debugging purposes)
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::output_nodes_information(std::ostringstream &output_filename)
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
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::output_boundary_nodes_information(std::ostringstream &output_filename)
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
 // Generate the interpolation matrix and the right-hand side vector
 // ===================================================================
 template<class MAT_TYPE, class VEC_TYPE>
 void ACMeshFreeProblem<MAT_TYPE, VEC_TYPE>::generate_interpolation_matrix_and_rhs_vector(std::vector<CCNode<Real> *> &center_nodes)
 {
  // Get the number of nodes and centers
  const unsigned n_node = n_nodes();
  const unsigned n_center = center_nodes.size();
  
  // Allocate memory for interpolation matrix and rhs-vector
  Interpolation_matrix.allocate_memory(n_node, n_center);
  RHS_vector.allocate_memory(n_node);
  
  // Get the dimension of the nodes and centers
  const unsigned dimension = node_pt(0)->dimension();
#ifdef CHAPCHOM_PANIC_MODE
  const unsigned tmp_dimension = center_nodes[0]->dimension();
  
  if (dimension != tmp_dimension)
   {
    // Error message
    std::ostringstream error_message;
    error_message << "The dimension of the nodes and the centers\n"
                  << "is different\n"
                  << "dim(nodes):" << dimension
                  << "\ndim(centers):" << tmp_dimension
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
#endif // #ifdef CHAPCHOM_PANIC_MODE
  
  // Loop over all nodes
  for (unsigned m = 0; m < n_node; m++)
   {
    
    // We need to check whether 
    
    // Loop over all centers
    for (unsigned n = 0; n < n_center; n++)
     {
      VEC_TYPE distance(dimension);
      // Loop over the elements of both, the node and the center
      for (unsigned k = 0; k < dimension; k++)
       {
        distance(k) = node_pt(m)->get_position(k) - center_nodes[n]->get_position(k);
       }
      
      // Get the distance
      Real r = distance.norm_2();
      
      Interpolation_matrix(m,n) = node_pt(m)->get_contribution_to_interpolation_matrix(r);
      
      // get_jacobian()
      
      // - Each RBF must add its contribution to the
      // - Jacobian/interpolation matrix part
      
      // get_residual() - Each RBF must add its contribution to the
      // RHS vector
      
      // We need to send the nodes, the interpolation matrix and the
      // RHS to the specific functions that agregates its values to
      // the matrix A (the RBF)
      
      // Here we need to choose what function of the rbf use
      if (interior node)
      Interpolation_matrix(m,n) = Lpsi(r, epsilon);
      else (boundary node)
      interpolation_matrix(m, n) = psi(r, epsilon);
     }
    
    VEC_TYPE tmp_v(dimension);
    for (unsigned k = 0; k < dimension; k++)
     {
      tmp_v(k) = node_pt(m)->get_position(k);
     }
    
    // --------------------------------------------------------------
    // Evaluate the function f() at the nodes positions 
    // --------------------------------------------------------------
    // Hero goes the RHS, the functions
    RHS_vector(m) = Lu<VEC_TYPE >(tmp_v);

    RHS_vector(m) = node_pt(m)->get_contribution_to_rhs_vector();
    
   }
  
 }
 
} // namespace chapchom

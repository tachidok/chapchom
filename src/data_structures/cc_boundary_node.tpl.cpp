// IN THIS FILE: Implementation of a concrete class to represent
// data. This is the simplest implementation

#include "cc_boundary_node.tpl.h"

namespace chapchom
{

 /// ===================================================================
 /// Constructor
 /// ===================================================================
 template<class T>
 CCBoundaryNode<T>::CCBoundaryNode(const unsigned boundary,
                                   const unsigned dimension,
                                   const unsigned n_variables,
                                   const unsigned n_history_values)
  : CCNode<T>(dimension, n_variables, n_history_values)
 {
  // Add the node to the boundary
  add_to_boundary(boundary);
 }
 
 /// ===================================================================
 /// Empty destructor
 /// ===================================================================
 template<class T>
 CCBoundaryNode<T>::~CCBoundaryNode()
 {
  
 }
 
 /// ===================================================================
 /// Add the node to the spefified boundary
 /// ===================================================================
 template<class T>
 void CCBoundaryNode<T>::add_to_boundary(const unsigned b)
 {
  Boundaries.insert(b);
 }
 
 /// ===================================================================
 /// Remove the node from an specific boundary
 /// ===================================================================
 template<class T>
 void CCBoundaryNode<T>::remove_from_boundary(const unsigned b)
 {
  // First check whether the node lies on the given boundary
  if(!is_on_boundary(b))
   {
    std::ostringstream error_message;
    error_message << "The node is not on boundary " << b << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  //Remove the boundary from the set 
  Boundaries.erase(b);
  
  //Need to delete the equivalent entry in the Boundary coordinate
  //map, if the storage has actually been allocated
  std::map<unsigned, std::vector<Real> >::iterator it = Boundary_coordinates.find(b);
  if (it != Boundary_coordinates.end())
   {
    Boundary_coordinates.erase(it);
   }
  else
   {
    std::ostringstream error_message;
    error_message << "The node is on boundary " << b << " but has no"
                  << "boundary coordinates assigned\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
 }
 
 /// ===================================================================
 /// Test whether the node is on any boundary
 /// ===================================================================
 template<class T>
 bool CCBoundaryNode<T>::is_on_boundary()
 {
  if (Boundaries.size() != 0)
   {
    return true;
   }
  
  return false;
  
 }
 
 /// ===================================================================
 /// Test whether the node is on a given boundary
 /// ===================================================================
 template<class T>
 bool CCBoundaryNode<T>::is_on_boundary(const unsigned b)
 {
  std::set<unsigned>::iterator it = Boundaries.find(b);
  if (it != Boundaries.end())
   {
    return true;
   }

  return false;
  
 }
 
 /// ===================================================================
 /// Set the boundary coordinates zeta of the node on boundary b
 /// ===================================================================
 template<class T>
 void CCBoundaryNode<T>::set_boundary_coordinates(const unsigned b, const std::vector<Real> &zeta)
 {
  // First check whether the node lies on the given boundary
  if(!is_on_boundary(b))
   {
    std::ostringstream error_message;
    error_message << "The node is not on boundary " << b << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Get the number of boundary coordinates and copy them
  const unsigned n_boundary_coordinates = zeta.size();
  Boundary_coordinates[b].resize(n_boundary_coordinates);
  for (unsigned i = 0; i < n_boundary_coordinates; i++)
   {
    Boundary_coordinates[b][i] = zeta[i];
   }
  
 }
 
 /// ===================================================================
 /// Get the boundary coordinates zeta of the node on boundary b
 /// ===================================================================
 template<class T>
 void CCBoundaryNode<T>::get_boundary_coordinates(const unsigned b, std::vector<Real> &zeta)
 {
  // First check whether the node lies on the given boundary
  if(!is_on_boundary(b))
   {
    std::ostringstream error_message;
    error_message << "The node is not on boundary " << b << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether there are boundary coordinates for this boundary
  std::map<unsigned, std::vector<Real> >::iterator it = Boundary_coordinates.find(b);
  if (it == Boundary_coordinates.end())
   {
    std::ostringstream error_message;
    error_message << "The node is on boundary " << b << " but has no"
                  << "boundary coordinates assigned\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Check whether the number of boundary coordinates matches that of
  // the output vector
  const unsigned n_boundary_coordinates = Boundary_coordinates[b].size();
  const unsigned n_output_boundary_coordinates = zeta.size();
  if (n_boundary_coordinates != n_output_boundary_coordinates)
   {
    std::ostringstream error_message;
    error_message << "The number of boundary coordinates of the output vector is\n"
                  << "not the same as the number of boundary coordinates for\n"
                  << "boundary " << b << ".\n" << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // Copy the boundary coordinates
  for (unsigned i = 0; i < n_boundary_coordinates; i++)
   {
    zeta[i] = Boundary_coordinates[b][i];
   }
  
 }
 
}

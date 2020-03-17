// IN THIS FILE: The definition of a class to represent nodes

// Check whether the class has been already defined
#ifndef CCBOUNDARYNODE_TPL_H
#define CCBOUNDARYNODE_TPL_H

#include "./cc_node.tpl.h"

namespace chapchom
{
 
 /// @class CCBoundaryNode cc_boundary_node.h
 
 /// Abstract class to represent boundary nodes
 template<class T>
  class CCBoundaryNode
 {
  
 public:
  
  /// Constructor
  CCBoundaryNode(const unsigned boundary, const unsigned dimension, const unsigned n_variables, const unsigned n_history_values);
  
  /// Empty destructor
  virtual ~CCBoundaryNode();
  
  /// Add the node to the spefified boundary
  void add_to_boundary(const unsigned b);
  
  /// Remove the node from an specific boundary
  void remove_from_boundary(const unsigned b);
  
  /// Test whether the node is on any boundary
  bool is_on_boundary();
  
  /// Test whether the node is on a given boundary
  bool is_on_boundary(const unsigned b);
  
  /// Set the boundary coordinates zeta of the node on boundary b
  void set_boundary_coordinates(const unsigned b, const std::vector<Real> &zeta);
  
  /// Get the boundary coordinates zeta of the node on boundary b
  void get_boundary_coordinates(const unsigned b, std::vector<Real> &zeta);
  
 protected:
  
  /// A set to store the boundaries where the node lies on
  std::set<unsigned> Boundaries;
  
  /// Intrinsic boundary coordiantes for a given boundary
  std::map<unsigned, std::vector<Real> > Boundary_coordinates;
  
 };
 
}

#endif // #ifndef CCBOUNDARYNODE_TPL_H

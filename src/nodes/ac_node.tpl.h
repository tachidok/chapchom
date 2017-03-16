// IN THIS FILE: The definition of an abstract class to represent
// nodes

// Check whether the class has been already defined
#ifndef ACNODE_H
#define ACNODE_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{
 
 /// @class ACNode ac_node.h
 
 // Abstract class to represent nodes
 template<class T, class DIM>
  class ACNode
 {
  
 public:
  
  // Empty constructor
  ACNode(const unsigned n_data);
  
 private:
  
  std::vector<double> x(DIM);
  std::vector<T> u;
  std::vector<bool> pin;
  
 };
 
}

#endif // #ifndef ACNODE_H

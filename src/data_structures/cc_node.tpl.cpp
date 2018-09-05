// IN THIS FILE: Implementation of a concrete class to represent
// data. This is the simplest implementation

#include "cc_node.tpl.h"

namespace chapchom
{

 // ===================================================================
 // Empty constructor
 // ===================================================================
 template<class T>
 CCNode<T>::CCNode(const unsigned dimension, const unsigned n_variables,
                   const unsigned n_history_values)
  : Dimension(dimension), N_variables(n_variables),
    N_history_values(n_history_values), X(Dimension, N_history_values),
    U(N_variables, N_history_values)
 { }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 template<class T>
 CCNode<T>::~CCNode()
 { }
 
}

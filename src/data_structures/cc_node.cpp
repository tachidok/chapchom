/// IN THIS FILE: Implementation of a concrete class to represent
/// nodes. This is the simplest implementation

#include "cc_node.h"

namespace chapchom
{

 /// ===================================================================
 /// Empty constructor
 /// ===================================================================
 CCNode::CCNode(const unsigned dimension, const unsigned n_variables,
                const unsigned n_history_values)
  : Dimension(dimension), N_variables(n_variables),
    N_history_values(n_history_values), X(Dimension, N_history_values),
    U(N_variables, N_history_values)
 { }
 
 /// ===================================================================
 /// Empty destructor
 /// ===================================================================
 CCNode::~CCNode()
 { }
 
 /// ===================================================================
 /// Output the data stored at the node (output horizontally without
 /// position by default, otherwise output vertically with position)
 /// ===================================================================
 void CCNode::output(bool output_position,
                     const unsigned t) const
 {
  // Check whether we should output positions
  if (output_position)
   {
    for (unsigned i = 0; i < this->Dimension; i++)
     {
      std::cout << X.value(i,t) << "\t";
     } // for (i < this->Dimension)
   } // if (output_position)
  
  for (unsigned i = 0; i < this->N_variables; i++)
   {
    std::cout << U.value(i,t) << "\t";
   } // for (i < this->N_variables)
  std::cout << std::endl; 
 }
 
 /// ===================================================================
 /// Output the data stored at the node to a file (output horizontally
 /// without position by default, otherwise output vertically with
 /// position)
 /// ===================================================================
 void CCNode::output(std::ofstream &outfile,
                        bool output_position,
                        const unsigned t) const
 {
  // Check whether we should output positions
  if (output_position)
   {
    for (unsigned i = 0; i < this->Dimension; i++)
     {
      outfile << X.value(i,t) << "\t";
     } // for (i < this->Dimension)
   } // if (output_position)
  
  for (unsigned i = 0; i < this->N_variables; i++)
   {
    outfile << U.value(i,t) << "\t";
   } // for (i < this->N_variables)
  outfile << std::endl;
 }
 
}

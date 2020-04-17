#ifndef CCNODEIMQPOISSON_H
#define CCNODEIMQPOISSON_H

#include "../../general/common_includes.h"
#include "../../general/utilities.h"

#include "../rbf/cc_inverse_multiquadric.h"

namespace chapchom
{
 /// A class than implements an Inverse Muliquadric RBF Node for the
 /// solution of the Poisson equation
 template<class NODE_TYPE>
  class CCNodeIMQPoisson : public virtual NODE_TYPE
 {


  ////////////////// HERE // We do not always need boundary nodes, we
  //////////////////only need boundary nodes when they are at the
  //////////////////boundary, we expect that we can create a class of
  //////////////////CCNodeIMQPoisson with the boundary features of the
  //////////////////nodes, and other class CCNodeIMQPoisson without
  //////////////////the boundary features of the node

  
 public:
  
  /// Constructor
  CCBoundaryNode(const unsigned boundary, const unsigned dimension, const unsigned n_variables, const unsigned n_history_values=1);
  
  /// Empty destructor
  virtual ~CCBoundaryNode();

  ///////////////////////*-*-*-*-*-*-*-*-*-*
  
 public:
  
  // Constructor
  CCNodeIMQPoisson();
  
  // Destructor
  virtual ~CCNodeIMQPoisson();
  
  // Laplacian psi
  const Real Lpsi(const Real r);
  
 private:
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCNodeIMQPoisson(const CCNodeIMQPoisson &copy)
   {
    BrokenCopy::broken_copy("CCNodeIMQPoisson");
   }
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCNodeIMQPoisson &copy)
   {
    BrokenCopy::broken_assign("CCNodeIMQPoisson");
   }
  
  /// The RBF
  CCInverseMultiquadric 
  
  
 };
 
}

#endif // #ifndef CCNODEIMQPOISSON_H

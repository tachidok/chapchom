#ifndef CCINVERSEMULTIQUADRICPOISSON_H
#define CCINVERSEMULTIQUADRICPOISSON_H

#include "../../general/common_includes.h"
#include "../../general/utilities.h"

#include "../rbf/cc_inverse_multiquadric.h"

namespace chapchom
{
 /// A class than implements the Inverse Muliquadric RBF for the
 /// Poisson equation
 class CCInverseMultiquadricPoisson : public virtual CCInverseMultiquadric
 {
  
 public:
  
  // Constructor
  CCInverseMultiquadricPoisson();
  
  // Destructor
  virtual ~CCInverseMultiquadricPoisson();
  
  // Laplacian psi
  const Real Lpsi(const Real r);
  
 private:
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCInverseMultiquadricPoisson(const CCInverseMultiquadricPoisson &copy)
   {
    BrokenCopy::broken_copy("CCInverseMultiquadricPoisson");
   }
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCInverseMultiquadricPoisson &copy)
   {
    BrokenCopy::broken_assign("CCInverseMultiquadricPoisson");
   }
  
 };
 
}

#endif // #ifndef CCINVERSEMULTIQUADRICPOISSON_H

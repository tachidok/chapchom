#ifndef CCINVERSEMULTIQUADRIC_H
#define CCINVERSEMULTIQUADRIC_H

#include "../../general/common_includes.h"
#include "../../general/utilities.h"

#include "ac_radial_base_function.h"

namespace scicellxx
{
 /// A class than implements the Inverse Muliquadric RBF
 class CCInverseMultiquadric : public virtual ACRadialBaseFunction
 {
  
 public:
  
  /// Constructor
  CCInverseMultiquadric(Real epsilon = 9.0);
  
  /// Destructor
  virtual ~CCInverseMultiquadric();
  
  /// Radial function
  const Real psi(const Real r);
  
  /// Read-only version
  Real epsilon() const {return Epsilon;}

  /// Write-access
  Real &epsilon() {return Epsilon;}
  
 private:
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCInverseMultiquadric(const CCInverseMultiquadric &copy)
   {
    BrokenCopy::broken_copy("CCInverseMultiquadric");
   }
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCInverseMultiquadric &copy)
   {
    BrokenCopy::broken_assign("CCInverseMultiquadric");
   }
  
 protected:

  /// Epsilon
  Real Epsilon;
  
 };
 
}

#endif // #ifndef CCINVERSEMULTIQUADRIC_H

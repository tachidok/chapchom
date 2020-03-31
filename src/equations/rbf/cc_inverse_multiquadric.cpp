#include "cc_inverse_multiquadric.h"

namespace chapchom
{
 
 // ===================================================================
 /// Constructor
 // ===================================================================
 CCInverseMultiquadric::CCInverseMultiquadric(Real epsilon)
  : Epsilon(epsilon)
 {
  
 }
 
 // ===================================================================
 /// Destructor
 // ===================================================================
 CCInverseMultiquadric::~CCInverseMultiquadric()
 {
  
 }
 
 // ===================================================================
 /// Radial function
 // ===================================================================
 const Real CCInverseMultiquadric::psi(const Real r)
 {
  return std::exp(-((r*Epsilon)*(r*Epsilon)));
 }
 
}

#include "cc_inverse_multiquadric_poisson.h"

namespace scicellxx
{
 
 // ===================================================================
 // Constructor
 // ===================================================================
 CCInverseMultiquadricPoisson::CCInverseMultiquadricPoisson()
 {
  
 }
 
 // ===================================================================
 // Destructor
 // ===================================================================
 CCInverseMultiquadricPoisson::~CCInverseMultiquadricPoisson()
 {
  
 }

// ===================================================================
 /// Radial function
 // ===================================================================
 const Real CCInverseMultiquadricPoisson::Lpsi(const Real r)
 {
  const Real er2 = (epsilon*r)*(epsilon*r);
  return 4*epsilon*epsilon*std::exp(-er2)*(er2-1);
 }
 
}

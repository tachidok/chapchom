#ifndef CCCHENODES_H
#define CCCHENODES_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"
// The class used to store the values of u and dudt
#include "../../../src/data_structures/cc_data.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/data_structures/ac_odes.h"

namespace chapchom
{

 /// \class CCChenODEs cc_chen_odes.h
    
 /// This class implements the Chen ODEs
 ///
 /// \frac{du_{1}}{dt} = a*(u_{2} - u_{1})
 /// \frac{du_{2}}{dt} = (c-a)*u_{1} - u_{1}*u_{3} + c*u_{2}
 /// \frac{du_{3}}{dt} = u_{1}*u_{2} - b*u_{3}
 class CCChenODEs : public virtual ACODEs
 {
 
 public:
  
  /// Constructor
  CCChenODEs(Real _a, Real _b, Real _c);
  
  /// Empty destructor
  virtual ~CCChenODEs();
  
  /// Evaluates the system of odes at time 't', using the history
  /// values of u at index k
  void evaluate_derivatives(const Real t, CCData &u, CCData &dudt, const unsigned k = 0);
  
 protected:
  
  // Specific ODEs parameters
  // ------------------------------------
  Real a;
  Real b;
  Real c;
  
 };
 
}

#endif // #ifndef CCCHENODES_H

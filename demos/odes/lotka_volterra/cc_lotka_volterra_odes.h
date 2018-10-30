#ifndef CCODESLOTKAVOLTERRAODES_H
#define CCODESLOTKAVOLTERRAODES_H

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

 /// \class CCLotkaVolterraODEs cc_lotka_volterra_odes.h
    
 /// This class implements the simplest version of the Lotka-Volterra
 /// equations
 ///
 /// \frac{du_{1}}{dt} = a*u_{1} - b*u_{1}*u_{2}
 /// \frac{du_{2}}{dt} = -c*u_{2} + d*u_{1}*u_{2}
 class CCLotkaVolterraODEs : public virtual ACODEs
 {
 
 public:
  
  /// Constructor
  CCLotkaVolterraODEs(Real _a, Real _b, Real _c, Real _d);
  
  /// Empty destructor
  virtual ~CCLotkaVolterraODEs();
  
  /// Evaluates the system of odes at time 't', using the history
  /// values of u at index k
  void evaluate(const Real t, CCData<Real> &u, CCData<Real> &dudt, const unsigned k = 0);
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCLotkaVolterraODEs(const CCLotkaVolterraODEs &copy)
  : ACODEs(copy)
  {
   BrokenCopy::broken_copy("CCLotkaVolterraODEs");
  }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCLotkaVolterraODEs &copy)
   {
    BrokenCopy::broken_assign("CCLotkaVolterraODEs");
   }
  
  // Specific ODEs parameters
  // ------------------------------------
  // The prey grow rate
  Real a;
  // The predator-prey interaction rate on the prey death
  Real b;
  // The predator death rate
  Real c;
  // The predator-prey interaction rate on the predator grow
  Real d;
  
 };
 
}

#endif // #ifndef CCODESLOTKAVOLTERRAODES_H

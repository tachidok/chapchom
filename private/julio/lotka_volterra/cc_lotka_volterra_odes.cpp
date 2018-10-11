/** \file This file implements the CCLotkaVolterraODEs class
 */
#include "cc_lotka_volterra_odes.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes.
 // ===================================================================
 CCLotkaVolterraODEs::CCLotkaVolterraODEs(Real _a, Real _b,
                                          Real _c, Real _d)
  : ACODEs(2)
 {  
  // Configure parameters
  a = _a;
  b = _b;
  c = _c;
  d = _d;
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCLotkaVolterraODEs::~CCLotkaVolterraODEs()
 { }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t".
 // ===================================================================
 void CCLotkaVolterraODEs::evaluate(const Real t,
                                    CCData<Real> &u,
                                    CCData<Real> &dudt)
 {
  // -----------------
  // u(0) Number of prey
  // u(1) Number of predators
  // -----------------
  // dudt(0) Rate of change or prey with respect to time
  // dudt(1) Rate of change of predators with respecto to time
  
  /// \frac{du_{1}}{dt} = a*u_{1} - b*u_{1}*u_{2}
  /// \frac{du_{2}}{dt} = -c*u_{2} + d*u_{1}*u_{2}
  dudt(0) = a*u(0) - b*u(0)*u(1);
  dudt(1) = -c*u(1) + d*u(0)*u(1);
  
 }
 
}

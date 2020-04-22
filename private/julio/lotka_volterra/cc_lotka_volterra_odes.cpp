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
 void CCLotkaVolterraODEs::evaluate_derivatives(const Real t,
                                                CCData &u,
                                                CCData &dudt,
                                                const unsigned k)
 {
  // -----------------
  // u(0,k) Number of prey at history index k
  // u(1,k) Number of predators at history index k
  // -----------------
  // dudt(0) Rate of change or prey with respect to time
  // dudt(1) Rate of change of predators with respecto to time
  
  /// \frac{du_{1}}{dt} = a*u_{1} - b*u_{1}*u_{2}
  /// \frac{du_{2}}{dt} = -c*u_{2} + d*u_{1}*u_{2}
  dudt(0) = a*u(0,k) - b*u(0,k)*u(1,k);
  dudt(1) = -c*u(1,k) + d*u(0,k)*u(1,k);
  
 }
 
}

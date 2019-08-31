/** \file This file implements the CCChenODEs class
 */
#include "cc_chen_odes.h"

namespace chapchom
{
 // ===================================================================
 // Constructor, sets the number of odes.
 // ===================================================================
 CCChenODEs::CCChenODEs(Real _a, Real _b, Real _c)
  : ACODEs(3)
 {  
  // Configure parameters
  a = _a;
  b = _b;
  c = _c;
 }
 
 // ===================================================================
 // Empty destructor
 // ===================================================================
 CCChenODEs::~CCChenODEs()
 { }
 
 // ===================================================================
 /// Evaluates the system of odes at time "t".
 // ===================================================================
 void CCChenODEs::evaluate_derivatives(const Real t,
                                       CCData<Real> &u,
                                       CCData<Real> &dudt,
                                       const unsigned k)
 {
  // -----------------
  /// \frac{du_{1}}{dt} = a*(u_{2} - u_{1})
  /// \frac{du_{2}}{dt} = (c-a)*u_{1} - u_{1}*u_{3} + c*u_{2}
  /// \frac{du_{3}}{dt} = u_{1}*u_{2} - b*u_{3}
  
  dudt(0) = a*(u(1,k) - u(0,k));
  dudt(1) = (c-a)*u(0,k) - (u(0,k)*u(2,k)) + (c*u(1,k));
  dudt(2) = (u(0,k)*u(1,k)) - (b*u(2,k));
  
 }
 
}

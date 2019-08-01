#ifndef CCODESBASIC3BODY_H
#define CCODESBASIC3BODY_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"
// The class used to store the values of u and dudt
#include "../../../src/data_structures/cc_data.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/data_structures/ac_odes.h"

// The dimension of the problem, the number of coordinates for the
// 3-bodies
#define DIM 3 // This specialised implementation assumes we are
              // working with 3 bodies in 3 dimensions
#define NBODIES 3

namespace chapchom
{

 /// \class CCODEsBasic3Body cc_odes_basic_3_body.h
    
 /// This class implements a set of odes associated with the n-body
 /// problem
 class CCODEsBasic3Body : public virtual ACODEs
 {
 
 public:
  
  /// Constructor, sets the number of bodies (this specialised
  // implementation assumes we are working with 3 bodies in 3
  // dimensions)
  CCODEsBasic3Body(const unsigned n_bodies = NBODIES);
  
  /// Empty destructor
  virtual ~CCODEsBasic3Body();
  
  /// Evaluates the system of odes at time "t". The values of the i-th
  /// function at previous times are accessible via u(i,1), u(i,2) and
  /// so on. The evaluation produces results in the vector dudt.
  void evaluate_derivatives(const Real t, CCData<Real> &u, CCData<Real> &dudt, const unsigned k = 0);
  
  // Gets access to the masses vector
  inline const Real m(const unsigned i) const {return M[i];}
  
  // Sets the value of the i-th body
  inline Real &m(const unsigned i) {return M[i];}
  
  // Gets access to the gravity vector
  inline const Real g(const unsigned i) const {return G[i];}
  
  // Sets the value of the i-th body
  inline Real &g(const unsigned i) {return G[i];}
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCODEsBasic3Body(const CCODEsBasic3Body &copy)
  : ACODEs(copy), N_bodies(0)
   {
    BrokenCopy::broken_copy("CCODEsBasic3Body");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCODEsBasic3Body &copy)
   {
    BrokenCopy::broken_assign("CCODEsBasic3Body");
   }
  
  // The number of bodies
  const unsigned N_bodies;

  // The masses of the bodies
  std::vector<Real> M;
  
  // The gravitational constant
  std::vector<Real> G;
  
 };
 
}

#endif // #ifndef CCODESBASIC3BODY_H

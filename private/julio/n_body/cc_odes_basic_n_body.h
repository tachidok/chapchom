#ifndef CCODESBASICNBODY_H
#define CCODESBASICNBODY_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"
// The class implementing the interfaces for the ODEs
#include "../../../src/odes/ac_odes.h"

// The dimension of the problem, the number of coordinates for the
// n-bodies
#define DIM 3 // This specialised implementation assumes we are
              // working with 4 bodies in 3 dimensions
#define NBODIES 4

namespace chapchom
{

 /// \class CCODEsBasicNBody cc_odes_basic_n_body.h
    
 /// This class implements a set of odes associated with the n-body
 /// problem
 class CCODEsBasicNBody : public virtual ACODEs
 {
 
 public:
  
  /// Constructor, sets the number of bodies (this specialised
  // implementation assumes we are working with 4 bodies in 3
  // dimensions)
  CCODEsBasicNBody(const double g, const unsigned n_bodies = NBODIES);
  
  /// Empty destructor
  virtual ~CCODEsBasicNBody(); 
  
  /// Set initial conditions
  void set_initial_conditions(std::vector<std::vector<double> > &y);
  
  /// Evaluates the system of odes at time "t". The values of the i-th
  /// function at previous times are accessible via y[i][1], y[i][2]
  /// and so on. The evaluation produces results in the vector dy.
  void evaluate(const double t,
                const std::vector<std::vector<double> > &y,
                std::vector<double> &dy);

  /// Evaluates the i-th ode at time "t". The values of the function
  /// at previous times are stores at y[1], y[2] and so on. The
  /// evaluation stores the result in dy.
  void evaluate(const unsigned i, const double t,
                const std::vector<double> &y, double &dy);
  
  // Gets access to the masses vector
  inline const double m(const unsigned i) const {return M[i];}
  
  // Sets the value of the i-th body
  inline double &m(const unsigned i) {return M[i];}
  
 protected:
  
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 CCODEsBasicNBody(const CCODEsBasicNBody &copy)
  : ACODEs(copy), N_bodies(0), G(0)
   {
    BrokenCopy::broken_copy("CCODEsBasicNBody");
   }
  
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCODEsBasicNBody &copy)
   {
    BrokenCopy::broken_assign("CCODEsBasicNBody");
   }
  
  // The number of bodies
  const unsigned N_bodies;

  // The masses of the bodies
  std::vector<double> M;

  // The gravitational constant
  const double G;
  
 };
 
}

#endif // #ifndef CCODESBASICNBODY_H

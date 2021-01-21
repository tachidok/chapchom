#include "ac_odes.h"

namespace scicellxx
{

 /// ===================================================================
 /// Constructor, sets the number of odes
 /// ===================================================================
 ACODEs::ACODEs(const unsigned n_odes)
  : N_odes(n_odes)
 {
 
  // Resize the container storing the number of calls to each
  // ODE. Initialise it to zero
  N_calls_ode.resize(n_odes, 0);
 
 }

 /// ===================================================================
 /// Destructor
 /// ===================================================================
 ACODEs::~ACODEs()
 {
  // Clear the storage of the vector
  N_calls_ode.clear();
 
 }

}

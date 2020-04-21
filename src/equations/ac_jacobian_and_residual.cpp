#include "ac_jacobian_and_residual.h"

namespace chapchom
{
 
 // ===================================================================
 /// Constructor
 // ===================================================================
 ACJacobianAndResidual::ACJacobianAndResidual()
 {
  /// Instantiate Jacobian and Residual based on the type of libraries
  /// we are using.
#ifdef CHAPCHOM_USES_ARMADILLO
  Jacobian_pt = new CCMatrixArmadillo<Real>();
  Residual_pt = new CCVectorArmadillo<Real>();
#else
  Jacobian_pt = new CCMatrix<Real>();
  Residual_pt = new CCVector<Real>();
#endif // #ifdef CHAPCHOM_USES_ARMADILLO
  
 }

 // ===================================================================
 /// Destructor
 // ===================================================================
 ACJacobianAndResidual::~ACJacobianAndResidual()
 {
  delete Jacobian_pt;
  Jacobian_pt = NULL;
  
  delete Residual_pt;
  Residual_pt = NULL;
  
 }
 
}


#ifndef ACJACOBIANANDRESIDUAL_H
#define ACJACOBIANANDRESIDUAL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/cc_data.h"
#include "../matrices/ac_vector.h"
#include "../matrices/ac_matrix.h"

#include "../matrices/cc_vector.h"
#include "../matrices/cc_matrix.h"

#ifdef SCICELLXX_USES_ARMADILLO
#include "../matrices/cc_vector_armadillo.h"
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef SCICELLXX_USES_ARMADILLO

#include "../matrices/cc_factory_matrices.h"

namespace scicellxx
{
 /// An abstract class used as a template for the algorithms to
 /// compute the Jacobian matrix
 class ACJacobianAndResidual
 {
  
 public:
  
  /// Constructor
  ACJacobianAndResidual();
  
  /// Destructor
  virtual ~ACJacobianAndResidual();
  
  /// In charge of computing the Jacobian based on the particular
  /// strategy implemented in the derived class
  virtual void compute_jacobian() = 0;
  
  /// Get access to the Jacobian
  inline ACMatrix<Real> *jacobian_pt() {return Jacobian_pt;}
  
  /// In charge of computing the residual vector based on the
  /// particular strategy implemented in the derived class
  virtual void compute_residual() = 0;
   
  /// Get access to the residual
  inline ACVector<Real> *residual_pt() {return Residual_pt;}
   
 protected:
  
  /// Storage for the Jacobian matrix
  ACMatrix<Real> *Jacobian_pt;
  
  /// Storage for the residual vector
  ACVector<Real> *Residual_pt;
  
 private:
   
  /// Copy constructor (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACJacobianAndResidual(const ACJacobianAndResidual &copy)
   {
    BrokenCopy::broken_copy("ACJacobianAndResidual");
   }
 
  /// Copy constructor (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACJacobianAndResidual &copy)
   {
    BrokenCopy::broken_assign("ACJacobianAndResidual");
   }
  
 };
 
}

#endif // #ifndef ACJACOBIANANDRESIDUAL_H


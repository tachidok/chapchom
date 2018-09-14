#ifndef ACJACOBIANANDRESIDUAL_TPL_H
#define ACJACOBIANANDRESIDUAL_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/cc_data.h"
#include "../matrices/cc_vector.h"
#include "../matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices and vectors since the templates may
// include Armadillo type matrices and vectors
#include "../matrices/cc_vector_armadillo.h"
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

namespace chapchom
{
 // An abstract class used as a template for the algorithms to compute
 // the Jacobian matrix
 template<class MAT_TYPE, class VEC_TYPE>
  class ACJacobianAndResidual
  {
   
  public:
   
   // Constructor
   ACJacobianAndResidual();
   
   // Destructor
   virtual ~ACJacobianAndResidual();
   
   // In charge of computing the Jacobian based on the particular
   // strategy implemented in the derived class
   virtual void compute_jacobian() = 0;
   
   // Get access to the Jacobian
   inline MAT_TYPE &jacobian() {return Jacobian;}
   
   // In charge of computing the residual vector based on the
   // particular strategy implemented in the derived class
   virtual void compute_residual() = 0;
   
   // Get access to the residual
   inline VEC_TYPE &residual() {return Residual;}
   
  protected:

   // Storage for the Jacobian matrix
   MAT_TYPE Jacobian;

   // Storage for the residual vector
   VEC_TYPE Residual;
   
  private:
  
   // Copy constructor (we do not want this class to be
   // copiable. Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   ACJacobianAndResidual(const ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("ACJacobianAndResidual");
    }
 
   // Copy constructor (we do not want this class to be
   // copiable. Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const ACJacobianAndResidual<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("ACJacobianAndResidual");
    }
  
  };
 
}

#endif // #ifndef ACJACOBIANANDRESIDUAL_TPL_H


#ifndef ACRESIDUAL_TPL_H
#define ACRESIDUAL_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/cc_data.h"
#include "../matrices/cc_vector.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type vectors since the templates may include
// Armadillo type vectors
#include "../matrices/cc_vector_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

namespace chapchom
{
 // An abstract class used as a template for the algorithms to compute
 // the residual vector (for Newton's method)
 template<class VEC_TYPE>
  class ACResidual
  {
   
  public:
   
   // Constructor
   ACResidual();
   
   // Destructor
   virtual ~ACResidual();
   
   // In charge of computing the residual vector based on the
   // particular strategy implemented in the derived class
   virtual void compute_residual() = 0;
   
   // Get access to the residual
   inline VEC_TYPE &residual() {return Residual;}
   
  protected:
   
   VEC_TYPE Residual;
   
  private:
   
   // Copy constructor (we do not want this class to be
   // copiable. Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   ACResidual(const ACResidual<VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("ACResidual");
    }
 
   // Copy constructor (we do not want this class to be
   // copiable. Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const ACResidual<VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("ACResidual");
    }
  
  };
 
}

#endif // #ifndef ACRESIDUAL_TPL_H


#ifndef ACJACOBIAN_TPL_H
#define ACJACOBIAN_TPL_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

#include "../data_structures/cc_data.h"
#include "../matrices/cc_matrix.h"

#ifdef CHAPCHOM_USES_ARMADILLO
// Include Armadillo type matrices since the templates may include
// Armadillo type matrices
#include "../matrices/cc_matrix_armadillo.h"
#endif // #ifdef CHAPCHOM_USES_ARMADILLO

namespace chapchom
{
 // An abstract class used as a template for the algorithms to compute
 // the Jacobian matrix
 template<class MAT_TYPE>
  class ACJacobian
  {
   
  public:
   
   // Constructor
   ACJacobian();
   
   // Destructor
   virtual ~ACJacobian();
   
   // In charge of computing the Jacobian based on the particular
   // strategy implemented in the derived class
   virtual void compute_jacobian() = 0;
   
   // Get access to the Jacobian
   inline MAT_TYPE &jacobian() {return Jacobian;}
   
  protected:
   
   MAT_TYPE Jacobian;
   
  private:
  
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   ACJacobian(const ACJacobian<MAT_TYPE> &copy)
    {
     BrokenCopy::broken_copy("ACJacobian");
    }
 
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const ACJacobian<MAT_TYPE> &copy)
    {
     BrokenCopy::broken_assign("ACJacobian");
    }
  
  };
 
}

#endif // #ifndef ACJACOBIAN_TPL_H


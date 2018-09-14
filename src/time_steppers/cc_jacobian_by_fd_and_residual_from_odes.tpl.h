#ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H
#define CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H

#include "../equations/ac_jacobian_and_residual.h"
#include "../data_structures/ac_odes.h"

namespace chapchom
{

 // A concrete class to compute the Jacobian matrix using Finite
 // Differences from a set of ODES
 template<class MAT_TYPE, class VEC_TYPE>
  class CCJacobianByFDAndResidualFromODEs : virtual public ACJacobianAndResidual<MAT_TYPE,VEC_TYPE>
  {
  
 public:
  
  // Constructor
   CCJacobianByFDAndResidualFromODEs();
  
   // Destructor
   ~CCJacobianByFDAndResidualFromODEs();
  
   // In charge of computing the Jacobian using Finite Differences
   // (virtual function implementation)
   void compute_jacobian();
   
   // In charge of computing the residual
   void compute_residual();
   
   // Set the ODEs to compute the Jacobian
   void set_ODEs(const ACODEs &odes);
   
   // Set the U vector/matrix with the values of the function at the
   // current time
   void set_U(const CCData<double> &u);
  
   // In charge of setting the constant time to compute the Jacobian
   // using Finite Differences
   void set_constant_time(const double t);
  
  protected:

   // Stores the set of ODEs used to compute the Jacobian
   ACODEs ODEs;
  
   // A flag to indicate whether the ODEs have been set or not
   bool ODEs_has_been_set;
  
   // The value of the function U at the current time (U is the
   // function that is been integrated from an ODEs in u')
   CCData<double> U;
  
   // A flag to indicate whether the U values have been set or not
   bool U_has_been_set;
   
   // The value of the current constant time, it should be set before
   // calling the computation of the Jacobian method
   double Constant_time;
   
   // Flag to indicate whether the constant time has been set
   bool Constant_time_has_been_set;
   
  private:
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   CCJacobianByFDAndResidualFromODEs(const CCJacobianByFDAndResidualFromODEs<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_copy("CCJacobianByFDAndResidualFromODEs");
    }
   
   // Copy constructor (we do not want this class to be copiable because
   // it contains dynamically allocated variables, A in this
   // case). Check
   // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
   void operator=(const CCJacobianByFDAndResidualFromODEs<MAT_TYPE,VEC_TYPE> &copy)
    {
     BrokenCopy::broken_assign("CCJacobianByFDAndResidualFromODEs");
    }
   
  };
 
}

#endif // #ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H


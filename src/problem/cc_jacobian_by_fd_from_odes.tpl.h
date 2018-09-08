#ifndef CCJACOBIANBYFDFROMODES_TPL_H
#define CCJACOBIANBYFDFROMODES_TPL_H

#include "ac_jacobian.h"
#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

namespace chapchom
{

 // A concrete class to compute the Jacobian matrix using Finite
 // Differences from a set of ODES
 template<class MAT_TYPE>
  class CCJacobianByFDFromODEs : virtual public ACJacobian<MAT_TYPE>
  {
  
 public:
  
  // Constructor
  CCJacobianByFDFromODEs();
  
  // Destructor
  ~CCJacobianByFDFromODEs();
  
  // In charge of computing the Jacobian using Finite Differences
  // (virtual function implementation)
  void compute_jacobian();
  
  // In charge of computing the Jacobian using Finite Differences
  void compute_jacobian(const double t);
  
  // Set the ODEs to compute the Jacobian
  void set_ODEs(const ACODEs &odes);
  
  // Set the U vector/matrix with the values of the function at the
  // current time
  void set_U(const CCData<double> &u);
  
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
  CCJacobianByFDFromODEs(const CCJacobianByFDFromODEs<MAT_TYPE> &copy)
   {
    BrokenCopy::broken_copy("CCJacobianByFDFromODEs");
   }
 
  // Copy constructor (we do not want this class to be copiable because
  // it contains dynamically allocated variables, A in this
  // case). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCJacobianByFDFromODEs<MAT_TYPE> &copy)
   {
    BrokenCopy::broken_assign("CCJacobianByFDFromODEs");
   }
   
 };
 
}

#endif // #ifndef CCJACOBIANBYFDFROMODES_TPL_H


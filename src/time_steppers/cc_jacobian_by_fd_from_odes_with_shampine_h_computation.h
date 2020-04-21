#ifndef CCJACOBIANBYFDFROMODES_H
#define CCJACOBIANBYFDFROMODES_H

#include "ac_jacobian.h"
#include "../data_structures/ac_odes.h"

namespace chapchom
{

 // A concrete class to compute the Jacobian matrix using Finite
 // Differences from a set of ODES
 class CCJacobianByFDFromODEs : virtual public ACJacobian
 {
  
 public:
  
  // Constructor
  CCJacobianByFDFromODEs();
  
  // Destructor
  ~CCJacobianByFDFromODEs();
   
  // In charge of computing the Jacobian using Finite Differences
  void compute_jacobian(const double time);
   
  // Set the ODEs to compute the Jacobian
  void set_ODEs(const ACODEs &odes);

 protected:

  // Stores the set of ODEs used to compute the Jacobian
  ACODEs ODEs;

  // A flag to indicate whether the ODEs have been set or not
  bool Set_of_ODEs_have_been_set;
   
 private:
  
  // Copy constructor (we do not want this class to be copiable because
  // it contains dynamically allocated variables, A in this
  // case). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCJacobianByFDFromODEs(const CCJacobianByFDFromODEs &copy)
   {
    BrokenCopy::broken_copy("CCJacobianByFDFromODEs");
   }
 
  // Copy constructor (we do not want this class to be copiable because
  // it contains dynamically allocated variables, A in this
  // case). Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCJacobianByFDFromODEs &copy)
   {
    BrokenCopy::broken_assign("CCJacobianByFDFromODEs");
   }
   
 };
 
}

#endif // #ifndef CCJACOBIANBYFDFROMODES_H


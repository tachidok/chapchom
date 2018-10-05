#ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H
#define CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H

#include "../equations/ac_jacobian_and_residual.h"
#include "../data_structures/ac_odes.h"
#include "../data_structures/cc_data.h"

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
   
   // Set the ODEs
   void set_ODEs(ACODEs *odes_pt);
   
   // Set the U vector/matrix with the values of the function at the
   // current time
   void set_U(CCData<double> *u_pt);
   
   // Sets the current time
   void set_current_time(const double t);
   
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
   
   // The ODEs
   ACODEs *ODEs_pt;
   
   // A flag to indicate whether the ODEs have been set or not
   bool ODEs_has_been_set;
   
   // The U values of the function at the current time
   CCData<double> *U_pt;
   
   // A flag to indicate whether the U values have been set or not
   bool U_has_been_set;
   
   // The current time
   double Current_time;
   
   // Flag to indicate whether the current time has been set
   bool Current_time_has_been_set;
   
  };
 
}

#endif // #ifndef CCJACOBIANBYFDANDRESIDUALFROMODES_TPL_H


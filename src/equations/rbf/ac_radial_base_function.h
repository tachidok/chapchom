#ifndef ACRADIALBASEFUNCTION_H
#define ACRADIALBASEFUNCTION_H

#include "../general/common_includes.h"
#include "../general/utilities.h"

namespace chapchom
{
 /// An abstract class used as a template for the radial base function
 class ACRadialBaseFunction
 {
  
 public:
  
  // Constructor
  ACRadialBaseFunction();
  
  // Destructor
  virtual ~ACRadialBaseFunction();
  
  // Radial function (must be implemented for every derived class)
  virtual const Real psi(const Real r) = 0;
  
 private:
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACRadialBaseFunction(const ACRadialBaseFunction &copy)
   {
    BrokenCopy::broken_copy("ACRadialBaseFunction");
   }
  
  // Copy constructor (we do not want this class to be
  // copiable. Check
  // http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACRadialBaseFunction &copy)
   {
    BrokenCopy::broken_assign("ACRadialBaseFunction");
   }
  
 };
 
}

#endif // #ifndef ACRADIALBASEFUNCTION_H

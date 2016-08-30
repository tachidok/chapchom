#ifndef CCFACTORYINTEGRATIONMETHOD_H
#define CCFACTORYINTEGRATIONMETHOD_H

// Include the parent class
#include "ac_factory_integration_method.h"

// Include the integration methods
#include "cc_euler_method.h"
#include "cc_RK4_method.h"

namespace chapchom
{

 /// @class CCFactoryIntegrationMethod cc_factory_integration_method.h

 /// This class implements a factory for the integration methods

 class CCFactoryIntegrationMethod : virtual public ACFactoryIntegrationMethod
 {
 
 public:
 
  /// Empty constructor
  CCFactoryIntegrationMethod();
 
  /// Empty destructor
  virtual ~CCFactoryIntegrationMethod();
 
  /// Returns the specified integration method
  ACIntegrationMethod* create_integration_method(std::string method);
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  CCFactoryIntegrationMethod(const CCFactoryIntegrationMethod &copy)
   {
    BrokenCopy::broken_copy("CCFactoryIntegrationMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const CCFactoryIntegrationMethod &copy)
   {
    BrokenCopy::broken_assign("CCFactoryIntegrationMethod");
   }
 
 };

}
 
#endif // #ifndef CCFACTORYINTEGRATIONMETHOD_H

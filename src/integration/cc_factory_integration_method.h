#ifdef CCFACTORYINTEGRATIONMETHOD_H
#define CCFACTORYINTEGRATIONMETHOD_H

#include "ac_integration_method.h"
#include "ac_explicit_integration_method.h"
#include "cc_euler_method.h"
#include "cc_RK4_method.h"

/// @class CCFactoryIntegrationMethod cc_factory_integration_method.h

/// This class implements a factory for the integration methods

class CCFactoryIntegrationMethod
{
 
 public:
 
 /// Empty constructor
 CCFactoryIntegrationMethod();
 
 /// Empty destructor
 virtual ~CCFactoryIntegrationMethod();
 
 /// Returns the specified integration method
 ACIntegrationMethod* create(std::string method);
 
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

#endif // #ifdef CCFACTORYINTEGRATIONMETHOD_H

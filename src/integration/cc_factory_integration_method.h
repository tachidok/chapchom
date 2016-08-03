#ifdef CCFACTORYINTEGRATIONMETHOD_H
#define CCFACTORYINTEGRATIONMETHOD_H

#include "ca_integration_method.h"
#include "ca_explicit_integration_method.h"
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
 virtual ~CCIntegrationMethod();

 /// Returns the specified integration method
 CAIntegrationMethod* create(std::string method);
 
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
 
}

#endif CCFACTORYINTEGRATIONMETHOD_H

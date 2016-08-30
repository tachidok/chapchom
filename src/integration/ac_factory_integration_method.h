#ifndef ACFACTORYINTEGRATIONMETHOD_H
#define ACFACTORYINTEGRATIONMETHOD_H

#include "ac_integration_method.h"
#include "ac_explicit_integration_method.h"

namespace chapchom
{

 /// @class ACFactoryIntegrationMethod ac_factory_integration_method.h

 /// This abstract class implements the interfaces for the factories in
 /// charge of creating integration methods

 class ACFactoryIntegrationMethod
 {
 
 public:
 
  /// Empty constructor
  ACFactoryIntegrationMethod();
 
  /// Empty destructor
  virtual ~ACFactoryIntegrationMethod();
 
  /// Returns the specified integration method
  virtual ACIntegrationMethod* create_integration_method(std::string method) = 0;
 
 protected:
 
  /// Copy constructor (we do not want this class to be
  /// copiable). Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  ACFactoryIntegrationMethod(const ACFactoryIntegrationMethod &copy)
   {
    BrokenCopy::broken_copy("ACFactoryIntegrationMethod");
   }
 
  /// Assignment operator (we do not want this class to be
  /// copiable. Check
  /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
  void operator=(const ACFactoryIntegrationMethod &copy)
   {
    BrokenCopy::broken_assign("ACFactoryIntegrationMethod");
   }
 
 };

}
 
#endif //#ifndef ACFACTORYINTEGRATIONMETHOD_H

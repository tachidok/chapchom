#include "cc_factory_integration_method.h"

// ===================================================================
// Empty constructor
// ===================================================================
CCFactoryIntegrationMethod::CCFactoryIntegrationMethod()
 : ACFactoryIntegrationMethod()
{ 

}

// ===================================================================
// Empty destructor
// ===================================================================
CCFactoryIntegrationMethod::~CCFactoryIntegrationMethod()
{ 

}

// ===================================================================
// Returns the specified integration method
// ===================================================================
ACIntegrationMethod* CCFactoryIntegrationMethod::
create_integration_method(std::string method)
{
 // Get the string and change it to lower case 
 std::transform(method.begin(), method.end(), method.begin(), ::tolower);
 
 // ---------------------------------------
 // Check what method we need to create
 // ---------------------------------------
 // Euler method
 if (method.compare("euler")==0)
  {
   return new CCEulerMethod();
  }
 // Runge-Kutta 4 method
 else if (method.compare("rk4")==0)
  {
   return new CCRK4Method();
  }
 else
  {
   std::ostringstream error_message;
   error_message << "The integration method you are trying to use is not "
                 << "implemented yet. Please implement it yourself or select"
                 << "another one" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
  
}



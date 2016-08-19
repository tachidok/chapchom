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
CAIntegrationMethod* CCFactoryIntegrationMethod::
create_integration_method(std::string method)
{
 std::string data = "Abc"; 
 std::transform(data.begin(), data.end(), data.begin(), ::tolower);
}



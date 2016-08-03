#include "ca_factory_integration_method.h"

// ===================================================================
// Empty constructor
// ===================================================================
CCFactoryIntegrationMethod::CCFactoryIntegrationMethod()
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
CAIntegrationMethod* CCFactoryIntegrationMethod::create(std::string method)
{
 std::string data = "Abc"; 
 std::transform(data.begin(), data.end(), data.begin(), ::tolower);
}


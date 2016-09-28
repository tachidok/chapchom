# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_integration_method.cpp ac_explicit_integration_method.cpp cc_euler_method.cpp cc_RK4_method.cpp ac_factory_integration_method.cpp cc_factory_integration_method.cpp)

# Create a library with the above files
ADD_LIBRARY(integration ${SRC_FILES})

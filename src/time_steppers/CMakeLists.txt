# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_time_stepper.cpp cc_euler_method.cpp cc_RK4_method.cpp cc_factory_time_stepper.cpp)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(time_stepper_lib STATIC ${SRC_FILES})
ELSEIF(${CHAPCHOM_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(time_stepper_lib SHARED ${SRC_FILES})
ELSE(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(integration_lib {SRC_FILES})
ENDIF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(time_stepper ${CMAKE_CURRENT_SOURCE_DIR})

# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES utilities.cpp initialise.cpp)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(general_lib STATIC ${SRC_FILES})
ELSEIF(${CHAPCHOM_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(general_lib SHARED ${SRC_FILES})
ELSE(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(general_lib ${SRC_FILES})
ENDIF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(general ${CMAKE_CURRENT_SOURCE_DIR})

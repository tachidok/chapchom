# =====================================================================
# Generation of header files by CMake
# =====================================================================
# Create and configure header files substituting variables set in
# CMakeLists.txt files into "*.h" files. The "*.in.h" in files are
# used as templates to create the "*.h" files. The "*.h" file is
# created in the same directory, otherwise we would required a call to
# INCLUDE_DIRECTORIES cmake method in every folder containing
# dependencies to the cmake generated file

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/cmake_definitions.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/cmake_definitions.h"
              )
# =====================================================================

# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES utilities.cpp initialise.cpp)

# Create a library with the above files based on the requested library
# version
IF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(general_lib STATIC ${SRC_FILES})
ELSEIF(${SCICELLXX_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(general_lib SHARED ${SRC_FILES})
ELSE(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(general_lib ${SRC_FILES})
ENDIF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(general ${CMAKE_CURRENT_SOURCE_DIR})

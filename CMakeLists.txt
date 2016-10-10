# Check for cmake minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name (this case library's name)
PROJECT(chapchom)
SET(${PROJET_NAME}_MAJOR_VERSION 0)
SET(${PROJET_NAME}_MINOR_VERSION 1)
SET(${PROJET_NAME}_PATCH_LEVEL 0)

# This seems to do nothing
SET(CMAKE_VERSBOSE_MAKEFILE TRUE)

# Output requested configuration
MESSAGE( STATUS "CHAPCHOM_LIB_TYPE:         " ${CHAPCHOM_LIB_TYPE} )
MESSAGE( STATUS "CHAPCHOM_BUILD_VERSION:         " ${CHAPCHOM_BUILD_VERSION} )

# Modify compilation variables
IF(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)
  SET(CHAPCHOM_C_FLAGS "-O0 -g -Wall -pedantic")
  SET(CHAPCHOM_CXX_FLAGS "-O0 -g -Wall -pedantic")
ELSEIF(${CHAPCHOM_BUILD_VERSION} STREQUAL RELEASE)
  SET(CHAPCHOM_C_FLAGS "-O3 -Wall -pedantic -DNDEBUG")
  SET(CHAPCHOM_CXX_FLAGS "-O3 -Wall -pedantic -DNDEBUG")
ELSE(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)
  SET(CHAPCHOM_C_FLAGS "-O0 -g -Wall -pedantic")
  SET(CHAPCHOM_CXX_FLAGS "-O0 -g -Wall -pedantic")
ENDIF(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)

# Use this if you require to add more libraries (do not forget to
# uncomment the respective line below to set linker variables)
#SET(CHAPCHOM_LINKER_FLAGS "-lmath")

# Set modified compilation variables
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CHAPCHOM_C_FLAGS}" )
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CHAPCHOM_CXX_FLAGS}" )

# Uncomment this line if you added extra libraries
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

# Include testing (this function already calls enable_testing())
include(CTest)

# Output configuration flags
# The flags passed to the C-compiler
MESSAGE( STATUS "CMAKE_C_FLAGS:         " ${CMAKE_C_FLAGS} )
# The flags passed to the C++ compiler
MESSAGE( STATUS "CMAKE_CXX_FLAGS:         " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_EXE_LINKER_FLAGS:         " ${CMAKE_EXE_LINKER_FLAGS} )

# Output some extra info.
MESSAGE( STATUS "CMAKE_VERSBOSE_MAKEFILE:         " ${CMAKE_VERSBOSE_MAKEFILE} )

# Add external source files sub-directories
ADD_SUBDIRECTORY(external_src)

# Add sub-directories with source files
ADD_SUBDIRECTORY(src)

# Once all source code has been compiled add sub-directories for demos
ADD_SUBDIRECTORY(demos)

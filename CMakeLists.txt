# Check for cmake minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# ----------------------------------------------------------------------
# Project intialisation
# ----------------------------------------------------------------------

# Project name (this case library's name)
PROJECT(chapchom)
SET(${CMAKE_PROJECT_NAME}_MAJOR_VERSION 0)
SET(${CMAKE_PROJECT_NAME}_MINOR_VERSION 2)
SET(${CMAKE_PROJECT_NAME}_PATCH_LEVEL 0)

# Prints a lot of stuff
#SET(CMAKE_VERBOSE_MAKEFILE TRUE)

# ----------------------------------------------------------------------
# Output requested configuration
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** GENERAL LIBRARY INFORMATION **" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "CHAPCHOM_LIB_TYPE:            " ${CHAPCHOM_LIB_TYPE} )
MESSAGE( STATUS "CHAPCHOM_BUILD_VERSION:       " ${CHAPCHOM_BUILD_VERSION} )
MESSAGE( STATUS "CHAPCHOM_BUILD_DEMOS:         " ${CHAPCHOM_BUILD_DEMOS} )
MESSAGE( STATUS "PROJECT_NAME:                 " ${PROJECT_NAME})
MESSAGE( STATUS "PROJECT_MAJOR_VERSION:        " ${chapchom_MAJOR_VERSION})
MESSAGE( STATUS "PROJECT_MINOR_VERSION:        " ${chapchom_MINOR_VERSION})
MESSAGE( STATUS "PROJECT_PATCH_LEVEL:          " ${chapchom_PATCH_LEVEL})
MESSAGE( STATUS "-----------------------------------------------------------------------" )

# ----------------------------------------------------------------------
# Read configuration file and extract values of variables
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** READ VARIABLES FROM CONFIGURATION FILE: " ${CHAPCHOM_CONFIGURATION_FILE} " **")
MESSAGE( STATUS "-----------------------------------------------------------------------" )
file(STRINGS ${CHAPCHOM_CONFIGURATION_FILE} ConfigContents)
foreach(NameAndValue ${ConfigContents})
  # Strip leading spaces
  string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
  # Find variable name
  string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
  # Find the value
  string(REPLACE "${Name}=" "" Value ${NameAndValue})
  # Set the variable
  set(${Name} "${Value}")
  MESSAGE( STATUS ${Name} " : " ${Value})
endforeach()

MESSAGE( STATUS "-----------------------------------------------------------------------" )

# ----------------------------------------------------------------------
# Do we want to compile using Armadillo?
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** ARMADILLO'S LIBRARY INFORMATION **" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
IF (CHAPCHOM_USES_ARMADILLO)
  IF (CHAPCHOM_AUTO_FIND_ARMADILLO_PATHS)
    # Try to find Armadillo to enable Armadillo wrappers
    FIND_PACKAGE(Armadillo REQUIRED)
    IF (ARMADILLO_FOUND)
      MESSAGE( STATUS "FOUND ARMADILLO_INCLUDE_DIRS:             " ${ARMADILLO_INCLUDE_DIRS} )
      MESSAGE( STATUS "FOUND ARMADILLO_LIBRARIES:                " ${ARMADILLO_LIBRARIES} )
      INCLUDE_DIRECTORIES($ARMADILLO_INCLUDE_DIRS)
    ENDIF (ARMADILLO_FOUND)
  ELSE (CHAPCHOM_AUTO_FIND_ARMADILLO_PATHS)
    MESSAGE( STATUS "USING YOUR OWN ARMADILLO'S INCLUDE AND LIB PATHS")
    MESSAGE( STATUS "ARMADILLO_INCLUDE_DIRS:             " ${ARMADILLO_INCLUDE_DIRS} )
    MESSAGE( STATUS "ARMADILLO_LIBRARIES:                " ${ARMADILLO_LIBRARIES} )
    INCLUDE_DIRECTORIES(${ARMADILLO_INCLUDE_DIRS})
  ENDIF (CHAPCHOM_AUTO_FIND_ARMADILLO_PATHS)

  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  MESSAGE( STATUS "" )
  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  MESSAGE( STATUS "** THREADS'S LIBRARY INFORMATION **" )
  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  # Find Threads packages (usually pthread)
  # Required by Armadillo
  FIND_PACKAGE(Threads REQUIRED)
  
ENDIF (CHAPCHOM_USES_ARMADILLO)
MESSAGE( STATUS "-----------------------------------------------------------------------" )

# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Modify compilation variables
# ----------------------------------------------------------------------
IF(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)
  SET(CHAPCHOM_C_FLAGS "-O0 -g -Wall -pedantic")
  SET(CHAPCHOM_CXX_FLAGS "-O0 -g -Wall -pedantic -std=c++11")
ELSEIF(${CHAPCHOM_BUILD_VERSION} STREQUAL RELEASE)
  SET(CHAPCHOM_C_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG")
  SET(CHAPCHOM_CXX_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG -std=c++11")
ELSEIF(${CHAPCHOM_BUILD_VERSION} STREQUAL PROFILING)
  SET(CHAPCHOM_C_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic")
  SET(CHAPCHOM_CXX_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic -std=c++11")
  MESSAGE( WARNING "You are compiling with profiling ENABLED, this will SIGNIFICANTLY increase execution times. If you do not want profiling to be ENABLED then choose another version when asked for library version" ) 
ELSE(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)
  SET(CHAPCHOM_C_FLAGS "-O0 -g -Wall -Wextra -pedantic")
  SET(CHAPCHOM_CXX_FLAGS "-O0 -g -Wall -Wextra -pedantic -std=c++11")
ENDIF(${CHAPCHOM_BUILD_VERSION} STREQUAL DEBUG)

# Use this if you require to add more libraries (do not forget to
# uncomment the respective line below to set linker variables)
#SET(CHAPCHOM_LINKER_FLAGS "-lmath")

# ----------------------------------------------------------------------
# Set modified compilation variables
# ----------------------------------------------------------------------
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CHAPCHOM_C_FLAGS}" )
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CHAPCHOM_CXX_FLAGS}" )

# Uncomment this line if you added extra libraries
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

# ----------------------------------------------------------------------
# Include testing (this function already calls enable_testing())
# ----------------------------------------------------------------------
INCLUDE(CTest)

# ----------------------------------------------------------------------
# Output configuration
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** GENERAL COMPILATION FLAGS **" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
# Output compilers versions
MESSAGE( STATUS "CMAKE_C_COMPILER:             " ${CMAKE_C_COMPILER} )
MESSAGE( STATUS "CMAKE_CXX_COMPILER:           " ${CMAKE_CXX_COMPILER} )

# Output configuration flags
# The flags passed to the C-compiler
MESSAGE( STATUS "CMAKE_C_FLAGS:                " ${CMAKE_C_FLAGS} )
# The flags passed to the C++ compiler
MESSAGE( STATUS "CMAKE_CXX_FLAGS:              " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_EXE_LINKER_FLAGS:       " ${CMAKE_EXE_LINKER_FLAGS} )

# Output some extra info.
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE:       " ${CMAKE_VERBOSE_MAKEFILE} )

MESSAGE( STATUS "-----------------------------------------------------------------------" )

# Add external source files sub-directories
ADD_SUBDIRECTORY(external_src)

# Add sub-directories with source files
ADD_SUBDIRECTORY(src)

# Add private folders (note that any source code in here is not
# compiled but only added to the make list)
ADD_SUBDIRECTORY(private)

# Once all source code has been compiled add sub-directories for demos
ADD_SUBDIRECTORY(demos)

MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "" )


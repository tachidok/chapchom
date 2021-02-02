# Check for cmake minimum required version (previously working with v2.8)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# ----------------------------------------------------------------------
# Project intialisation
# ----------------------------------------------------------------------

# Project name (this case library's name)
PROJECT(SCICELLXX)
SET(${CMAKE_PROJECT_NAME}_MAJOR_VERSION 0)
SET(${CMAKE_PROJECT_NAME}_MINOR_VERSION 5)
SET(${CMAKE_PROJECT_NAME}_PATCH_LEVEL 0)

# Prints a lot of stuff
#SET(CMAKE_VERBOSE_MAKEFILE TRUE)

# ----------------------------------------------------------------------
# Output requested configuration
# ----------------------------------------------------------------------
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "CMAKE VERSION:                 " ${CMAKE_VERSION} )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** GENERAL LIBRARY INFORMATION **" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "SCICELLXX_LIB_TYPE:            " ${SCICELLXX_LIB_TYPE} )
MESSAGE( STATUS "SCICELLXX_BUILD_VERSION:       " ${SCICELLXX_BUILD_VERSION} )
MESSAGE( STATUS "SCICELLXX_BUILD_DEMOS:         " ${SCICELLXX_BUILD_DEMOS} )
MESSAGE( STATUS "PROJECT_NAME:                 " ${PROJECT_NAME})
MESSAGE( STATUS "PROJECT_MAJOR_VERSION:        " ${SCICELLXX_MAJOR_VERSION})
MESSAGE( STATUS "PROJECT_MINOR_VERSION:        " ${SCICELLXX_MINOR_VERSION})
MESSAGE( STATUS "PROJECT_PATCH_LEVEL:          " ${SCICELLXX_PATCH_LEVEL})

# ----------------------------------------------------------------------
# Read configuration file and extract values of variables
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** READ VARIABLES FROM CONFIGURATION FILE: " ${SCICELLXX_CONFIGURATION_FILE} " **")
MESSAGE( STATUS "-----------------------------------------------------------------------" )
file(STRINGS ${SCICELLXX_CONFIGURATION_FILE} ConfigContents)
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
IF (SCICELLXX_USES_ARMADILLO)
  IF (SCICELLXX_AUTO_FIND_ARMADILLO_PATHS)
    # Set the suggested folder where to look for Armadillo's library (where the
    # ArmadilloConfig.cmake) file lives
    LIST(APPEND CMAKE_PREFIX_PATH ${ARMADILLO_AUTO_FIND_FOLDER})
    # Try to find Armadillo to enable Armadillo wrappers
    FIND_PACKAGE(Armadillo REQUIRED)
    IF (ARMADILLO_FOUND)
      MESSAGE( STATUS "FOUND ARMADILLO_INCLUDE_DIRS:             " ${ARMADILLO_INCLUDE_DIRS} )
      MESSAGE( STATUS "FOUND ARMADILLO_LIBRARIES:                " ${ARMADILLO_LIBRARIES} )
      INCLUDE_DIRECTORIES(${ARMADILLO_INCLUDE_DIRS})
    ENDIF (ARMADILLO_FOUND)
  ELSE (SCICELLXX_AUTO_FIND_ARMADILLO_PATHS)
    MESSAGE( STATUS "USING YOUR OWN ARMADILLO'S INCLUDE AND LIB PATHS")
    MESSAGE( STATUS "ARMADILLO_INCLUDE_DIRS:             " ${ARMADILLO_INCLUDE_DIRS} )
    MESSAGE( STATUS "ARMADILLO_LIBRARIES:                " ${ARMADILLO_LIBRARIES} )
    INCLUDE_DIRECTORIES(${ARMADILLO_INCLUDE_DIRS})
  ENDIF (SCICELLXX_AUTO_FIND_ARMADILLO_PATHS)

  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  MESSAGE( STATUS "" )
  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  MESSAGE( STATUS "** THREADS'S LIBRARY INFORMATION **" )
  MESSAGE( STATUS "-----------------------------------------------------------------------" )
  # Find Threads packages (usually pthread)
  # Required by Armadillo
  FIND_PACKAGE(Threads REQUIRED)
  
ENDIF (SCICELLXX_USES_ARMADILLO)

# ----------------------------------------------------------------------
# Do we want to compile using VTK? It should be a must
# ----------------------------------------------------------------------
MESSAGE( STATUS "" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
MESSAGE( STATUS "** VTK'S LIBRARY INFORMATION **" )
MESSAGE( STATUS "-----------------------------------------------------------------------" )
IF (SCICELLXX_USES_VTK)
  IF (SCICELLXX_AUTO_FIND_VTK_PATHS)
    # Set the suggested folder where to look for VTK's library (where the
    # VTKConfig.cmake) file lives
    LIST(APPEND CMAKE_PREFIX_PATH ${VTK_AUTO_FIND_FOLDER})
    # Try to find VTK to enable VTK wrappers
    FIND_PACKAGE(VTK REQUIRED)
    IF (VTK_FOUND)
      MESSAGE( STATUS "FOUND VTK_INCLUDE_DIRS:             " ${VTK_INCLUDE_DIRS} )
      MESSAGE( STATUS "FOUND VTK_LIBRARIES:                " ${VTK_LIBRARIES} )
      INCLUDE_DIRECTORIES(${VTK_INCLUDE_DIRS})
    ENDIF (VTK_FOUND)
  ELSE (SCICELLXX_AUTO_FIND_VTK_PATHS)
    MESSAGE( STATUS "USING YOUR OWN VTK'S INCLUDE AND LIB PATHS")
    MESSAGE( STATUS "VTK_INCLUDE_DIRS:             " ${VTK_INCLUDE_DIRS} )
    MESSAGE( STATUS "VTK_LIBRARIES:                " ${VTK_LIBRARIES} )
    INCLUDE_DIRECTORIES(${VTK_INCLUDE_DIRS})
  ENDIF (SCICELLXX_AUTO_FIND_VTK_PATHS)
  
ENDIF (SCICELLXX_USES_VTK)
MESSAGE( STATUS "-----------------------------------------------------------------------" )

# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Modify compilation variables
# ----------------------------------------------------------------------
IF(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)
  SET(SCICELLXX_C_FLAGS "-O0 -g -Wall -Wshadow --coverage")
  SET(SCICELLXX_CXX_FLAGS "-O0 -g -Wall -Wshadow -std=c++11 --coverage")
ELSEIF(${SCICELLXX_BUILD_VERSION} STREQUAL RELEASE)
  SET(SCICELLXX_C_FLAGS "-O3 -Wall -Wshadow -DNDEBUG")
  SET(SCICELLXX_CXX_FLAGS "-O3 -Wall -Wshadow -DNDEBUG -std=c++11")
ELSEIF(${SCICELLXX_BUILD_VERSION} STREQUAL PROFILING)
  SET(SCICELLXX_C_FLAGS "-O0 -pg -Wall -Wshadow")
  SET(SCICELLXX_CXX_FLAGS "-O0 -pg -Wall -Wshadow -std=c++11")
  MESSAGE( WARNING "You are compiling with profiling ENABLED, this will SIGNIFICANTLY increase execution times. If you do not want profiling to be ENABLED then choose another version when asked for library version" ) 
ELSE(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)
  SET(SCICELLXX_C_FLAGS "-O0 -g -Wall -Wshadow")
  SET(SCICELLXX_CXX_FLAGS "-O0 -g -Wall -Wshadow -std=c++11")
ENDIF(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)

#IF(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)
#  SET(SCICELLXX_C_FLAGS "-O0 -g -Wall -Wextra -Wshadow -Wconversion -pedantic")
#  SET(SCICELLXX_CXX_FLAGS "-O0 -g -Wall -Wextra -Wshadow -Wconversion -pedantic -std=c++11")
#ELSEIF(${SCICELLXX_BUILD_VERSION} STREQUAL RELEASE)
#  SET(SCICELLXX_C_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG")
#  SET(SCICELLXX_CXX_FLAGS "-O3 -Wall -Wextra -Wshadow -Wconversion -pedantic -DNDEBUG -std=c++11")
#ELSEIF(${SCICELLXX_BUILD_VERSION} STREQUAL PROFILING)
#  SET(SCICELLXX_C_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic")
#  SET(SCICELLXX_CXX_FLAGS "-O0 -pg -Wall -Wshadow -Wconversion -Wextra -pedantic -std=c++11")
#  MESSAGE( WARNING "You are compiling with profiling ENABLED, this will SIGNIFICANTLY increase execution times. If you do not want profiling to be ENABLED then choose another version when asked for library version" ) 
#ELSE(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)
#  SET(SCICELLXX_C_FLAGS "-O0 -g -Wall -Wextra -Wshadow -Wconversion -pedantic")
#  SET(SCICELLXX_CXX_FLAGS "-O0 -g -Wall -Wextra -Wshadow -Wconversion -pedantic -std=c++11")
#ENDIF(${SCICELLXX_BUILD_VERSION} STREQUAL DEBUG)

# Use this if you require to add more libraries (do not forget to
# uncomment the respective line below to set linker variables)
#SET(SCICELLXX_LINKER_FLAGS "-lmath")

# ----------------------------------------------------------------------
# Append extra definitions based on configuration files
# ----------------------------------------------------------------------
SET(SCICELLXX_RANGE_CHECK_DEFINITION "-DSCICELLXX_RANGE_CHECK")
IF (SCICELLXX_RANGE_CHECK)
  SET(SCICELLXX_CXX_FLAGS "${SCICELLXX_CXX_FLAGS} ${SCICELLXX_RANGE_CHECK_DEFINITION}" )
ENDIF (SCICELLXX_RANGE_CHECK)

SET(SCICELLXX_USES_DOUBLE_PRECISION_DEFINITION "-DTYPEDEF_REAL_IS_DOUBLE")
IF (SCICELLXX_USES_DOUBLE_PRECISION)
  SET(SCICELLXX_CXX_FLAGS "${SCICELLXX_CXX_FLAGS} ${SCICELLXX_USES_DOUBLE_PRECISION_DEFINITION}" )
ENDIF (SCICELLXX_USES_DOUBLE_PRECISION)

SET(SCICELLXX_ARMADILLO_DEFINE "-DSCICELLXX_USES_ARMADILLO")
IF (SCICELLXX_USES_ARMADILLO)
  SET(SCICELLXX_CXX_FLAGS "${SCICELLXX_CXX_FLAGS} ${SCICELLXX_ARMADILLO_DEFINE}" )
ENDIF (SCICELLXX_USES_ARMADILLO)

SET(SCICELLXX_VTK_DEFINE "-DSCICELLXX_USES_VTK")
IF (SCICELLXX_USES_VTK)
  SET(SCICELLXX_CXX_FLAGS "${SCICELLXX_CXX_FLAGS} ${SCICELLXX_VTK_DEFINE}" )
ENDIF (SCICELLXX_USES_VTK)

SET(SCICELLXX_PANIC_MODE_DEFINE "-DSCICELLXX_PANIC_MODE")
IF (SCICELLXX_PANIC_MODE)
  SET(SCICELLXX_CXX_FLAGS "${SCICELLXX_CXX_FLAGS} ${SCICELLXX_PANIC_MODE_DEFINE}" )
ENDIF (SCICELLXX_PANIC_MODE)

# ----------------------------------------------------------------------
# Set modified compilation variables
# ----------------------------------------------------------------------
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SCICELLXX_C_FLAGS}" )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SCICELLXX_CXX_FLAGS}" )

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


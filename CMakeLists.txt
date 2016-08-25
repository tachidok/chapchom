
# Check for cmake minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Project name (this case library's name)
PROJECT(chapchom)
#SET(${PROJET_NAME}_MAJOR_VERSION 0)
#SET(${PROJET_NAME}_MINOR_VERSION 1)
#SET(${PROJET_NAME}_PATCH_LEVEL 0)

# set default cmake build type to Debug (None Debug Release
# RelWithDebInfo MinSizeRel)
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

#set default install prefix to project root directory
#IF(CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
#	SET(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
#ENDIF()

# Adding library's sources
SET(include_src_directories src/general src/matrices src/linear_solvers src/odes
src/interpolation src/integration)

# Adding include directories
INCLUDE_DIRECTORIES(include_src_directories)
# Add flags for compiling
#ADD_DEFINITIONS(-ffloat-store)

# Adding library's sources
# SET(src_lib_directories Builders Integrator IVP Methods
#Methods/NumericalRecipes Observers ODEs)

# Adding source directories and directory for storing building files
#FOREACH(i ${src_lib_directories})
   #ADD_SUBDIRECTORY(${i} ../build)
#ENDFOREACH()

# Getting all the source codes from directories
AUX_SOURCE_DIRECTORY(src/general src_lib_general)
AUX_SOURCE_DIRECTORY(src/matrices src_lib_matrices)
AUX_SOURCE_DIRECTORY(src/linear_solvers src_lib_linear_solvers)
AUX_SOURCE_DIRECTORY(src/odes src_lib_odes)
AUX_SOURCE_DIRECTORY(src/interpolation src_lib_interpolation)
AUX_SOURCE_DIRECTORY(src/integration src_lib_integration)

#FOREACH(i ${src_lib_directories})
	#ADD_SUBDIRECTORY(${i})
	#AUX_SOURCE_DIRECTORY(${i})
#ENDFOREACH()

#SET(src_lib_Builders CAbsBuilderIntegrator	CCncrtBuilderIntegratorBackward CCncrtBuilderIntegratorFactory	CCncrtBuilderIntegratorForward	CCncrtDirectorIntegrator)
#SET(src_lib_Integrator CAbsIntegrator CAbsIntegratorMultirate CAbsObservable CCncrtIntegratorBasic CCncrtIntegratorMultirateBackward CCncrtIntegratorMultirateForward)
#SET(src_lib_IVP	CAbsIVP	CCncrtIVPExample1 CCncrtIVPExampleLinesMethod)
#SET(src_lib_Methods	CAbsExpMethod CAbsExpMethodRungeKutta CAbsImpMethod CAbsJaccAlgorithm CAbsMethod CAbsMethodFactory CCncrtExpMethodEuler CCncrtExpMethodRungeKutta2 CCncrtExpMethodRungeKutta3 CCncrtExpMethodRungeKutta4 CCncrtExpMethodRungeKuttaDormandPrince54 CCncrtExpMethodRungeKuttaFehlberg45 CCncrtExpMethodRungeKuttaMerson CCncrtImpMethodBackwardEuler CCncrtImpMethodTrapezoidalRule CCncrtJaccAlgorithmBasic CCncrtMethodConfiguration CCncrtMethodFactory)
#SET(src_lib_Observers CAbsObserver	CCncrtObserverVector)
#SET(src_lib_ODEs CAbsODEs CCncrtODEsExample1 CCncrtODEsExampleLinesMethod)
#SET(src_lib_NumericalRecipes lubksb	ludcmp)

# setting sources and main file
SET(sources ${src_lib_general} ${src_lib_matrices} ${src_lib_linear_solvers} ${src_lib_odes} ${src_lib_interpolation} ${src_lib_integration})
#SET(main_source CCncrtSolver)

#SET_TARGET_PROPERTIES(${PROJECT_NAME} LIBRARY_OUTPUT_DIRECTORY ../lib)

## Building library
IF(${lib_type} STREQUAL "SHARED")
	ADD_LIBRARY(${PROJECT_NAME} SHARED ${sources} ${main_source})
ELSE(${lib_type} STREQUAL "STATIC")
	ADD_LIBRARY(${PROJECT_NAME} STATIC ${sources} ${main_source})
ENDIF()

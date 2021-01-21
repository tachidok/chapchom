# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(BASE_SRC_FILES ac_linear_solver.cpp  cc_lu_solver_numerical_recipes.cpp cc_factory_linear_solver.cpp)
SET(ARMADILLO_SRC_FILES cc_solver_armadillo.cpp)

SET(SRC_FILES ${BASE_SRC_FILES})

IF (SCICELLXX_USES_ARMADILLO)
  LIST(APPEND SRC_FILES ${ARMADILLO_SRC_FILES})
ENDIF (SCICELLXX_USES_ARMADILLO)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(linear_solvers_lib STATIC ${SRC_FILES})
ELSEIF(${SCICELLXX_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(linear_solvers_lib SHARED ${SRC_FILES})
ELSE(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(linear_solvers_lib ${SRC_FILES})
ENDIF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(linear_solvers ${CMAKE_CURRENT_SOURCE_DIR})

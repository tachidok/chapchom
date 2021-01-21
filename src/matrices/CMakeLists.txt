# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(BASE_SRC_FILES ac_vector.tpl.cpp cc_vector.tpl.cpp ac_matrix.tpl.cpp cc_matrix.tpl.cpp cc_factory_matrices.tpl.cpp)
SET(ARMADILLO_SRC_FILES cc_vector_armadillo.tpl.cpp cc_matrix_armadillo.tpl.cpp)

SET(SRC_FILES ${BASE_SRC_FILES})

IF (SCICELLXX_USES_ARMADILLO)
  LIST(APPEND SRC_FILES ${ARMADILLO_SRC_FILES})
ENDIF (SCICELLXX_USES_ARMADILLO)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
  ADD_LIBRARY(matrices_lib STATIC ${SRC_FILES})
ELSEIF(${SCICELLXX_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(matrices_lib SHARED ${SRC_FILES})
ELSE(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(matrices_lib ${SRC_FILES})
ENDIF(${SCICELLXX_LIB_TYPE} STREQUAL STATIC)

# Indicate dependencies within libraries (it seems not to be necessary)
#TARGET_LINK_LIBRARIES(matrices_lib general_lib)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(matrices ${CMAKE_CURRENT_SOURCE_DIR})

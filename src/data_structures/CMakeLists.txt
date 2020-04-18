# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES cc_data.cpp cc_node.cpp cc_boundary_node.cpp ac_odes.cpp)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(data_structures_lib STATIC ${SRC_FILES})
ELSEIF(${CHAPCHOM_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(data_structures_lib SHARED ${SRC_FILES})
ELSE(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(data_structures_lib ${SRC_FILES})
ENDIF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)

# Indicate dependencies within libraries (it seems not to be necessary)
#TARGET_LINK_LIBRARIES(data_lib general_lib)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(data ${CMAKE_CURRENT_SOURCE_DIR})

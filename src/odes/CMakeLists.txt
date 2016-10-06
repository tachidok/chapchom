# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_odes.cpp)

# Include current directory to the path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files
ADD_LIBRARY(odes_lib ${SRC_FILES})

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(odes ${CMAKE_CURRENT_SOURCE_DIR})

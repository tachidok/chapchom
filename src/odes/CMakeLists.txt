# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_odes.cpp)

# Create a library with the above files
ADD_LIBRARY(odes ${SRC_FILES})

# Now make the library available for its use
TARGET_INCLUDE_DIRECTORIES(odes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

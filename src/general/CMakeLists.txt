# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES utilities.cpp initialise.cpp)

# Include current directory to the path
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files
ADD_LIBRARY(general ${SRC_FILES})

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(general ${CMAKE_CURRENT_SOURCE_DIR})

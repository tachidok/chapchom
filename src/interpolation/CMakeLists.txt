# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_interpolator.cpp cc_newton_interpolator.cpp)

# Create a library with the above files
ADD_LIBRARY(interpolation ${SRC_FILES})

# Now make the library available for its use
TARGET_INCLUDE_DIRECTORIES(interpolation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

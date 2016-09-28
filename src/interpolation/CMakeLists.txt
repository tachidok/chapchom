# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_interpolator.cpp cc_newton_interpolator.cpp)

# Create a library with the above files
ADD_LIBRARY(interpolation ${SRC_FILES})

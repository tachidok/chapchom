# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES initialise.cpp utilities.cpp)

# Create a library with the above files
ADD_LIBRARY(general ${SRC_FILES})

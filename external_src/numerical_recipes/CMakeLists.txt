# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES lubksb.cpp ludcmp.cpp)

# Create a library with the above files
ADD_LIBRARY(numerical_recipes_lib ${SRC_FILES})

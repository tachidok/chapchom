# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_vector.tpl.cpp cc_vector.tpl.cpp ac_matrix.tpl.cpp cc_matrix.tpl.cpp)

# Create a library with the above files
ADD_LIBRARY(matrices ${SRC_FILES})

# Now make the library available for its use
TARGET_INCLUDE_DIRECTORIES(matrices PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

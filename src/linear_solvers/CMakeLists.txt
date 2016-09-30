# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_linear_solver.tpl.cpp  cc_lu_solver_numerical_recipes.tpl.cpp)

# Create a library with the above files
ADD_LIBRARY(linear_solvers ${SRC_FILES})

# Now make the library available for its use
TARGET_INCLUDE_DIRECTORIES(linear_solvers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

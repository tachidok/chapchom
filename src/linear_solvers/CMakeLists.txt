# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_linear_solver.tpl.cpp  cc_lu_solver_numerical_recipes.tpl.cpp)

# Create a library with the above files
ADD_LIBRARY(linear_solvers ${SRC_FILES})

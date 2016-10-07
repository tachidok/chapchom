# Include testing (this function already calls enable_testing())
include(CTest)

# Indicate source files
SET(SOURCES demo_linear_solver.cpp)

# ... and create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_linear_solver ${SOURCES})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_linear_solver EXCLUDE_FROM_ALL ${SOURCES})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIBRARIES numerical_recipes_lib general_lib matrices_lib linear_solvers_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_linear_solver ${LIBRARIES})

# ===========================================
# Do tests
# ===========================================
# Run the application to check it works
add_test (NAME TEST_check_it_runs
          COMMAND ${SOURCES})
#WORKING_DIRECTORY TESTS
add_test(NAME TEST_check_it_runs_output
         COMMAND ${CMAKE_COMMAND} -E compare_files output_correct.dat output_test.dat)

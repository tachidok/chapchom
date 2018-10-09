# Indicate source files
SET(SRC_demo_linear_solver demo_linear_solver.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_linear_solver ${SRC_demo_linear_solver})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_linear_solver EXCLUDE_FROM_ALL ${SRC_demo_linear_solver})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_linear_solver numerical_recipes_lib general_lib matrices_lib linear_solvers_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_linear_solver ${LIB_demo_linear_solver})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_linear_solver
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_linear_solver_run
          COMMAND demo_linear_solver)
#WORKING_DIRECTORY TESTS
#ADD_TEST(NAME TEST_demo_linear_solver_check_output
#         COMMAND ${CMAKE_COMMAND} -E compare_files output_correct.dat output_test.dat)
IF (CHAPCHOM_USES_DOUBLE_PRECISION)
   SET (VALIDATE_FILENAME_demo_linear_solver "validate_double_demo_linear_solver.dat")
ELSE (CHAPCHOM_USES_DOUBLE_PRECISION)
     SET (VALIDATE_FILENAME_demo_linear_solver "validate_demo_linear_solver.dat")
ENDIF (CHAPCHOM_USES_DOUBLE_PRECISION)
ADD_TEST(NAME TEST_demo_linear_solver_check_output
         COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_linear_solver} ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)
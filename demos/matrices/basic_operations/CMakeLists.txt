# Indicate source files
SET(SRC_demo_matrix_basic_operations demo_matrix_basic_operations.cpp)
SET(SRC_demo_copy_matrices demo_copy_matrices.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations ${SRC_demo_matrix_basic_operations})
  ADD_EXECUTABLE(demo_copy_matrices ${SRC_demo_copy_matrices})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations EXCLUDE_FROM_ALL ${SRC_demo_matrix_basic_operations})
  ADD_EXECUTABLE(demo_copy_matrices EXCLUDE_FROM_ALL ${SRC_demo_copy_matrices})  
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_matrix_basic_operations general_lib matrices_lib)
SET(LIB_demo_copy_matrices general_lib matrices_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_matrix_basic_operations ${LIB_demo_matrix_basic_operations})
TARGET_LINK_LIBRARIES(demo_copy_matrices ${LIB_demo_copy_matrices})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_matrix_basic_operations
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
set_target_properties( demo_copy_matrices
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_matrix_basic_operations_run
         COMMAND demo_matrix_basic_operations)
# Validate output
ADD_TEST(NAME TEST_demo_matrix_basic_operations_check_output
         COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_matrix_basic_operations.dat ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)
# Run the application to check it works
ADD_TEST(NAME TEST_demo_copy_matrices_run
         COMMAND demo_copy_matrices)
# Validate output
ADD_TEST(NAME TEST_demo_copy_matrices_check_output
         COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_copy_matrices.dat ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)

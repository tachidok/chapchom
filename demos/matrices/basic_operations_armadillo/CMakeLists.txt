# Indicate source files
SET(SRC_demo_matrix_basic_operations_armadillo demo_matrix_basic_operations_armadillo.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations_armadillo ${SRC_demo_matrix_basic_operations_armadillo})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations_armadillo EXCLUDE_FROM_ALL ${SRC_demo_matrix_basic_operations_armadillo})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_matrix_basic_operations_armadillo general_lib matrices_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_matrix_basic_operations_armadillo ${LIB_demo_matrix_basic_operations_armadillo})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_matrix_basic_operations_armadillo
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_matrix_basic_operations_armadillo_run
  COMMAND demo_matrix_basic_operations_armadillo)
# Validate output
ADD_TEST(NAME TEST_demo_matrix_basic_operations_armadillo_check_output
  COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_matrix_basic_operations_armadillo.dat ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)


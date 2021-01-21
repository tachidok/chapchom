# Indicate source files
SET(SRC_demo_matrix_basic_operations_armadillo demo_matrix_basic_operations_armadillo.cpp)

# Create executable (check whether compilation was requested or not)
IF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations_armadillo ${SRC_demo_matrix_basic_operations_armadillo})
ELSE(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations_armadillo EXCLUDE_FROM_ALL ${SRC_demo_matrix_basic_operations_armadillo})
ENDIF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_matrix_basic_operations_armadillo general_lib matrices_lib ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
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
IF (SCICELLXX_USES_DOUBLE_PRECISION)
   SET (VALIDATE_FILENAME_demo_matrix_basic_operations_armadillo "validate_double_demo_matrix_basic_operations_armadillo.dat")
ELSE (SCICELLXX_USES_DOUBLE_PRECISION)
     SET (VALIDATE_FILENAME_demo_matrix_basic_operations_armadillo "validate_demo_matrix_basic_operations_armadillo.dat")
ENDIF (SCICELLXX_USES_DOUBLE_PRECISION)
ADD_TEST(NAME TEST_demo_matrix_basic_operations_armadillo_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_matrix_basic_operations_armadillo} ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)

# ===========================================
# Test execution order
# ===========================================
SET_TESTS_PROPERTIES(TEST_demo_matrix_basic_operations_armadillo_check_output PROPERTIES DEPENDS TEST_demo_matrix_basic_operations_armadillo_run)
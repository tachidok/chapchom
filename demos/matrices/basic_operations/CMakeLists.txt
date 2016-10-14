# Indicate source files
SET(SRC_demo_matrix_basic_operations demo_matrix_basic_operations.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations ${SRC_demo_matrix_basic_operations})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations EXCLUDE_FROM_ALL ${SRC_demo_matrix_basic_operations})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_matrix_basic_operations general_lib matrices_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_matrix_basic_operations ${LIB_demo_matrix_basic_operations})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set output directory for executables
set_target_properties( demo_matrix_basic_operations
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_matrix_basic_operations_run
         COMMAND demo_matrix_basic_operations)
#WORKING_DIRECTORY TESTS
ADD_TEST(NAME TEST_demo_matrix_basic_operations_check_output
         COMMAND ${CMAKE_COMMAND} -E compare_files ${CMAKE_CURRENT_SOURCE_DIR}/bin/output_correct.dat ${CMAKE_CURRENT_SOURCE_DIR}/bin/output_test.dat)

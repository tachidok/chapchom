# Set output directory for executables
SET(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE( STATUS "RUNTIME_OUTPUT_DIRECTORY:         " ${RUNTIME_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR:         " ${CMAKE_CURRENT_SOURCE_DIR} )

# Indicate source files
SET(SOURCES demo_matrix_basic_operations.cpp)

# ... and create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations ${SOURCES})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_matrix_basic_operations EXCLUDE_FROM_ALL ${SOURCES})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIBRARIES general_lib matrices_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_matrix_basic_operations ${LIBRARIES})

# ===========================================
# Do tests
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_matrix_basic_operations_run
         COMMAND demo_matrix_basic_operations)
#WORKING_DIRECTORY TESTS
ADD_TEST(NAME TEST_demo_matrix_basic_operations_check_output
         COMMAND ${CMAKE_COMMAND} -E compare_files output_correct.dat output_test.dat)

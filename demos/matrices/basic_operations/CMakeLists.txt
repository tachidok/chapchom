# Include testing (this function already calls enable_testing())
include(CTest)

# Indicate source files
SET(SOURCES demo_matrix_basic_operations.cpp)
# ... and create executable
ADD_EXECUTABLE(demo_matrix_basic_operations ${SOURCES})
# Use this line when we do not require to compile demos
#ADD_EXECUTABLE(demo_matrix_basic_operations EXCLUDE_FROM_ALL ${SOURCES})

# Indicate linking libraries
SET(LIBRARIES general_lib matrices_lib)
# ... and link againts them
TARGET_LINK_LIBRARIES(demo_matrix_basic_operations ${LIBRARIES})

# ===========================================
# Do tests
# ===========================================
# Run the application to check it works
add_test (NAME TEST_check_it_runs
          COMMAND ${SOURCES})
#WORKING_DIRECTORY TESTS
add_test(NAME TEST_check_it_runs_output
         COMMAND ${CMAKE_COMMAND} -E compare_files output_correct.dat output_test.dat)

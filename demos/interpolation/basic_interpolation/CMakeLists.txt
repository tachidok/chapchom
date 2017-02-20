# Indicate source files
SET(SRC_demo_basic_interpolation demo_basic_interpolation.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_interpolation ${SRC_demo_basic_interpolation})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_interpolation EXCLUDE_FROM_ALL ${SRC_demo_basic_interpolation})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_basic_interpolation general_lib interpolation_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_basic_interpolation ${LIB_demo_basic_interpolation})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties(demo_basic_interpolation
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_basic_interpolation_run
          COMMAND demo_basic_interpolation)
ADD_TEST(NAME TEST_demo_basic_interpolation_check_output
         COMMAND sdiff -s ${CMAKE_CURRENT_SOURCE_DIR}/validate/validate_demo_basic_interpolation.dat ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)
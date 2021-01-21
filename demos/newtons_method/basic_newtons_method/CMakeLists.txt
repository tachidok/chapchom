# Indicate source files
SET(SRC_demo_basic_newtons_method demo_basic_newtons_method.cpp)

# Create executable (check whether compilation was requested or not)
IF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_newtons_method ${SRC_demo_basic_newtons_method})
ELSE(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_newtons_method EXCLUDE_FROM_ALL ${SRC_demo_basic_newtons_method})
ENDIF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_basic_newtons_method data_structures_lib matrices_lib equations_lib problem_lib linear_solvers_lib general_lib numerical_recipes_lib)

# Check whether scicellxx is using Armadillo
IF (SCICELLXX_USES_ARMADILLO)
 LIST(APPEND LIB_demo_basic_newtons_method ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (SCICELLXX_USES_ARMADILLO)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_basic_newtons_method ${LIB_demo_basic_newtons_method})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_basic_newtons_method
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_basic_newtons_method_run
         COMMAND demo_basic_newtons_method)
# Validate output
SET (VALIDATE_FILENAME_demo_basic_newtons_method "validate_demo_basic_newtons_method.dat")
ADD_TEST(NAME TEST_demo_basic_newtons_method_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_basic_newtons_method} ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)

SET_TESTS_PROPERTIES(TEST_demo_basic_newtons_method_check_output PROPERTIES DEPENDS TEST_demo_basic_newtons_method_run)
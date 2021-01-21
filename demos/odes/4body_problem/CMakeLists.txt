# Indicate source files and dependencies in the files
SET(SRC_demo_basic_4_body demo_basic_4_body.cpp cc_odes_basic_4_body.cpp)

# Create executable (check whether compilation was requested or not)
IF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_4_body ${SRC_demo_basic_4_body})
ELSE(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_basic_4_body EXCLUDE_FROM_ALL ${SRC_demo_basic_4_body})
ENDIF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_basic_4_body data_structures_lib matrices_lib time_stepper_lib equations_lib vtk_lib problem_lib linear_solvers_lib numerical_recipes_lib argparse_lib general_lib)

# Check whether chapchom is using Armadillo
IF (SCICELLXX_USES_ARMADILLO)
 LIST(APPEND LIB_demo_basic_4_body ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (SCICELLXX_USES_ARMADILLO)

# Check whether chapchom is using VTK (either way this demo is not
# going to work without VTK support, so it should be selected in the
# ./configs/default file)
IF (SCICELLXX_USES_VTK)
  LIST(APPEND LIB_demo_basic_4_body ${VTK_LIBRARIES})
ENDIF (SCICELLXX_USES_VTK)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_basic_4_body ${LIB_demo_basic_4_body})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties(demo_basic_4_body
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_basic_4_body_run
          COMMAND demo_basic_4_body --test)
IF (SCICELLXX_USES_DOUBLE_PRECISION)
   SET (VALIDATE_FILENAME_demo_basic_4_body "validate_4_body.dat")
ELSE (SCICELLXX_USES_DOUBLE_PRECISION)
     SET (VALIDATE_FILENAME_demo_basic_4_body "validate_4_body.dat")
ENDIF (SCICELLXX_USES_DOUBLE_PRECISION)

ADD_TEST(NAME TEST_demo_basic_4_body_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_basic_4_body} ${CMAKE_CURRENT_BINARY_DIR}/output_test.dat)

# ===========================================
# Test execution order
# ===========================================
SET_TESTS_PROPERTIES(TEST_demo_basic_4_body_check_output PROPERTIES DEPENDS TEST_demo_basic_4_body_run)

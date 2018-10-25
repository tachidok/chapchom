# Indicate source files and dependencies in the files
SET(SRC_demo_lotka_volterra demo_lotka_volterra.cpp cc_lotka_volterra_odes.cpp)

# Create executable (check whether compilation was requested or not)
IF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_lotka_volterra ${SRC_demo_lotka_volterra})
ELSE(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_lotka_volterra EXCLUDE_FROM_ALL ${SRC_demo_lotka_volterra})
ENDIF(${CHAPCHOM_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_lotka_volterra data_structures_lib numerical_recipes_lib matrices_lib linear_solvers_lib time_stepper_lib problem_lib general_lib)

# Check whether chapchom is using Armadillo
IF (CHAPCHOM_USES_ARMADILLO)
 LIST(APPEND LIB_demo_lotka_volterra ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (CHAPCHOM_USES_ARMADILLO)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_lotka_volterra ${LIB_demo_lotka_volterra})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_lotka_volterra
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
ADD_TEST(NAME TEST_demo_lotka_volterra_run
         COMMAND demo_lotka_volterra)
# Validate output
SET (VALIDATE_FILENAME_demo_lotka_volterra_euler "validate_euler.dat")
ADD_TEST(NAME TEST_demo_lotka_volterra_euler_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_lotka_volterra_euler} ${CMAKE_CURRENT_BINARY_DIR}/euler.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_lotka_volterra_rk4 "validate_rk4.dat")
ADD_TEST(NAME TEST_demo_lotka_volterra_rk4_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_lotka_volterra_rk4} ${CMAKE_CURRENT_BINARY_DIR}/rk4.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_lotka_volterra_am2pc "validate_am2pc.dat")
ADD_TEST(NAME TEST_demo_lotka_volterra_am2pc_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_lotka_volterra_am2pc} ${CMAKE_CURRENT_BINARY_DIR}/am2pc.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_lotka_volterra_bdf1 "validate_bdf1.dat")
ADD_TEST(NAME TEST_demo_lotka_volterra_bdf1_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_lotka_volterra_bdf1} ${CMAKE_CURRENT_BINARY_DIR}/bdf1.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_lotka_volterra_am2 "validate_am2.dat")
ADD_TEST(NAME TEST_demo_lotka_volterra_am2_check_output
         COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_lotka_volterra_am2} ${CMAKE_CURRENT_BINARY_DIR}/am2.dat)

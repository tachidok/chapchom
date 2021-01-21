# Indicate source files and dependencies in the files
SET(SRC_demo_chen demo_chen.cpp cc_chen_odes.cpp)

# Create executable (check whether compilation was requested or not)
IF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_odes_chen ${SRC_demo_chen})
ELSE(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)
  ADD_EXECUTABLE(demo_odes_chen EXCLUDE_FROM_ALL ${SRC_demo_chen})
ENDIF(${SCICELLXX_BUILD_DEMOS} STREQUAL TRUE)

# Indicate linking libraries
SET(LIB_demo_chen data_structures_lib matrices_lib time_stepper_lib equations_lib problem_lib linear_solvers_lib numerical_recipes_lib argparse_lib general_lib)

# Check whether chapchom is using Armadillo
IF (SCICELLXX_USES_ARMADILLO)
 LIST(APPEND LIB_demo_chen ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (SCICELLXX_USES_ARMADILLO)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_odes_chen ${LIB_demo_chen})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/RESLT)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/RESLT")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/RESLT)

# Set directory where to create the executables
set_target_properties( demo_odes_chen
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# ===========================================
# Tests section
# ===========================================
# Run the application to check it works
SET (VALIDATE_TEST_FOLDER_demo_odes_chen "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
ADD_TEST(NAME TEST_demo_odes_chen_run
  COMMAND ${VALIDATE_TEST_FOLDER_demo_odes_chen}demo_odes_chen --test)
# Validate output 
SET (VALIDATE_FILENAME_demo_odes_chen_rk4_0_200 "validate_rk4_0_200.dat")
ADD_TEST(NAME TEST_demo_odes_chen_rk4_0_200_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_rk4_0_200} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/rk4_0_200.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_odes_chen_rk4_49800_50000 "validate_rk4_49800_50000.dat")
ADD_TEST(NAME TEST_demo_odes_chen_rk4_49800_50000_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_rk4_49800_50000} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/rk4_49800_50000.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_odes_chen_am2pc_2_0_200 "validate_am2pc_2_0_200.dat")
ADD_TEST(NAME TEST_demo_odes_chen_am2pc_2_0_200_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_am2pc_2_0_200} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/am2pc_2_0_200.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_odes_chen_am2pc_2_49800_50000 "validate_am2pc_2_49800_50000.dat")
ADD_TEST(NAME TEST_demo_odes_chen_am2pc_2_49800_50000_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_am2pc_2_49800_50000} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/am2pc_2_49800_50000.dat)
  # Validate output
SET (VALIDATE_FILENAME_demo_odes_chen_bepc_2_0_200 "validate_bepc_2_0_200.dat")
ADD_TEST(NAME TEST_demo_odes_chen_bepc_2_0_200_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_bepc_2_0_200} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/bepc_2_0_200.dat)
# Validate output
SET (VALIDATE_FILENAME_demo_odes_chen_bepc_2_49800_50000 "validate_bepc_2_49800_50000.dat")
ADD_TEST(NAME TEST_demo_odes_chen_bepc_2_49800_50000_check_output
  COMMAND ${PROJECT_SOURCE_DIR}/tools/fpdiff.py ${CMAKE_CURRENT_SOURCE_DIR}/validate/${VALIDATE_FILENAME_demo_odes_chen_bepc_2_49800_50000} ${CMAKE_CURRENT_BINARY_DIR}/RESLT/bepc_2_49800_50000.dat)

# ===========================================
# Test execution order
# ===========================================
SET_TESTS_PROPERTIES(TEST_demo_odes_chen_rk4_0_200_check_output TEST_demo_odes_chen_rk4_49800_50000_check_output TEST_demo_odes_chen_am2pc_2_0_200_check_output TEST_demo_odes_chen_am2pc_2_49800_50000_check_output TEST_demo_odes_chen_bepc_2_0_200_check_output TEST_demo_odes_chen_bepc_2_49800_50000_check_output PROPERTIES DEPENDS TEST_demo_odes_chen_run)

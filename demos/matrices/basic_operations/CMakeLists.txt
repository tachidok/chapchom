# Check for cmake minimum required
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#Project name (this case library's name)
PROJECT(${example_name})
#SET(${PROJET_NAME}_MAJOR_VERSION 1)
#SET(${PROJET_NAME}_MINOR_VERSION 0)
#SET(${PROJET_NAME}_PATCH_LEVEL 0)

# Include testing (this function already calls enable_testing())
include(CTest)

#set default cmake build type to Debug (None Debug Release RelWithDebInfo MinSizeRel)
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

#Set include path
#SET(include_dirs ../../src)

#Adding include directories
INCLUDE_DIRECTORIES(../../../src)

#Adding link directories
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../../lib)

#Adding library's sources
SET(main_source demo_matrix_basic_operations)

ADD_EXECUTABLE(${PROJECT_NAME} ${main_source})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} chapchom)

# ===========================================
# Do tests
# ===========================================
# Run the application to check it works
add_test (NAME TEST_check_it_runs
          COMMAND ${main_source})
#WORKING_DIRECTORY TESTS
add_test(NAME TEST_check_it_runs_output
         COMMAND ${CMAKE_COMMAND} -E compare_files output_correct.dat output_test.dat)

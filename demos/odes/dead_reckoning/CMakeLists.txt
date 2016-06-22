
# Check for cmake minimum required
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#Project name (this case library's name)
PROJECT(${example_name})
#SET(${PROJET_NAME}_MAJOR_VERSION 1)
#SET(${PROJET_NAME}_MINOR_VERSION 0)
#SET(${PROJET_NAME}_PATCH_LEVEL 0)

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
SET(src_files cc_odes_from_table_based_on_velocity)

SET(main_source demo_dead_reckoning_from_velocities)

#FIND_LIBRARY(multirate_path multirate ../../lib)

ADD_EXECUTABLE(${PROJECT_NAME} ${src_files} ${main_source})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} chapchom)

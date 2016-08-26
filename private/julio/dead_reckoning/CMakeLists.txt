
# Check for cmake minimum required
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#Project name (this case library's name)
PROJECT(${example_name})
#SET(${PROJET_NAME}_MAJOR_VERSION 1)
#SET(${PROJET_NAME}_MINOR_VERSION 0)
#SET(${PROJET_NAME}_PATCH_LEVEL 0)

#set default cmake build type to Debug (None Debug Release RelWithDebInfo MinSizeRel)
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

#Adding include directories
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

#Adding link directories
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../../lib)

#Adding library's sources
#SET(src_files cc_odes_from_table_based_on_velocity)
#SET(src_files cc_odes_from_table_based_on_acceleration)
#SET(src_files cc_odes_from_table_based_on_acceleration2)
SET(src_files cc_odes_from_table_from_xsensMT9B)

#SET(main_source demo_dead_reckoning_from_velocities)
#SET(main_source demo_dead_reckoning_from_accelerations)
#SET(main_source demo_dead_reckoning_from_accelerations2)
SET(main_source demo_dead_reckoning_for_xsensMT9B)

#FIND_LIBRARY(multirate_path multirate ../../lib)

ADD_EXECUTABLE(${PROJECT_NAME} ${src_files} ${main_source})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} chapchom)

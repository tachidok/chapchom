# Check for cmake minimum required version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name (this case library's name)
PROJECT(chapchom)
SET(${PROJET_NAME}_MAJOR_VERSION 0)
SET(${PROJET_NAME}_MINOR_VERSION 1)
SET(${PROJET_NAME}_PATCH_LEVEL 0)

# set default cmake build type to Debug (None Debug Release
#  RelWithDebInfo MinSizeRel)
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Debug")
ENDIF()

# Add external source files sub-directories
ADD_SUBDIRECTORY(external_src)

# Add sub-directories with source files
ADD_SUBDIRECTORY(src)

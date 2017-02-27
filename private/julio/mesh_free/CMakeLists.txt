# Indicate source files and dependencies in the files

SET(SRC_demo_distance_matrix demo_distance_matrix.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(demo_distance_matrix EXCLUDE_FROM_ALL ${SRC_demo_distance_matrix})

# Indicate linking libraries
SET(LIB_demo_distance_matrix general_lib matrices_lib)

# ... and link againts them
TARGET_LINK_LIBRARIES(demo_distance_matrix ${LIB_demo_distance_matrix})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_distance_matrix
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

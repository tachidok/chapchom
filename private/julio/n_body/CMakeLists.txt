# Indicate source files and dependencies in the files
SET(SRC_demo_basic_n_body demo_basic_n_body.cpp cc_odes_basic_n_body.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(demo_basic_n_body EXCLUDE_FROM_ALL ${SRC_demo_basic_n_body})

# Indicate linking libraries
SET(LIB_demo_basic_n_body general_lib data_structures_lib time_stepper_lib)

# Check whether chapchom is using VTK (either way this demo is not
# going to work without VTK support, so it should be selected in the
# ./configs/default file)
IF (CHAPCHOM_USES_VTK)
  LIST(APPEND LIB_demo_basic_n_body ${VTK_LIBRARIES})
ENDIF (CHAPCHOM_USES_VTK)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_basic_n_body ${LIB_demo_basic_n_body})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_basic_n_body
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )


# Indicate source files and dependencies in the files
SET(SRC_demo_basic_3_body demo_basic_3_body.cpp cc_odes_basic_3_body.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(demo_basic_3_body EXCLUDE_FROM_ALL ${SRC_demo_basic_3_body})

# Indicate linking libraries
SET(LIB_demo_basic_3_body data_structures_lib matrices_lib time_stepper_lib equations_lib vtk_lib problem_lib linear_solvers_lib numerical_recipes_lib argparse_lib general_lib)

# Check whether chapchom is using Armadillo
IF (CHAPCHOM_USES_ARMADILLO)
 LIST(APPEND LIB_demo_basic_3_body ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (CHAPCHOM_USES_ARMADILLO)

# Check whether chapchom is using VTK (either way this demo is not
# going to work without VTK support, so it should be selected in the
# ./configs/default file)
IF (CHAPCHOM_USES_VTK)
  LIST(APPEND LIB_demo_basic_3_body ${VTK_LIBRARIES})
ENDIF (CHAPCHOM_USES_VTK)

# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_basic_3_body ${LIB_demo_basic_3_body})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_basic_3_body
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )


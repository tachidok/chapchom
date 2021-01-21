# Indicate source files and dependencies in the files
SET(SRC_demo_non_symmetric_RBF demo_non_symmetric_RBF_collocation.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(julio_demo_non_symmetric_RBF EXCLUDE_FROM_ALL ${SRC_demo_non_symmetric_RBF})

# Indicate linking libraries
SET(LIB_demo_non_symmetric_RBF numerical_recipes_lib argparse_lib general_lib matrices_lib ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} linear_solvers_lib vtk_lib)

# Check whether chapchom is using VTK (either way this demo is not
# going to work without VTK support, so it should be selected in the
# ./configs/default file)
IF (SCICELLXX_USES_VTK)
  LIST(APPEND LIB_demo_non_symmetric_RBF ${VTK_LIBRARIES})
ENDIF (SCICELLXX_USES_VTK)

# ... and link againts them
TARGET_LINK_LIBRARIES(julio_demo_non_symmetric_RBF ${LIB_demo_non_symmetric_RBF})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( julio_demo_non_symmetric_RBF
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

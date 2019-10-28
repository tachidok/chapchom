# Indicate source files and dependencies in the files
SET(SRC_demo_first_RBF demo_first_RBF.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(julio_demo_first_RBF EXCLUDE_FROM_ALL ${SRC_demo_first_RBF})

# Indicate linking libraries
SET(LIB_demo_first_RBF numerical_recipes_lib general_lib matrices_lib ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} linear_solvers_lib)

# ... and link againts them
TARGET_LINK_LIBRARIES(julio_demo_first_RBF ${LIB_demo_first_RBF})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( julio_demo_first_RBF
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

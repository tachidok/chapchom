# Indicate source files and dependencies in the files
SET(SRC_lotka_volterra demo_lotka_volterra.cpp cc_lotka_volterra_odes.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(julio_demo_lotka_volterra EXCLUDE_FROM_ALL ${SRC_lotka_volterra})

# Indicate linking libraries
SET(LIB_lotka_volterra data_structures_lib numerical_recipes_lib matrices_lib linear_solvers_lib time_stepper_lib problem_lib general_lib)

# Check whether chapchom is using Armadillo
IF (CHAPCHOM_USES_ARMADILLO)
 LIST(APPEND LIB_lotka_volterra ${ARMADILLO_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
ENDIF (CHAPCHOM_USES_ARMADILLO)

# ... and link againts them  
TARGET_LINK_LIBRARIES(julio_demo_lotka_volterra ${LIB_lotka_volterra})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( julio_demo_lotka_volterra
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )


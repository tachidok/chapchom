# Add directories with demo/test cases
ADD_SUBDIRECTORY(basic_direct_solver)
IF (CHAPCHOM_USES_ARMADILLO)
  ADD_SUBDIRECTORY(basic_armadillo_solver)
ENDIF (CHAPCHOM_USES_ARMADILLO)

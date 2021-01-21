# Add directories with demo/test cases
ADD_SUBDIRECTORY(basic_direct_solver)
IF (SCICELLXX_USES_ARMADILLO)
  ADD_SUBDIRECTORY(basic_armadillo_solver)
ENDIF (SCICELLXX_USES_ARMADILLO)

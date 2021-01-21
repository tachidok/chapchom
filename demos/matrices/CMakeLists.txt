# Add directories with demo/test cases
ADD_SUBDIRECTORY(basic_operations)
IF (SCICELLXX_USES_ARMADILLO)
   ADD_SUBDIRECTORY(basic_operations_armadillo)
ENDIF (SCICELLXX_USES_ARMADILLO)


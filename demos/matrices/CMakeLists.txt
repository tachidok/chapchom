# Add directories with demo/test cases
ADD_SUBDIRECTORY(basic_operations)
IF (CHAPCHOM_USES_ARMADILLO)
   ADD_SUBDIRECTORY(basic_operations_armadillo)
ENDIF (CHAPCHOM_USES_ARMADILLO)


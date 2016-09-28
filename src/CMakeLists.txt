# Add directories with source files (in order of dependence, the ones
# with no dependency first then the others)
ADD_SUBDIRECTORY(general)
ADD_SUBDIRECTORY(matrices)
ADD_SUBDIRECTORY(linear_solvers)
ADD_SUBDIRECTORY(odes)
ADD_SUBDIRECTORY(interpolation)
ADD_SUBDIRECTORY(integration)

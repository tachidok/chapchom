# Add source files in order of dependence, the ones with no dependency
# first then the others
SET(SRC_FILES ac_time_stepper.cpp cc_euler_method.cpp cc_runge_kutta_4_method.cpp ac_predictor_corrector_time_stepper.cpp cc_backward_euler_predictor_corrector_method.cpp cc_adams_moulton_2_predictor_corrector_method.cpp ac_adaptive_new_step_size_strategy.cpp cc_adaptive_new_step_size_half_double.cpp ac_adaptive_time_stepper.cpp cc_adaptive_runge_kutta_45F_method.cpp cc_adaptive_runge_kutta_45DP_method.cpp ac_jacobian_and_residual_for_implicit_time_stepper.cpp ac_newtons_method_for_implicit_time_stepper.cpp cc_jacobian_by_fd_and_residual_from_odes.cpp cc_jacobian_and_residual_for_backward_euler.cpp cc_newtons_method_for_backward_euler.tpl.cpp cc_backward_euler_method.tpl.cpp cc_jacobian_and_residual_for_adams_moulton_2.cpp cc_newtons_method_for_adams_moulton_2.tpl.cpp cc_adams_moulton_2_method.tpl.cpp cc_jacobian_and_residual_for_bdf_2.cpp cc_newtons_method_for_bdf_2.tpl.cpp cc_bdf_2_method.tpl.cpp cc_factory_time_stepper.tpl.cpp)

# Include current directory to the path
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

# Create a library with the above files based on the requested library
# version
IF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(time_stepper_lib STATIC ${SRC_FILES})
ELSEIF(${CHAPCHOM_LIB_TYPE} STREQUAL SHARED)
 ADD_LIBRARY(time_stepper_lib SHARED ${SRC_FILES})
ELSE(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)
 ADD_LIBRARY(integration_lib {SRC_FILES})
ENDIF(${CHAPCHOM_LIB_TYPE} STREQUAL STATIC)

# Now make the library available for its use
#TARGET_INCLUDE_DIRECTORIES(time_stepper ${CMAKE_CURRENT_SOURCE_DIR})

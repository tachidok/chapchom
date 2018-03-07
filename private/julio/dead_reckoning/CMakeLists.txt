# Indicate source files and dependencies in the files

SET(SRC_demo_dead_reckoning_for_xsensMT9B demo_dead_reckoning_for_xsensMT9B.cpp cc_odes_from_table_from_xsensMT9B.cpp)

SET(SRC_demo_nmea_decoder_test demo_cc_nmea_decoder_test.cpp cc_nmea_decoder.cpp)

SET(SRC_demo_ublox_decoder_test demo_cc_ublox_decoder_test.cpp cc_ublox_decoder.cpp)

SET(SRC_demo_dead_reckoning_for_TelitSL869DR demo_dead_reckoning_for_TelitSL869-DR.cpp cc_odes_from_sensors_TelitSL869-DR.cpp cc_nmea_decoder.cpp)

SET(SRC_demo_dead_reckoning_for_TelitSL869DR_based_on_plan demo_dead_reckoning_for_TelitSL869-DR_based_on_plan.cpp cc_odes_from_sensors_TelitSL869-DR.cpp cc_nmea_decoder.cpp)

SET(SRC_demo_dead_reckoning_for_GEOFOG3D_based_on_plan demo_dead_reckoning_for_GEOFOG3D_based_on_plan.cpp cc_odes_from_sensors_GEOFOG3D.cpp)

SET(SRC_demo_dead_reckoning_for_more_data demo_dead_reckoning_for_more_data.cpp cc_odes_from_sensors_more_data.cpp)

SET(SRC_demo_dead_reckoning_for_UBLOX_based_on_plan demo_dead_reckoning_for_UBLOX_based_on_plan.cpp cc_odes_from_sensors_UBLOX.cpp cc_nmea_decoder.cpp cc_ublox_decoder.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(demo_dead_reckoning_for_xsensMT9B EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_xsensMT9B})
ADD_EXECUTABLE(demo_nmea_decoder_test EXCLUDE_FROM_ALL ${SRC_demo_nmea_decoder_test})
ADD_EXECUTABLE(demo_ublox_decoder_test EXCLUDE_FROM_ALL ${SRC_demo_ublox_decoder_test})
ADD_EXECUTABLE(demo_dead_reckoning_for_TelitSL869DR EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_TelitSL869DR})
ADD_EXECUTABLE(demo_dead_reckoning_for_TelitSL869DR_based_on_plan EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_TelitSL869DR_based_on_plan})
ADD_EXECUTABLE(demo_dead_reckoning_for_GEOFOG3D_based_on_plan EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_GEOFOG3D_based_on_plan})
ADD_EXECUTABLE(demo_dead_reckoning_for_more_data EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_more_data})
ADD_EXECUTABLE(demo_dead_reckoning_for_UBLOX_based_on_plan EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_UBLOX_based_on_plan})

# Indicate linking libraries
SET(LIB_demo_dead_reckoning_for_xsensMT9B general_lib odes_lib integration_lib interpolation_lib)
SET(LIB_demo_nmea_decoder_test general_lib)
SET(LIB_demo_ublox_decoder_test general_lib)
SET(LIB_demo_dead_reckoning_for_TelitSL869DR general_lib odes_lib integration_lib)
SET(LIB_demo_dead_reckoning_for_TelitSL869DR_based_on_plan general_lib odes_lib integration_lib)
SET(LIB_demo_dead_reckoning_for_GEOFOG3D_based_on_plan general_lib odes_lib integration_lib)
SET(LIB_demo_dead_reckoning_for_more_data general_lib odes_lib integration_lib)
SET(LIB_demo_dead_reckoning_for_UBLOX_based_on_plan general_lib odes_lib integration_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_xsensMT9B ${LIB_demo_dead_reckoning_for_xsensMT9B})
TARGET_LINK_LIBRARIES(demo_nmea_decoder_test ${LIB_demo_nmea_decoder_test})
TARGET_LINK_LIBRARIES(demo_ublox_decoder_test ${LIB_demo_ublox_decoder_test})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_TelitSL869DR ${LIB_demo_dead_reckoning_for_TelitSL869DR})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_TelitSL869DR_based_on_plan ${LIB_demo_dead_reckoning_for_TelitSL869DR_based_on_plan})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_GEOFOG3D_based_on_plan ${LIB_demo_dead_reckoning_for_GEOFOG3D_based_on_plan})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_more_data ${LIB_demo_dead_reckoning_for_more_data})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_UBLOX_based_on_plan ${LIB_demo_dead_reckoning_for_UBLOX_based_on_plan})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_xsensMT9B
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

# Set directory where to create the executables
set_target_properties( demo_nmea_decoder_test
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_ublox_decoder_test
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_TelitSL869DR
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_TelitSL869DR_based_on_plan
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_GEOFOG3D_based_on_plan
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_more_data
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )

# Set directory where to create the executables
set_target_properties( demo_dead_reckoning_for_UBLOX_based_on_plan
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  )


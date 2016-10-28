# Indicate source files and dependencies in the files
SET(SRC_demo_dead_reckoning_for_xsensMT9B demo_dead_reckoning_for_xsensMT9B.cpp cc_odes_from_table_from_xsensMT9B.cpp)

SET(SRC_demo_nmea_decoder_test demo_cc_nmea_decoder_test.cpp cc_nmea_decoder.cpp)

SET(SRC_demo_dead_reckoning_for_TelitSL869DR demo_dead_reckoning_for_TelitSL869-DR.cpp cc_odes_from_sensors_TelitSL869-DR.cpp cc_nmea_decoder.cpp)

# Do not create executable but add them to the 'make' list
ADD_EXECUTABLE(demo_dead_reckoning_for_xsensMT9B EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_xsensMT9B})
ADD_EXECUTABLE(demo_nmea_decoder_test EXCLUDE_FROM_ALL ${SRC_demo_nmea_decoder_test})
ADD_EXECUTABLE(demo_dead_reckoning_for_TelitSL869DR EXCLUDE_FROM_ALL ${SRC_demo_dead_reckoning_for_TelitSL869DR})

# Indicate linking libraries
SET(LIB_demo_dead_reckoning_for_xsensMT9B general_lib odes_lib integration_lib interpolation_lib)
SET(LIB_demo_nmea_decoder_test general_lib)
SET(LIB_demo_dead_reckoning_for_TelitSL869DR general_lib odes_lib integration_lib)
# ... and link againts them  
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_xsensMT9B ${LIB_demo_dead_reckoning_for_xsensMT9B})
TARGET_LINK_LIBRARIES(demo_nmea_decoder_test ${LIB_demo_nmea_decoder_test})
TARGET_LINK_LIBRARIES(demo_dead_reckoning_for_TelitSL869DR ${LIB_demo_dead_reckoning_for_TelitSL869DR})

# Check if the output/bin directory exists
IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
  # Then create the directory
  FILE(MAKE_DIRECTORY "${bin}")
ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Set output directory for executables
set_target_properties( demo_dead_reckoning_for_xsensMT9B
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

# Set output directory for executables
set_target_properties( demo_nmea_decoder_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

# Set output directory for executables
set_target_properties( demo_dead_reckoning_for_TelitSL869DR
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    )

#Adding library's sources
#SET(src_files cc_odes_from_table_based_on_velocity)
#SET(src_files cc_odes_from_table_based_on_acceleration)
#SET(src_files cc_odes_from_table_based_on_acceleration2)
#SET(src_files cc_odes_from_table_from_xsensMT9B)

#SET(main_source demo_dead_reckoning_from_velocities)
#SET(main_source demo_dead_reckoning_from_accelerations)
#SET(main_source demo_dead_reckoning_from_accelerations2)
#SET(main_source demo_dead_reckoning_for_xsensMT9B)

#ifndef CCUBLOXDECODER_H
#define CCUBLOXDECODER_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

#include <fstream>
#include <iostream>

namespace chapchom
{
 /// \struct UBX_ESF_RAW cc_ublox_decoder.h
 
 /// Stores the information decoded from the block UBX-ESF-RAW. See page 224
 struct UBX_ESF_RAW
 {
  bool valid_gyroscope_temperature;
  double time_gyroscope_temperature;
  double gyroscope_temperature;
  bool valid_gyroscope_x;
  double time_gyroscope_x;
  double gyroscope_x;
  bool valid_gyroscope_y;
  double time_gyroscope_y;
  double gyroscope_y;
  bool valid_gyroscope_z;
  double time_gyroscope_z;
  double gyroscope_z;
  bool valid_accelerometer_x;
  double time_accelerometer_x;
  double accelerometer_x;
  bool valid_accelerometer_y;
  double time_accelerometer_y;
  double accelerometer_y;
  bool valid_accelerometer_z;
  double time_accelerometer_z;
  double accelerometer_z;
 };
 
 /// \class CCUBLOXDecoder cc_ubloc_decoder.h
 
 /// This class reads data provided in the UBX Protocol. See page 131
 /// for an introduction
 class CCUBLOXDecoder
 {
  
 public:
  
  // Constructor, establish the maximum number of fields, the maximum
  // size of the fields, and the size of the checksum (in bytes)
  CCUBLOXDecoder(const unsigned max_fields = 7,
                 const unsigned max_fields_size = 4,
                 const unsigned checksum_size = 2);
  
  // Destructor (release allocated memory)
  virtual ~CCUBLOXDecoder();
  
  // Eats a byte, validates the byte as part of the UBX protocol and
  // stores its entry in a matrix structure containing the parsed
  // information
  void parse(const unsigned char character);
  
  // Method to check whether new values from ubx-esf-raw block are ready
  // or not
  inline bool is_ubx_esf_raw_data_ready() {return UBX_ESF_RAW_data_ready;}
  
  // Indicate that the ubx-esf-raw block data has been processed
  inline void consume_ubx_esf_raw_data() {UBX_ESF_RAW_data_ready = false;}
  
  // Return a reference to the structure PSTM3DACC
  inline struct UBX_ESF_RAW &get_ubx_esf_raw() {return ubx_esf_raw;}
  
 protected:
  
  // Initialise any variables (of the state machine). This method is
  // called any time a non-valid UBX protocol data is identified
  void reset_state_machine();
  
  // Clean-up any info. stored in the Fields matrix
  void clean_fields_matrix();
  
  // Decode message and fill the corresponding data structure
  void decode_message_and_fill_structure();
  
  // The maximum number of fields
  const unsigned Max_fields;
  
  // The maximum size of each field
  const unsigned Max_fields_size;
  
  // Stores the maximum number of entries of the NMEA string
  const unsigned Max_UBX_block_size;
  
  // Stores the allowed size for the checksum
  const unsigned Checksum_size;
  
  // The number of read bytes from the input UBLOX data block
  unsigned Counter_n_read_characters;
  
  // Total number of fields identified in the UBLOX data block
  unsigned Total_number_of_fields;
  
  // The current number of fields identified in the UBLOX data block
  unsigned Counter_n_current_fields;
  
  // Current state on the state machine
  unsigned Current_state;
  
  // The last state on the state machine
  unsigned Last_state;
  
  // Stores the checksum read from the UBLOX data block
  char* Input_checksum;
  
  // Stores the identified fields of the UBLOX data block. It
  // stores each identified data of the UBLOX data block in a cell o the matrix
  // Fields[0] = number
  // Fields[1] = number
  // Fields[2] = number
  char **Fields;
  
  // Matrix with the transitions of the state machine
  unsigned *State_machine_transitions;
  
  // The number of states in the state machine
  const unsigned NStates;
  
  // The number of transitions on of the state machine
  const unsigned NTransitions;
  
  // Final state of the state machine
  unsigned Final_state;
  
  // Stores the computed checksum of the currently reading UBLOX data
  // block
  unsigned Computed_checksum;
   
 private:
  
  // Decode the UBX-ESF-RAW block and fill the corresponding data
  // structure
  bool decode_UBX_ESF_RAW_and_fill_structure();
  
  // Print the data stored in the UBX_ESF_RAW structure
  void print_UBX_ESF_RAW_structure(); 
  
  // Structure to store the values received from the UBX-ESF-RAW data
  // block
  struct UBX_ESF_RAW ubx_esf_raw;
  
  // Flag to indicate that new values from the UBX-ESF-RAW data block
  // are ready
  bool UBX_ESF_RAW_data_ready; 
  
 };
  
}

#endif // #ifndef CCUBLOXDECODER_H

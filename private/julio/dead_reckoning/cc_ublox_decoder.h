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
  unsigned int time_gyroscope_temperature;
  double gyroscope_temperature;
  bool valid_gyroscope_x;
  unsigned int time_gyroscope_x;
  double gyroscope_x;
  bool valid_gyroscope_y;
  unsigned int time_gyroscope_y;
  double gyroscope_y;
  bool valid_gyroscope_z;
  unsigned int time_gyroscope_z;
  double gyroscope_z;
  bool valid_accelerometer_x;
  unsigned int time_accelerometer_x;
  double accelerometer_x;
  bool valid_accelerometer_y;
  unsigned int time_accelerometer_y;
  double accelerometer_y;
  bool valid_accelerometer_z;
  unsigned int time_accelerometer_z;
  double accelerometer_z;
 };
 
 /// \class CCUBLOXDecoder cc_ubloc_decoder.h
 
 /// This class reads data provided in the UBX Protocol. See page 131
 /// for an introduction
 class CCUBLOXDecoder
 {
  
 public:
  
  // Constructor, establish the size of the checksum (in bytes)
  CCUBLOXDecoder(const unsigned checksum_size = 2);
  
  // Destructor (release allocated memory)
  virtual ~CCUBLOXDecoder();
  
  // Eats a byte, validates the bytes as part of the UBX
  // protocol. Also in charge of calling the proper methods to store
  // the info. in the corresponding data structures
  void parse(const unsigned char &byte);
  
  // Method to check whether new values from ubx-esf-raw block are ready
  // or not
  inline bool is_UBX_ESF_RAW_data_ready() {return UBX_ESF_RAW_data_ready;}
  
  // Indicate that the UBX-ESF-RAW block data has been processed
  inline void consume_UBX_ESF_RAW_data() {UBX_ESF_RAW_data_ready = false;}
  
  // Return a reference to the structure UBX-ESF-RAW
  inline struct UBX_ESF_RAW &get_UBX_ESF_RAW() {return UBX_ESF_RAW;}
  
 protected:
  
  // Initialise any variables (of the state machine). This method is
  // called any time a non-valid UBX protocol data is identified
  void reset_general_state_machine();
  
  // In charge of cleaning the checksum
  void reset_checksum();
  
  // In charge of filling the class and IDs numbers of the data blocks
  // that are decoded
  void fill_class_and_ids();
  
  // The number of read bytes from the input UBLOX data block
  unsigned Counter_n_read_bytes;
  
  // Current state on the state machine
  int Current_general_state;
  
  // The last state on the state machine
  int Last_general_state;
    
  // Matrix with the transitions of the general state machine
  int *General_transition_matrix;
  
  // The number of states in the general state machine
  const unsigned NGeneral_states;
  
  // The number of transitions of the general state machine
  const unsigned NGeneral_transitions;
  
  // Final state of the general state machine
  int General_final_state;
  
  // Stores the allowed size for the checksum
  const unsigned Checksum_size;
  
  // Stores the checksum read from the UBLOX data block
  unsigned char* Read_checksum;
  
  // Stores the computed checksum of the currently reading UBLOX data
  // block
  unsigned char *Computed_checksum;
  
  // The index of the computed checksum
  unsigned Computed_checksum_index;
  
  // Stores the two bytes of the payload
  unsigned char Payload_byte1;
  unsigned char Payload_byte2;
  
  // Store the length of the payload
  int Payload_length;
  
  // Keep track of the number of bytes read from the payload
  unsigned N_read_payload_bytes;
  
  // Store the class_id
  unsigned char Class_id_c;
  
  // Set with the class ids that are decoded
  std::set<unsigned char> Class_id;
  
  // Store the id
  unsigned char ID_c;
  
  // Set with the ids decoded
  std::set<unsigned char> IDs;
  
 private:
  
  // Initialise any variables (of the UBX-ESF-RAW state machine). This
  // method is called any time a non-valid UBX protocol data is
  // identified
  void reset_UBX_ESF_RAW_state_machine();
  
  // The number of read bytes from the input UBLOX data block
  unsigned Counter_UBX_ESF_RAW_n_read_bytes;

  // A counter to indicate the beggining and end of each UBX-ESF-RAW
  // block
  unsigned Local_block_UBX_ESF_RAW_counter;
  
  // Set all data in UBX-ESF-RAW block as invalid
  void set_UBX_ESF_RAW_data_as_invalid();
  
  // Set all data in UBX-ESF-RAW block as valid
  void set_UBX_ESF_RAW_data_as_valid();
  
  // The data blocks of the UBX-ESF-RAW are of four bytes
  unsigned char UBX_ESF_RAW_data_block[4];
  
  // Indicate whether we are decoding the data or the sTtag part
  bool Is_data_part;

  // Keep track of the data type we are currently working on
  unsigned char Data_type;
  
  // Number of data expected in a block of data (7 data = 3 acc data +
  // 3 gyro data + 1 gyro temperature)
  unsigned N_UBX_ESF_RAW_data_block;
  
  // Decode the UBX-ESF-RAW block and fill the corresponding data
  // structure
  bool decode_UBX_ESF_RAW_and_fill_structure(const unsigned char &byte);
  
  // Print the data stored in the UBX_ESF_RAW structure
  void print_UBX_ESF_RAW_structure(); 
  
  // Structure to store the values received from the UBX-ESF-RAW data
  // block
  struct UBX_ESF_RAW UBX_ESF_RAW;
  
  // Flag to indicate that new values from the UBX-ESF-RAW data block
  // are ready
  bool UBX_ESF_RAW_data_ready;
  
 };
  
}

#endif // #ifndef CCUBLOXDECODER_H

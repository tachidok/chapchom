/** \file This file implements the CCUBLOXDecoder class
 */
#include "cc_ublox_decoder.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor, establish the size of the checksum (in bytes)
 // ===================================================================
 CCUBLOXDecoder::CCUBLOXDecoder(const unsigned checksum_size)
  : NGeneral_states(10), NGeneral_transitions(5),
    Checksum_size(checksum_size),
    NUBX_ESF_RAW_states(3),
    NUBX_ESF_RAW_transitions(1),
    UBX_ESF_RAW_data_ready(false)
 {
  // ----------------------------------------------------------
  // Finite state machine
  // ----------------------------------------------------------
  // Resize the transition matrix
  const unsigned n_general_states = NGeneral_states;
  const unsigned n_general_transitions = NGeneral_transitions;
  
  // The transition matrix
  int general_transition_matrix[] =
   {
    1, 0, 0, 0, 0,
    1, 2, 0, 0, 0,
    1, 0, 3, 0, 0,
    1, 0, 0, 4, 0,
    1, -1, -1, -1, 5,
    1, -1, -1, -1, 6,
    6, 6, 6, 6, 6,
    -1, -1, -1, -1, 8,
    -1, -1, -1, -1, 9,
    -1, -1, -1, -1, -1
   };
  
  // Allocate memory for the general transition matrix
  General_transition_matrix = new int[n_general_states*n_general_transitions];
  // Copy the "general_transition_matrix" into the "General_transition_matrix"
  // structure
  unsigned k = 0;
  for (unsigned i = 0; i < n_general_states; i++)
   {
    for (unsigned j = 0; j < n_general_transitions; j++)
     {
      General_transition_matrix[i*n_general_transitions+j] = general_transition_matrix[k++];
     } // for (j < n_general_transitions)
    
   } // for (i < n_general_states)
  
  // Allocate memory to store checksum entries
  Read_checksum = new unsigned char[checksum_size];
  
  // Initialise/reset state machine and checksum vector
  reset_general_state_machine();
  
  // Establish the final state
  General_final_state = 10;

  // ----------------------------------------------------------
  // Reset all particular state machines
  // ----------------------------------------------------------
  reset_UBX_ESF_RAW_state_machine();
  
  // ----------------------------------------------------------
  // Mark all data structures as invalid
  // ----------------------------------------------------------
  set_UBX_ESF_RAW_data_as_invalid();

  // ----------------------------------------------------------
  // Fill the sets with the class and ids that are decoded
  // ----------------------------------------------------------
  fill_class_and_ids();
  
 }
 
 // ===================================================================
 // Destructor (release allocated memory)
 // ===================================================================
 CCUBLOXDecoder::~CCUBLOXDecoder()
 {
  // Free memory for state machien transitions
  delete General_transition_matrix;
  General_transition_matrix = 0;
  
  // Free memory for checksum (read/computed)
  delete Read_checksum;
  Read_checksum = 0;
  
  // Free memory for all particular state machines
  delete UBX_ESF_RAW_transition_matrix;
  UBX_ESF_RAW_transition_matrix = 0;
  
 }
 
 // ===================================================================
 // Eats a byte, validates the bytes as part of the UBX
 // protocol. Also in charge of calling the proper methods to store
 // the info. in the corresponding data structures
 // ===================================================================
 void CCUBLOXDecoder::parse(const unsigned byte)
 {
  // Keep track of the last state of the general state machine (before
  // doing the change to the next state)
  Last_general_state = Current_general_state;
  // Increase the number of read chacacters
  Counter_n_read_bytes++;
  
  // Check whether the parsed-byte is part of the Class_id set
  std::set<unsigned char>::iterator it_class = Class_id.find(byte);
  // Check whether the parsed-byte is part of the Class_id set
  std::set<unsigned char>::iterator it_id = IDs.find(byte);
  
  // ------------------------------------------------------------------
  // Identify the read byte and transition accordingly
  // ------------------------------------------------------------------
  if (byte == 0xB5) // Indicates the beggining of the header of
   // the UBX Protocol. Header first part
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+0];
   }
  else if (byte == 0x62) // Header second part
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+1];
   }
  else if (it_class != Class_id.end()) // Class
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+2];
   }
  else if (it_id != IDs.end()) // ID
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+3];
   }
  else if (byte == 0x2A) // Any byte
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+4];
   }
  
  // -----------------------------------------------------------------------
  // Is there something we need to do in each state?
  // -----------------------------------------------------------------------
  if (Current_general_state == 3)
   {
    // Save the class id
    Class_id_c = byte;
   }
  else if (Current_general_state == 4)
   {
    // Save the ID
    ID_c = byte;
   }
  else if (Current_general_state == 5)
   {
    // Save the payload byte 1
    Payload_byte1 = byte;
    // Add the byte to the payload storage
    Payload_length = 0xFF00 & (byte << 8);
   }
  else if (Current_general_state == 6 && Last_general_state == 5)
   {
    // Save the payload byte 2
    Payload_byte2 = byte;
    // Add the byte to the payload storage
    Payload_length = 0x00FF & byte;
    // Based on the size of the payload allocate storage for the
    // checksum
    Computed_checksum = new unsigned char[Payload_length+4];
    // Add the stored bytes until now that are part of the checksum
    Computed_checksum[0] = Class_id_c;
    Computed_checksum[1] = ID_c;
    Computed_checksum[2] = Payload_byte1;
    Computed_checksum[3] = Payload_byte2;
    Computed_checksum_index = 4;
   }
  // This is not the first time we are in this state - thus ...
  else if (Current_general_state == 6 && Last_general_state == 6)
   {
    // Add the element to the checksum list
    Computed_checksum[Computed_checksum_index++] = byte;
    // Call the sub-parser method and check whether we should override
    // the transition to the next state
    bool override_transition_to_the_next_state = true;
    if (override_transition_to_the_next_state)
     {
      // Treat the read byte as if we were already in state 7 and do
      // the corresponding transition
      Current_general_state = 8;
      Read_checksum[0] = byte; // CK_A
     }
   }
  else if (Current_general_state == 8)
   {
    // Add the element to the checksum list
    Computed_checksum[Computed_checksum_index++] = byte;
    Read_checksum[1] = byte; // CK_B
   }
  
  // Check whether we have reached a final state
  if (Current_general_state == General_final_state) // TODO IMPLEMENT THE DECODING OF THE CHECKSUM
   {
    unsigned CK_A = 0;
    unsigned CK_B = 0;
    // Loop over the elements used to create the checksum
    for (int i = 0; i < Payload_length + 4; i++)
     {
      
      
     }
    // Validate the checksum
    char *computed_checksum_hex = new char[Checksum_size];
    // Transform to hexadecimal
    sprintf(computed_checksum_hex, "%02X", Computed_checksum);
    // To upper case
    std::string str(Input_checksum);
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    
    if (strcmp(str.c_str(), computed_checksum_hex)!=0)
     {
      reset_state_machine();
      // Error message
      std::ostringstream error_message;
      error_message << "The checksum is not correct\n"
                    << "We got [" << computed_checksum_hex << "] as the computed checksum,\n"
                    << "and [" << str << "] as the checksum in the input string."
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }

    // Free memory
    delete computed_checksum_hex;
    computed_checksum_hex = 0;
    
    decode_message_and_fill_structure();
    
   }
  
 }
 
 // ===================================================================
 // Initialise any variables (of the state machine). This method is
 // called any time a non-valid UBX protocol data is identified
 // ===================================================================
 void CCUBLOXDecoder::reset_general_state_machine()
 {
  // Reset state information of the general state machine
  Current_general_state = 0;
  Last_general_state = 0;
  // Initialise the number of read bytes
  Counter_n_read_bytes = 0;
  // Reset checksum
  reset_checksum();
  // Reset the payload length
  Payload_length = 0;
 }
 
 // ===================================================================
 // In charge of cleaning the checksum
 // ===================================================================
 void CCUBLOXDecoder::reset_checksum()
 {
  for (unsigned i = 0; i < Checksum_size; i++)
   {
    Read_checksum[i] = 0;
   }
 }
 
 // ===================================================================
 // In charge of filling the class and IDs numbers of the data blocks
 // that are decoded
 // ===================================================================
 void CCUBLOXDecoder::fill_class_and_ids()
 {
  // Fill the data structures with the corresponding data blocks to
  // decode
  Class_id.insert(0x10);
  IDs.insert(0x03);
 }
 
 // ===================================================================
 // Initialise any variables (of the UBX-ESF-RAW state machine). This
 // method is called any time a non-valid UBX protocol data is
 // identified
 // ===================================================================
 void CCUBLOXDecoder::reset_UBX_ESF_RAW_state_machine()
 {
  // The number of read bytes from the input UBLOX data block
  // Reset state information of the UBX-ESF-RAW state machine
  Counter_UBX_ESF_RAW_n_read_bytes = 0;
  Current_UBX_ESF_RAW_general_state = 0;
  Last_UBX_ESF_RAW_general_state = 0;
 }
 
 // ===================================================================
 // Set all data in UBX-ESF-RAW block as invalid
 // ===================================================================
 void CCUBLOXDecoder::set_UBX_ESF_RAW_data_as_invalid()
 {
  UBX_ESF_RAW.valid_gyroscope_temperature = false;
  UBX_ESF_RAW.valid_gyroscope_x = false;
  UBX_ESF_RAW.valid_gyroscope_y = false;
  UBX_ESF_RAW.valid_gyroscope_z = false;
  UBX_ESF_RAW.valid_accelerometer_x = false;
  UBX_ESF_RAW.valid_accelerometer_y = false;
  UBX_ESF_RAW.valid_accelerometer_z = false;
 }

 // ===================================================================
 // Set all data in UBX-ESF-RAW block as valid
 // ===================================================================
 void CCUBLOXDecoder::set_UBX_ESF_RAW_data_as_valid()
 {
  UBX_ESF_RAW.valid_gyroscope_temperature = true;
  UBX_ESF_RAW.valid_gyroscope_x = true;
  UBX_ESF_RAW.valid_gyroscope_y = true;
  UBX_ESF_RAW.valid_gyroscope_z = true;
  UBX_ESF_RAW.valid_accelerometer_x = true;
  UBX_ESF_RAW.valid_accelerometer_y = true;
  UBX_ESF_RAW.valid_accelerometer_z = true;
 }
 
 // ===================================================================
 // Decode the UBX-ESF-RAW block and fill the corresponding data
 // structure
 // ===================================================================
 bool CCUBLOXDecoder::decode_UBX_ESF_RAW_and_fill_structure()
 {
  // Indicate that UBX-ESF-RAW data is not ready
  UBX_ESF_RAW_data_ready = false;
  
  // Reset valid status of data
  set_UBX_ESF_RAW_data_as_invalid();
  
  // Start decoding data
  if (transform_helper(pstm3dacc.time, Fields[1]))
   {
    pstm3dacc.valid_data_time = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(pstm3dacc.acc_x, Fields[2]))
   {
    pstm3dacc.valid_data_acc_x = true;
   }
  else
   {
    return false;
   }  
  
  if (transform_helper(pstm3dacc.acc_y, Fields[3]))
   {
    pstm3dacc.valid_data_acc_y = true;
   }
  else
   {
    return false;
   }  
  
  if (transform_helper(pstm3dacc.acc_z, Fields[4]))
   {
    pstm3dacc.valid_data_acc_z = true;
   }
  else
   {
    return false;
   }  
  
  // Indicate that accelerometer data is ready
  UBX_ESF_RAW_data_ready = true;
  
  // Only return true when no error occurred, otherwise return with
  // false
  return true;
  
 }
 
 // ===================================================================
 // Print the data stored in the UBX_ESF_RAW structure
 // ===================================================================
 void CCUBLOXDecoder::print_UBX_ESF_RAW_structure()
 {
  std::cout << std::endl;
  if (ubx_esf_raw.valid_gyroscope_temperature)
   {
    std::cout << "ubx_esf_raw.time_gyroscope_temperature:[" << ubx_esf_raw.time_gyroscope_temperature << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.time_gyroscope_temperature:[NO_VALID_DATA]" << std::endl;
   }
  
  if (ubx_esf_raw.valid_gyroscope_x)
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_x:[" << ubx_esf_raw.valid_gyroscope_x << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_x:[NO_VALID_DATA]" << std::endl;
   }

  if (ubx_esf_raw.valid_gyroscope_y)
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_y:[" << ubx_esf_raw.valid_gyroscope_y << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_y:[NO_VALID_DATA]" << std::endl;
   }

  if (ubx_esf_raw.valid_gyroscope_z)
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_z:[" << ubx_esf_raw.valid_gyroscope_z << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_gyroscope_z:[NO_VALID_DATA]" << std::endl;
   }
  
  if (ubx_esf_raw.valid_accelerometer_x)
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_x:[" << ubx_esf_raw.valid_accelerometer_x << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_x:[NO_VALID_DATA]" << std::endl;
   }

  if (ubx_esf_raw.valid_accelerometer_y)
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_y:[" << ubx_esf_raw.valid_accelerometer_y << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_y:[NO_VALID_DATA]" << std::endl;
   }

  if (ubx_esf_raw.valid_accelerometer_z)
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_z:[" << ubx_esf_raw.valid_accelerometer_z << "]" << std::endl;
   }
  else
   {
    std::cout << "ubx_esf_raw.valid_accelerometer_z:[NO_VALID_DATA]" << std::endl;
   }
  
 } 
 
}

/** \file This file implements the CCUBLOXDecoder class
 */
#include "cc_ublox_decoder.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor, establish the maximum number of fields, the maximum
 // size of the fields, and the size of the checksum (in bytes)
 // ===================================================================
 CCUBLOXDecoder::CCUBLOXDecoder(const unsigned max_fields,
                                const unsigned max_fields_size,
                                const unsigned checksum_size)
  : Max_fields(max_fields), Max_fields_size(max_fields_size),
    Max_UBX_block_size(max_fields*max_fields_size), Checksum_size(checksum_size),
    NStates(4), NTransitions(4),
    UBX_ESF_RAW_data_ready(false)
 {
  // ----------------------------------------------------------
  // Finite state machine
  // ----------------------------------------------------------
  // Resize the transition matrix
  const unsigned n_states = NStates;
  const unsigned n_transitions = NTransitions;
  
  // The transition matrix
  unsigned transition_matrix[] =
   {
    1, 0, 0, 0,
    0, 2, 0, 0,
    0, 0, 3, 0,
    0, 0, 0, 2
   };
  
  // Allocate memory for the State transition matrix
  State_machine_transitions = new unsigned[n_states*n_transitions];
  // Copy the "transition_matrix" into the "State_machine_transitions"
  // structure
  unsigned k = 0;
  for (unsigned i = 0; i < n_states; i++)
   {
    for (unsigned j = 0; j < n_transitions; j++)
     {
      State_machine_transitions[i*n_transitions+j] = transition_matrix[k++];
     } // for (j < n_transitions)
    
   } // for (i < n_states)
  
  // Allocate memory for the Fields matrix
  Fields = new char*[max_fields];
  // Allocate memory for each row of the Fields matrix
  for (unsigned i = 0; i < max_fields; i++)
   {
    Fields[i] = new char[max_fields_size];
   }
  
  // Allocate memory for checsum entries
  Input_checksum = new char[checksum_size];
  
  // Initialise/reset state machine and checksum vector
  reset_state_machine();
  // Establish the final state
  Final_state = 3;
  
  // ----------------------------------------------------------
  // Read data (initialise structures)
  // ----------------------------------------------------------
  ubx_esf_raw.valid_gyroscope_temperature = false;
  ubx_esf_raw.valid_gyroscope_x = false;
  ubx_esf_raw.valid_gyroscope_y = false;
  ubx_esf_raw.valid_gyroscope_z = false;
  ubx_esf_raw.valid_accelerometer_x = false;
  ubx_esf_raw.valid_accelerometer_y = false;
  ubx_esf_raw.valid_accelerometer_z = false;
  
 }
 
 // ===================================================================
 // Destructor (release allocated memory)
 // ===================================================================
 CCUBLOXDecoder::~CCUBLOXDecoder()
 {
  // Free memory for state machien transitions
  delete State_machine_transitions;
  State_machine_transitions = 0;
  
  // Free memory allocated for entries in the Fields matrix
  for (unsigned i = 0; i < Max_fields; i++)
   {
    delete Fields[i];
    Fields[i] = 0;
   }
  
  delete [] Fields;
  Fields = 0;
  
  // Free memory for checksum
  delete Input_checksum;
  Input_checksum = 0;
  
 }
 
 // ===================================================================
 // Initialise any variables (of the state machine). This method is
 // called any time a non-valid UBX protocol data is identified
 // ===================================================================
 void CCUBLOXDecoder::reset_state_machine()
 {
  // Reset number of fields variables
  Total_number_of_fields = 0;
  Counter_n_current_fields = 0;
  // Reset state information of the state machine
  Current_state = 0;
  Last_state = 0;
  // Initialise the number of read characters
  Counter_n_read_characters = 0;
  // Reset checksum
  Computed_checksum = 0;
  
  // Clean fields
  clean_fields_matrix();
  
 }

 // ===================================================================
 // Clean-up any info. stored in the Fields matrix
 // ===================================================================
 void CCUBLOXDecoder::clean_fields_matrix()
 {
  // Loop over the fields and fill with zeroes
  for (unsigned i = 0; i < Max_fields; i++)
   {
    memset(Fields[i], 0, Max_fields_size);
   }
  
  // Clean the stored checksum as well
  memset(Input_checksum, 0, Checksum_size);
  
 }
 
 // ===================================================================
 // Eats a byte, validates the byte as part of the UBX protocol and
 // stores its entry in a matrix structure containing the parsed
 // information
 // ===================================================================
 void CCUBLOXDecoder::parse(const unsigned char character)
 {
  // Keep track of the last state
  Last_state = Current_state;
  // Increase the number of read chacacters
  Counter_n_read_characters++;
  
  // Check whether we have exceed the maximum number of read
  // characters
  if (Counter_n_read_characters > Max_UBX_block_size)
   {
    // Reset all
    reset_state_machine();
    // Error message
    std::ostringstream error_message;
    error_message << "The maximum number of the UBX block size has been exceeded.\n"
                  << "The maximum UBX block size is: [" << Max_UBX_block_size << "]"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // ------------------------------------------------------------------
  // Identify the group that the input character is part of, and
  // transition accordingly
  // ------------------------------------------------------------------
  if (character == 0xB5) // Start of UBX Protocol, Header first part
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+0];
   }
  else if (character == 0x62) // Header second part
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+1];
   }
  else if (character == 0x62) // Class
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+2];
   }
  else if (character == 0x03) // ID
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+3];
   }
  else if (character == 0x2A) // GROUP E // TODO HERE
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+4];
   }
   
  // -----------------------------------------------------------------------
  // Is there something we need to do in each state?
  // -----------------------------------------------------------------------
  if (Current_state == 1) // eat characters, add them tot he Fields
                          // structure and and compute the checksum
   {
    if (character == 0x2C) // , (coma)), end of field by found
                           // delimiter
     {
      Computed_checksum ^= character;
      Fields[Total_number_of_fields][Counter_n_current_fields] = 0;
      Total_number_of_fields++;
      Counter_n_current_fields = 0;
     }
    else if (character != 0x24) // Include to the fields structure any
                                // other thing different from $
     {
      Computed_checksum ^= character;
      Fields[Total_number_of_fields][Counter_n_current_fields] = character;
      Counter_n_current_fields++;
     }
   }
  else if (Current_state == 3) // First checksum character
   {
    Total_number_of_fields++;
    Input_checksum[0] = character;
   }
  else if (Current_state == 4) // Second checksum character
   {
    Input_checksum[1] = character;
   }
  
  // Check whether we have reached a final state
  if (Current_state == Final_state) // TODO IMPLEMENT THE DECODING OF THE CHECKSUM
   {
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
 // Decode message and fill the corresponding data structure
 // ===================================================================
 void CCUBLOXDecoder::decode_message_and_fill_structure()
 {
  // Based on the first field in the Fields matrix call the
  // correspoing method in charge of filling the data structure
  if (Fields[2] == 0x10 && Fields[3] == 0x03)
   {
    decode_UBX_ESF_RAW_and_fill_structure();
    //print_UBX_ESF_RAW_structure();
   }
  
 }
 
 // ===================================================================
 // Decode the UBX-ESF-RAW block and fill the corresponding data
 // structure
 // ===================================================================
 bool CCUBLOXDecoder::decode_PSTM3DACC_and_fill_structure()
 {
  // Indicate that UBX-ESF-RAW data is not ready
  UBX_ESF_RAW_data_ready = false;
  
  // Reset valid status of data
  ubx_esf_raw.valid_gyroscope_temperature = false;
  ubx_esf_raw.valid_gyroscope_x = false;
  ubx_esf_raw.valid_gyroscope_y = false;
  ubx_esf_raw.valid_gyroscope_z = false;
  ubx_esf_raw.valid_accelerometer_x = false;
  ubx_esf_raw.valid_accelerometer_y = false;
  ubx_esf_raw.valid_accelerometer_z = false;
  
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

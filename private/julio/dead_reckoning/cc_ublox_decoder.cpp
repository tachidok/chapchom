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
    1, 5, 5, 5, 5,
    1, 6, 6, 6, 6,
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
    
 }
 
 // ===================================================================
 // Eats a byte, validates the bytes as part of the UBX
 // protocol. Also in charge of calling the proper methods to store
 // the info. in the corresponding data structures
 // ===================================================================
 void CCUBLOXDecoder::parse(const unsigned char &byte)
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
  else // Any byte
   {
    Current_general_state = General_transition_matrix[NGeneral_transitions*Current_general_state+4];
   }
  
  // -----------------------------------------------------------------------
  // Is there something we need to do in each state?
  // -----------------------------------------------------------------------
  if (Current_general_state == 0)
   {
    std::cout << "Reading garbage: [" << byte << "]" << std::endl;
   } 
  if (Current_general_state == 1)
   {
    // Reset the number of read characters
    Counter_n_read_bytes = 1;
    std::cout << "Found first UBLOX header\n" << std::endl;
   }
  else if (Current_general_state == 2)
   {
    std::cout << "Found second UBLOX header\n" << std::endl;
   }
  else if (Current_general_state == 3)
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
   }
  else if (Current_general_state == 6 && Last_general_state == 5)
   {
    // Save the payload byte 2
    Payload_byte2 = byte;
    // Add the byte to the payload storage
    Payload_length = ((Payload_byte1 << 8) & 0xFF00) || 0x00FF & Payload_byte2;
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
    // Call the sub-parser method and check whether we should override
    // the transition to the next state
    bool override_transition_to_the_next_state = false;
    if (Class_id_c == 0x10 && ID_c == 0x03) // UBX-ESF-RAW
     {
      override_transition_to_the_next_state = decode_UBX_ESF_RAW_and_fill_structure(byte);
     }
    if (override_transition_to_the_next_state)
     {
      // Reset all particular state machines
      reset_UBX_ESF_RAW_state_machine();
      
      // Treat the read byte as if we were already in state 7 and do
      // the corresponding transition
      Current_general_state = 8;
      Read_checksum[0] = byte; // CK_A
     }
    else
     {
      // If still decoding then add the element to the checksum list
      Computed_checksum[Computed_checksum_index++] = byte;
     }
   }
  else if (Current_general_state == 9)
   {
    Read_checksum[1] = byte; // CK_B
   }
  
  // Check whether we have reached a final state
  if (Current_general_state == General_final_state)
   {
    unsigned CK_A = 0;
    unsigned CK_B = 0;
    // Loop over the elements used to create the checksum
    for (int i = 0; i < Payload_length + 4; i++)
     {
      CK_A = CK_A + Computed_checksum[i];
      CK_B = CK_B + CK_A;
     }
    // Validate the checksum    
    if (CK_A != Read_checksum[0] || CK_B != Read_checksum[1])
     {
      reset_general_state_machine();
      // Error message
      std::ostringstream error_message;
      error_message << "The checksum is not correct\n"
                    << "We got CK_A: [" << CK_A << "] and CK_B: [" << CK_B <<"],\n"
                    << "but the received checksum is CK_A: [" << Read_checksum[0]
                    << "] and CK_B:[" << Read_checksum[1] << "]."
                    << std::endl;
      throw ChapchomLibError(error_message.str(),
                             CHAPCHOM_CURRENT_FUNCTION,
                             CHAPCHOM_EXCEPTION_LOCATION);
     }
    
    // Free memory
    delete Computed_checksum;
    Computed_checksum = 0;
    
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
  Local_block_UBX_ESF_RAW_counter = 0;
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
 bool CCUBLOXDecoder::decode_UBX_ESF_RAW_and_fill_structure(const unsigned char &byte)
 {
  // Indicate that accelerometer data is ready
  UBX_ESF_RAW_data_ready = false;
  // Reset valid status of data
  set_UBX_ESF_RAW_data_as_invalid();
  
  // Have we read all the data in the payload
  if (Counter_UBX_ESF_RAW_n_read_bytes >= static_cast<unsigned>(Payload_length + 4))
   {
    // Indicate that accelerometer data is ready
    UBX_ESF_RAW_data_ready = true;
    // Indicate that the data in the UBX_ESF_RAW structure is valid
    set_UBX_ESF_RAW_data_as_valid();
    return true;
   }
  
  // Skip the first 4 bytes since they are reserved
  if (Counter_UBX_ESF_RAW_n_read_bytes >= 4)
   {
    // Add the read byte into the storage
    UBX_ESF_RAW_data_block[Local_block_UBX_ESF_RAW_counter++] = byte;
    
    if (Local_block_UBX_ESF_RAW_counter >= 7)
     {
      // -------------------------------------------
      // Decode the data
      {
       unsigned int data = ((UBX_ESF_RAW_data_block[6] << 16) & 0xFF0000) |
        ((UBX_ESF_RAW_data_block[5] << 8) & 0xFF00) |
        (UBX_ESF_RAW_data_block[4] & 0xFF);
       // ---------------------
       // Decode the data type
       unsigned char data_type = UBX_ESF_RAW_data_block[7];
       if (data_type == 5) // z-axis gyroscope angular rate
        {
         
        }
       else if (data_type == 12) // gyroscope temperature
        {
         
        }
       else if (data_type == 13) // y-axis gyroscope angular rate
        {
         
        }
       else if (data_type == 14) // x-axis gyroscope angular rate
        {
         
        }
       else if (data_type == 16) // x-axis accelerometer specific force
        {
         
        }
       else if (data_type == 17) // y-axis accelerometer specific force
        {
         
        }
       else if (data_type == 18) // z-axis accelerometer specific force
        {
         
        }
       
       // ---------------------
       // Decode the data field
      }

      {
       // -------------------------------------------
       // Decode the timing
       unsigned int data = ((UBX_ESF_RAW_data_block[2] << 16) & 0xFF0000) |
        ((UBX_ESF_RAW_data_block[1] << 8) & 0xFF00) |
        (UBX_ESF_RAW_data_block[0] & 0xFF);
       // ---------------------
       // Decode the data type
       unsigned char data_type = UBX_ESF_RAW_data_block[3];
       if (data_type == 5) // z-axis gyroscope angular rate
        {
         UBX_ESF_RAW.time_gyroscope_z = data;
        }
       else if (data_type == 12) // gyroscope temperature
        {
         UBX_ESF_RAW.time_gyroscope_temperature = data;
        }
       else if (data_type == 13) // y-axis gyroscope angular rate
        {
         UBX_ESF_RAW.time_gyroscope_y = data;
        }
       else if (data_type == 14) // x-axis gyroscope angular rate
        {
         UBX_ESF_RAW.time_gyroscope_x = data;
        }
       else if (data_type == 16) // x-axis accelerometer specific force
        {
         UBX_ESF_RAW.time_accelerometer_x = data;
        }
       else if (data_type == 17) // y-axis accelerometer specific force
        {
         UBX_ESF_RAW.time_accelerometer_y = data;
        }
       else if (data_type == 18) // z-axis accelerometer specific force
        {
         UBX_ESF_RAW.time_accelerometer_z = data;
        }
      }
      
      // Restart local block counter
      Local_block_UBX_ESF_RAW_counter = 0;
     }
    
   } // if (Counter_UBX_ESF_RAW_n_read_bytes >= 4)
 
#if 0
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
#endif // #if 0
  
  // Increase the number of read bytes
  Counter_UBX_ESF_RAW_n_read_bytes++;
  
  // Return false when we have not reached the number of bytes
  // specified in the Payload, or in other words, that we are still
  // decoding
  return false;
  
 }
 
 // ===================================================================
 // Print the data stored in the UBX_ESF_RAW structure
 // ===================================================================
 void CCUBLOXDecoder::print_UBX_ESF_RAW_structure()
 {
  std::cout << std::endl;
  if (UBX_ESF_RAW.valid_gyroscope_temperature)
   {
    std::cout << "UBX_ESF_RAW.time_gyroscope_temperature:[" << UBX_ESF_RAW.time_gyroscope_temperature << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.time_gyroscope_temperature:[NO_VALID_DATA]" << std::endl;
   }
  
  if (UBX_ESF_RAW.valid_gyroscope_x)
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_x:[" << UBX_ESF_RAW.valid_gyroscope_x << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_x:[NO_VALID_DATA]" << std::endl;
   }

  if (UBX_ESF_RAW.valid_gyroscope_y)
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_y:[" << UBX_ESF_RAW.valid_gyroscope_y << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_y:[NO_VALID_DATA]" << std::endl;
   }

  if (UBX_ESF_RAW.valid_gyroscope_z)
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_z:[" << UBX_ESF_RAW.valid_gyroscope_z << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_gyroscope_z:[NO_VALID_DATA]" << std::endl;
   }
  
  if (UBX_ESF_RAW.valid_accelerometer_x)
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_x:[" << UBX_ESF_RAW.valid_accelerometer_x << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_x:[NO_VALID_DATA]" << std::endl;
   }

  if (UBX_ESF_RAW.valid_accelerometer_y)
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_y:[" << UBX_ESF_RAW.valid_accelerometer_y << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_y:[NO_VALID_DATA]" << std::endl;
   }

  if (UBX_ESF_RAW.valid_accelerometer_z)
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_z:[" << UBX_ESF_RAW.valid_accelerometer_z << "]" << std::endl;
   }
  else
   {
    std::cout << "UBX_ESF_RAW.valid_accelerometer_z:[NO_VALID_DATA]" << std::endl;
   }
  
 } 
 
}

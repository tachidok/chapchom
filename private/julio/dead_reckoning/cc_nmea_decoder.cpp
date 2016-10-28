/** \file This file implements the CCNMEADecoder class
 */
#include "cc_nmea_decoder.h"

namespace chapchom
{
 
 // ===================================================================
 // Constructor, establish the maximum size of the nmea string and
 // the size of the checksum
 // ===================================================================
 CCNMEADecoder::CCNMEADecoder(const unsigned max_fields,
                              const unsigned max_fields_size,
                              const unsigned checksum_size)
  : Max_fields(max_fields), Max_fields_size(max_fields_size),
    Max_nmea_string_size(max_fields*max_fields_size), Checksum_size(checksum_size),
    NStates(5), NTransitions(5),
    Accelerometer_data_ready(false),
    Gyro_data_ready(false),
    GPRMC_data_ready(false)
 {

  // ----------------------------------------------------------
  // Finite state machine
  // ----------------------------------------------------------
  // Resize the transition matrix
  const unsigned n_states = NStates;//6;
  const unsigned n_transitions = NTransitions;//15;
  
#if 0
  // The transition matrix
  unsigned transition_matrix[] =
   {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 0,    
    0, 0, 1, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
#endif // #if 0
  
  // The transition matrix
  unsigned transition_matrix[] =
   {
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 2,
    0, 0, 3, 1, 0,
    0, 0, 4, 1, 0,
    0, 0, 0, 1, 0
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
  //Final_state = 5;
  Final_state = 4;

  // ----------------------------------------------------------
  // Read data (initialise structures)
  // ----------------------------------------------------------
  pstm3dacc.valid_data_time = false;
  pstm3dacc.valid_data_acc_x = false;
  pstm3dacc.valid_data_acc_y = false;
  pstm3dacc.valid_data_acc_z = false;
  
  pstm3dgyro.valid_data_time = false;
  pstm3dgyro.valid_data_raw_x = false;
  pstm3dgyro.valid_data_raw_y = false;
  pstm3dgyro.valid_data_raw_z = false;
  pstm3dgyro.valid_data_odometer_counter = false;
  pstm3dgyro.valid_data_reverse = false;
  
 }
 
 // ===================================================================
 // Destructor (release allocated memory)
 // ===================================================================
 CCNMEADecoder::~CCNMEADecoder()
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
 // called any time a non-valid nmea string is identified
 // ===================================================================
 void CCNMEADecoder::reset_state_machine()
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
 void CCNMEADecoder::clean_fields_matrix()
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
 // Eats a character, validates the character as part of an nmea
 // string and stores its entry in a matrix structure containing the
 // parsed information
 // ===================================================================
 void CCNMEADecoder::parse(const unsigned char character)
 {
  // Keep track of the last state
  Last_state = Current_state;
  // Increase the number of read chacacters
  Counter_n_read_characters++;
  
  // Check whether we have exceed the maximum number of read
  // characters
  if (Counter_n_read_characters > Max_nmea_string_size)
   {
    // Reset all
    reset_state_machine();
    // Error message
    std::ostringstream error_message;
    error_message << "The maximum number of the NMEA string has been exceeded.\n"
                  << "The maximum NMEA string size is: [" << Max_nmea_string_size << "]"
                  << std::endl;
    throw ChapchomLibError(error_message.str(),
                           CHAPCHOM_CURRENT_FUNCTION,
                           CHAPCHOM_EXCEPTION_LOCATION);
   }
  
  // ------------------------------------------------------------------
  // Identify the group that the input character is part of, and
  // transition accordingly
  // ------------------------------------------------------------------
  if ((character <= 0x1F) ||                       // GROUP A (unit separator) 
      ((0x7F <= character) && (character <= 0xFF)) // GROUP O (extended ASCII))
      )
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+0];
   }
  else if (((0x20 <= character) && (character <= 0x23)) || // GROUP B (space), !, ", #
           ((0x25 <= character) && (character <= 0x29)) || // GROUP D %, &, ', (, )
           (character == 0x2B) ||                          // GROUP F +
           (character == 0x2C) ||                          // GROUP G , (coma)
           ((0x2D <= character) && (character <= 0x2F)) || // GROUP H -,.,/
           ((0x3A <= character) && (character <= 0x40)) || // GROUP J :, ;, <, =, >, ?, @
           ((0x47 <= character) && (character <= 0x60)) || // GROUP L G, H, I,..., X, Y, Z, [, \, ], ^, _, `
           ((0x67 <= character) && (character <= 0x7E))    // GROUP N g, h, i,...,x, y, z, {, |, }, ~
           )
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+1];
   }
  else if (((0x30 <= character) && (character <= 0x39)) || // GROUP I 0,1,...,9
           ((0x41 <= character) && (character <= 0x46)) || // GROUP K A, B, C, D, E, F
           ((0x61 <= character) && (character <= 0x66))    // GROUP M a, b, c, d, e, f           
           )
   {
    Current_state = State_machine_transitions[NTransitions*Current_state+2];
   }
  else if (character == 0x24) // GROUP C $
   {
    reset_state_machine();
    // Always uses transition [0][3] since reset_state_machine() sets
    // Current_state = 0
    Current_state = State_machine_transitions[NTransitions*Current_state+3];
   }
  else if (character == 0x2A) // GROUP E *
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
  if (Current_state == Final_state)
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
 // Decode the NMEA message and fill the corresponding data structure
 // ===================================================================
 void CCNMEADecoder::decode_message_and_fill_structure()
 {
  // Based on the first field in the Fields matrix call the
  // correspoing method in charge of filling the data structure
  if (strcmp(Fields[0], "PSTM3DACC") == 0)
   {
    decode_PSTM3DACC_and_fill_structure();
    //print_PSTM3DACC_structure();
   }
  else if (strcmp(Fields[0], "PSTM3DGYRO") == 0)
   {
    decode_PSTM3DGYRO_and_fill_structure();
    //print_PSTM3DGYRO_structure();
   }
  else if (strcmp(Fields[0], "GPRMC") == 0)
   {
    decode_GPRMC_and_fill_structure();
    //print_GPRMC_structure();
   }
  
 }
 
 // ===================================================================
 // Decode the $PSTM3DACC string and fill the corresponding data
 // structure
 // ===================================================================
 bool CCNMEADecoder::decode_PSTM3DACC_and_fill_structure()
 {
  // Indicate that accelerometer data is not ready
  Accelerometer_data_ready = false;
  
  // Reset valid status of data
  pstm3dacc.valid_data_time = false;
  pstm3dacc.valid_data_acc_x = false;
  pstm3dacc.valid_data_acc_y = false;
  pstm3dacc.valid_data_acc_z = false;
  
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
  Accelerometer_data_ready = true;
  
  // Only return true when no error occurred, otherwise return with
  // false
  return true;
  
 }
 
 // ===================================================================
 // Print the data stored in the $PSTM3DACC structure
 // ===================================================================
 void CCNMEADecoder::print_PSTM3DACC_structure()
 {
  std::cout << std::endl;
  if (pstm3dacc.valid_data_time)
   {
    std::cout << "pstm3dacc.time:[" << pstm3dacc.time << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dacc.time:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dacc.valid_data_acc_x)
   {
    std::cout << "pstm3dacc.acc_x:[" << pstm3dacc.acc_x << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dacc.acc_x:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dacc.valid_data_acc_y)
   {
    std::cout << "pstm3dacc.acc_y:[" << pstm3dacc.acc_y << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dacc.acc_y:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dacc.valid_data_acc_z)
   {
    std::cout << "pstm3dacc.acc_z:[" << pstm3dacc.acc_z << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dacc.acc_z:[NO_VALID_DATA]" << std::endl;
   }   
 }
 
 // ===================================================================
 // Decode the $PSTM3DGYRO string and fill the corresponding data
 // structure
 // ===================================================================
 bool CCNMEADecoder::decode_PSTM3DGYRO_and_fill_structure()
 {
  // Indicate that gryo data is not ready
  Gyro_data_ready = false;
  
  pstm3dgyro.valid_data_time = false;
  pstm3dgyro.valid_data_raw_x = false;
  pstm3dgyro.valid_data_raw_y = false;
  pstm3dgyro.valid_data_raw_z = false;
  pstm3dgyro.valid_data_odometer_counter = false;
  pstm3dgyro.valid_data_reverse = false;

  // Start decoding data
  if (transform_helper(pstm3dgyro.time, Fields[1]))
   {
    pstm3dgyro.valid_data_time = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(pstm3dgyro.raw_x, Fields[2]))
   {
    pstm3dgyro.valid_data_raw_x = true;
   }
  else
   {
    return false;
   }  
  
  if (transform_helper(pstm3dgyro.raw_y, Fields[3]))
   {
    pstm3dgyro.valid_data_raw_y = true;
   }
  else
   {
    return false;
   }  
  
  if (transform_helper(pstm3dgyro.raw_z, Fields[4]))
   {
    pstm3dgyro.valid_data_raw_z = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(pstm3dgyro.odometer_counter, Fields[5]))
   {
    pstm3dgyro.valid_data_odometer_counter = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(pstm3dgyro.reverse, Fields[6]))
   {
    pstm3dgyro.valid_data_reverse = true;
   }
  else
   {
    return false;
   }
  
  // Indicate that gryo data is ready
  Gyro_data_ready = true;
  
  // Only return true when no error occurred, otherwise return with
  // false
  return true;
  
 }
 
 // ===================================================================
 // Print the data stored in the $PSTM3DGYRO structure
 // ===================================================================
 void CCNMEADecoder::print_PSTM3DGYRO_structure()
 {
  std::cout << std::endl;
  if (pstm3dgyro.valid_data_time)
   {
    std::cout << "pstm3dgyro.time:[" << pstm3dgyro.time << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.time:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dgyro.valid_data_raw_x)
   {
    std::cout << "pstm3dgyro.raw_x:[" << pstm3dgyro.raw_x << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.raw_x:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dgyro.valid_data_raw_y)
   {
    std::cout << "pstm3dgyro.raw_y:[" << pstm3dgyro.raw_y << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.raw_y:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dgyro.valid_data_raw_z)
   {
    std::cout << "pstm3dgyro.raw_z:[" << pstm3dgyro.raw_z << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.raw_z:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dgyro.valid_data_odometer_counter)
   {
    std::cout << "pstm3dgyro.odometer_counter:[" << pstm3dgyro.odometer_counter << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.odometer_counter:[NO_VALID_DATA]" << std::endl;
   }
  
  if (pstm3dgyro.valid_data_reverse)
   {
    std::cout << "pstm3dgyro.reverse:[" << pstm3dgyro.reverse << "]" << std::endl;
   }
  else
   {
    std::cout << "pstm3dgyro.reverse:[NO_VALID_DATA]" << std::endl;
   }
  
 }
 
 // ===================================================================
 // Decode the $GPRMC string and fill the corresponding data structure
 // ===================================================================
 bool CCNMEADecoder::decode_GPRMC_and_fill_structure()
 {
  // Indicate that gprmc data is not ready
  GPRMC_data_ready = false;
  
  // Reset valid status of data
  gprmc.valid_data_UTC_time = false;
  gprmc.valid_data_status = false;
  gprmc.valid_data_latitude = false;
  gprmc.valid_data_NS = false;
  gprmc.valid_data_longitude = false;
  gprmc.valid_data_EW = false;
  gprmc.valid_data_speed_knots = false;
  gprmc.valid_data_course_degrees = false;
  gprmc.valid_data_date = false;
  gprmc.valid_data_magnetic_variation_degrees = false;
  gprmc.valid_data_EW_magnetic = false;
  
  // Start decoding data
  if (transform_helper(gprmc.UTC_time, Fields[1]))
   {
    gprmc.valid_data_UTC_time = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.status, Fields[2]))
   {
    gprmc.valid_data_status = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.latitude, Fields[3]))
   {
    gprmc.valid_data_latitude = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.NS, Fields[4]))
   {
    gprmc.valid_data_NS = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.longitude, Fields[5]))
   {
    gprmc.valid_data_longitude = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.EW, Fields[6]))
   {
    gprmc.valid_data_EW = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.speed_knots, Fields[7]))
   {
    gprmc.valid_data_speed_knots = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.course_degrees, Fields[8]))
   {
    gprmc.valid_data_course_degrees = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.date, Fields[9]))
   {
    gprmc.valid_data_date = true;
   }
  else
   {
    return false;
   }
  
  if (transform_helper(gprmc.magnetic_variation_degrees, Fields[10]))
   {
    gprmc.valid_data_magnetic_variation_degrees = true;
   }
  else
   {
    // return false; // TODO: tachidok, check for special case when we
    // have no data, a comma after another comma ,,
   }
  
  if (transform_helper(gprmc.EW_magnetic, Fields[11]))
   {
    gprmc.valid_data_EW_magnetic = true;
   }
  else
   {
    // return false; // TODO: tachidok, check for special case when we
    // have no data, a comma after another comma ,,    
    // return false;
   }  
  
  // Indicate that gprmc data is ready
  GPRMC_data_ready = true;
  
  // Only return true when no error occurred, otherwise return with
  // false
  return true;
  
 }
 
 // ===================================================================
 // Print the data stored in the $GPRMC structure
 // ===================================================================
 void CCNMEADecoder::print_GPRMC_structure()
 {
  std::cout << std::endl;
  if (gprmc.valid_data_UTC_time)
   {
    std::cout << "gprmc.UTC_time:[" << gprmc.UTC_time << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.UTC_time:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_status)
   {
    std::cout << "gprmc.status:[" << gprmc.status << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.status:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_latitude)
   {
    std::cout << "gprmc.latitude:[" << gprmc.latitude << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.latitude:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_NS)
   {
    std::cout << "gprmc.NS:[" << gprmc.NS << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.NS:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_longitude)
   {
    std::cout << "gprmc.longitude:[" << gprmc.longitude << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.longitude:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_EW)
   {
    std::cout << "gprmc.EW:[" << gprmc.EW << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.EW:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_speed_knots)
   {
    std::cout << "gprmc.speed_knots:[" << gprmc.speed_knots << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.speed_knots:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_course_degrees)
   {
    std::cout << "gprmc.course_degrees:[" << gprmc.course_degrees << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.course_degrees:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_date)
   {
    std::cout << "gprmc.date:[" << gprmc.date << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.date:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_magnetic_variation_degrees)
   {
    std::cout << "gprmc.magnetic_variation_degrees:[" << gprmc.magnetic_variation_degrees << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.magnetic_variation_degrees:[NO_VALID_DATA]" << std::endl;
   }
  
  if (gprmc.valid_data_EW_magnetic)
   {
    std::cout << "gprmc.EW_magnetic:[" << gprmc.EW_magnetic << "]" << std::endl;
   }
  else
   {
    std::cout << "gprmc.EW_magnetic:[NO_VALID_DATA]" << std::endl;
   }
  
 }
 
 // ===================================================================
 // Helper function to transform from string to double
 // ===================================================================
 bool CCNMEADecoder::transform_helper(double &number, char *string)
 {
  // Null pointer?
  if (string == NULL)
   {
    return false;
   }

  // No elements in the string?
  if (strlen (string) <=0)
   {
    return false;
   }
  
  // Pointer to the end of string
  char *end_string;
  double tmp_number = std::strtod(string, &end_string);
  // Check whether all the string was consumed
  if (std::strlen(end_string) != 0)
   {
    return false;
   }
  else
   {
    number = tmp_number;
    return true;
   }
  
  // Never reached code but added to avoid warning
  return false;
  
 }

 // ===================================================================
 // Helper function to transform from string to int
 // ===================================================================
 bool CCNMEADecoder::transform_helper(int &number, char *string)
 {
  // Null pointer?
  if (string == NULL)
   {
    return false;
   }

  // No elements in the string?
  if (strlen (string) <=0)
   {
    return false;
   }
  
  // Pointer to the end of string
  char *end_string;
  int tmp_number = static_cast<int>(std::strtod(string, &end_string));
  // Check whether all the string was consumed
  if (std::strlen(end_string) != 0)
   {
    return false;
   }
  else
   {
    number = tmp_number;
    return true;
   }
  
  // Never reached code but added to avoid warning
  return false;
  
 }
 
 // ===================================================================
 // Helper function to transform from string to char 
 // ===================================================================
 bool CCNMEADecoder::transform_helper(char &character, char *string)
 {
  // Null pointer?
  if (string == NULL)
   {
    return false;
   }

  // No elements in the string?
  if (strlen (string) <=0)
   {
    return false;
   }
  
  // Copy the first character
  character = string[0];
  
  return true;
  
 }
 
}

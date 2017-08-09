#ifndef CCNMEADECODER_H
#define CCNMEADECODER_H

// Include general/common includes, utilities and initialisation
#include "../../../../../src/general/common_includes.h"
#include "../../../../../src/general/utilities.h"
#include "../../../../../src/general/initialise.h"

#include <fstream>
#include <iostream>

namespace chapchom
{
 
 /// \struct DRRAWG cc_nmea_decoder.h
 
 /// Stores the information decoded from the $DRRAWG NMEA string
 struct DRRAWG
 {
  double time;
  bool valid_data_time;
  double raw_gyro_x;
  bool valid_data_raw_gyro_x;
  double raw_gyro_y;
  bool valid_data_raw_gyro_y;
  double raw_gyro_z;
  bool valid_data_raw_gyro_z;
 };
 
 /// \struct DRRAWA cc_nmea_decoder.h

 /// Stores the information decoded from the $DRRAWG NMEA string
 struct DRRAWA
 {
  double time;
  bool valid_data_time;
  double raw_acc_x;
  bool valid_data_raw_acc_x;
  double raw_acc_y;
  bool valid_data_raw_acc_y;
  double raw_acc_z;
  bool valid_data_raw_acc_z;
 };
  
 /// \struct DRROG cc_nmea_decoder.h

 /// Stores the information decoded from the $DRROG NMEA string
 struct DRROG
 {
  double time;
  bool valid_data_time;
  double rotated_gyro_x;
  bool valid_data_rotated_gyro_x;
  double rotated_gyro_y;
  bool valid_data_rotated_gyro_y;
  double rotated_gyro_z;
  bool valid_data_rotated_gyro_z;
 };

 /// \struct DRROA cc_nmea_decoder.h

 /// Stores the information decoded from the $DRROA NMEA string
 struct DRROA
 {
  double time;
  bool valid_data_time;
  double rotated_acc_x;
  bool valid_data_rotated_acc_x;
  double rotated_acc_y;
  bool valid_data_rotated_acc_y;
  double rotated_acc_z;
  bool valid_data_rotated_acc_z;
 };

 /// \struct DRFIG cc_nmea_decoder.h

 /// Stores the information decoded from the $DRFIG NMEA string
 struct DRFIG
 {
  double time;
  bool valid_data_time;
  double filtered_gyro_x;
  bool valid_data_filtered_gyro_x;
  double filtered_gyro_y;
  bool valid_data_filtered_gyro_y;
  double filtered_gyro_z;
  bool valid_data_filtered_gyro_z;
 };

 /// \struct DRFIA cc_nmea_decoder.h

 /// Stores the information decoded from the $DRFIA NMEA string
 struct DRFIA
 {
  double time;
  bool valid_data_time;
  double filtered_acc_x;
  bool valid_data_filtered_acc_x;
  double filtered_acc_y;
  bool valid_data_filtered_acc_y;
  double filtered_acc_z;
  bool valid_data_filtered_acc_z;
 };

 /// \struct DRALG cc_nmea_decoder.h

 /// Stores the information decoded from the $DRALG NMEA string
 struct DRALG
 {
  double time;
  bool valid_data_time;
  double aligned_gyro_x;
  bool valid_data_aligned_gyro_x;
  double aligned_gyro_y;
  bool valid_data_aligned_gyro_y;
  double aligned_gyro_z;
  bool valid_data_aligned_gyro_z;
 };

 /// Stores the information decoded from the $DRALA NMEA string
 struct DRALA
 {
  double time;
  bool valid_data_time;
  double aligned_acc_x;
  bool valid_data_aligned_acc_x;
  double aligned_acc_y;
  bool valid_data_aligned_acc_y;
  double aligned_acc_z;
  bool valid_data_aligned_acc_z;
 };

 /// Stores the information decoded from the $DREAG NMEA string
 struct DREAG
 {
  double time;
  bool valid_data_time;
  double phi_gyro;
  bool valid_data_phi_gyro;
  double theta_gyro;
  bool valid_data_theta_gyro;
  double psi_gyro;
  bool valid_data_psi_gyro;
 };

 /// Stores the information decoded from the $DREAA NMEA string
 struct DREAA
 {
  double time;
  bool valid_data_time;
  double phi_acc;
  bool valid_data_phi_acc;
  double theta_acc;
  bool valid_data_theta_acc;
 };

 /// Stores the information decoded from the $DREAF NMEA string
 struct DREAF
 {
  double time;
  bool valid_data_time;
  double phi_fused;
  bool valid_data_phi_fused;
  double theta_fused;
  bool valid_data_theta_fused;
  double psi_fused;
  bool valid_data_psi_fused;
 };

 /// Stores the information decoded from the $DRGBF NMEA string
 struct DRGBF
 {
  double time;
  bool valid_data_time;
  double gravity_body_frame_x;
  bool valid_data_gravity_body_frame_x;
  double gravity_body_frame_y;
  bool valid_data_gravity_body_frame_y;
  double gravity_body_frame_z;
  bool valid_data_gravity_body_frame_z;
 };

 /// Stores the information decoded from the $DRLAC NMEA string
 struct DRLAC
 {
  double time;
  bool valid_data_time;
  double linear_acc_x;
  bool valid_data_linear_acc_x;
  double linear_acc_y;
  bool valid_data_linear_acc_y;
  double linear_acc_z;
  bool valid_data_linear_acc_z;
 };

 /// Stores the information decoded from the $DRIAC NMEA string
 struct DRIAC
 {
  double time;
  bool valid_data_time;
  double inertial_acc_x;
  bool valid_data_inertial_acc_x;
  double inertial_acc_y;
  bool valid_data_inertial_acc_y;
  double inertial_acc_z;
  bool valid_data_inertial_acc_z;
 };

 /// Stores the information decoded from the $DRVBF NMEA string
 struct DRVBF
 {
  double time;
  bool valid_data_time;
  double velocity_body_frame_x;
  bool valid_data_velocity_body_frame_x;
  double velocity_body_frame_y;
  bool valid_data_velocity_body_frame_y;
 };

 /// Stores the information decoded from the $DRVIF NMEA string
 struct DRVIF
 {
  double time;
  bool valid_data_time;
  double velocity_inertial_frame_x;
  bool valid_data_velocity_inertial_frame_x;
  double velocity_inertial_frame_y;
  bool valid_data_velocity_inertial_frame_y;
 };

 /// Stores the information decoded from the $DRPBF NMEA string
 struct DRPBF
 {
  double time;
  bool valid_data_time;
  double position_body_frame_x;
  bool valid_data_position_body_frame_x;
  double position_body_frame_y;
  bool valid_data_position_body_frame_y;
 };

 /// Stores the information decoded from the $DRPIF NMEA string
 struct DRPIF
 {
  double time;
  bool valid_data_time;
  double position_inertial_frame_x;
  bool valid_data_position_inertial_frame_x;
  double position_inertial_frame_y;
  bool valid_data_position_inertial_frame_y;
 };

 /// \class CCNMEADecoder cc_nmea_decoder.h

 /// This class reads NMEA strings and fill data structures (other
 /// classes) with the decoded info. Note that it is not required that
 /// the NMEA string has the <CR><LF> charaters at the end. The
 /// checksum is computed as the 8-bits XOR of the received data. The
 /// decoding strategy uses an state machine to validate the input
 /// nmea strings
 class CCNMEADecoder
 {
  
 public:
  
  // Constructor, establish the maximum number of fields, the maximum
  // size of the fields, and the size of the checksum
  CCNMEADecoder(const unsigned max_fields = 10,
                const unsigned max_fields_size = 30,
                const unsigned checksum_size = 3);
  
  // Destructor (release allocated memory)
  virtual ~CCNMEADecoder();
  
  // Eats a character, validates the character as part of an nmea
  // string and stores its entry in a matrix structure containing the
  // parsed information
  void parse(const unsigned char character);
  
  // Check whether new values from raw gyro are ready or not
  inline bool is_raw_gyro_data_ready() {return Raw_gyro_data_ready;}
  
  // Indicate that the raw gyro data has been processed
  inline void consume_raw_gyro_data() {Raw_gyro_data_ready = false;}
  
  // Returns a reference to the structure DRRAWG
  inline struct DRRAWG &get_drrawg() {return drrawg;}

  // Check whether new values from raw acc are ready or not
  inline bool is_raw_acc_data_ready() {return Raw_acc_data_ready;}

  // Indicate that the raw acc data has been processed
  inline void consume_raw_acc_data() {Raw_acc_data_ready = false;}

  // Returns a reference to the structure DRRAWA
  inline struct DRRAWA &get_drrawa() {return drrawa;}

  // Check whether new values from rotated gyro are ready or not
  inline bool is_rotated_gyro_data_ready() {return Rotated_gyro_data_ready;}

  // Indicate that the rotated gyro data has been processed
  inline void consume_rotated_gyro_data() {Rotated_gyro_data_ready = false;}

  // Returns a reference to the structure DRROG
  inline struct DRROG &get_drrog() {return drrog;}

  // Check whether new values from rotated acc are ready or not
  inline bool is_rotated_acc_data_ready() {return Rotated_acc_data_ready;}

  // Indicate that the rotated acc data has been processed
  inline void consume_rotated_acc_data() {Rotated_acc_data_ready = false;}

  // Returns a reference to the structure DRROA
  inline struct DRROA &get_drroa() {return drroa;}

  // Check whether new values from filtered gyro are ready or not
  inline bool is_filtered_gyro_data_ready() {return Filtered_gyro_data_ready;}

  // Indicate that the filtered gyro data has been processed
  inline void consume_filtered_gyro_data() {Filtered_gyro_data_ready = false;}

  // Returns a reference to the structure DRFIG
  inline struct DRFIG &get_drfig() {return drfig;}

  // Check whether new values from filtered acc are ready or not
  inline bool is_filtered_acc_data_ready() {return Filtered_acc_data_ready;}

  // Indicate that the filtered acc data has been processed
  inline void consume_filtered_acc_data() {Filtered_acc_data_ready = false;}

  // Returns a reference to the structure DRFIA
  inline struct DRFIA &get_drfia() {return drfia;}

  // Check whether new values from aligned gyro are ready or not
  inline bool is_aligned_gyro_data_ready() {return Aligned_gyro_data_ready;}

  // Indicate that the aligned gyro data has been processed
  inline void consume_aligned_gyro_data() {Aligned_gyro_data_ready = false;}

  // Returns a reference to the structure DRALG
  inline struct DRALG &get_dralg() {return dralg;}

  // Check whether new values from aligned acc are ready or not
  inline bool is_aligned_acc_data_ready() {return Aligned_acc_data_ready;}

  // Indicate that the aligned acc data has been processed
  inline void consume_aligned_acc_data() {Aligned_acc_data_ready = false;}

  // Returns a reference to the structure DRALA
  inline struct DRALA &get_drala() {return drala;}

  // Check whether new values from Euler angles gyro are ready or not
  inline bool is_euler_angles_gyro_data_ready() {return Euler_angles_gyro_data_ready;}

  // Indicate that the Euler angles gyro data has been processed
  inline void consume_euler_angles_gyro_data() {Euler_angles_gyro_data_ready = false;}

  // Returns a reference to the structure DRALG
  inline struct DREAG &get_dreag() {return dreag;}

  // Check whether new values from Euler angles acc are ready or not
  inline bool is_euler_angles_acc_data_ready() {return Euler_angles_acc_data_ready;}

  // Indicate that the Euler angles acc data has been processed
  inline void consume_euler_angles_acc_data() {Euler_angles_acc_data_ready = false;}

  // Returns a reference to the structure DREAA
  inline struct DREAA &get_dreaa() {return dreaa;}

  // Check whether new values from Euler angles fused are ready or not
  inline bool is_euler_angles_fused_data_ready() {return Euler_angles_fused_data_ready;}

  // Indicate that the Euler angles fused data has been processed
  inline void consume_euler_angles_fused_data() {Euler_angles_fused_data_ready = false;}

  // Returns a reference to the structure DREAF
  inline struct DREAF &get_dreaf() {return dreaf;}

  // Check whether new values from gravity body frame are ready or not
  inline bool is_gravity_body_frame_data_ready() {return Gravity_body_frame_data_ready;}

  // Indicate that the Euler angles fused data has been processed
  inline void consume_gravity_body_frame_data() {Gravity_body_frame_data_ready = false;}

  // Returns a reference to the structure DRGBF
  inline struct DRGBF &get_drgbf() {return drgbf;}

  // Check whether new values from linear acc are ready or not
  inline bool is_linear_acceleration_data_ready() {return Linear_acceleration_data_ready;}

  // Indicate that the linear acceleration data has been processed
  inline void consume_linear_acceleration_data() {Linear_acceleration_data_ready = false;}

  // Returns a reference to the structure DRLAC
  inline struct DRLAC &get_drlac() {return drlac;}

  // Check whether new values from inertial acc are ready or not
  inline bool is_inertial_acceleration_data_ready() {return Inertial_acceleration_data_ready;}

  // Indicate that the inertial acceleration data has been processed
  inline void consume_inertial_acceleration_data() {Inertial_acceleration_data_ready = false;}

  // Returns a reference to the structure DRIAC
  inline struct DRIAC &get_driac() {return driac;}

  // Check whether new values from body frame velocity are ready or not
  inline bool is_body_frame_velocity_data_ready() {return Velocity_body_frame_data_ready;}

  // Indicate that the body frame velocity data has been processed
  inline void consume_body_frame_velocity_data() {Velocity_body_frame_data_ready = false;}

  // Returns a reference to the structure DRVBF
  inline struct DRVBF &get_drvbf() {return drvbf;}

  // Check whether new values from inertial frame velocity are ready or not
  inline bool is_inertial_frame_velocity_data_ready() {return Velocity_inertial_frame_data_ready;}

  // Indicate that the inertial frame velocity data has been processed
  inline void consume_inertial_frame_velocity_data() {Velocity_inertial_frame_data_ready = false;}

  // Returns a reference to the structure DRVIF
  inline struct DRVIF &get_drvif() {return drvif;}

  // Check whether new values from body frame position are ready or not
  inline bool is_body_frame_position_data_ready() {return Position_body_frame_data_ready;}

  // Indicate that the body frame position data has been processed
  inline void consume_body_frame_position_data() {Position_body_frame_data_ready = false;}

  // Returns a reference to the structure DRPBF
  inline struct DRPBF &get_drpbf() {return drpbf;}

  // Check whether new values from inertial frame position are ready or not
  inline bool is_inertial_frame_position_data_ready() {return Position_inertial_frame_data_ready;}

  // Indicate that the inertial frame position data has been processed
  inline void consume_inertial_frame_position_data() {Position_inertial_frame_data_ready = false;}

  // Returns a reference to the structure DRPIF
  inline struct DRPIF &get_drpif() {return drpif;}
      
 protected:
  
  // Initialise any variables (of the state machine). This method is
  // called any time a non-valid nmea string is identified
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
  const unsigned Max_nmea_string_size;
  
  // Stores the allowed size for the checksum
  const unsigned Checksum_size;
  
  // The number of read characters from the input NMEA string
  unsigned Counter_n_read_characters;
  
  // Total number of fields identified in the NMEA string
  unsigned Total_number_of_fields;
  
  // The current number of fields identified in the NMEA string
  unsigned Counter_n_current_fields;
  
  // Current state on the state machine
  unsigned Current_state;
  
  // The last state on the state machine
  unsigned Last_state;
  
  // Stores the checksum read from the input NMEA string
  char* Input_checksum;
  
  // Stores the identified fields of the input NMEA string. It
  // transforms
  // "$G2MOV,12.1,11.1"
  // into
  // Fields[0] = "G2MOV",
  // Fields[1] = "12.1",
  // Fields[2] = "11.1"
  char **Fields;
  
  // Matrix with the transitions of the state machine
  unsigned *State_machine_transitions;
  
  // The number of states in the state machine
  const unsigned NStates;
  
  // The number of transitions on of the state machine
  const unsigned NTransitions;
  
  // Final state of the state machine
  unsigned Final_state;
  
  // Stores the computed checksum of the currently reading NMEA
  // string
  unsigned Computed_checksum;
   
 private:
  
  // Decode the $DRRAWG string and fill the data structure
  bool decode_DRRAWG_and_fill_structure();
  
  // Print the data stored in the $DRRAWG structure
  void print_DRRAWG_structure();

  // Decode the $DRRAWA string and fill the data structure
  bool decode_DRRAWA_and_fill_structure();

  // Print the data stored in the $DRRAWA structure
  void print_DRRAWA_structure();

  // Decode the $DRROG string and fill the data structure
  bool decode_DRROG_and_fill_structure();

  // Print the data stored in the $DRROG structure
  void print_DRROG_structure();

  // Decode the $DRROA string and fill the data structure
  bool decode_DRROA_and_fill_structure();

  // Print the data stored in the $DRROA structure
  void print_DRROA_structure();

  // Decode the $DRFIG string and fill the data structure
  bool decode_DRFIG_and_fill_structure();

  // Print the data stored in the $DRFIG structure
  void print_DRFIG_structure();

  // Decode the $DRFIA string and fill the data structure
  bool decode_DRFIA_and_fill_structure();

  // Print the data stored in the $DRFIA structure
  void print_DRFIA_structure();

  // Decode the $DRALG string and fill the data structure
  bool decode_DRALG_and_fill_structure();

  // Print the data stored in the $DRALG structure
  void print_DRALG_structure();

  // Decode the $DRALA string and fill the data structure
  bool decode_DRALA_and_fill_structure();

  // Print the data stored in the $DRALA structure
  void print_DRALA_structure();

  // Decode the $DREAG string and fill the data structure
  bool decode_DREAG_and_fill_structure();

  // Print the data stored in the $DREAG structure
  void print_DREAG_structure();

  // Decode the $DREAA string and fill the data structure
  bool decode_DREAA_and_fill_structure();

  // Print the data stored in the $DREAA structure
  void print_DREAA_structure();

  // Decode the $DREAF string and fill the data structure
  bool decode_DREAF_and_fill_structure();

  // Print the data stored in the $DREAF structure
  void print_DREAF_structure();

  // Decode the $DRGBF string and fill the data structure
  bool decode_DRGBF_and_fill_structure();

  // Print the data stored in the $DRGBF structure
  void print_DRGBF_structure();

  // Decode the $DRLAC string and fill the data structure
  bool decode_DRLAC_and_fill_structure();

  // Print the data stored in the $DRLAC structure
  void print_DRLAC_structure();

  // Decode the $DRIAC string and fill the data structure
  bool decode_DRIAC_and_fill_structure();

  // Print the data stored in the $DRIAC structure
  void print_DRIAC_structure();

  // Decode the $DRVBF string and fill the data structure
  bool decode_DRVBF_and_fill_structure();

  // Print the data stored in the $DRVBF structure
  void print_DRVBF_structure();

  // Decode the $DRVIF string and fill the data structure
  bool decode_DRVIF_and_fill_structure();

  // Print the data stored in the $DRVIF structure
  void print_DRVIF_structure();

  // Decode the $DRPBF string and fill the data structure
  bool decode_DRPBF_and_fill_structure();

  // Print the data stored in the $DRPBF structure
  void print_DRPBF_structure();

  // Decode the $DRPIF string and fill the data structure
  bool decode_DRPIF_and_fill_structure();

  // Print the data stored in the $DRPIF structure
  void print_DRPIF_structure();
    
  // Helper function to transform from string to double
  bool transform_helper(double &number, char *string);
  
  // Helper function to transform from string to int
  bool transform_helper(int &number, char *string);
  
  // Helper function to transform from string to char
  bool transform_helper(char &character, char *string);
  
  // Structure to store the values received from the $DRRAWG NMEA string
  struct DRRAWG drrawg;
  
  // Flag to indicate that new values from raw gyro are ready
  bool Raw_gyro_data_ready;
  
  // Structure to store the values received from the $DRRAWA NMEA string
  struct DRRAWA drrawa;

  // Flag to indicate that new values from raw acc are ready
  bool Raw_acc_data_ready;

  // Structure to store the values received from the $DRROG NMEA string
  struct DRROG drrog;

  // Flag to indicate that new values from rotated gyro are ready
  bool Rotated_gyro_data_ready;

  // Structure to store the values received from the $DRROA NMEA string
  struct DRROA drroa;

  // Flag to indicate that new values from rotated acc are ready
  bool Rotated_acc_data_ready;

  // Structure to store the values received from the $DRFIG NMEA string
  struct DRFIG drfig;

  // Flag to indicate that new values from filtered gyro are ready
  bool Filtered_gyro_data_ready;

  // Structure to store the values received from the $DRFIA NMEA string
  struct DRFIA drfia;

  // Flag to indicate that new values from filtered acc are ready
  bool Filtered_acc_data_ready;

  // Structure to store the values received from the $DRALG NMEA string
  struct DRALG dralg;

  // Flag to indicate that new values from aligned gyro are ready
  bool Aligned_gyro_data_ready;

  // Structure to store the values received from the $DRALA NMEA string
  struct DRALA drala;

  // Flag to indicate that new values from aligned acc are ready
  bool Aligned_acc_data_ready;

  // Structure to store the values received from the $DREAG NMEA string
  struct DREAG dreag;

  // Flag to indicate that new values from euler angles gyro are ready
  bool Euler_angles_gyro_data_ready;

  // Structure to store the values received from the $DREAA NMEA string
  struct DREAA dreaa;

  // Flag to indicate that new values from euler angles acc are ready
  bool Euler_angles_acc_data_ready;

  // Structure to store the values received from the $DREAF NMEA string
  struct DREAF dreaf;

  // Flag to indicate that new values from euler angles fused are ready
  bool Euler_angles_fused_data_ready;

  // Structure to store the values received from the $DRGBF NMEA string
  struct DRGBF drgbf;

  // Flag to indicate that new values from gravity body frame are ready
  bool Gravity_body_frame_data_ready;

  // Structure to store the values received from the $DRLAC NMEA string
  struct DRLAC drlac;

  // Flag to indicate that new values from linear acceleration are ready
  bool Linear_acceleration_data_ready;

  // Structure to store the values received from the $DRIAC NMEA string
  struct DRIAC driac;

  // Flag to indicate that new values from inertial acceleration are ready
  bool Inertial_acceleration_data_ready;

  // Structure to store the values received from the $DRVBF NMEA string
  struct DRVBF drvbf;

  // Flag to indicate that new values from velocity body frame are ready
  bool Velocity_body_frame_data_ready;

  // Structure to store the values received from the $DRVIF NMEA string
  struct DRVIF drvif;

  // Flag to indicate that new values from velocity inertial frame are ready
  bool Velocity_inertial_frame_data_ready;

  // Structure to store the values received from the $DRPBF NMEA string
  struct DRPBF drpbf;

  // Flag to indicate that new values from position body frame are ready
  bool Position_body_frame_data_ready;

  // Structure to store the values received from the $DRPIF NMEA string
  struct DRPIF drpif;

  // Flag to indicate that new values from position inertial frame are ready
  bool Position_inertial_frame_data_ready;

 };
  
}

#endif // #ifndef CCNMEADECODER_H

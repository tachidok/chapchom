#ifndef CCNMEADECODER_H
#define CCNMEADECODER_H

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

#include <fstream>
#include <iostream>

namespace chapchom
{
 /// \struct PSTM3DACC cc_nmea_decoder.h
 
 /// Stores the information decoded from the $PSTM3DACC NMEA string
 struct PSTM3DACC
 {
  double time;
  bool valid_data_time;
  double acc_x;
  bool valid_data_acc_x;
  double acc_y;
  bool valid_data_acc_y;
  double acc_z;
  bool valid_data_acc_z;
 };
 
 /// \struct PSTM3DGYRO cc_nmea_decoder.h
 
 /// Stores the information decoded from the $PSTM3DGYRO NMEA string
 struct PSTM3DGYRO
 {
  double time;
  bool valid_data_time;
  double raw_x;
  bool valid_data_raw_x;
  double raw_y;
  bool valid_data_raw_y;
  double raw_z;
  bool valid_data_raw_z;
  int odometer_counter;
  bool valid_data_odometer_counter;
  int reverse;
  bool valid_data_reverse;
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
  
  // Decode the $PSTM3DACC string and fill the corresponding data
  // structure
  bool decode_PSTM3DACC_and_fill_structure();

  // Print the data stored in the $PSTM3DACC structure
  void print_PSTM3DACC_structure();
  
  // Decode the $PSTM3DGYRO string and fill the corresponding data
  // structure
  bool decode_PSTM3DGYRO_and_fill_structure();
  
  // Print the data stored in the $PSTM3DACC structure
  void print_PSTM3DGYRO_structure();
  
  // Helper function to transform from string to double
  bool transform_helper(double &number, char *string);
  
  // Helper function to transform from string to int
  bool transform_helper(int &number, char *string);
  
  // Structure to store the values received from the $PSTM3DACC NMEA
  // string
  struct PSTM3DACC pstm3dacc;
  
  // Structure to store the values received from the $PSTM3DGYRO NMEA
  // string
  struct PSTM3DGYRO pstm3dgyro;
  
 };
  
}

#endif // #ifndef CCNMEADECODER_H

#if 0

#define CNMEA_MAX_STR_SIZE 125 //!< Tamanio maximo de la cadena NMEA
#define CNMEA_MAX_MTT_TARGETS 6 //!<Numero Maximo de targets que se aceptaran en la cadena MTT
#define CNMEA_CHECKSUM_SIZE 3 //!<Tamanio del buffer que almacenara el campo del checksum.



class CNmeaParser {
public:

        int contradar;
	CNmeaParser();
	virtual ~CNmeaParser();

	/*! \brief Establece las variables a su estado inicial
	 */
	void iniciarVariables();

	/*! \brief Introduce el ultimo caracter recibido a la clase, para integrarlo a la revision actual de la cadena.
			@param caracter [in] Ultimo dato recibido
			@return 1 si el caracter es valido, -1 si el caracter no se encuentra en el rango permitido
	 */
	int parse(unsigned char caracter);
	int verificarMensaje(int numeroCampos);

        /* --- obtengo valores y regreso segun su estado --- */
    double getvelocidadViento();
    double getDireccionViento();
    double getTemperatura();
    double getPresion();
    double getHumedad();
    double getLatitud();
    double getLongitud();
    double getRumboBarco();
    double getVelocidadBarco();
	double getLaserDistance();
	int getNS();
	int getEO();
	double medirLaser();
	int nuevoDatoLaser;
	float distanciaLaser;
	
	string gethora();
	void gethoraGTM(int *horas, int *minutos);
    
    /* --- obtengo valores y regreso segun su estado --- */
	bool ttm_state;
	bool ttm_prev_state;
	bool block_received;
	bool switch_deque;
	
	std::deque<SInfoTargets> &dqBlock;
	std::deque<SInfoTargets> dqBlock_A;
	std::deque<SInfoTargets> dqBlock_Z;
		
	CCLaser laser;

	void saveInformationTargets();
	
public:

	CCINF inf;//!< Estructura que almacena la cadena, INF: General Information
	CCTTM ttm;//!< Estructura que almacena la cadena, TTM:Tracked Target Message
	CCVTG vtg;//!< Estructura que almacena la cadena, VTG:Track made good and Ground speed
	CCVHW vhw;//!< Estructura que almacena la cadena, VHW:Water speed and heading
	CCHDT hdt;//!< Estructura que almacena la cadena, HDT:Heading-True
	CCGLL gll;//!< Estructura que almacena la cadena, GLL: Geographic Position - Latitude/Longitude
	CCGGA gga;//!< Estructura que almacena la cadena, GGA:Global Positioning System Fix Data
	CCVBW vbw;//!< Estructura que almacena la cadena, VBW:Dual Ground/Water Speed
	CCRMC rmc;//!< Estructura que almacena la cadena, RMC: Recommended Minimum Navigation Information
	CCMWV mwv;
	CCMWD mwd;
	CCXDR xdr;
	CCEMVA emva;//!< added by Jesus: Valores en estado manual
	
public:

	int contadorEntrada; //!<Contador del numero de datos que han entrado al parser. Sirve para detectar si ya se tienen mas de 82.
	int contadorCampo; //!<Contador del numero de datos que han entrado al campo actual

	char cadenaChecksum[CNMEA_CHECKSUM_SIZE]; //!<Cadena con los datos obtenidos en el campo checksum.
	char campos[CNMEA_MAX_CAMPOS][CNMEA_CAMPO_SIZE]; //!<Arreglo con los campos contenidos en la cadena. Por ejemplo, en la cadena "$G2MOV,12.1,11.1" campos[0] = "G2MOV", campos[1] = "12.1", campos[2] = "11.1"
	int numeroCampos; //!<Numero de campos encontrados en la cadena analizada, desde el address field hasta encontrar el checksum.

	int matrizAutomata[6][15]; //!<Matriz que describe el AFD
	int estadoActual; //!< Estado actual del AFD
	int estadoAnterior; //!<Indica el estado que tenia el AFD antes de recibir el ultimo caracter
	int estadosFinales[1]; //!<Estados finales del AFD
	int checksum; //!< Checksum calculado

	double pesoProyectil;
	double velProyectil;
	int cadencia;

	//int currentTarget;
	double velRadar;
	double dirRadar;
	int modoRadar;
};

#endif // #if 0

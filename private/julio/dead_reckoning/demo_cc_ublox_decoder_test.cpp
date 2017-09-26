#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The UBLOX decoder
#include "cc_ublox_decoder.h"

#define TO_RADIANS (M_PI/180.0)
#define TO_DEGREES (180.0/M_PI)

using namespace chapchom;

int main(int argc, char *argv[])
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Create the UBLOX decoder
 CCUBLOXDecoder ublox_decoder;
 
 // Create the object to deal with a file
 std::ifstream infile;
 //infile.open("./UBLOX/data.bin", std::ios::in | std::ios::binary);
 //infile.open("./UBLOX/data2.bin", std::ios::in | std::ios::binary);
 //infile.open("./UBLOX/data2.bin", std::ios::in);
 //infile.open("./UBLOX/Betancourt/trajectory.bin", std::ios::in | std::ios::binary);
 //infile.open("./UBLOX/Betancourt/COM8_170926_220050_julio.ubx", std::ios::in | std::ios::binary);
 infile.open("./UBLOX/Betancourt/COM8_170926_221026_julio_2.ubx", std::ios::in | std::ios::binary);
 if (infile.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "We could not open the UBLOX bin file" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Raw gyro
 char file_raw_gyro_name[100];
 sprintf(file_raw_gyro_name, "./RESLT/raw_gyro.dat");
 std::ofstream outfile_raw_gyro;
 outfile_raw_gyro.open(file_raw_gyro_name, std::ios::out);
 if (outfile_raw_gyro.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_gyro_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Raw accelerations
 char file_raw_accelerations_name[100];
 sprintf(file_raw_accelerations_name, "./RESLT/raw_accelerations.dat");
 std::ofstream outfile_raw_acc;
 outfile_raw_acc.open(file_raw_accelerations_name, std::ios::out);
 if (outfile_raw_acc.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "Could not create the file [" << file_raw_accelerations_name << "]"
                 << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }
 
 // Extracted byte
 char byte;
 // Loop until eof
 while(!infile.eof())
  {
   infile.get(byte);
   //std::cerr << character;
   ublox_decoder.parse(byte);
   // Check whether any of the data structures has new information
   if (ublox_decoder.is_UBX_ESF_RAW_data_ready())
    {
     // Get the data structure
     struct UBX_ESF_RAW ubx_esf_raw = ublox_decoder.get_UBX_ESF_RAW();
     // Print the read data
     std::cout << ubx_esf_raw.gyroscope_temperature << " " << ubx_esf_raw.gyroscope_x << " " << ubx_esf_raw.gyroscope_y << " " << ubx_esf_raw.gyroscope_z << " " << ubx_esf_raw.accelerometer_x << " " << ubx_esf_raw.accelerometer_y << " " << ubx_esf_raw.accelerometer_z << std::endl;
     // Consume UBX-ESF-RAW
     ublox_decoder.consume_UBX_ESF_RAW_data();     
    }
   
  } // while(!infile.eof())
 
 // Close the files
 infile.close();
 outfile_raw_gyro.close();
 outfile_raw_acc.close();
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}

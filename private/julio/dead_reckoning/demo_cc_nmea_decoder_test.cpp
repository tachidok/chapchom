#include <iostream>
#include <cmath>
#include <fstream>

// Include general/common includes, utilities and initialisation
#include "../../../src/general/common_includes.h"
#include "../../../src/general/utilities.h"
#include "../../../src/general/initialise.h"

// The nmea decoder
#include "cc_nmea_decoder.h"

using namespace chapchom;

int main(int argc, char *argv[])
{
 // Create the nmea decoder
 CCNMEADecoder nmea_decoder(20);
 // Create the object to deal with a file
 std::ifstream infile;
 infile.open("./bin/Cadenas_GNSS.txt", std::ios::in);
 if (infile.fail())
  {
   // Error message
   std::ostringstream error_message;
   error_message << "We could not open the NMEA strings file" << std::endl;
   throw ChapchomLibError(error_message.str(),
                          CHAPCHOM_CURRENT_FUNCTION,
                          CHAPCHOM_EXCEPTION_LOCATION);
  }

 // Extracted character
 char character;
 // Loop until eof
 while(!infile.eof())
  {
   infile.get(character);
   std::cerr << character;
   nmea_decoder.parse(character);
  }
 
 // Close the file
 infile.close();
 
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}

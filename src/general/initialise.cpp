// Include the initialisation rutines headers
#include "initialise.h"

namespace chapchom
{
 bool initialise_chapchom()
 {
  chapchom_output << "Initialising chapchom .." << std::endl;
  // These variables are defined in the header file
  // cmake_definitions.h, which is automatically generated from the
  // cmake_definitions.h.in file
  chapchom_output << "This is chapchom version "
                  << MAJOR_VERSION
                  << "."
                  << MINOR_VERSION
                  << "."
                  << PATCH_LEVEL
                  << std::endl;
  
  /// Setup terminate helper
  TerminateHelper::setup();
  chapchom_output << "[DONE]: Chapchom initialisation" << std::endl;
  // Everything was alright
  return true;
  
 }
 
 bool finalise_chapchom()
 {
  chapchom_output << "Finalising chapchom ..." << std::endl;
  chapchom_output << "[DONE]: Chapchom termination" << std::endl;
  // Everything was alright
  return true;
 }
 
}

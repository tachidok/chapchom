// Include the initialisation rutines headers
#include "initialise.h"

namespace chapchom
{
 bool initialise_chapchom()
 {
  chapchom_output << "Initialising chapchom .." << std::endl;
  
  /// Setup terminate helper
  TerminateHelper::setup();
  chapchom_output << "[DONE]: Chapchom initialisation" << std::endl;
 }
 
 bool finalise_chapchom()
 {
  chapchom_output << "Finalising chapchom ..." << std::endl;
  chapchom_output << "[DONE]" << std::endl;
 }
 
}

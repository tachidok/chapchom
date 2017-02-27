#ifndef INITIALISE_H
#define INITIALISE_H

#include "common_includes.h"
#include "utilities.h"

namespace chapchom
{
 // Initialisation function, everything required before using chapchom
 // should be called here
 bool initialise_chapchom();
 
 // Finalise function, call all finalisation methods, free memory
 // allocated by chapchom
 bool finalise_chapchom();
 
}

#endif // #ifndef INITIALISE_H

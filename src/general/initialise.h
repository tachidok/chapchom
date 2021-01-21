#ifndef INITIALISE_H
#define INITIALISE_H

#include "common_includes.h"
#include "utilities.h"

namespace scicellxx
{
 /// Initialisation function, everything required before using scicellxx
 /// should be called here
 bool initialise_scicellxx();
 
 /// Finalise function, call all finalisation methods, free memory
 /// allocated by scicellxx
 bool finalise_scicellxx();
 
}

#endif // #ifndef INITIALISE_H

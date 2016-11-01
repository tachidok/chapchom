#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

// ====================================================================
// Check this page for more information about the included libraries
// 
// http://en.cppreference.com/w/cpp/header
// 
// ====================================================================

// ====================================================================
// Utilities library
// ====================================================================
#include <typeinfo> // 	Runtime type information utilities
#include <utility> // Various utility components
#include <ctime> // C-style time/date utilites
// #include <chrono> // (since C++11) C++ time utilites

// ====================================================================
// Utilities library / Numeric limits
// ====================================================================
#include <climits>
#include <cfloat>
#include <limits>

// ====================================================================
// Utilities library / Error handling
// ====================================================================
#include <exception> // Exception handling utilities
#include <stdexcept> // Standard exception objects
#include <cassert> // Conditionally compiled macro that compares its
		   // argument to zero
//#include <system_error> // (since C++11) defines std::error_code, a
			// platform-dependent error code
#include <cerrno> // Macro containing the last error number

// ====================================================================
// String library
// ====================================================================
#include <cstring> // various narrow character string handling functions
#include <string>  // library to handle strings, implements std::string

// ====================================================================
// Containers library
// ====================================================================
//#include <array> // (since C++11) std::array container
#include <vector> // std::vector container
#include <list> // std::list container
#include <set> // std::set container
#include <map> // std::map container

// ====================================================================
// Algorithms library
// ====================================================================
#include <algorithm> // Algorithms that operate on containers

// ====================================================================
// Numerics library
// ====================================================================
#include <cmath>

// ====================================================================
// Input/output library
// ====================================================================
#include <iostream> // several standard stream objects
#include <fstream> // functions for inputting from and outputting to files
#include <sstream>

// Own chapchom definitions
#include "definitions.h"
#include "cmake_definitions.h"

#endif // #ifndef COMMON_INCLUDES_H

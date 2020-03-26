#ifndef DEFINITIONS_H
#define DEFINITIONS_H

namespace chapchom
{

#ifdef TYPEDEF_REAL_IS_DOUBLE
 typedef double Real;
#else
 typedef float Real;
#endif // #ifdef TYPEDEF_REAL_IS_DOUBLE
 
#define PANIC_MODE
#ifdef PANIC_MODE
 // =======================================================================
 // Macros for debugging
 // =======================================================================
#define DEB(x) std::cerr<<"DEB ["<<#x<<"] = "<<x<<std::endl<<std::flush;
#define DEB2(x,y) std::cerr<<"DEB ["<<x<<" "<<y<<"]"<<std::endl<<std::flush;
#define DEB3(x,y,z) std::cerr<<"DEB ["<<x<<" "<<y<<" "<<z<<"]"<<std::endl<<std::flush;
#define DEB4(t,x,y,z) std::cerr<<"DEB ["<<t<<" "<<x<<" "<<y<<" "<<z<<"]"<<std::endl<<std::flush;
#define DEB_TO_FILE(F,x) F<<"["<<#x<<"] = "<<x<<std::endl<<std::flush;
#define DEB_TO_FILE1(F,x) F<<x<<std::endl<<std::flush;
#define DEB_TO_FILE2(F,x,y) F<<x<<" "<<y<<std::endl<<std::flush;
#define DEB_TO_FILE3(F,x,y,z) F<<x<<" "<<y<<" "<<z<<std::endl<<std::flush;
#define DEB_TO_FILE4(F,t,x,y,z) F<<t<<" "<<x<<" "<<y<<" "<<z<<std::endl<<std::flush;
#endif // #ifdef PANIC_MODE
 
 // =======================================================================
 // Macros to transform from degrees to radians and vice versa
 // =======================================================================
#define TO_RADIANS (M_PI/180.0)
#define TO_DEGREES (180.0/M_PI)
 
 // =======================================================================
 // The macros to deal with strings for error messages are taken from
 // oomph-lib
 // =======================================================================

 //Pre-processor magic for error reporting
 //Macro that converts argument to string
#define CHAPCHOM_MAKE_STRING(x) #x

 //Macro wrapper to CHAPCHOM_MAKE_STRING, required because calling
 //CHAPCHOM_MAKE_STRING(__LINE__) directly returns __LINE__
 //i.e. the conversion of __LINE__ into a number must be performed before
 //its conversion into a string
#define CHAPCHOM_TO_STRING(x) CHAPCHOM_MAKE_STRING(x)

 //Combine the FILE and LINE built-in macros into a string that can
 //be used in error messages.
#define CHAPCHOM_EXCEPTION_LOCATION __FILE__ ":" CHAPCHOM_TO_STRING(__LINE__)

 // Get the current function name. All the mess is due to different
 // compilers naming the macro we need differently.
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
# define CHAPCHOM_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)
# define CHAPCHOM_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)
# define CHAPCHOM_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
# define CHAPCHOM_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
# define CHAPCHOM_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
# define CHAPCHOM_CURRENT_FUNCTION __func__

#else
# define CHAPCHOM_CURRENT_FUNCTION "[Unknown function -- unrecognised compiler]"

#endif

}
 
#endif // #ifdef DEFINITIONS_H


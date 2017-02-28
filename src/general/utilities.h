#ifndef UTILITIES_H
#define UTILITIES_H

#include "common_includes.h"

namespace chapchom
{

 // ======================================================================
 /// The error messages are based on oomph-lib's implementation to deal
 /// with errors
 //=======================================================================

 namespace BrokenCopy
 {
  /// Issue error message and terminate execution
  extern void broken_assign(const std::string& class_name);
 
  /// Issue error message and terminate execution
  extern void broken_copy(const std::string& class_name);
 }

 //=======================================================================
 /// Helper namespace for set_terminate function -- used to spawn
 /// messages from uncaught errors (their destructor may not be called)
 ///======================================================================
 namespace TerminateHelper
 {
  /// Setup terminate helper
  extern void setup();

  /// \short Suppress error messages (e.g. because error has been caught)
  extern void suppress_exception_error_messages();

  /// Function to spawn messages from uncaught errors
  extern void spawn_errors_from_uncaught_errors();

  /// Stream to output error messages
  extern std::ostream* Error_message_stream_pt;

  /// String stream that records the error message
  extern std::stringstream* Exception_stringstream_pt;

 }

 //=====================================================================
 /// Run-time exception handling  (error and warning).
 ///
 /// The (protected) constructor combines its string arguments into a
 /// standard format for uniform exception reports which are written to
 /// the specified output stream.
 ///
 //=====================================================================

 /// The class can only be instantiated by the derived classes
 /// ChapchomLibError and ChapchomLibWarning.
 class ChapchomLibException : public std::runtime_error
 {
 
 public:
 
  /// Suppress error message in destructor (useful if error is caught
  /// successfully!)
  void disable_error_message();
 
 protected:
 
  /// Constructor takes the error description, function name and a
  /// location string provided by the CHAPCHOM_EXCEPTION_LOCATION macro
  /// and combines them into a standard header. The exception type will
  /// be the string "WARNING" or "ERROR" and the message is written to
  /// the exception_stream, with a specified output_width. Optionally
  /// provide a traceback of the function calls.
  ChapchomLibException(const std::string &error_description,
                       const std::string &function_name,
                       const char *location,
                       const std::string &exception_type,
                       std::ostream &exception_stream,
                       const unsigned &output_width);
 
  /// The destructor cannot throw an exception (C++ STL standard)
  ~ChapchomLibException() throw(); 
 
  /// Exception stream to which we write message in destructor        
  std::ostream* Exception_stream_pt;
 
  /// String stream that records the error message
  std::stringstream* Exception_string_stream_pt;
 
  /// Boolean to suppress issuing of the error message in destructor
  /// (useful if error is caught successfully!)
  bool Suppress_error_message;
 
 };

 /// ====================================================================
 /// Throw this object when an run-time / error is encountered. The
 /// error stream and stream width can be specified. The default is
 /// cerr with a width of 70 characters.
 /// ====================================================================
 class ChapchomLibError : public ChapchomLibException
 {
  /// Output stream that is used to write the errors
  static std::ostream *Stream_pt;
 
  /// Width in characters of the output report
  static unsigned Output_width;

 public:

  /// Constructor requires the error description and the function in
  /// which the error occured and the location provided by the
  /// CHAPCHOM_EXCEPTION_LOCATION macro
 ChapchomLibError(const std::string &error_description,
		  const std::string &function_name,
		  const char *location) :
  ChapchomLibException(error_description,function_name,location,"ERROR",
                       *Stream_pt, Output_width) 
   { }
 
  /// Static member function used to specify the error stream, which
  /// must be passed as a pointer because streams cannot be copied.
  static inline void set_stream_pt(std::ostream* const &stream_pt)
  {Stream_pt = stream_pt;}
 
  /// Static member function used to specify the width (in characters)
  /// of the error stream
  static inline void set_output_width(const unsigned &output_width)
  {Output_width = output_width;}
 
 };

 //====================================================================
 /// An ChapchomLibWarning object which should be created as a temporary
 /// object to issue a warning. The warning stream and stream width can
 /// be specified. The default is cerr with a width of 70 characters.
 //====================================================================
 class ChapchomLibWarning : public ChapchomLibException
 {
  /// Output stream that is used to write the errors
  static std::ostream *Stream_pt;

  /// Width of output
  static unsigned Output_width;

 public:

  /// Constructor requires the warning description and the function
  /// in which the warning occurred.
 ChapchomLibWarning(const std::string &warning_description,
		    const std::string &function_name,
		    const char* location) :
  ChapchomLibException(warning_description,function_name, location,
                       "WARNING",*Stream_pt,Output_width) { }
 
  /// Static member function used to specify the error stream, which
  /// must be passed as a pointer because streams cannot be copied.
  static inline void set_stream_pt(std::ostream* const &stream_pt)
  {Stream_pt = stream_pt;}
 
  /// \short Static member function used to specify the width (in characters)
  /// of the error stream
  static inline void set_output_width(const unsigned &output_width)
  {Output_width = output_width;}
 
 };

 ////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////
 
 //========================================================================
 // Wrapper to a stream and an output modifier used to control the
 // output from chapchom. Its instantiation can be used like std::cout.
 // =======================================================================
 class ChapchomOutput
 {
  
 private:
  
  ///Pointer to the output stream -- defaults to std::cout
  std::ostream *Stream_pt;
  
 public:
  
  ///\short Set default values for the output stream (cout)
  ///and modifier (no modification)
  ChapchomOutput();
  
#if 0
  ///\short Overload the << operator, writing output to the stream addressed by
  ///Stream_pt and calling the function defined by the object addressed by
  ///Output_modifier_pt
  template<class _Tp>
   std::ostream &operator<<(_Tp argument);
#endif // #if 0
  
#if 1
  template<class _Tp>
   std::ostream &operator<<(_Tp argument)
   {
    *Stream_pt << argument;
    return (*Stream_pt);
   }
#endif // #if 1
  
  ///Access function for the stream pointer
  std::ostream* &stream_pt() {return Stream_pt;}
 
  ///Overload insertor to handle stream modifiers
  std::ostream &operator<<(std::ostream& (*f)(std::ostream &))
   {
    return f(*Stream_pt);
   }
 
 };
 
 //========================================================================
 // Single (global) instantiation of the ChapchomOutput object -- this
 // is used throughout the library as a "replacement" for std::cout
 //========================================================================
 extern ChapchomOutput chapchom_output;

 //==================================================================
 // Utility method to time a program
 //==================================================================
 namespace Timing
 {
  // ================================================================
  // Use this method when you want to know the "wall time" a section
  // of code, method or program takes for its execution. Call it at
  // the beggining of the section and then at the end of the section
  // you want to time
  // ================================================================
  inline time_t wall_time() {return time(0);}
  
  // ================================================================
  // Use this method to get the difference (IN SECONDS) between two
  // "wall_time()" method calls
  // ================================================================
  inline double diff_wall_time(time_t &initial_time, time_t &final_time)
  {return difftime(final_time, initial_time);}
  
  // ================================================================
  // Use this method when you want to know the "cpu time" a section of
  // code, method or program takes for its execution. Call it at the
  // beggining of the section and then at the end of the section you
  // want to time
  // ================================================================
  inline clock_t cpu_clock_time() {return clock();}
  
  // ================================================================
  // Use this method to get the difference (IN SECONDS) between two
  // "cpu_clock_time()" method calls
  // ================================================================
  inline double diff_cpu_clock_time(clock_t &initial_cpu_time,
                                    clock_t &final_cpu_time)
  {return
    static_cast<double>(final_cpu_time-initial_cpu_time)/CLOCKS_PER_SEC;}
  
 }
 
} 

#endif // #ifndef UTILITIES_H

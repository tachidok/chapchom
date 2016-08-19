#ifndef UTILITIES_H
#define UTILITIES_H

#include "common_includes.h"

// =======================================================================
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

//=====================================================================
/// Run-time exception handling  (error and warning).
///
/// The (protected) constructor combines its string arguments into a
/// standard format for uniform exception reports which are written to
/// the specified output stream.
///
//======================================================================

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
		      *Stream_pt,Output_width) 
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

#endif // #ifndef UTILITIES_H

#include "utilities.h"

namespace chapchom
{
 
 // =======================================================================
 // The error messages are based on oomph-lib's implementation to deal
 // with errors
 // =======================================================================

 //=======================================================================
 /// The error messages for broken copy constructors and assignment
 /// operators. Check
 /// http://www.learncpp.com/cpp-tutorial/912-shallow-vs-deep-copying/
 //=======================================================================

 namespace BrokenCopy
 {
  /// Issue error message and terminate execution
  void broken_assign(const std::string& class_name)
  {
   //Write the error message into a string
   std::ostringstream error_message;
   error_message << "No assignment operator allowed for class\n\n";
   error_message << class_name;
   error_message << "\n\n";
   error_message << "Deliberately broken to avoid the accidental \n";
   error_message << "use of the inappropriate C++ default.\n";
   error_message << "If you really need an assignment operator\n";
   error_message << "for this class, write it yourself...\n";
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }
 
  /// Issue error message and terminate execution
  void broken_copy(const std::string& class_name)
  {
   //Write the error message into a string
   std::ostringstream error_message;
   error_message << "No copy constructor allowed for class\n\n";
   error_message << class_name;
   error_message << "\n\n";
   error_message << "is deliberately broken to avoid the accidental\n";
   error_message << "use of the inappropriate C++ default.\n";
   error_message <<
    "All function arguments should be passed by reference or\n";
   error_message <<
    "constant reference. If you really need a copy constructor\n";
   error_message << "for this class, write it yourself...\n";
   throw ChapchomLibError(error_message.str(),
			  CHAPCHOM_CURRENT_FUNCTION,
			  CHAPCHOM_EXCEPTION_LOCATION);
  }

 }

 //=======================================================================
 /// Helper namespace for set_terminate function -- used to spawn
 /// messages from uncaught errors
 ///=======================================================================
 namespace TerminateHelper
 {

  /// Setup terminate helper
  void setup()
  {
   if (Exception_stringstream_pt!=0) delete Exception_stringstream_pt;
   Exception_stringstream_pt=new std::stringstream;
   std::set_terminate(spawn_errors_from_uncaught_errors);
  }

  /// \short Flush string stream of error messages (call when error has been
  /// caught)
  void suppress_exception_error_messages()
  {
   delete Exception_stringstream_pt;
   Exception_stringstream_pt=new std::stringstream;
  }

  /// Function to spawn messages from uncaught errors
  void spawn_errors_from_uncaught_errors()
  {
   (*Error_message_stream_pt) << (*Exception_stringstream_pt).str();
  }

  /// Stream to output error messages
  std::ostream* Error_message_stream_pt=&std::cerr;

  /// String stream that records the error message
  std::stringstream* Exception_stringstream_pt=0;
 }

 ///////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////////

 //==========================================================================
 /// Constructor takes the error description, function name and a
 /// location string provided by the EXCEPTION_LOCATION macro and
 /// combines them into a standard header. The exception type will be
 /// the string "WARNING" or "ERROR" and the message is written to the
 /// exception_stream, with a specified output_width. Optionally
 /// provide a traceback of the function calls.
 //==========================================================================
 ChapchomLibException::ChapchomLibException(const std::string &error_description,
                                            const std::string &function_name,
                                            const char *location,
                                            const std::string &exception_type,
                                            std::ostream &exception_stream,
                                            const unsigned &output_width) : 
  std::runtime_error("Exception")
 {
  // By default we shout
  Suppress_error_message=false;
 
  // Store exception stream
  Exception_stream_pt=&exception_stream;
 
  // Create storage for error message
  Exception_string_stream_pt=new std::stringstream;
 
  //Build an exception header string from the information passed
  //Start with a couple of new lines to space things out
  std::string exception_header="\n\n";
 
  //Now add a dividing line
  for(unsigned i=0;i<output_width;i++) {exception_header += "=";}
  exception_header += "\n";
 
  //Write the type of exception
  exception_header += exception_type;

  //Add the function in which it occurs
  exception_header += "\n\n at ";
  exception_header += location;
  exception_header += "\n\n in ";
  exception_header += function_name;

  //Finish with two new lines 
  exception_header +="\n\n";

  //and a closing line
  for(unsigned i=0;i<(unsigned)(0.8*output_width);i++)  
   {exception_header +=  "-";}
 
  //Output the error header to the stream
  (*Exception_string_stream_pt) << exception_header << std::endl;

  //Report the error
  (*Exception_string_stream_pt) << std::endl << error_description << std::endl;
  
  //Finish off with another set of double lines
  for(unsigned i=0;i<output_width;i++) {(*Exception_string_stream_pt) << "=";}
  (*Exception_string_stream_pt) << std::endl << std::endl;
 
  // Copy message to stream in terminate helper in case the message
  // doesn't get caught and/or doesn/t make it to the destructor
  (*TerminateHelper::Exception_stringstream_pt)<<
   (*Exception_string_stream_pt).str();
 
 }

 //========================================================================
 /// The ChapchomLibException destructor actually spawns the error message
 /// created in the constructor (unless suppresed)
 //==========================================================================
 ChapchomLibException::~ChapchomLibException() throw()
 {
  if (!Suppress_error_message)
   {
    (*Exception_stream_pt) << (*Exception_string_stream_pt).str();
   }
  delete Exception_string_stream_pt;
  Exception_string_stream_pt=0;
 }

 //========================================================================
 /// Default output stream for ChapchomLibErrors (cerr)
 //========================================================================
 std::ostream *ChapchomLibError::Stream_pt = &std::cerr;

 //=======================================================================
 /// Default output width for ChapchomLibErrors (70)
 //=======================================================================
 unsigned ChapchomLibError::Output_width = 70;

 //=======================================================================
 /// Default output stream for ChapchomLibWarnings (cerr)
 //=======================================================================
 std::ostream *ChapchomLibWarning::Stream_pt = &std::cerr;

 //=======================================================================
 /// Default output width for ChapchomLibWarnings (70)
 //=======================================================================
 unsigned ChapchomLibWarning::Output_width = 70;

 ////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////

 //=======================================================================
 // Set default values for the output stream (cout) and modifier (no
 // modification)
 // =======================================================================
 ChapchomOutput::ChapchomOutput() : Stream_pt(&std::cout)
 { }

#if 0
 // =======================================================================
 // Overload the << operator, writing output to the stream addressed by
 // Stream_pt and calling the function defined by the object addressed
 // by Output_modifier_pt
 // =======================================================================
 template<class _Tp>
 std::ostream &ChapchomOutput::operator<<(_Tp argument)
 {
  *Stream_pt << argument;
  return (*Stream_pt);
 }
#endif // #if 0
 
 //========================================================================
 // Single (global) instantiation of the ChapchomOutput object -- this
 // is used throughout the library as a "replacement" for std::cout
 //========================================================================
 ChapchomOutput chapchom_output;
 
}

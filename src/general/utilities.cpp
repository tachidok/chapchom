#include "utilities.h"

// =======================================================================
/// The error messages are based on oomph-lib's implementation to deal
/// with errors
//=======================================================================

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

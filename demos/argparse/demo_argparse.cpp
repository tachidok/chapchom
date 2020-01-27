#include "../../src/general/common_includes.h"
#include "../../src/general/utilities.h"
#include "../../src/general/initialise.h"

// Use the namespace of the framework
using namespace chapchom;

struct Args {
 argparse::ArgValue<bool> boolean_argument;
 argparse::ArgValue<std::string> string_argument;
 argparse::ArgValue<size_t> verbosity;
 argparse::ArgValue<Real> real_argument;
 argparse::ArgValue<std::vector<Real> > vector_real_arguments_one_or_more;
 argparse::ArgValue<std::vector<Real> > vector_real_arguments_none_or_more;
};

int main(int argc, const char** argv)
{
 // Initialise chapcom
 initialise_chapchom();
 
 // Output for testing/validation
 std::ofstream output_test("output_test.dat", std::ios_base::out);
 
 // Instantiate parser
 Args args;
 auto parser = argparse::ArgumentParser(argv[0], "Description of application");
 
 // Add arguments
 
 // Positional
 parser.add_argument(args.string_argument, "string_argument")
  .help("File to process");
 
 // Optional
 parser.add_argument(args.boolean_argument, "--boolean_argument")
  .help("Boolean argument")
  .default_value("false")
  .action(argparse::Action::STORE_TRUE); 
 
 // Note the use of choices values
 parser.add_argument(args.verbosity, "--verbosity", "-v")
  .help("Sets the verbosity")
  .default_value("1")
  .choices({"0", "1", "2"});
 
 parser.add_argument<Real>(args.real_argument, "--real_argument")
  .help("Sets Real argument")
  .default_value("1.0");
 
 // One or more real arguments with default values
 parser.add_argument(args.vector_real_arguments_one_or_more, "--vector_real_arguments_one_or_more")
  .help("One or more Real values")
  .nargs('+')
  .default_value({"1.0", "0.2"});
 
 // None or more real arguments
 parser.add_argument(args.vector_real_arguments_none_or_more, "--vector_real_arguments_none_or_more")
  .help("Zero or more float values")
  .nargs('*')
  .default_value({});
 
 // Parse the input arguments
 parser.parse_args(argc, argv);
 
 //Show the arguments
 std::cout << "args.string_argument: " << args.string_argument << "\n";
 std::cout << "args.boolean_argument: " << args.boolean_argument << "\n";
 std::cout << "args.verbosity: " << args.verbosity << "\n";
 std::cout << "args.real_argument: " << args.real_argument << "\n";
 std::cout << "args.vector_real_arguments_one_or_more: " << argparse::join(args.vector_real_arguments_one_or_more.value(), ", ") << "\n";
 std::cout << "args.vector_real_arguments_none_or_more: " << argparse::join(args.vector_real_arguments_none_or_more.value(), ", ") << "\n";
 std::cout << "\n";

 output_test << "args.string_argument: " << args.string_argument << "\n";
 output_test << "args.boolean_argument: " << args.boolean_argument << "\n";
 output_test << "args.verbosity: " << args.verbosity << "\n";
 output_test << "args.real_argument: " << args.real_argument << "\n";
 output_test << "args.vector_real_arguments_one_or_more: " << argparse::join(args.vector_real_arguments_one_or_more.value(), ", ") << "\n";
 output_test << "args.vector_real_arguments_none_or_more: " << argparse::join(args.vector_real_arguments_none_or_more.value(), ", ") << "\n";
 
 // Close the output for test
 output_test.close();
  
 // Finalise chapcom
 finalise_chapchom();
 
 return 0;
 
}


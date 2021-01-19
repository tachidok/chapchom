#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# Usage function
usage()
{
cat << EOF
usage: $0 [OPTIONS]

This script run the test1 or test2 over a machine.

OPTIONS:
   -h      Show this message
   -t      Indicates a 'STATIC' or 'SHARED' library files
   -b      Build version 'DEBUG' or 'RELEASE'
   -c      Configuration file
   -n      Number of processors to build the framework
   -d      Number of processors to run demos (set to '0' to skip demos testing)
   -i      Interative mode, launches the interactive mode to prompt for FULL configuration options (any other parameters are ignored)
   -r      Generate code coverage report
   -v      Verbose
EOF
}

# An small function 'borrowed' from the oomph-lib installation
# script...
OptionPrompt() 
{ 
 printf "%s " "$1" 
}

# Another small function 'borrowed' from the oomph-lib installation
# script...
OptionRead()
{
 read Opt
 if test "$Opt" = "" ; then
  Opt=$1
 fi
 echo $Opt
}

#====================================================================
# Variables (and default values)
#====================================================================
build_dir=build
src_dir=src
external_src_dir=external_src

# The name of the library
lib_name=SciCell++
# The extension of the library is given by the choosing of STATIC or
# SHARED library
#lib_ext=*
# The type of the library is given by the choosing of STATIC or SHARED
# library
lib_type=STATIC
# The version of the library is given by whether the user choose to
# build the DEBUG or the RELEASE version of the library
lib_build=DEBUG
# Indicates the configuration file with variables for paths for
# external libraries
configuration_file=./configs/current
# Indicates the number of processors to build the library
default_number_of_processors_to_build_library=4
number_of_processors_to_build_library=$default_number_of_processors_to_build_library
# Indicates whether to build/compile test demos
build_test_demos=TRUE
# Indicates the number of processors to build the demos
default_number_of_processors_to_run_demos=4
number_of_processors_to_run_demos=$default_number_of_processors_to_run_demos
# Prompts for FULL configuration
full_configuration=FALSE
# Generate code coverage report (default to FALSE)
generate_code_coverage_report=FALSE
# Indicates whether to output building information (currently not in use)
verbose=TRUE

#====================================================================
# Parse arguments
# ====================================================================
# The ':' followed by the argument letter indicates that it requires
# an argument value. Example: 't:' indicates that 't' is followed by
# an argument value. 'h', 'i', 'r' and 'v' do not require arguments.
while getopts “ht:b:c:n:d:irv” OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         t)
             lib_type=$OPTARG
             ;;
         b)
             lib_build=$OPTARG
             ;;
         c)
             configuration_file=$OPTARG
             ;;
         n)
             number_of_processors_to_build_library=$OPTARG
             ;;
         d)
             number_of_processors_to_run_demos=$OPTARG
             ;;
         i)
             full_configuration=TRUE
             ;;
         r)
             generate_code_coverage_report=TRUE
             ;;
         v)
             verbose=TRUE
             ;;
         ?)
             echo ""
             echo "============================================================= "
             echo ""
             echo "ERROR: No recognized parameter"
             echo ""
             echo "============================================================= "
             echo ""
             usage
             exit 1
             ;;
     esac
done


#====================================================================
# The building script
#====================================================================

echo " "
echo "============================================================= "
echo "            "$lib_name" installation script" 
echo "============================================================= "
echo " "

echo ""
echo "============================================================= "
echo ""
echo "This script allows you to install and/or run test for "$lib_name
echo ""
echo "============================================================= "
echo ""
echo ""

#====================================================================
# Library type
#====================================================================

# Check whether FULL CONFIGURATION was requested
if test "$full_configuration" = "TRUE" ; then

    # Answer's default value
    static_or_shared='a'
    
    echo "Which library type do you want to build?"
    OptionPrompt "The a)STATIC or the b)SHARED type library? [a/b -- default: a]"
    static_or_shared=`OptionRead`

    if test "$static_or_shared" = "b" -o "$static_or_shared" = "B" ; then 
        lib_type=SHARED
        #lib_ext=.so
    else
        lib_type=STATIC
        #lib_ext=.a
    fi

    echo ""
    echo "============================================================= "
    echo ""
    
fi

#====================================================================
# Build version
#====================================================================

# Check whether FULL CONFIGURATION was requested
if test "$full_configuration" = "TRUE" ; then

    # Answer's default value
    debug_or_release='a'
    
    echo "Which library version do you want to build?"
    OptionPrompt "The a)DEBUG or the b)RELEASE version of the library ? [a/b -- default: a]"
    debug_or_release=`OptionRead`

    if test "$debug_or_release" = "b" -o "$debug_or_release" = "B" ; then 
        lib_build=RELEASE
    else
        lib_build=DEBUG
    fi

    echo ""
    echo "============================================================= "
    echo ""
    
fi

#====================================================================
# Configuration file for extra configuration
#====================================================================

# Check whether FULL CONFIGURATION was requested
if test "$full_configuration" = "TRUE" ; then

    # Default configuration file
    default_config_file="./configs/current"

    # Answer's default value
    your_config_file=""

    echo "Specify the path config file with extra configuration flags:"
    OptionPrompt "[default: ${default_config_file}]"
    your_config_file=`OptionRead`

    if test "$your_config_file" = ""; then 
        configuration_file=${default_config_file}
    else
        configuration_file=${your_config_file}
    fi

    echo ""
    echo "============================================================= "
    echo ""

fi

#====================================================================
# Number of processors to build framework
#====================================================================

# Check whether FULL CONFIGURATION was requested
if test "$full_configuration" = "TRUE" ; then

    echo "How many processor should use to build $lib_name?"
    OptionPrompt "[1] [2] [4] [8] [16] [default: $default_number_of_processors_to_build_library]"
    number_of_processors_to_build_library=`OptionRead`

    if test "$number_of_processors_to_build_library" != 1 -a "$number_of_processors_to_build_library" != 2 -a "$number_of_processors_to_build_library" != 4 -a "$number_of_processors_to_build_library" != 8 -a "$number_of_processors_to_build_library" != 16; then
        number_of_processors_to_build_library=$default_number_of_processors_to_build_library
        echo "Setting the number of processors to build library to [$default_number_of_processors_to_build_library]"
        echo "We do not currently support the number of processors you"
        echo "specified!"
    fi

    echo ""
    echo "============================================================= "
    echo ""
    
fi

#====================================================================
# Build demos
#====================================================================

# Check whether FULL CONFIGURATION was requested
if test "$full_configuration" = "TRUE" ; then

    # Answer's default value
    build_and_run_demos='a'
    
    echo "Do you want to build and run the demos?"
    OptionPrompt "a)DO BUILD/RUN demos b)DO NOT BUILD/RUN demos [a/b -- default: a]"
    build_and_run_demos=`OptionRead`
    
    if test "$build_and_run_demos" = "b" -o "$build_and_run_demos" = "B" ; then 
        build_test_demos=FALSE
    else
        build_test_demos=TRUE
        
        echo "How many processor should use to run tests?"
        OptionPrompt "[1] [2] [4] [8] [16] [default: $default_number_of_processors_to_run_demos]"
        number_of_processors_to_run_demos=`OptionRead`

        if test "$number_of_processors_to_run_demos" != 1 -a "$number_of_processors_to_run_demos" != 2 -a "$number_of_processors_to_run_demos" != 4 -a "$number_of_processors_to_run_demos" != 8 -a "$number_of_processors_to_run_demos" != 16; then
            number_of_processors_to_run_demos=$default_number_of_processors_to_run_demos
            echo "Setting the number of processors to run tests to [$default_number_of_processors_to_run_demos]"
            echo "We do not currently support the number of processors you"
            echo "specified!"
        fi
        
    fi

    echo ""
    echo "============================================================= "
    echo ""

else
    # If no FULL CONFIGURATION was requested then check for number of
    # processors to run demos, if zero is set then do not run demos
    if test $number_of_processors_to_run_demos = 0; then
        build_test_demos=FALSE
    fi

fi

#====================================================================
# Summary for building process to run
#====================================================================

echo ""
echo "============================================================= "
echo "************************************************************* "
echo "============================================================= "
echo "Building the " $lib_type "/" $lib_build" version of the library"
echo "using ["$number_of_processors_to_build_library"] processor(s)"
echo "with configuration file ["$configuration_file"]"
echo ""
echo "BUILD_DEMOS="$build_test_demos
if test "$build_test_demos" = "TRUE" ; then
    echo "Using ["$number_of_processors_to_run_demos"] processor(s) to run tests"
else
    echo "Skipping demos testing"
fi
echo "============================================================= "
echo "************************************************************* "
echo "============================================================= "
echo ""

#====================================================================
# Going to the build directory
#====================================================================
echo "I will use the ./"$build_dir" directory as the temp build folder"
if (test -d  $build_dir); then
    rm -r $build_dir/*
    echo "Cleaning up ..."
    cd $build_dir
    echo "Done"
else
    mkdir $build_dir
    cd $build_dir
fi
echo ""

#====================================================================
# Calling CMake
#====================================================================
echo "============================================================= "
echo "I am going to run CMake ..."
echo "============================================================= "
echo ""
# Go one folder up since we did a cd into ./build
# Run CMake and test for any error
if ! cmake ../ \
     -DCHAPCHOM_LIB_TYPE=$lib_type \
     -DCHAPCHOM_BUILD_VERSION=$lib_build \
     -DCHAPCHOM_BUILD_DEMOS=$build_test_demos \
     -DCHAPCHOM_CONFIGURATION_FILE=$configuration_file \
     -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ; then # Added to create the
                                              # 'compile_commands.json
                                              # file for emacs
                                              # autocompletion in
                                              # irony mode'
    
    echo ""
    echo "============================================================= "
    echo "[ERROR] CMake"
    echo "============================================================= "
    echo ""
    exit 1 # Add this flag for GitHub Actions report
fi

#if test cmake_output != 0 ; then
#    echo ""
#    echo "============================================================= "
#    echo "[ERROR] CMake"
#    echo "============================================================= "
#    echo ""
#    exit 1
#fi

echo ""
echo "============================================================= "
echo "[Done] CMake"
echo "============================================================= "
echo ""
echo "============================================================= "
echo "Make clean"
echo "============================================================= "
echo ""
make clean
echo "============================================================= "
echo "Make"
echo "============================================================= "
echo ""
echo "Make with ["$number_of_processors_to_build_library"] processor(s)"
echo ""
# The -k option allows make to continue compiling even a compilation
# error is found
if ! make -k -j"$number_of_processors_to_build_library" ; then
    echo ""
    echo ""
    echo ""
    echo "============================================================= "
    echo ""
    echo "Do not commit any broken version of the library."
    echo "If any build/test fails try to fix it and report back to the"
    echo "developers."
    echo ""
    echo "============================================================= "
    echo "[FAILED] make -k -j$number_of_processors_to_build_library"
    echo "============================================================= "
    echo ""
    exit 1 # Add this flag for GitHub Actions report
fi

#====================================================================
# Finishing up !!!
#====================================================================

# Go to the root directory
cd ..

echo ""
echo "============================================================= "
echo ""
echo "Finishing library built process ... (cmake and make have"
echo "finished!)"
echo "If you can not spot any error messages above this, the" 
echo $lib_name" library should now be ready to RUN TEST UNITS"
echo ""
echo "============================================================= "
echo ""
echo ""
echo ""

#====================================================================
# Run tests?
#====================================================================

if test "$build_test_demos" = "TRUE" ; then
    echo ""
    echo ""
    echo ""
    echo "============================================================= "
    echo ""
    echo "I am going to run the tests as requested"
    echo "----------------------------------------"
    echo "Using ["$number_of_processors_to_run_demos"] processor(s)"
    echo ""
    echo "============================================================= "
    echo ""
    echo ""
    
    # Go into the build folder to run tests
    cd $build_dir
    
    # Call the make test function instead of ctest (make test enables
    # testing and then calls ctest)
    # Use as many processors as requested to run tests in parallel
    if ! make test ARGS=-j"$number_of_processors_to_run_demos" ; then
        echo ""
        echo ""
        echo ""
        echo "============================================================= "
        echo ""
        echo "Do not commit any broken version of the library."
        echo "If any build/test fails try to fix it and report back to the"
        echo "developers."
        echo ""
        echo "============================================================= "
        echo "[FAILED] make test"
        echo "============================================================= "
        echo ""
        exit 1 # Add this flag for GitHub Actions report
    fi
    
    # Go one directory up
    cd ..
    
    # Once all test have been run, copy the file with the results of
    # the test to the root directoy
    echo ""
    echo "============================================================= "
    echo ""
    echo "Copying validation files ..."
    cp build/Testing/Temporary/LastTest.log ./validation.log
    cp build/Testing/Temporary/CTestCostData.txt ./validation_short.log    
    echo ""
    echo "============================================================= "
    echo ""
    echo "Finishing library test process ... (make test has finished!)"
    echo "If you can't spot any error messages above this, the" 
    echo $lib_name" library should now be ready to use and free of errors" 
    echo ""
    echo "============================================================= "
    echo ""
    echo "Check the validation files for information regarding"
    echo "PASSED/FAILED tests."
    echo ""
    echo "============================================================= "
    echo ""
else
    echo ""
    echo ""
    echo ""
    echo "============================================================= "
    echo ""
    echo "You did not requested for RUN TEST UNITS."
    echo ""
    echo "We highly recommend to RUN TEST UNITS before continue"
    echo "Type 'make test' and hit enter inside the build folder=$build_dir"
    echo "If you want to use more than one processor, then type"
    echo "'make test ARGS=-j#', where # represents the number of"
    echo "processors you want to use to run the tests"
    echo ""
    echo "============================================================= "
    echo ""
fi

#====================================================================
# Generate code coverage report?
#====================================================================

if test "$generate_code_coverage_report" = "TRUE" ; then
    echo ""
    echo ""
    echo ""
    echo "============================================================= "
    echo ""
    echo "I am going to generate the code coverage report as requested"
    echo ""
    echo "============================================================= "
    echo ""
    echo ""
        
    if ! ./tools/run_codecov.sh ; then
        echo ""
        echo ""
        echo ""
        echo "========================================================= "
        echo "[FAIL] './tools/run_codecov.sh'"
        echo "========================================================= "
        echo ""
        exit 1
    fi

fi

echo ""
echo "============================================================= "
echo ""
echo "Do not commit any broken version of the library."
echo "If any build/test fails try to fix it and report back to the"
echo "developers."
echo ""
echo "Your contributions are very welcome!"
echo ""
echo "Please contact the developers if you encountered any"
echo "build/test problem."
echo ""
echo "============================================================= "
echo ""

# If reaching this point then everything should be OK
exit 0

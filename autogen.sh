#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

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
# Variables
#====================================================================
build_dir=build
src_dir=src
external_src_dir=external_src

# The name of the library
lib_name=chapchom
# The extension of the library is given by the choosing of STATIC or
# SHARED library
lib_ext=*
# The type of the library is given by the choosing of STATIC or SHARED
# library
lib_type=*
# The version of the library is given by whether the user choose to
# build the DEBUG or the RELEASE version of the library
lib_version=*
# Indicates whether to build/compile demos
build_demos=TRUE
# Indicates the number of processors to build the demos
number_of_processors_to_run_demos=1
# Indicates the number of processors to build the library
number_of_processors_to_build_library=4
# Indicates the configuration file with variables for paths for
# external libraries
configuration_file=./configs/current

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
echo "I am going to build "$lib_name
echo "I will use the ./"$build_dir" directory as the temp build folder"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# Going to the build directory
#====================================================================
if (test -d  $build_dir); then 
    cd $build_dir
    echo "Cleaning up ..."
    rm -r *
    echo "Done"
else
    mkdir $build_dir
    cd $build_dir
fi
echo ""
echo ""

#====================================================================
# Library type
#====================================================================

echo "Which library type do you want to build?"
OptionPrompt "The a)STATIC or the b)SHARED type library? [a/b -- default: a]"
static_or_shared=`OptionRead`
if test "$static_or_shared" = "b" -o "$static_or_shared" = "B" ; then 
    lib_type=SHARED
    lib_ext=.so
else
    lib_type=STATIC
    lib_ext=.a
fi

echo ""
echo "============================================================= "
echo ""

#====================================================================
# Library version
#====================================================================

echo "Which library version do you want to build?"
OptionPrompt "The a)DEBUG or the b)RELEASE version of the library ? [a/b -- default: a]"
debug_or_release=`OptionRead`
if test "$debug_or_release" = "b" -o "$debug_or_release" = "B" ; then 
    lib_version=RELEASE
else
    lib_version=DEBUG
fi

echo ""
echo "============================================================= "
echo ""

#====================================================================
# Number of processors to build library
#====================================================================
echo "How many processor to use to build $lib_name?"
OptionPrompt "[1] [2] [4] [default: 4]"
number_of_processors_to_build_library=`OptionRead`
if test "$number_of_processors_to_build_library" != 1 -a "$number_of_processors_to_build_library" != 2 -a "$number_of_processors_to_build_library" != 4; then
    number_of_processors_to_build_library=4
    echo "Setting the number of processors to build library to [4]" 
    echo "We do not currently support the number of processors you"
    echo "specified!"
fi

echo ""
echo "============================================================= "
echo ""

#====================================================================
# Configuration file for extra configuration
#====================================================================

echo "Specify the path config file with extra configuration flags:"
OptionPrompt "[default: ./configs/current]"
extra_config_file=`OptionRead`
if test "$extra_config_file" = "" -o "$extra_config_file" = "" ; then 
    configuration_file=./configs/current
else
    configuration_file=${extra_config_file}
fi

echo ""
echo "============================================================= "
echo ""

#====================================================================
# Build demos
#====================================================================

echo "Do you want to build and run the demos?"
OptionPrompt "a)DO BUILD/RUN demos b)DO NOT BUILD/RUN demos [a/b -- default: a]"
build_and_run_demos=`OptionRead`
if test "$build_and_run_demos" = "b" -o "$build_and_run_demos" = "B" ; then 
    build_demos=FALSE
else
    build_demos=TRUE
    echo "How many processor use to run tests?"
    OptionPrompt "[1] [2] [4] [default: 1]"
    number_of_processors_to_run_demos=`OptionRead`
    if test "$number_of_processors_to_run_demos" != 1 -a "$number_of_processors_to_run_demos" != 2 -a "$number_of_processors_to_run_demos" != 4; then
        number_of_processors_to_run_demos=1
        echo "Setting the number of processors to run tests to [1]" 
        echo "We do not currently support the number of processors you"
        echo "specified!"
    fi
fi

echo ""
echo "============================================================= "
echo ""

echo ""
echo "============================================================= "
echo "************************************************************* "
echo "============================================================= "
echo "Building the " $lib_type "/" $lib_version " version of the library"
echo "Using ["$number_of_processors_to_build_library"] processor(s) to build library"
echo "BUILD_DEMOS="$build_demos
if test "$build_demos" = "TRUE" ; then
    echo "Using ["$number_of_processors_to_run_demos"] processor(s) to run tests"
fi
echo "============================================================= "
echo "************************************************************* "
echo "============================================================= "
echo ""

#====================================================================
# Calling CMake
#====================================================================
echo "============================================================= "
echo "I am going to run CMake ..."
echo "============================================================= "
echo ""
# Go one folder up since we did a cd into ./build
cmake ../ \
      -DCHAPCHOM_LIB_TYPE=$lib_type \
      -DCHAPCHOM_BUILD_VERSION=$lib_version \
      -DCHAPCHOM_BUILD_DEMOS=$build_demos \
      -DCHAPCHOM_CONFIGURATION_FILE=$configuration_file \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1 # Added to create the
# 'compile_commands.json file
# for emacs autocompletion in
# irony mode'
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
if test "$number_of_processors_to_build_library" != 1; then
    echo "Make with ["$number_of_processors_to_build_library"] processors"
    echo ""
    # The -k option allows make to continue compiling even a compilation
    # error is found
    make -k -j"$number_of_processors_to_build_library"
else
    # The -k option allows make to continue compiling even a compilation
    # error is found
    make -k
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
echo $lib_name" library should now be ready to use... " 
echo " "
echo "If you want to run the test type 'make test' and hit enter in"
echo "the build folder=$build_dir"
echo "If you want to use more than one processor, then type"
echo "'make test ARGS=-j#', where # represents the number of"
echo "processors you want to use to run the tests"
echo ""
echo "Please contact the developers if you encountered any"
echo "building problem!"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# Run tests
#====================================================================

if test "$build_demos" = "TRUE" ; then
    echo ""
    echo ""
    echo ""
    echo "============================================================= "
    echo ""
    echo "I am going to run the tests as you requested."
    echo "Using ["$number_of_processors_to_run_demos"] processor(s)"
    echo ""
    echo "============================================================= "
    echo ""
    echo ""
    # Go into the build folder to run tests
    cd $build_dir
    # Call the make test function instead of ctest (make test enables
    # testing and then calls ctest)
    # Use four processors to run tests in parallel
    make test ARGS=-j"$number_of_processors_to_run_demos"
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
    echo ""
    echo "============================================================= "
    echo ""
    echo "Check the validation files for information regarding"
    echo "PASSED/FAILED tests."
    echo ""
    echo "============================================================= "    
    echo "If you can't spot any error messages above this, the" 
    echo $lib_name" library should now be ready to use and free of errors" 
    echo " "
    echo "Do not commit any broken version of the library. If any test "
    echo "fails and you know what the problem is about then try to fix "
    echo "it and report back to the developers."
    echo ""
    echo "Your contributions are very welcome!"
    echo ""
    echo "Please contact the developers if you encountered any"
    echo "test/building problem."
    echo ""
    echo "============================================================= "
    echo ""
fi

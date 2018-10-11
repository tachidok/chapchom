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
# Indicates the configuration file with variables for paths for
# external libraries
configuration_file=./configs/default

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
# Configuration file for extra configuration
#====================================================================

echo "Specify the path config file with extra configuration flags:"
OptionPrompt "[default: ./configs/default]"
extra_config_file=`OptionRead`
if test "$extra_config_file" = "" -o "$extra_config_file" = "" ; then 
    configuration_file=./configs/default
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
fi

echo ""
echo "============================================================= "
echo "Building the " $lib_type "/" $lib_version " version of the library "
echo "with BUILD_DEMOS="$build_demos
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
make -k

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
echo "If you can't spot any error messages above this, the" 
echo $lib_name" library should now be ready to use... " 
echo " "
echo "If you want to run the test type 'make test' and hit enter in"
echo "the build folder=$build_dir"
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
    echo ""
    echo "============================================================= "
    echo ""
    echo ""
    cd $build_dir
    make test
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

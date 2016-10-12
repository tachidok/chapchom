#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# A little function 'borrowed' from the oomph-lib installation
# script...
OptionPrompt() 
{ 
 printf "%s " "$1" 
}

# Another little function 'borrowed' from the oomph-lib installation
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
      -DCHAPCHOM_BUILD_DEMOS=$build_demos
make clean
make

echo ""
echo "============================================================= "
echo "[Done] CMake"
echo "============================================================= "

#====================================================================
# Finishing up !!!
#====================================================================

cd ..

echo ""
echo "============================================================= "
echo ""
echo "Finishing library built process ... (autogen.sh has finished!)"
echo "If you can't spot any error messages above this, the" 
echo $lib_name " library should now be ready to use... " 
echo " "
echo "Please contact the developers if you encountered any"
echo "building problem!"
echo ""
echo "============================================================= "
echo ""

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
tmp_dir=tmp_chapchom
src_dir=src
external_src_dir=external_src

# The name of the library
lib_name=chapchom
# The version of the library is given by whether the user choose to
# build the DEBUG or the RELEASE version of the library
lib_version=*

#====================================================================
# The building script
#====================================================================

echo " "
echo "============================================================= "
echo "        "$lib_name" make clean distro script" 
echo "============================================================= "
echo " "

echo ""
echo "============================================================= "
echo ""
echo "I am going to create a clean distro and package it"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# Go one directory up
#====================================================================
cd ..

#====================================================================
# Make a temporal directory
#====================================================================
if (test -d  $tmp_dir); then 
    cd $tmp_dir
    echo "Cleaning up ..."
    rm -r *
    echo "Done"
else
    mkdir $tmp_dir
    cd $tmp_dir
fi
echo ""
echo ""

echo ""
echo "============================================================= "
echo ""

#====================================================================
# Making copy
#====================================================================
echo "============================================================= "
echo "Copying the library into" $tmp_dir" folder ..."
echo "============================================================= "
cp -r ../$lib_name ./chapchom_copy
echo ""
echo "[COPY DONE]"
echo ""

#====================================================================
# Deleting .git folder
#====================================================================
echo "============================================================= "
echo "I am going to delete .git folder"
echo "============================================================= "
echo ""
rm -rf ./chapchom_copy/.git
echo ""
echo "[DELETE GIT FOLDER DONE]"
echo ""

#====================================================================
# Deleting build folder
#====================================================================
echo "============================================================= "
echo "I am going to delete" $build_dir " folder"
echo "============================================================= "
echo ""
rm -rf ./chapchom_copy/$build_dir
echo ""
echo "[DELETE GIT FOLDER DONE]"
echo ""

#====================================================================
# Deleting dat png in folders
#====================================================================
echo "============================================================= "
echo "I am going to delete dat and png files, ignoring those in"
echo "demos and private folders"
echo "============================================================= "
echo ""
./chapchom_copy/tools/clean_distro.py --root_folder ./chapchom_copy/ --ext dat png --ignore_in_path demos
echo ""
echo "[DELETE DAT AND PNG FILES DONE]"
echo ""

#====================================================================
# Create the package of the new distribution
#====================================================================
echo "============================================================= "
echo "I am going to create a package with the new clean"
echo "distribution"
echo "============================================================= "
echo ""
tar cvfz chapchom_copy.tar.gz ./chapchom_copy/
echo ""
echo "[PACKAGE DONE]"
echo ""

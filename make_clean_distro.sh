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
# The name of the library
lib_name=chapchom

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
# Remove previous distros packages
#====================================================================
rm -i $lib_name.tar.gz

#====================================================================
# Get working folder
#====================================================================
working_folder=$(pwd)

#====================================================================
# Make a temporal directory
#====================================================================
tmp_dir=$(mktemp -d -t tachidok-XXXXXXXXXX)
echo ""
echo $tmp_dir
echo ""

#====================================================================
# Making a copy
#====================================================================
echo "============================================================= "
echo "Copying the library into" $tmp_dir" folder ..."
echo "============================================================= "
cp -r $working_folder $tmp_dir
echo ""
echo "[COPY DONE]"
echo ""

#====================================================================
# Deleting .git folder
#====================================================================
echo "============================================================= "
echo "I am going to delete .git folder"
echo "============================================================= "
rm -rf $tmp_dir/$lib_name/.git
echo ""
echo "[DELETE GIT FOLDER DONE]"
echo ""

#====================================================================
# Deleting build folder
#====================================================================
echo "============================================================= "
echo "I am going to delete" $build_dir "folder"
echo "============================================================= "
rm -rf $tmp_dir/$lib_name/$build_dir
echo ""
echo "[DELETE BUILD FOLDER DONE]"
echo ""

#====================================================================
# Deleting dat png in folders
#====================================================================
echo "============================================================= "
echo "I am going to delete [dat,png] files, ignoring those in"
echo "[demos] folders"
echo "============================================================= "
echo ""
$tmp_dir/$lib_name/tools/clean_distro.py --root_folder $tmp_dir/$lib_name --ext dat png --ignore_in_path demos
echo ""
echo "[DELETE DAT AND PNG FILES DONE]"
echo ""

#====================================================================
# Create the package of the new distribution
#====================================================================
echo "============================================================= "
echo "I am going to create a package with the new clean"
echo "distribution and delete temporal folder"
echo "============================================================= "
echo ""
tar cvfz $lib_name.tar.gz $tmp_dir/$lib_name
rm -rf $tmp_dir
echo ""
echo "[PACKAGE/DELETE TMP FOLDER DONE]"
echo ""

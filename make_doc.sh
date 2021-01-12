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
doc_doxy_dir=doxy_doc
# The name of the library
lib_name=SciCell++

#====================================================================
# The building script
#====================================================================

echo " "
echo "============================================================= "
echo "        "$lib_name" make doc script" 
echo "============================================================= "
echo " "

echo ""
echo "============================================================= "
echo ""
echo "I am going to create the documentation"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# Check whether the doc folder exists
#====================================================================
if (test -d  $doc_doxy_dir); then
    echo "Cleaning up ..."
    rm -r $doc_doxy_dir/*
    echo "Done"
else
    mkdir $doc_doxy_dir
fi
echo ""

#====================================================================
# Calling doxygen
#====================================================================
echo "============================================================= "
echo "I am going to run doxygen ..."
echo "============================================================= "
echo ""
# Go one folder up since we did a cd into ./build
doxygen ./tools/doxyfile.config 

echo ""
echo "============================================================= "
echo "[Done] doxygen"
echo "============================================================= "
echo ""
echo "The documentation is in the $doc_doxy_dir folder"

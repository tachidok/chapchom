#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# A little function 'borrowed' from the oomph-lib installation script...
OptionPrompt() 
{ 
 printf "%s " "$1" 
}

# Another little function 'borrowed' from the oomph-lib installation script...
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
bin_dir=bin
example=basic_direct_solver

#====================================================================
# The building script
#====================================================================

echo ""
echo "============================================================= "
echo ""
echo "Example: ("$example")"
echo ""
echo ""
echo "I will use the '"$build_dir"' directory as the temp build folder"
echo "The complete built example will be stored in the '"$bin_dir"' folder"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# Checking if bin_dir exists
#====================================================================
if (test -d $bin_dir); then 
	continue
else
	mkdir $bin_dir
fi

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

echo "Building the '"$example"' example ..."
cmake ../ -Dexample_name=$example
make clean
make
cp $example ../$bin_dir
echo "Done"

#====================================================================
# Finishing up !!!
#====================================================================s

cd ..

echo ""
echo "============================================================= "
echo ""
echo "Example '"$example"' built and ready to use"
echo "You can run it by typing '"./$example"' at the '"$bin_dir"' directory"
echo ""
echo "============================================================= "
echo ""

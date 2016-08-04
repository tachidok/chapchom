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
example_velocity=dead_reckoning_from_velocities
example_acceleration=dead_reckoning_from_accelerations
example_acceleration2=dead_reckoning_from_accelerations2
example_xsensMT9B=dead_reckoning_for_xsensMT9B

example_velocity=dead_reckoning_for_xsensMT9B

#====================================================================
# The building script
#====================================================================

echo ""
echo "============================================================= "
echo ""
echo "Example: ("$example_velocity")"
echo "Example: ("$example_acceleration")"
echo "Example: ("$example_acceleration2")"
echo "Example: ("$example_xsensMT9B")"
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

echo "Building the '"$example_velocity"' example ..."
cmake ../ -Dexample_name=$example_velocity
make clean
make
cp $example_velocity ../$bin_dir
echo "Done"

#====================================================================
# Finishing up !!!
#====================================================================s

cd ..

echo ""
echo "============================================================= "
echo ""
echo "Example '"$example_velocity"' built and ready to use"
echo "You can run it by typing '"./$example_velocity"' at the '"$bin_dir"' directory"
echo ""
echo "============================================================= "
echo ""

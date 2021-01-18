#! /bin/sh

#====================================================================
# Variables
#====================================================================
# Folder to scan for coverage info
working_folder=$(pwd)
# File for coverage information
lcov_output_file=coverage.info
# Output folder for full report
lcov_output_folder=lcov_output_folder
# The name of the library
lib_name=SciCell++

#====================================================================
# The building script
#====================================================================

echo ""
echo "============================================================= "
echo "        $lib_name code coverage script" 
echo "============================================================= "
echo ""

#====================================================================
# Run the lcov tool in the current directory ./ and output in the
# specified file
#====================================================================
echo ""
echo "============================================================= "
echo "I am going to run the coverage tools (lcov)"
echo "============================================================= "
echo ""
lcov --capture --directory $working_folder --output-file $lcov_output_file
lcov --remove $lcov_output_file '/usr/*' --output-file $lcov_output_file
lcov --list $lcov_output_file

#====================================================================
# Update the report to CodeCov.io
#====================================================================
echo ""
echo "============================================================= "
echo "I am going to update the report to CodeCov.io"
echo "============================================================= "
echo ""
bash <(curl -s https://codecov.io/bash) -f $lcov_output_file || echo "Codecov did not collect coverage reports"

#====================================================================
# Generate report using the 
#====================================================================
#genhtml $lcov_output_file --output-directory $lcov_output_folder

echo ""
echo "[DONE] Coverage report script"
echo ""

# Done
exit 1

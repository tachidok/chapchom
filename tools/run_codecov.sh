#! /bin/sh

#====================================================================
# Variables
#====================================================================
# Folder to scan for coverage info
working_folder=$(pwd)
build_dir=build
# File for coverage information
lcov_output_file=coverage.info
# Folder to store code report
code_report_dir=code_report
# Folder to store html report output
code_report_html_dir=html

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
echo "Running coverage tools (lcov --capture) ... "
echo "============================================================= "
echo ""
if ! lcov --capture --directory $working_folder/$build_dir --output-file $lcov_output_file ; then
    echo ""
    echo ""
    echo ""
    echo "========================================================= "
    echo "[FAIL] lcov --capture"
    echo "========================================================= "
    echo ""
    exit 1
fi

#====================================================================
# Remove kernel information from report and output in the specified
# file
# ===================================================================
echo ""
echo "============================================================= "
echo "Removing kernel information (lcov --remove)"
echo "============================================================= "
echo ""
if ! lcov --remove $lcov_output_file '/usr/*' --output-file $lcov_output_file ; then
    echo ""
    echo ""
    echo ""
    echo "========================================================= "
    echo "[FAIL] lcov --remove"
    echo "========================================================= "
    echo ""
    exit 1
fi

#====================================================================
# Listitng file on stdout
# ===================================================================
echo ""
echo "============================================================= "
echo "Listing file on stdout (lcov --list)"
echo "============================================================= "
echo ""
if ! lcov --list $lcov_output_file; then
    echo ""
    echo ""
    echo ""
    echo "========================================================= "
    echo "[FAIL] lcov --list"
    echo "========================================================= "
    echo ""
    exit 1
fi

#====================================================================
# Move report to $code_report_dir
# ===================================================================
echo ""
echo "Moving report to '$code_report_dir'"
echo ""
#====================================================================
# Check whether the code_report folder exist
#====================================================================
if (test -d  $code_report_dir); then
    rm -r $code_report_dir/*
else
    mkdir $code_report_dir
fi

if ! mv $lcov_output_file ./$code_report_dir; then
    echo ""
    echo ""
    echo ""
    echo "========================================================= "
    echo "[FAIL] 'mv $lcov_output_file ./$code_report_dir'"
    echo "========================================================= "
    echo ""
    exit 1
fi

#====================================================================
# Generate report using the 
#====================================================================
echo ""
echo "Generate HTML code report in './$code_report_dir/$code_report_html_dir'"
echo ""
if ! genhtml ./$code_report_dir/$lcov_output_file --output-directory ./$code_report_dir/$code_report_html_dir ; then
    echo ""
    echo ""
    echo ""
    echo "========================================================= "
    echo "[FAIL] 'genhtml ./$code_report_dir/$lcov_output_file --output-directory ./$code_report_dir/$code_report_html_dir'"
    echo "========================================================= "
    echo ""
    exit 1
fi

#====================================================================
# Update the report to CodeCov.io
#====================================================================
#echo ""
#echo "============================================================= "
#echo "I am going to update the report to CodeCov.io"
#echo "============================================================= "
#echo ""
#bash <(curl -s https://codecov.io/bash) -f $lcov_output_file || echo "Codecov did not collect coverage reports"

echo ""
echo "[DONE] Coverage report script"
echo ""

# Done
exit 0

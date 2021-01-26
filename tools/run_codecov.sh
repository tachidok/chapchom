#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# Usage function
usage()
{
cat << EOF
usage: $0 [OPTIONS]

This script runs the code coverage tools and updates the report to CodeCov.io

OPTIONS:
   -h      Show this message
   -w      Generates the web version of the code coverage report
   -u      Updates the code coverage report to CodeCov.io
   -v      Verbose
EOF
}

#====================================================================
# Variables (and default values)
#====================================================================
# Folder to scan for coverage info
working_folder=$(pwd)
build_dir=build
# File for coverage information
lcov_output_file=coverage.info
# Folder to store code report
code_report_dir=code_report

# Generate web version of code coverage report
web_version_of_code_report=FALSE
# Folder to store html report output
code_report_html_dir=html

# Update code report to CodeCov.io
update_report_to_codecovio=FALSE
# Name for the CodeCov.io script
code_cov_script_filename=codecov.sh

# The name of the library
lib_name=SciCell++

#====================================================================
# Parse arguments
# ====================================================================
# Scans for input arguments. None of the current arguments requires
# additional options, therefore no ':' symbol is used. If you need an
# example when using the ":" symbol check the 'autogen.sh' file in the
# root directory
while getopts “hwuv” OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         w)
             web_version_of_code_report=TRUE
             ;;
         u)
             update_report_to_codecovio=TRUE
             ;;
         v)
             verbose=TRUE
             ;;
         ?)
             echo ""
             echo "============================================================= "
             echo ""
             echo "ERROR: No recognized parameter"
             echo ""
             echo "============================================================= "
             echo ""
             usage
             exit 1
             ;;
     esac
done

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
# Generate web version of the code report
#====================================================================
if test "$web_version_of_code_report" = "TRUE" ; then
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
    
    echo ""
    echo "[DONE] Generate web version of code report"
    echo ""
    
fi

#====================================================================
# Update the report to CodeCov.io
#====================================================================
if test "$update_report_to_codecovio" = "TRUE" ; then
    echo ""
    echo "============================================================= "
    echo ""
    echo "Coverage report will not be updated, only master branch code"
    echo "coverage report will be updated"
    echo ""
    echo "============================================================= "
    echo ""
fi

# Overwrite option so report is not updated even if was requested
update_report_to_codecovio=FALSE

if test "$update_report_to_codecovio" = "TRUE" ; then
    echo ""
    echo "============================================================= "
    echo "I am going to update the report to CodeCov.io"
    echo "============================================================= "
    echo ""
    echo "Downloading the CodeCov.io script"
    echo ""
    curl -o $code_cov_script_filename https://codecov.io/bash
    export CODECOV_TOKEN=a4a203a3-9183-47ca-b122-9e09b0a5dd45
    echo ""
    echo "Running the CodeCov.io script $code_cov_script_filename"
    echo ""
    #    if ! bash <(curl -s https://codecov.io/bash) -f ./$code_report_dir/$lcov_output_file ; then
    if ! bash ./$code_cov_script_filename ; then
        echo ""
        echo ""
        echo ""
        echo "========================================================= "
        echo "[FAIL] 'sh ./$code_cov_script_filename'"
        echo "========================================================= "
        echo ""
        exit 1
    fi
    
    echo ""
    echo "[DONE] Update report to CodeCov.io"
    echo ""
    echo "Cleaning up"
    rm $code_cov_script_filename
    rm *.gcov
    
fi

echo ""
echo "[DONE] Coverage report script"
echo ""

# Done
exit 0

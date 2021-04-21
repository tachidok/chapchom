#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# Usage function
usage()
{
cat << EOF
usage: $0 [OPTIONS]

This script runs SciCell++ inside a Docker container

OPTIONS:
   -h      Show this message
   -v      Verbose
EOF
}

#====================================================================
# Variables (and default values)
#====================================================================
# Verbose option
verbose=TRUE

#====================================================================
# Variables (and default values)
#====================================================================
dockerhub_image_tag=0.1
dockerhub_image_name=scicellxx/scicellxx-base-all
dockerhub_image=$dockerhub_image_name:$dockerhub_image_tag

project_name=scicellxx
container_name=$project_name

# For volume mounting
#~/local/working/research/tmp/scicellxx/
folder_in_local_machine=`pwd`/$project_name
folder_in_container=/home/scicellxx
working_folder_in_container=/home/scicellxx/

# Command to run in container (default)
run_this_command=''
#run_this_command='./autogen.sh -t STATIC -b DEBUG -n 4 -c ./configs/container -d 4 -v'
#run_this_command='./autogen.sh -t STATIC -b RELEASE -n 4 -c ./configs/container -d 4 -v'
#run_this_command='./autogen.sh -t STATIC -b RELEASE -n 16 -c ./configs/container -d 16 -v'

#====================================================================
# Parse arguments
# ====================================================================
while getopts “hv” OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         v)
             verbose=TRUE
             ;;
         ?)
             echo ""
             echo "============================================================= "
             echo ""
             echo "[ERROR] No recognized parameter"
             echo ""
             echo "============================================================= "
             echo ""
             usage
             exit 1
             ;;
     esac
done

#####################################################################
                   ## RUN THE DOCKER IMAGE ##
#####################################################################

if ! docker run --name=$container_name \
     -v $folder_in_local_machine:$folder_in_container \
     -w $working_folder_in_container \
     -it \
     $dockerhub_image ; then
    echo ""
    echo "[ERROR] - Executing the docker image"
    echo ""
    exit 1
fi

echo ""
echo "============================================================= "
echo ""
echo "[DONE] - Finishing SciCell++ in docker container"
echo ""
echo "============================================================= "
echo ""

# Success
exit 0

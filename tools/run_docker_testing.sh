#! /bin/sh

#====================================================================
# A few helper functions
#====================================================================

# Usage function
usage()
{
cat << EOF
usage: $0 [OPTIONS]

This script gets a copy of SciCell++ from GitHub, then builds and runs the test using a container from the SciCell++ DockerHub repository

OPTIONS:
   -h      Show this message
   -g      Get a recent copy of SciCell++ from GitHub
   -d      Get a recent copy of the official SciCell++ container from DockerHub
   -G      Folder name on GitHub Actions [override -g option]
   -v      Verbose
EOF
}

#====================================================================
# Variables (and default values)
#====================================================================
# Get project from GitHub
get_project_from_github=FALSE
# Get a container copy from DockerHub
get_container_from_dockerhub=FALSE
# Running on GitHub server
run_on_GitHub_server=FALSE
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

# Command to run in container
run_this_command='./autogen.sh -t STATIC -b DEBUG -n 4 -c ./configs/container -d 4 -v'
#run_this_command='./autogen.sh -t STATIC -b RELEASE -n 4 -c ./configs/container -d 4 -v'
#run_this_command='./autogen.sh -t STATIC -b RELEASE -n 16 -c ./configs/container -d 16 -v'

#====================================================================
# Parse arguments
# ====================================================================
while getopts “hgdG:v” OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         g)
             get_project_from_github=TRUE
             ;;
         d)
             get_container_from_dockerhub=TRUE
             ;;
         G)
             folder_in_local_machine=$OPTARG
             run_on_GitHub_server=TRUE
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

#====================================================================
# Get the project from GitHub
#====================================================================
echo ""
echo "============================================================= "
echo ""
echo "I am going to get a copy of SciCell++ from the official"
echo "GitHub repository"
echo ""
echo "============================================================= "
echo ""
# Check whether github clone was requested
if test "$run_on_GitHub_server" = "FALSE" ; then
    # Running on local machine
    if test "$get_project_from_github" = "TRUE" ; then
        # Check whether the directory already exists, if that is true then
        # exit with an error
        if (test -d  $project_name); then
            echo ""
            echo "[ERROR] - There is already a folder with the same name of the project"
            echo ""
            exit 1
        else
            if ! git clone https://github.com/tachidok/$project_name ; then
                echo ""
                echo "[ERROR] - Getting a copy of SciCell++ from GitHub"
                echo ""
                exit 1
            fi
        fi
    else
        echo ""
        echo "[DONE] - Skipping getting a copy of SciCell++ from GitHub"
        echo ""
    fi
    
    echo ""
    echo "============================================================= "
    echo ""
    echo "[DONE] - Get a copy of SciCell++ from GitHub "
    echo ""
    echo "============================================================= "
    echo ""
    
    # Check that there is already a directory with the project name,
    # otherwise exit with an error
    if ! (test -d  $project_name); then
        echo ""
        echo "[ERROR] - There is no folder with the project name"
        echo ""
        exit 1
    fi
    
else

    echo ""
    echo "============================================================= "
    echo ""
    echo "[DONE] - Running on GitHub server"
    echo ""
    echo "============================================================= "
    echo ""
    
fi

#====================================================================
# Get the docker images from DockerHub
#====================================================================
echo ""
echo "============================================================= "
echo ""
echo "I am going to get a container from the official SciCell++"
echo "DockerHub repository"
echo ""
echo "Container name: $dockerhub_image_name"
echo "Container tag: $dockerhub_image_tag"
echo "Full container name: $dockerhub_image"
echo ""
echo "============================================================= "
echo ""
# Check whether pull container from DockerHub was requested
if test "$get_container_from_dockerhub" = "TRUE" ; then
    if ! docker pull $dockerhub_image ; then
        echo ""
        echo "[ERROR] - Getting SciCell++ container from DockerHub"
        echo ""
        exit 1
    fi
else
    echo ""
    echo "[DONE] - Skipping getting the official SciCell++ container"
    echo "         from DockerHub"
    echo ""
fi

echo ""
echo "============================================================= "
echo ""
echo "[DONE] - Get a container from the official SciCell++"
echo "         DockerHub repository"
echo ""
echo "============================================================= "
echo ""

#====================================================================
# launch the container, start the compilation and testing process
#====================================================================
echo ""
echo "============================================================= "
echo ""
echo "I am going to run the container and execute the building and"
echo "testing processes"
echo ""
echo "============================================================= "
echo ""
if ! docker run --name=$container_name \
     -v $folder_in_local_machine:$folder_in_container \
     -w $working_folder_in_container \
     $dockerhub_image \
     $run_this_command ; then
    echo ""
    echo "[ERROR] - Executing the container image"
    echo ""
    exit 1
fi

echo ""
echo "============================================================= "
echo ""
echo "[DONE] - Execute building and testing processes in container"
echo ""
echo "============================================================= "
echo ""

# Success
exit 0

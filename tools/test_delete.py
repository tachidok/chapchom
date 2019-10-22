#!/usr/bin/env python

import os
import sys
import shutil

# Similar to cd (folder) or cd ..
#os.chdir('./')
# Copies the entire structure of the origen folder into destination
# folder
#shutil.copytree('./', './copy')
#shutil.move('source_folder', 'destination_folder')
# -------------------------------------------------------------------
# CAREFUL
# -------------------------------------------------------------------
# Deletes permanently the file at the indicated path
#os.unlink('path')
# Deletes permanently the folder at the indicated path, the folder
# must be empty
#os.rmdir('path')
# Deletes permanently the folder at the path indicated in parenthesis
#shutil.rmtree('path')

#def list_dat_files():
#    for filename in os.listdir():
#        if filename.endswith('.dat'):
#            print(f"File ending with .dat : {filename}")

def list_all_type_files(root_folder, type_file):
    sum_type_files = 0
    for folderName, subfolders, filenames in os.walk(root_folder):
        # List all files of type file
        for filename in filenames:
            if filename.endswith(type_file):
                print(f"File ending with {type_file} : {filename}")
                sum_type_files = sum_type_files + 1
        
        for subfolder in subfolders:
            #if subfolder.startswith('RESLT'):
            print(f"Entering {subfolder} ...")
            # Create full path
            leaf_folder = os.path.join(root_folder, subfolder)
            #print(f"Leaf folder {leaf_folder} from {root_folder}")
            #list_dat_files()
            #os.chdir(leaf_folder)
            sum_type_files = sum_type_files + list_all_type_files(leaf_folder, type_file)
            #os.chdir('../')
            
    return sum_type_files

'''
    For the given path, get the List of all files in the directory tree 
'''
def getListOfFiles(dirName):
    # create a list of file and sub directories 
    # names in the given directory 
    listOfFile = os.listdir(dirName)
    allFiles = list()
    # Iterate over all the entries
    for entry in listOfFile:
        # Create full path
        fullPath = os.path.join(dirName, entry)
        # If entry is a directory then get the list of files in this directory 
        if os.path.isdir(fullPath):
            allFiles = allFiles + getListOfFiles(fullPath)
        else:
            allFiles.append(fullPath)
                
    return allFiles        
 
 
def here(dirName):
    
    # Get the list of all files in directory tree at given path
    listOfFiles = getListOfFiles(dirName)
    
    # Print the files
    for elem in listOfFiles:
        print(elem)
 
    print ("****************")
    
    # Get the list of all files in directory tree at given path
    listOfFiles = list()
    for (dirpath, dirnames, filenames) in os.walk(dirName):
        listOfFiles += [os.path.join(dirpath, file) for file in filenames]
        
        
    # Print the files    
    for elem in listOfFiles:
        print(elem)

def scan_for_files_of_a_type(root_folder="./", type_file=".dat", list_ignore_has_in_filename=[]):
    # A counter for the number of files to be deleted
    sum_type_files = 0

    # A list with the full names of the files found
    list_of_files_found = list()

    # Get the list of all files in directory tree at given path
    list_of_files = list()
    for (dir_path, dir_names, file_names) in os.walk(root_folder):
        list_of_files += [os.path.join(dir_path, file) for file in file_names]
    
    for entry in list_of_files:
        # Flag to check whether to ignore or not the file
        ignore_file = False
        for item in list_ignore_has_in_filename:
            if entry.find(item) >= 0:
                ignore_file = True
                break
        
        if (not ignore_file) and entry.endswith(type_file):
            #print(f"File ending with {type_file} : {entry}")
            list_of_files_found.append(entry)
            sum_type_files = sum_type_files + 1
                
    return sum_type_files, list_of_files_found

    # Prints the list of files in the current folder
#    for filename in os.listdir():
#        print(filename)
        
#        if filename.startswith('RESLT'):
#            print("Entering RESLT* folder")
#            os.chdir(filename)
#            list_dat_file()
#            os.chdir('../')


'''
Usage:
  ./test_delete root_folder extension list of strings in filename to ignore
'''

if __name__ == '__main__':
    
    root_folder = sys.argv[1]
    type_file = sys.argv[2]

    # Get the list of strings in filenames to ignore
    n_args = len(sys.argv)
    list_ignore_has_in_filename = list()
    for i in range(3, n_args):
        list_ignore_has_in_filename.append(sys.argv[i])
    
    #here(root_folder)
    
    #print(f"Search for {type_file} files in {root_folder} directory and all subdirectories")
    #n_dat_files = list_all_type_files(root_folder, type_file)
    #print(f"Number of {type_file} files: {n_dat_files}")

    files_found = list()
    print(f"Search for '{type_file}' files in '{root_folder}' directory and all subdirectories ...\n")

    for item in list_ignore_has_in_filename:
        print(f"Ignoring filenames with: {item}")
    
    print(f"Scanning ...")
    
    n_type_files, files_found = scan_for_files_of_a_type(root_folder, type_file, list_ignore_has_in_filename)
    #n_type_files, files_found = scan_for_files_of_a_type()

    if n_type_files > 0:
        print(f"List of files '{type_file}':")
        for item in files_found:
            print(item)

        print(f"\nNumber of {type_file} files: {n_type_files}\n")
        user_input = input("Really delete? [y/n]: ")
        if user_input.lower() == 'y':
            for item in files_found:
                print(f"Deleting {item}")
                os.unlink(item)
        else:
            print("No files deleted\n")
    else:
        print(f"No '{type_file}' files found")

    print("[Done]\n")


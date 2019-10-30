#!/usr/bin/env python

import os
import sys
import shutil
import argparse

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

def main():
    if len(sys.argv) < 2:
        print("Usage: clean_distro.py [root_folder] [extension] [list_of_strings_to_ignore_in_filename]")
        sys.exit()

    # Create the parser to deal with the arguments
    parser = argparse.ArgumentParser("Creates a clean distribution to move into antoher machine")

    # Add gropus of expected arguments
    group.add_argument()
    
    # Add mutually exclusive group of arguments
    group = parser.add_mutually_exclusive_group('--root_folder', dest='root_folder', required=True)
    group = parser.add_mutually_exclusive_group('--type_file', dest='type_file', required=True)
    group = parser.add_mutually_exclusive_group('--ignore_filename', nargs='*', dest='list_ignore_has_in_file', required=False)
    
    # parse args
    args = parser.parse_args()
    
    #root_folder = sys.argv[1]
    #type_file = sys.argv[2]
    
    # Get the list of strings in filenames to ignore
    #n_args = len(sys.argv)
    #list_ignore_has_in_filename = list()
    #for i in range(3, n_args):
    #    list_ignore_has_in_filename.append(sys.argv[i])
    
    #files_found = list()
    #print(f"Search for '{type_file}' files in '{root_folder}' directory and all subdirectories ...\n")
    print(f"Search for '{args.type_file}' files in '{args.root_folder}' directory and all subdirectories ...\n")
    
    #for item in list_ignore_has_in_filename:
    for item in args.list_ignore_has_in_filename:
        print(f"Ignoring filenames with: {item}")
    
    print(f"Scanning ...")
    
    #n_type_files, files_found = scan_for_files_of_a_type(root_folder, type_file, list_ignore_has_in_filename)
    n_type_files, files_found = scan_for_files_of_a_type(args.root_folder, args.type_file, args.list_ignore_has_in_filename)
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

'''
Usage:
  ./clean_distro.py root_folder extension_type list of strings in filename to ignore
'''
if __name__ == '__main__':
    # Run the main function
    main()
    


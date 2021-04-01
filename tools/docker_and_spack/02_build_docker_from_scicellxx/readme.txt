* Dockerfile

** Use this file to create a "clean version" of the FULL scicellxx
   container version. The "clean version" means to take an
   ubuntu:18.04 fresh version, install additional packages such as:
   nano, less and build-essential; and copy the installed packages
   from the FULL scicellxx version (without spack).

** The size of this new version is significantly reduced from the FULL
   scicellxx container version.

** Use this version for development purposes.

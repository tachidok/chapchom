# Chapchom

![Travis(.org)](https://img.shields.io/travis/tachidok/chapchom?label=master)
![Travis (.org)branch](https://img.shields.io/travis/tachidok/chapchom/julio?label=julio)

[![BuildStatus](https://travis-ci.org/tachidok/chapchom.svg?branch=julio)](https://travis-ci.org/tachidok/chapchom)

# Welcome!
Hi there, this is the official git repository for the **chapchom**
library.

## What the project is about?
We intent to develop a **Object-Oriented-Parallel numerical library**
with aims to solve PDE's by Mesh Free Methods and the Finite Element
Method. We are interested in particle methods.

## How to get your own copy of the project?

### What you need to have to work and run it nicely?
* A C++ compiler - demo drivers and library built with version
  7.4.0. It may work with previous versions as well.
  
* MPI support for future parallel features (not currently supported)

* CMake - to configure and install it. We have version 3.10.2 and it
  works all fine.

* Python - use it to test output from demo drivers with validation
  files and to produce nice plots. We use version 3.7.3 but it
  probably works with any version >= 3

* Latex - to build documentation (see notes in the doc folder for
  installation instructions of Latex). Most documentation is built
  with org mode.

* Doxygen - to build classes diagrams and useful documentation from
  the code (not currently supported)

### Recommended but not compulsory external libraries
If you want to get the maximum performance of the library you will
need to install the following external packages. However, if you are
in a rush and do not have the time to install them then do not worry,
the library runs still nicely without them.

* OpenBLAS
* SuperLU (requires OpenBLAS)
* Armadillo (requires SuperLU)
* VTK (for visuallisation purposes, we use it in combination with
  Paraview)

### How to configure it?
* Open a terminal (shell command line) and do the following

```shell
git clone https://github.com/tachidok/chapchom
cd chapchom
./autogen.sh
```

That should be it. Follow the instructions on screen from the
_autogen.sh_ script to configure your copy of the library.

### Examples and test cases

Demos, examples or test cases can be found in the "demos" directory
under the root folder. These demos are also used to self test the
implementation. You should run all of them to make sure nothing is
broken.

A large number of examples is expected to live in the "demos"
directory so you can check there for any feature available in the
library.

#### Current demos for specific functionalities
* Interpolation
* Linear solvers
* Matrices operations
* Newton's method
* Solution of ODE's
  * Lotka-Volterra solved with different time steppers
  * 3-body problem
  * N-body problem
  * Explicit time steppers
  * Implicit time steppers (full implicit and E(PC)^k E
    implementations)
  * Adaptive time steppers

## License

Mmm ... that is something we need to carefully think about.

## How to contribute

Once we have something intereseting to share with you we will  make the
project public. Please check continuously for updates or contact the
developers :construction: :envelope: (jcp.sansalvador.at.inaoep.mx) :envelope: :construction:

### Notes for contributors
Please check the documentation (in construction :construction: ) for anything you need to
set-up your account, get a copy of the latest development and start
submitting your contributions ....

### Facts and curiosities

### How many developers are currently working on the library

At Mondat, 09 September 2019 there is one and only one developer, me :no_mouth:

:construction: :construction: :construction: :construction: :construction:

### When did this start?
This project was initially uploaded to GitHub on Friday, 11 March 2016
:smile:

## Here is a list (in wikipedia) of other software packages that implement the FEM

https://en.wikipedia.org/wiki/List_of_finite_element_software_packages

## Have fun and enjoy .... !!!


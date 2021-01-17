
[![codecov](https://codecov.io/gh/tachidok/scicellxx/branch/master/graph/badge.svg?token=JAAOFSS1IQ)](https://codecov.io/gh/tachidok/scicellxx)

# Chapchom

![Travis(.org)](https://img.shields.io/travis/tachidok/chapchom?label=master)
![Travis (.org)branch](https://img.shields.io/travis/tachidok/chapchom/julio?label=julio)

---

## Welcome!
This is the official git repository for the **SciCell++** project.

## What the project is about?
We intent to develop a **Object-Oriented-Parallel numerical framework**
with aims to solve PDE's by Mesh Free/Finite Element Method.

## Ultra-fast installation!!!
We are adopting containers to ease the installation and release of
versions so you do not need to worry about any dependencies.

Follow the instructions in
[here](https://docs.docker.com/engine/install/) to get Docker
installed in your system.

Then get the image from our Docker repository and ta-dah, you are
ready to go.

## Fast installation and starting up!!!

### What you need to have it running and working nicely?
* A C++ compiler - demo drivers and library built with version
  7.4.0. It may work with previous versions as well.
  
* CMake - to configure and install it. We tested with version 3.10.2.

* Python - to test output from demo drivers with validation files
  (also to produce nice plots). We tested with version 3.7.3 but it
  should work with any version >= 3

#### Optional

* Latex - to build documentation. Most documentation is generated from
  `.org` files.

* Doxygen - to build classes diagrams and useful documentation from
  the code.

* MPI support for parallel features - `not currently supported`.

### Get your own copy of the project
You need **git** installed in your computer, then type in a terminal

```shell
git clone https://github.com/tachidok/scicellxx
cd scicellxx
git checkout -b john
```

After executing the first line you will be prompted with your github
user name and your password. The third line generates your fully
customised branch and assumes your name is _john_

### Configuration
* In a terminal (shell command line) go into the `scicellxx` folder
  then type

```shell
./autogen.sh
```

* Follow up the instructions on screen to configure your own copy of
the project.

* From here on you can continue with the `starting_up` document in the
`doc` folder.

**For full details and additional features please check the full
documentation in the `doc` folder.**

#### Documentation

If you got doxygen installed in your system then generate the
documentation by typing in a terminal,

```shell
./make_doc.sh
```

the documentation will be automatically generated into the
`doc/doxy_doc/html` folder, then open the `index.html` file in a
web-browser.

### Additional and recommended external libraries
If you want to get the maximum performance you will need to install
the following external packages. You can find information on how to
configure them in the `doc` folder.

* OpenBLAS
* SuperLU (requires OpenBLAS)
* Armadillo (requires SuperLU)
* VTK (for visuallisation purposes, we use it in combination with
  Paraview)
  
NOTE: The project works and runs nicely without these packages.

## Examples and test cases

Demos, examples or test cases are in the `demos` folder. These demos
are also used to self test the implementation. You should run all of
them to make sure nothing is broken. You can select to perform a full
test at installation time, otherwise type

```shell
./ctest
```
into the specified build folder (the default one is `build`).

A large number of examples is expected to live in the `demos` folder
so check there for any feature available in the project.

### Current demos for specific functionalities
* Interpolation
* Linear solvers
* Matrices operations
* Newton's method
* Solution of ODE's
  * Lotka-Volterra solved with different time steppers
  * N-body problem (only 3-body and 4-body)
  * Explicit time steppers
  * Implicit time steppers (full implicit and _E(PC)^k E_
    implementations)
  * Adaptive time steppers

## License

Mmm ... that is something we need to carefully think about.

## How to contribute

Once we have something intereseting to share with you we will  make the
project public. Please check continuously for updates or contact the
developers :construction: :envelope: (jcp.sansalvador.at.inaoe.mx) :envelope: :

### Notes for contributors
For full details on contributions please check the documentation in
the `doc` folder. Contact the developers for current in-development
features.

## Facts and curiosities

### How many developers are currently working on the library

At Sunday, April/12, 2020 there is one and only one developer, me
:no_mouth:

:construction: :construction: :construction: :construction: :construction:

### When did this start?
This project was initially uploaded to GitHub on Friday, 11 March 2016
:smile:

## Here is a list (in wikipedia) of other software packages that implement the FEM

https://en.wikipedia.org/wiki/List_of_finite_element_software_packages

## Have fun and enjoy .... !!!

---

## DELETE?

New and shields images
[![Build Status](https://img.shields.io/travis/tachidok/scicellxx?label=master)](https://travis-ci.org/tachidok/scicellxx)
[![Build Status](https://img.shields.io/travis/tachidok/scicellxx/julio?label=julio)](https://travis-ci.org/tachidok/scicellxx)

Old with modifications
![Travis(.org)](https://img.shields.io/travis/tachidok/scicellxx?label=master)
![Travis(.org)branch](https://img.shields.io/travis/tachidok/scicellxx/julio?label=julio)

New originals
[![Build Status](https://travis-ci.org/tachidok/scicellxx.svg?branch=master)](https://travis-ci.org/tachidok/scicellxx)
[![Build Status](https://travis-ci.org/tachidok/scicellxx.svg?branch=julio)](https://travis-ci.org/tachidok/scicellxx)

Previous
![Travis(.org)](https://img.shields.io/travis/tachidok/chapchom?label=master)
![Travis (.org)branch](https://img.shields.io/travis/tachidok/chapchom/julio?label=julio)

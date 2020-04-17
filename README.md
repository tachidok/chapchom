# Chapchom

![Travis(.org)](https://img.shields.io/travis/tachidok/chapchom?label=master)
![Travis (.org)branch](https://img.shields.io/travis/tachidok/chapchom/julio?label=julio)

---

## Welcome!
Hi there, this is the official git repository for the **chapchom**
project.

## What the project is about?
We intent to develop a **Object-Oriented-Parallel numerical library**
with aims to solve PDE's by Mesh Free/Finite Element Method.

## Fast installation and starting up!!!

### What you need to have it working nicely?
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

### How to get your own copy of the project?
You need **git** installed in your computer, then type in a terminal

```shell
git clone https://github.com/tachidok/chapchom
cd chapchom
git checkout bob
```

The second line generates your fully customised branch and assumes
your name is _bob_

### How to configure it?
* In a terminal (shell command line) go into the `chapchom` folder
  then type

```shell
./autogen.sh
```

* Follow up the instructions on screen to configure your own copy of
the project.

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

## Additional and recommended external libraries
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

Get your own copy and have fun. Do not hesitate to contact the
developers at :envelope: (jcp.sansalvador.at.inaoep.mx) :envelope:

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

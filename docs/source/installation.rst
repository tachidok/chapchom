Installation
============

We have two main approaches to install the framework and have it ready
to go.

* Docker-based installation: use this installation if you want an easy
  and strees-free installation process.

* Manual installation: use this installation if you are familiar with
  unix based systems and if you love full configuration with command
  line installation process.
  
Docker-based installation
-------------------------

This type of installation provides you with a ready-out-of-the-box
container (a magic box with all software dependencies preinstalled and
ready to go). You do not need to worry about software dependencies
such that you to focus on using SciCell++ to solve your specific
problem right-out-of-the-box.

Docker installation
^^^^^^^^^^^^^^^^^^^

Follow the instructions in `the official docker web page <https://docs.docker.com/engine/install/>`_ to get Docker installed in your system.

Get the docker container from the official repository
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. warning:: Not finished section.

Manual installation
-------------------
This type of installation requires you to install few software
packages in your machine needed by SciCell++. This give you full
customization of the software and hardware resources in your machine.

Required software
^^^^^^^^^^^^^^^^^

Make sure you have the following software installed in your machine:

* **Git** to get a copy of the framework in your system.

* A **C++ compiler** to build the framework and the demo drivers. Tested with version 7.4.0.
  
* **CMake** tool to configure and install it. We tested with version 3.10.2.

* **Python** language to run the unit test. For some demos we include python based scripts to plot the result . Tested with version 3.7.3.

The following software packages are optional:
  
* **Doxygen** to build documentation and classes diagrams from source code.

* **Latex** to generate math symbols in documentation generated from source.

* **MPI** support for parallel features (not currently supported).

You can use our spack.yml file in case you use `spack
<https://spack.readthedocs.io/en/latest/>`_ as your software package manager.

.. code-block:: shell

   Here goes the spack file

Get your own copy of the project
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
In the command line type the following:

.. code-block:: shell
   
   git clone https://github.com/tachidok/chapchom
   cd chapchom
   git checkout -b john_cool

After executing the first line you will be prompted to provide your
GitHub user name and password. The third line generates a fully
customised branch named ``john_cool``.

Configuration
^^^^^^^^^^^^^

* In a command line go into the ``chapchom`` folder and execute the
  automatic generator shell script as follows:

.. code-block:: shell

   ./autogen.sh

.. warning::

   You can pass parameters to the ``autogen`` script, try it with the
   ``-h`` option to get the full list of arguments.
   
* From here on you can continue with the `starting_up` document in the
`doc` folder.

**For full details and additional features please check the full
documentation in the `doc` folder.**

Generating ``doxygen`` documentation from source code
-----------------------------------------------------

If you got doxygen installed in your system then you can generate the
source code documentation by typing the following in a command line:

.. code-block:: shell

   ./make_doc.sh

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

Installation
============

We have two main approaches to install SciCell++ and have it ready to
go.

`Docker-based installation`_
  Use this installation if you want an easy and strees-free
  installation process.

`Manual installation`_
  Use this installation if you are familiar with Unix based systems
  and if you prefer command line installation..

Docker-based installation
-------------------------

This type of installation provides you with a ready-out-of-the-box
container (a magic box with all software dependencies preinstalled and
ready to go). You do not need to worry about software dependencies
such that you to focus on using SciCell++ to solve your specific
problem right-out-of-the-box.

1. Install docker

Follow the instructions in `docker official installation website
<https://docs.docker.com/engine/install/>`_ to get Docker installed in
your system.

2. Get the docker container from the official repository

.. warning:: Not finished section.

3. Run the docker application

4. Run the docker image


Manual installation
-------------------

This type of installation gives you full customization of the software
and hardware resources in your machine.

**Requirements**

* `Git <https://git-scm.com/>`_ to get a copy of SciCell++ in your
  system.

* A **C++ compiler** to build the SciCell++ and the demos. We tested
  with `gcc <https://gcc.gnu.org/>`_ version 7.4.0.
  
* The `CMake <https://cmake.org/>`_ tool to configure and install
  SciCell++. We tested with CMake version 3.10.2.

* The `Python <https://www.python.org/>`_ language to run some of the
  demos and the unit test. We include Python based scripts to plot the
  result for some demos . Tested with Python version 3.7.3.

The following software packages are optional (but recommended)
  
* `Doxygen <https://www.doxygen.nl/index.html>`_ to build
  documentation and classes diagrams from source code for SciCell++.

* `Latex <https://www.latex-project.org/>`_ to generate *math* symbols
  in documentation generated from source code.

* A software implementation of **MPI** to support parallel features
  (openmpi/mpicc recommended - not currently supported-).

.. important::
   
   If you use `Spack <https://spack.readthedocs.io/en/latest/>`_ as
   your software package manager here is our spack :download:`file
   <./spack.yaml>`. Feel free to use it to ease the installation
   process.

**Steps**
   
Now follow the steps below that guide you through the installation
process:

1. Get your own copy of SciCell++

   Open a command line and type the following:

.. code-block:: shell
   
   git clone https://github.com/tachidok/scicellxx
   cd scicellxx
   git checkout -b john_cool

The previous commands get a copy of SciCell++ from the `official
GitHub repository <https://github.com/tachidok/scicellxx>`_ down to
your local machine and moves into the ``scicellxx`` folder. Finally, a
new branch named ``john_cool`` is generated.

.. note::

   Feel free to rename de ``john_cool`` folder with your name.

2. Configuration

Within the ``scicellxx`` folder execute the automatic generator shell
script as follows:

.. code-block:: shell

   ./autogen.sh

.. important::

   This commands executes a full compilation of SciCell++ and runs all
   the demos and tests to make sure you are working with an stable
   copy. If you want to fully configure the compilation process use
   the ``-i`` parameter. You will be able to specify the number of
   processors to compile SciCell++, also the number of processor to
   run the demos, use predefined configuration files for access to
   third-party libraries and many more. For a full list of available
   options use the ``-h`` parameter.

A summary of the compilation and testing process is shown once they
have finished. If no errors were reported then SciCell++ is ready to
go. We recommend you to have a look at the list of :doc:`demos` as
follow up.

Additional features
-------------------

Generating ``doxygen`` documentation for SciCell++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This includes class diagramas and full source documentation.

**Requirements**

* `Doxygen <https://www.doxygen.nl/index.html>`_ and `Latex
  <https://www.latex-project.org/>`_ to generate documentation from
  source code.

**Steps**
  
1. Go to the upper level folder of the project, probably called
`scicellxx`.

2. Open a command line and type
  
.. code-block:: shell

   ./make_doc.sh

Voila! The documentation will be automatically generated into the
`docs/doxy_doc/html` folder. Open the file `index.html` within your
favorite web-browser to read the documentation.

A list (in wikipedia) of `software packages that implement the FEM`_

References
----------

.. target-notes::
   
.. _`software packages that implement the FEM`: https://en.wikipedia.org/wiki/List_of_finite_element_software_packages

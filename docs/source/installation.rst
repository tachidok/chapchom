.. _installation-label_installation.rst:

Installation
============

We have two main approaches to install SciCell++ and have it ready to
go:

  `Docker-based installation`_: Use this installation if you prefer a
  fast and easier installation of SciCell++.

  `Manual installation`_: Use this installation if you are familiar
  with Unix based systems, within this installation you have control
  over the versions of the third-part packages used by SciCell++.

Docker-based installation
-------------------------

This type of installation provides you with a ready-out-of-the-box
container (a magic box with all software dependencies preinstalled and
ready to go). You will be able to use SciCell++ just
right-out-of-the-box.

Windows systems
^^^^^^^^^^^^^^^


Ubuntu 18.04.5 LTS
^^^^^^^^^^^^^^^^^^

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

.. note::

   Currently only Unix based systems are considerd for this type of
   installation. The steps provided in this section have been tested
   in Ubuntu 16.04 LTS, Ubuntu 18.04.2 LTS and Ubuntu 18.04.5 LTS.

.. note::
   
   If you use `Spack <https://spack.readthedocs.io/en/latest/>`_ as
   your software package manager we provide you with our spack
   :download:`file <./spack.yaml>`. Feel free to use it to ease the
   installation process and skip this section.
   
**Software pacakges requirements**

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

**Steps**
   
The following step guide you through the installation process:

1. Get your own copy of SciCell++

   Open a command line and type in the following:

   .. code-block:: shell
   
                   git clone https://github.com/tachidok/scicellxx
                   cd scicellxx
                   git checkout -b john_cool

   The previous commands get a copy of SciCell++ from the `official
   GitHub repository <https://github.com/tachidok/scicellxx>`_ down to
   your local machine and moves into the ``scicellxx``
   folder. Finally, a new branch named ``john_cool`` is generated.

   .. note::

      Feel free to rename the ``john_cool`` folder with your name.
   
2. Configuration

   Within the ``scicellxx`` folder execute the automatic generator
   shell script as follows:

   .. code-block:: shell

                   ./autogen.sh

   .. important::

      This commands executes a full compilation of SciCell++ and runs
      all the demos and tests to make sure you are working with an
      stable copy. If you want to fully configure the compilation
      process use the ``-i`` parameter. You will be able to specify
      the number of processors to compile SciCell++, also the number
      of processor to run the demos, use predefined configuration
      files for access to third-party libraries and many more. For a
      full list of available options use the ``-h`` parameter.

   A summary of the compilation and testing process is shown once they
   have finished. If no errors were reported then SciCell++ is ready
   to go. We recommend you to have a look at the :doc:`tutorials` and
   :doc:`demos` as follow up.

Additional features
-------------------

In this section we present some additional features that may help you
to generate the full documentation of SciCell++ from source code, and
to move SciCell++ to a computer with no Internet access.

Generate ``doxygen`` documentation for SciCell++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This allows you to create class diagrams and browseable documentation
directly from the source code of SciCell++.

**Requirements**

* `Doxygen <https://www.doxygen.nl/index.html>`_ and `Latex
  <https://www.latex-project.org/>`_ to generate documentation from
  source code.

  Check :ref:`this section <doxygen-installation-label_installation.rst>` for doxygen installation.
  
**Steps**
  
1. Open a command line and go to the upper level folder of the
   project, probably called ``scicellxx``.

2. In the command line type the following:
  
   .. code-block:: shell

                   ./make_doc.sh

   Voila! The documentation will be automatically generated into the
   ``docs/doxy_doc/html`` folder.

3. Open the file ``index.html`` within your favorite web-browser to
   read the documentation.

Generate a ``.tar.gz`` file to distribute SciCell++
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The easiest way to distributed SciCell++ is by means of the official
GitHub repository, however, if you need to move your current copy of
SciCell++ to a computer with no Internet access (ex. an isolated
cluster of computers or a SuperComputer) this is an easy way to do
so. Follow the steps in this section to create a ``.tar.gz`` package
file with your current version of SciCell++.

**Requirements**

* Save all of your work
* Make sure that your current version has neither errors nor broken
  demos. You can verify this by running the ``./autogen.sh`` script at
  the root directory of SciCell++.

**Steps**

1. Go to the upper level folder of the project, probably called
   ``scicellxx``.

2. Open a command line and type

   .. code-block:: shell

                   ./make_clean_distro.sh

   The full folder containing SciCell++ will be copied into a
   temporary location, all the control version information generated
   by Git will be removed. You will be prompted to remove all files
   with the extension ``.dat, .png, .tar.gz, .fig, .bin, .rar, .vtu,
   .ubx, .gp, .m`` (only those in the ``demos`` folder will be
   keep). The process of creating a compressed file will start.

3. Once finished a file named ``SciCell++.tar.gz`` will be created in
   the root folder of SciCell++.

.. _external-packages-installation-label_installation.rst:
   
External packages installation
------------------------------

If you want to get the maximum performance for SciCell++ you will need
to install some or all of the packages listed in this section.

.. note::

   You do not need to install these packages for basic use of
   SciCell++, install them only if you require additional features.

.. note::
   
   If you used our provided spack :download:`file <./spack.yaml>` at
   the :ref:`installation
   <doxygen-installation-label_installation.rst>` step then you
   already have these ones as well. You may skip this section.

The list of packages is the following:

* :ref:`Doxygen <doxygen-installation-label_installation.rst>`
* :ref:`OpenBLAS <openblas-installation-label_installation.rst>`
* :ref:`SuperLU <superlu-installation-label_installation.rst>` (requires OpenBLAS)
* :ref:`Armadillo <armadillo-installation-label_installation.rst>` (it is recommended to previously install SuperLU)
* :ref:`VTK <vtk-installation-label_installation.rst>` (for visuallisation purposes, we use it with `Paraview <https://www.paraview.org/>`_)

.. note:: Please note that the provided instructions were tested in
   the following distributions of Ubuntu:

   * Ubuntu 16.04 LTS 64 bits
     
   * Ubuntu 18.04.2 LTS 64 bits
     
   * Ubuntu 18.04.5 LTS 64 bits

**General requirements**

1. Before installing any of the external libraries in your system
   ensure that none of them is already installed in your system, this
   may produce crashes between versions.

   You may remove the installed packages with the following command:

   .. code-block:: shell

      sudo apt-get remove --purge <package-name>

   where `<package-name>` should be substituted by the name of the
   package you want to remove.
   
2. Install the following packages in your system.

   .. note:: We provide the version of each package that we used for
             the installation. You could check the available version
             of a package for your system by typing:

             .. code-block:: shell

                apt-cache policy <package-name>

             where `<package-name>` should be substituted by the name
             of the package which you want to check its version.
   
  **Ubuntu 16.04 LTS 64 bits**
     
     + cmake (cmake 3.5.1-1ubuntu3)
       
     + liblapack (liblapack-dev 3.6.0-2ubuntu2)
       
     + libarpack (libarpack2, libarpack2-dev 3.3.0-1build2)

   Install them by typing:

   .. code-block:: shell

      sudo apt-get install cmake liblapack-dev libarpack2 libarpack2-dev

  **Ubuntu 18.04.2 LTS 64 bits**
     
     + cmake 3.10.2
       
     + liblapack (liblapack3 3.7.1-4ubuntu1, liblapack-dev
       3.7.1-4ubuntu1)
       
     + libarpack (libarpack2 3.5.0+real-2, libarpack2-dev
       3.5.0+real-2)

   Install them by typing:

   .. code-block:: shell

      sudo apt-get install cmake liblapack3 liblapack-dev libarpack2 libarpack2-dev
       
3. Once installed follow the order below for installing the external
   packages

.. _doxygen-installation-label_installation.rst:
   
Doxygen
^^^^^^^

If you want to create documentation from the source code then install
Doxygen and graphviz.

**Steps**

1. Open a terminal and type

.. code-block:: shell

  sudo apt-get install doxygen
  sudo apt-get install graphviz

.. note:: Tested versions with Ubuntu 18.04.2 LTS 64 bits:
          
          * doxygen 1.8.13-10
          * graphviz 2.40.1-2

.. _openblas-installation-label_installation.rst:
   
OpenBLAS
^^^^^^^^

OpenBLAS is an optimised version of the Basic Linear Algebra
Subprograms (BLAS). This section guides you through the installation
of ``OpenBLAS 0.2.20`` on the following Ubuntu distributions:

* Ubuntu 16.04 LTS 64 bits
* Ubuntu 18.04.2 LTS 64 bits
* Ubuntu 18.04.5 LTS 64 bits

.. note:: Please refer to the `original documentation
          <https://www.openblas.net/>`_ in case you have problems with
          the installation.

**Requirements**

Double-check that no previous installation of OpenBLAS is part of your
system. If that is the case we recommend you to uninstall them before
continuing.

  **Ubuntu 16.04 LTS 64 bits**

  Packages to install:
  
  * libblas-dev (libblas-common, libblas-dev 3.6.0-2ubuntu2)

  Open a terminal and type the following:

  .. code-block:: shell

     sudo apt-get install libblas-common libblas-dev
     
  **Ubuntu 18.04.2 LTS 64 bits**

  Packages to install:

  * libblas-dev (libblas3 3.7.1-4ubuntu1, libblas-dev 3.7.1-4ubuntu1)

  Open a terminal and type the following:

  .. code-block:: shell
  
     sudo apt-get install libblas3 libblas-dev

**Steps**

1. Extract the compressed file in
   ``scicellxx/external_src/openBLAS/OpenBLAS-0.2.20.tar.gz`` in a folder.

  .. warning:: We recommend you to extract it out of the ``scicellxx``
               project folder to avoid adding the files to the git
               repository. If you do extract it in the ``scicellxx``
               project folder then do not commit that folder within
               the project.
  
2. Open a terminal and go into the folder where you extracted the
   files and type

   .. code-block:: shell

                   make

   .. note:: You can try with ``make -j <number_of_processors>`` to
             use more processors at compilation time.

3. Once compilation is finished type the following to start the
   installation process

   .. code-block:: shell

                   mkdir installation
                   make PREFIX=./installation install
                   
   .. note:: If you prefer you can specify a different installation
             foilder as follow:

             .. code-block:: shell

                             make PREFIX=/path/to/your/installation install
                

.. _superlu-installation-label_installation.rst:

SuperLU
^^^^^^^

SuperLU is a library for the direct solution of large, sparse,
nonsymmetric systems of linear equations. This section guides you
through the installation of ``SuperLU 5.2.0`` on the following Ubuntu
distributions:

* Ubuntu 16.04 LTS 64 bits
* Ubuntu 18.04.2 LTS 64 bits

.. note:: Please refer to the `original documentation
          <http://crd-legacy.lbl.gov/~xiaoye/SuperLU/>`_ in case you
          have problems with the installation.
  
**Requirements**

Double-check that no previous installation of SuperLU is part of your
system. If that is the case we recommend you to uninstall them before
continuing.

You must have cmake installed in your system. Please refer to
:ref:`that section
<external-packages-installation-label_installation.rst>` to ensure its
installation.

**Steps**

1. Extract the compressed file ``/external_src/superLU/superlu_5.2.0.tar.gz`` in a folder of your
  preference. We recommend you to extract it out of the chapchom
  project folder to avoid adding the files to the git repository. If
  you do extract it inside the chapchom project folder please extreme
  precautions when adding your files to the git repository.

- Go to the folder where you extracted the files and type

#+BEGIN_SRC bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../lib
#+END_SRC

the last line indicates where to perform the installation, I use to
install it in the =lib= directory of the SuperLU folder, that is why
that value. However, if you have root privileges then you may not need
to specify a value for the =CMAKE_INSTALL_PREFIX= variable.

NOTE: If you are installing =Armadillo= with =SuperLU= support then
you may need to install =SuperLU= with the flag =-fPIC= (which stands
for 'Position Independent Code'), to do so open the =CMakeLists.txt=
file in the main folder of =SuperLU= and edit the line where =CFLAGS=
are added (in =SuperLU 5.2.0= it is in line =68=). This is how it
looks for =version 5.2.0=.

#+BEGIN_SRC cmake
set(CMAKE_C_FLAGS "-fPIC -DPRNTlevel=0 -DAdd_ ${CMAKE_C_FLAGS}")
#+END_SRC

- When the process finish then type

#+BEGIN_SRC bash
make
#+END_SRC

You can try =make -j # of processors= instead of =make= to use more
processors at compilation time.

- Install it ...

#+BEGIN_SRC bash
make install
#+END_SRC

- And finally, run the test by typing

#+BEGIN_SRC bash
ctest
#+END_SRC

You can check the results of the testing process in the following
files

| =build/TESTING/s_test.out= | =single precision, real=   |
| =build/TESTING/d_test.out= | =double precision, real=   |
| =build/TESTING/c_test.out= | =single precision, complex=   |
| =build/TESTING/z_test.out= | =double precision, complex=   |

.. _armadillo-installation-label_installation.rst:

Armadillo
^^^^^^^^^

.. _vtk-installation-label_installation.rst:

VTK
^^^

External packages webpages
^^^^^^^^^^^^^^^^^^^^^^^^^^

* `Doxygen <https://www.doxygen.nl/index.html>`_
* `OpenBLAS <https://www.openblas.net/>`_
* `SuperLU <https://portal.nersc.gov/project/sparse/superlu/>`_
* `Armadillo <http://arma.sourceforge.net/>`_
* `VTK <https://vtk.org/>`_
* `Paraview <https://www.paraview.org/>`_

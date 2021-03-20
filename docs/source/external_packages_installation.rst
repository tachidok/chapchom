External packages installation
=============================

If you want to get the maximum performance for SciCell++ you will need
to install the following external packages.

* `OpenBLAS <https://www.openblas.net/>`_
* `SuperLU <https://portal.nersc.gov/project/sparse/superlu/>`_ (requires OpenBLAS)
* `Armadillo <http://arma.sourceforge.net/>`_ (requires SuperLU)
* `VTK <https://vtk.org/>`_ (for visuallisation purposes, we use it in
  combination with `Paraview <https://www.paraview.org/>`_)

.. important::
   
   If you used our provided spack :download:`file <./spack.yaml>` then
   you have already installed these ones as well.
  
.. important::

   You do not need to install these packages for basic use of
   SciCell++, install these packages only if you require additional
   features.
   
.. important::

   The provied instructions were tested in the following
   distributions of Ubuntu

   * Ubuntu 16.04 LTS 64 bits
   * Ubuntu 18.04.2 LTS 64 bits
   * Ubuntu 18.04.5 LTS 64 bits

**General requirements**

Before installing any of the external libraries in your system ensure
that none of them is already installed in your system, this may
produce crashes between versions.

Installing OpenBLAS
-------------------

Installing SuperLU
------------------

Installing Armadillo
--------------------

Installing VTK
--------------



This guide is to allow [[https://github.com/tachidok/chapchom][chapchom]] to work with external libraries such
as =Armadillo=, =SuperLU= and =VTK (for visualisation)= in the
following =OS=:
 - =Ubuntu 16.04 LTS 64 bits=,
 - =Ubuntu 18.04.2 LTS 64 bits=.
If you find any problem or something in this guide makes no sense
please contact the author.

* Requirements
Before installing any of the external libraries in your system ensure
that none of them is already installed in your system, this may
produce crashes between versions.

Once you ensure that non other versions of the external packages are
already installed in your system then proceed to check that you have
the following packages installed in your system.[fn:note:You may need
to install =synaptic= package manager to install them.]

 * =Ubuntu 16.04 LTS 64 bits=
   - cmake (=cmake 3.5.1-1ubuntu3=)
   - liblapack (=liblapack-dev 3.6.0-2ubuntu2=)
   - libarpack (=libarpack2=, =libarpack2-dev 3.3.0-1build2=)
 * =Ubuntu 18.04.2 LTS 64 bits=
   - =cmake 3.10.2=
   - liblapack (=liblapack3 3.7.1-4ubuntu1=, =liblapack-dev
     3.7.1-4ubuntu1=)
   - libarpack (=libarpack2 3.5.0+real-2=, =libarpack2-dev
     3.5.0+real-2=)

 * +libblas-dev (tested with =libblas-common=, =libblas-dev 3.6.0-2ubuntu2=)+

* Optional
If you want to create the documentation then install doxygen and
graphviz.
 * Tested versions with =Ubuntu 18.04.2 LTS 64 bits=
  - =doxygen 1.8.13-10= (installed from package manager synaptic)
  - =graphviz 2.40.1-2= (installed from package manager synaptic)

* Installation

Suggested (and working) installation order
- OpenBLAS
- SuperLU
- Armadillo
- VTK

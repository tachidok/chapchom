
# SciCell++

![GitHub-master-push](https://github.com/tachidok/scicellxx/workflows/Build-and-Test/badge.svg?branch=master&event=push)
[![codecov](https://codecov.io/gh/tachidok/scicellxx/branch/master/graph/badge.svg?token=JAAOFSS1IQ)](https://codecov.io/gh/tachidok/scicellxx)
[![Documentation Status](https://readthedocs.org/projects/scicellxx/badge/?version=latest)](https://scicellxx.readthedocs.io/en/latest/?badge=latest)

---

## Welcome!
This is the official GitHub repository for the **SciCell++** project.

## What is SciCell++?

SciCell++ is an object-oriented framework for the simulation of biological and physical phenomena modelled as continuous or discrete processes.

## Table of Contents

1. [Installation](#installation)
2. [Examples and test cases](#examples_and_test_cases)
3. [Documentation](#documentation)
4. [How to contribute](#how_to_contribute)
5. [Facts and curiosities](#facts_and_curiosities)
6. [License](#license)

## Installation <a name="installation"></a>

### Docker-based installation
We are adopting containers to ease the installation and release of
versions so you do not need to worry about any dependencies.

This section and installation procedure is under development.
:construction: :construction: :construction: :construction: :construction:

Follow the instructions in
[here](https://docs.docker.com/engine/install/) to get Docker
installed in your system.

Then get the image from our Docker repository and ta-dah, you are
ready to go.

### Fast installation and starting up!!!

#### What you need to have it running and working nicely?
* A C++ compiler - demo drivers and library built with version
  7.4.0. It may work with previous versions as well.
  
* CMake - to configure and install it. We tested with version 3.10.2.

* Python - to test output from demo drivers with validation files
  (also to produce nice plots). We tested with version 3.7.3 but it
  should work with any version >= 3

##### Optional

* MPI support for parallel features - `not currently supported`.

#### Get your own copy of the project
You need **git** installed in your computer, then type in a terminal

```shell
git clone https://github.com/tachidok/scicellxx
cd scicellxx
git checkout -b john_cool
```

After executing the first line you will be prompted with your GitHub
user name and your password. The third line generates your fully
customised branch, we assume that your name is _john_cool_

#### Configuration
* In a terminal (shell command line) go into the `scicellxx` folder
  then type

```shell
./autogen.sh
```

* Follow up the instructions on screen to configure your own copy of
the project.

## Demos <a name="examples_and_test_cases"></a>

Demos live in the `demos` folder. You should run all of them to make sure nothing is broken. If you did not run them at installation time (by default) you can do it at any time by typing in a terminal

```shell
./ctest
```
into the specified build folder (the default one is `build`).

A large number of demos is expected to live in the `demos` folder so check there for any feature available in the project or review the [corresponding documentation](https://scicellxx.readthedocs.io/en/latest/?badge=latest).

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

## Documentation <a name="documentation"></a>

The full documentation is [here](https://scicellxx.readthedocs.io/en/latest/?badge=latest).

## How to contribute <a name="how_to_contribute"></a>

Please check the [corresponding documentation](https://scicellxx.readthedocs.io/en/latest/?badge=latest) section for contributions.

## Facts and curiosities <a name="facts_and_curiosities"></a>

### How many developers are currently working on this project

At Wednesday, March/31, 2021 there is one and only one developer, me
:no_mouth: :envelope:

:construction: :construction: :construction: :construction: :construction:

### When did this start?
This project was initially uploaded to GitHub on Friday, 11 March 2016
:smile:

## License <a name="license"></a>

Licensed under the GNU GPLv3. A copy can be found on the [LICENSE](./LICENSE) file.

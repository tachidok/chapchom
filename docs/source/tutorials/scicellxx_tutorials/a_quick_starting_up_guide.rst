A quick starting-up guide
=========================

In this section we provide you with the basic tool to start working
with SciCell++, we present the main folder structure and how to create
your very first project. There is also a section for including your
project as a demo for further reference of new collaborators.

A framework, not a library
--------------------------

SciCell++ is a **software framework**, that means, we provide you with
the main code structure and you only have to fill-in the specific
details for your project. In a library, you are in charge of the main
flow of the program and the tools that you include.

The code that you write becomes part of the framework, this will help
others to build on your code just as you built on the code wrote by
others. We encourage you to personalise SciCell++ based on your needs
**by extending** its current behavior to provide it with extra
functionalities.

Folder structure of the framework
---------------------------------

This is what each folder is about in the framework:

* ``bin``, stores scripts used by the framework at compilation time,
  there are also scripts that help on the generation of *clean
  distributions* of the framework. These are compressed files that you
  may want to generate when copying the framework to a computer
  without Internet access; for example a supercomputer node.
  
* ``build``, this folder is automatically generated when compiling the
  library and all the compilation files are stored there. *You do not
  need to deal with the files within this folder, just leave them
  alone*.
  
* ``configs``, store configuration files, each file corresponds to an
  specialised configuration of the framework. For example, you can
  indicate to use Armadillo, VTK, double precision arithmetic, panic
  mode, etc. Have a look at :ref:`the full list of options
  <options_for_the_configuration_file-label_a_quick_starting_up_guide.rst>`. The
  default configuraton is stored in the ``default`` file. If you want
  to use an specialised configuration of the framework you should
  store it here and select it when prompting for a `configuration
  file` when running the ``autogen.sh`` file. Try any other of the
  configurations in this folder, some of them make use of external
  libraries so make sure you have installed them.
  
* ``demos``, stores a large set of demos that you may want to use as
  templates or starting points for your project. These demos provide a
  good insight on the features available in SciCell++. This folder
  also helps for testing the framework and report any found issues
  after new features are implemented. When you want to update your
  contributions to the SciCell++ repository make sure all of the demos
  compile, run and pass the tests.
  
* ``external_src``, this folder stores any external library packages
  used within the framework to provide extra features. You should not
  modify this folder unless you are providing new functionalities that
  depend on external software packages.
  
* ``private``, stores private files for each user or collaborator of
  SciCell++. Each one should have its own private folder here, this
  should be used as the development folder of each user. We encorage
  you to fully document your projects so that it can be included in
  the ``demo`` folder to shown specialised features of the framework.
  
* ``src``, this is the hearth of SciCell++, here lies all the source
  code. Prior to include files in this folder you should test them in
  your ``private`` folder, by adding files to this folder you are
  extending the capabilities of SciCell++.
  
* ``tools``, a set of tools used for the library, mainly Python codes
  for visualisation issues.

.. _options_for_the_configuration_file-label_a_quick_starting_up_guide.rst:
  
Options for the configuration file
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* SCICELLXX_LIB_TYPE

  Specify the building type of the library ``STATIC`` or ``SHARED``.

  Example:

  .. code-block:: shell

     SCICELLXX_LIB_TYPE=STATIC
  
* SCICELLXX_RANGE_CHECK

  Specify whether to check for out-of-range in vectors or not. This
  significantly increase the running time of your application. We
  recommend you to enable this option only for developing purposes to
  ease you finding errors in the code. When using this option consider
  to compile with debugging options when prompted by the
  ``autogen.sh`` file. Once you move into the release mode disable
  this option and compile with full optimisation when prompted by the
  ``autogen.sh`` file.
  
  Example:
  
  .. code-block:: shell

     SCICELLXX_RANGE_CHECK=TRUE
  
* SCICELLXX_USES_DOUBLE_PRECISION

  Specify whether to use single (``float``) or double (``double``)
  precision at running time.
  
  Example:
  
  .. code-block:: shell

     SCICELLXX_USES_DOUBLE_PRECISION=TRUE
  
* SCICELLXX_USES_ARMADILLO

  Specify whether to use the external library Armadillo for linear
  algebra. You would need to :ref:`install Armadillo
  <armadillo-installation-label_installation.rst>` to enable this
  option.
  
  Example:
  
  .. code-block:: shell

     SCICELLXX_USES_ARMADILLO=FALSE
  
* SCICELLXX_AUTO_FIND_ARMADILLO_PATHS

  Use this option to automatically find the corresponding installation
  folder of Armadillo. Enable this option only if the option
  ``SCICELLXX_USES_ARMADILLO`` was set to ``TRUE``.
  
  Example:
  
  .. code-block:: shell

     SCICELLXX_AUTO_FIND_ARMADILLO_PATHS=TRUE
     
* ARMADILLO_AUTO_FIND_FOLDER

  If you want ot use Armadillo and you set the variable
  ``SCICELLXX_AUTO_FIND_ARMADILLO_PATHS`` to ``TRUE`` you may indicate
  an starting folder for the automatic finding of the Armadillo
  installation.

  Example:
  
  .. code-block:: shell
 
     ARMADILLO_AUTO_FIND_FOLDER=/home/tachidok/local/working/research/armadillo-8.300.3

* ARMADILLO_INCLUDE_DIRS

  If you want to use Armadillo but set the variable
  ``SCICELLXX_AUTO_FIND_ARMADILLO_PATHS`` to ``FALSE`` you must
  indicate the ``include`` directory in this option.
  
  Example:
  
  .. code-block:: shell

     ARMADILLO_INCLUDE_DIRS=/home/tachidok/local/working/research/armadillo-8.300.3/installation/include

* ARMADILLO_LIBRARIES

  If you want to use Armadillo but set the variable
  ``SCICELLXX_AUTO_FIND_ARMADILLO_PATHS`` to ``FALSE`` you must
  indicate the ``lib`` directory in this option.
  
  Example:
  
  .. code-block:: shell

     ARMADILLO_LIBRARIES=/home/tachidok/local/working/research/armadillo-8.300.3/installation/lib/libarmadillo.so.8.300.3
     
* SCICELLXX_USES_VTK

  Specify whether to use the external library VTK for results
  visualization. Some demos require VTK to generate output. You would
  need to :ref:`install VTK <vtk-installation-label_installation.rst>`
  to enable this option.

  Example:

  .. code-block:: shell

     SCICELLXX_USES_VTK=FALSE
  
* SCICELLXX_AUTO_FIND_VTK_PATHS

  Use this option to automatically find the corresponding installation
  folder of VTK. Enable this option only if the option
  ``SCICELLXX_USES_VTK`` was set to ``TRUE``.
  
  Example:

  .. code-block:: shell

     SCICELLXX_AUTO_FIND_VTK_PATHS=TRUE

* VTK_AUTO_FIND_FOLDER

  If you want ot use VTK and you set the variable
  ``SCICELLXX_AUTO_FIND_VTK_PATHS`` to ``TRUE`` you may indicate an
  starting folder for the automatic finding of the VTK installation.
  
  Example:

  .. code-block:: shell

     VTK_AUTO_FIND_FOLDER=/home/tachidok/local/working/research/VTK-8.1.1/VTK-bin
                  
* VTK_INCLUDE_DIRS

  If you want to use VTK but set the variable
  ``SCICELLXX_AUTO_FIND_VTK_PATHS`` to ``FALSE`` you must indicate the
  ``include`` directory in this option.
  
  Example:

  .. code-block:: shell

     VTK_INCLUDE_DIRS=/home/tachidok/local/working/research/VTK-8.1.1/VTK-bin/installation/include/vtk-8.1
     
* VTK_LIBRARIES

  If you want to use VTK but set the variable
  ``SCICELLXX_AUTO_FIND_VTK_PATHS`` to ``FALSE`` you must indicate the
  ``lib`` directory in this option.
  
  Example:

  .. code-block:: shell

     VTK_LIBRARIES=/home/tachidok/local/working/research/VTK-8.1.1/VTK-bin/installation/lib/libvtkalglib-8.1.so.1
     
* SCICELLXX_PANIC_MODE

  This option enables a large number of validations at running time,
  it also enables error messages that may help you to identify
  problems in your code. However, this considerably increase the
  running time of your application. Use this option only at developing
  time. Deactivate this function when runnig on release mode, also
  make sure to activate full optimisation at compilation time when
  prompted by the ``autogen.sh`` script.
  
  Example:

  .. code-block:: shell

     SCICELLXX_PANIC_MODE=TRUE

Running demos
-------------

Go to the demo folder you are interested and type =./bin/= followed by
the name of the demo. Make sure there is a =./RESLT/= folder in the
directory you are running the demo since the results of the
computations are stored in there.

Once the demo has started you should see output messages on the
terminal with general information about the results of the
computations.

**Input arguments**
Some demos require input arguments to run, you can check what input
arguments you need to pass by passing the =--help= or =-h= option to
the demo driver.

Create your ``private`` folder
----------------------------

In order to modify or create your own code we encourage you to do so
in your own private folder, to do so open a terminal and create your
folder inside the =private= folder.

In a terminal type

#+BEGIN_SRC bash
cd private
mkdir john
cd john
#+END_SRC

Note that we are assuming you are named =john=, change that with your
name. Once you have created your own private folder update the
=CMakeLists.txt= file in the private folder by adding your folder name
at the end of the file using the following line

#+BEGIN_SRC bash
ADD_SUBDIRECTORY(john)
#+END_SRC

Substitute =john= with your folder name.

Compile again the full framework using the =./autogen.sh= comand at the
root folder and make sure no problems are found.

Creating your own project
-------------------------

Start by copying a demo driver into your private folder, here we copy
the demo driver =demo_basic_interpolation.cpp= in the folder
=demos/interpolation/basic_interpolation=. Assuming you are in your
private folder type the following in a terminal

#+BEGIN_SRC bash
cp demos/interpolation/basic_interpolation/demo_basic_interpolation.cpp demo_john.cpp
#+END_SRC

Then copy the =CMakeLists.txt.private_template= file that lives in the
=tools= folder into your private directory and change its name to
=CMakeLists.txt=, then change its content as follows:

+ All the instances of the tag =SRC_demo_john= for your own tag to
  identify source code.
+ All the instances of =demo_john.cpp= for the name of your code file.
+ All the instances of =demo_john=, this is the name of your executable
  and the name you need to type to compile your project.
+ All the instances of the tag =LIB_demo_john= for your own tag to
  identify libraries required for your code
+ Include the libraries you need. In the example only the
  =general_lib= and the =problem_lib= are included (in section # there
  is a list for the name of the libraries that you may include into
  your project).

Compile again the full framework using the =./autogen.sh= comand at
the root folder and make sure no compilation errors are found. Once
compilation has finished without errors you can compile your code by
going to the =build= folder and type

#+BEGIN_SRC bash
make demo_john
#+END_SRC

The compilation output should be displayed in your screen. Fix any
compilation problem you found, then to run your code go back to your
=private= folder, make sure you have a =RESLT= folder in your
directory and type

#+BEGIN_SRC bash
./bin/demo_john
#+END_SRC

Any output from your code should be displayed on the terminal.

** Compilation or source code and exection of binaries
As you have noticed, the generation and execution of your project is
made in two different folders:
+ the =build= folder and
+ your =private= folder.
We followed this two-folders strategy to avoid having automatically
generated =CMake= files all over the folder structure of the
project. By following this strategy we keep a clean structure for
the project and group all files generated by =CMake= in the =build=
folder. This help us to keep track for changes easily since we can
exclude the =build= folder from the =git= repository.

Just keep in mind that whenever you want to compile your source code
you need to do so in the =build= directory, just type =make= followed
by the name of your project. Then when you want to execute your
project go back to your =private= folder and type =./bin/=
concatenated with the name of your executable file.

Add your project as a demo into the ``demos`` folder
----------------------------------------------------

Once you are fully happy with the results of your project you can
include it as part of the framework in the =demos= folder. Here are
three things that you need to do before including it in the =demos=
folder.
1) You need to think where in the =demos= folder structure to include
   your demo.
2) You need to create the expected/correct output files that will be
   used by the testing unit to check for running errors.
3) You will have to check your demo is run and passed properly when
   running the demos of the project.
After considering these points proceed as follows:
+ Create the required folder structure into the =demo= folder.
+ Add =ADD_SUBDIRECTORY= lines in the corresponding =CMakeLists.txt=
  files to include your newly created folder structure.
+ Copy the =CMakeLists.txt.demo_template= file into the demo folder
  and rename it to =CMakeLists.txt=.
+ Create a =validate= folder into the newly created folder structure
  for your demo.
+ Store the expected/correct output files generated by your demo in
  the =validate= folder. The validation files should be named as
  =validate_double_demo_john.dat= and =validate_demo_john.dat= changing
  =john= by the name of your project. Please generate double and single
  precision validation files by running your project with both
  configurations.
+ Rename the same tags and variables as in =* Creating your own
  project into the framework= section.
+ Rename ALL instances of =TEST_demo_john_run= by the name of your
  demo. Keep the =TEST= and =_run= prefix and postfix, respectively.
+ Rename ALL instances of =demo_john= with the name of your demo.
+ Rename ALL instances of =VALIDATE_FILENAME_demo_john= with the name
  of your tag for the validation file.
+ Change the name of the validation file
  =validate_double_demo_john.dat= by yours, this file should have the
  expected/correct output of your project using double precision.
+ Change the name of the validation file =validate_demo_john.dat= by
  yours, this file should have the expected/correct output of your
  project using single precision.
+ Rename ALL instances of =TEST_demo_john_check_output= by the name of
  your demo. Keep the =TEST= and =_output= prefix and postfix,
  respectively.
+ Make sure that your demo generates an output file named
  =output_test.dat= with the information that will be checked by the
  testing process.

* [OPTIONAL] Include the =bin= folder of the project to your =PATH= variable

Add the following lines at the end of your =.bashrc= file in your home
folder.

#+BEGIN_SRC bash
export PATH="/home/tachidok/local/working/research/chapchom/bin/:$PATH"
#+END_SRC

Assumming the working directory of the framework is at

#+BEGIN_SRC bash
/home/tachidok/local/working/research/chapchom/
#+END_SRC

change it according to your working directory.

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

SciCell++ is released with a set of demos that show you some of its
main features. We recommend you to explore the demos section of the
documentation and the demos folder. Whenever you want to run a demo
just go to the demo folder which you are interested, create a folder
called ``RESLT`` if it is not already there and type ``./bin/``
followed by the name of the demo.

* **Example:** Lets say you want to run the Lotka-Volterra demo in the
  folder ``/demos/lotka_volterra/``, once you are in that folder
  create the ``RESLT`` folder where the output is stored (all the
  demos are configured to store its output in a folder with that name,
  if the folder does not exist then the output is not generated) and
  run the demo:

  .. code-block:: shell

     mkdir RESLT
     ./bin/demo_lotka_volterra

  Once the demo has started you should see output messages on the
  terminal with general information about the results of the
  computations. You can check the produced results in the ``RESLT``
  folder.

.. note:: Observe that some demos are equipped with Python or GNUPlot
          script to visualise the results. Try to run them as ``python
          <name-of-the-python-script.py>`` or ``gnuplot
          <name-of-the-gnu-script.gp>``.

Input arguments
^^^^^^^^^^^^^^^

Some demos require input arguments to run, if you try to run one of
those and pass nothing you will get a message indicating what you need
to pass. You can also check what input arguments a demo needs by
passing the ``--help`` or ``-h`` options at running time.

Create your ``private`` folder
------------------------------

Every user has its own private folder, use this folder to store all of
your work, in-development demos and any of your new developed features
for SciCell++. One of the first things that you should do in order to
start developing new features for SciCell++ is to create your private
folder, to do so follow theses instructions:

1. Open a terminal and go to the ``private`` folder of SciCell++ and
   typet the following (make sure to substitute ``john_cool`` by
   your name):

   .. code-block:: shell

      cd private
      mkdir john_cool
      cd john_cool

2. Update the ``CMakeLists.txt`` file in the private folder by adding
   your folder name at the end of the file as follow (make sure to
   substitute ``john_cool`` by your name):

   .. code-block:: shell

      ADD_SUBDIRECTORY(john_cool)

3. Run the ``autogen.sh`` script at the root folder of SciCell++ and
   make sure no problems are found. If there are any problem
   double-check that you added your folder inside the ``private``
   folder of SciCell++ and that you are modifying the correct
   ``CMakeLists.txt`` file.

Creating your own project
-------------------------

The easiest way to start a new project is to use a demo as a
template. For this example we are going to copy the demo driver
``demo_basic_interpolation.cpp`` from the folder
``demos/interpolation/basic_interpolation``.

1. Open a terminal and go to your private folder.

2. Type the following to copy the demo driver into your private folder:

   .. code-block:: shell

      cp ../../demos/interpolation/basic_interpolation/demo_basic_interpolation.cpp demo_john.cpp

3. Copy the ``CMakeLists.txt.private_template`` file from the
``tools`` folder into your private directory and change its name to
``CMakeLists.txt``

   .. code-block:: shell

      cp ../../tools/CMakeLists.txt.private_template CMakeLists.txt

4. Change the content of the ``CMakeLists.txt`` file as follow:

  * Change all the instances of the tag ``SRC_demo_john`` for your own
    tag to identify your source code. For example: ``SRC_project_sophy``.

  * Change all the instances of ``demo_john.cpp`` for the name of your
    source code file. For example: ``project_sophy.cpp``.

  * Change all the instances of ``demo_john``, this will be the name
    of your executable and the name you need to type at the terminal
    to compile your project. For example:``project_sophy``.
    
  * Change all the instances of the tag ``LIB_demo_john`` for your own
    tag to identify libraries required for your code. For example:
    ``LIB_project_sophy``.

  * Include the modules you need. In the template we only include the
    ``general_lib`` and the ``problem_lib`` modules. Check the
    :doc:`modules` document for the full list of module and their
    details.

5. Go to the root folder of SciCell++ and execute the ``./autogen.sh``
   script. If you find errors please make sure you correctly changed
   all the tags indicated in the previous step. Once building has
   finished without errors you can build your own project.

Building and executing your project
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Open a terminal and follow these instructions:

1. Go to the ``build`` folder in the root SciCell++ folder and type

   .. code-block:: shell
   
      make demo_sophy
      
   The building output should be displayed at your screen. Once no
   errors have been reported you may run your code.

2. Go to your ``private`` folder, create a ``RESLT`` folder if you
   have no one, and type:

   .. code-block:: shell

      ./bin/demo_sophy
                   
3. You should see the output of your project at the terminal.

.. important:: As you noticed, the generation and execution of your
               project is performed in two different folders:

               * the ``build`` folder (building)
               * your ``private`` folder (execution)

               We use this two-folders strategy to avoid cluttering
               the folder structure of SciCell++ with files
               automatically generated by CMake. By following this
               strategy we keep a clean folder structure for SciCell++
               and group all files generated by CMake in the ``build``
               folder. This help us to keep track for changes easily
               since we can exclude the whole ``build`` folder from
               the git repository.

               **Just keep in mind the following:**

               * Whenever you want to build your project you need to do so in the ``build`` folder, inthere just type ``make`` followed by the name of your project.

               * Whenever you want to execute your project go to your ``private`` folder and type ``./bin/the-name-of-your-project``.
            
Add your project to the ``demos`` folder
----------------------------------------

If you add a new feature to SciCell++ we encourage you to
:doc:`create_a_tutorial` and a demo showing these new features. Here
we detail the process to include your project as part of the demos of
SciCell++. We divide this process in two parts, the first one guides
you to create your folder and your validation files, the second part
shows you how to configure the SciCell++ to build and execute your
demo. In both sections we suppose that your demo is called
``demo_sophy``.

Create your demo and validation folder for your demo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The initial steps to include your demo as part of SciCell++ involve
create a folder in the SciCell++ demos folder structure and to
generate the validation files.

1. Execute your project and save its output into a file. We encorage
   you to execute it using single and double precision so that we have
   two different outputs. The files that you generate should be named:
   
   * ``validate_demo_sophy.dat`` for the single precision generated
     output.
   * ``validate_double_demo_sophy.dat`` for the double precision
     generated output.

2. Create a new folder into the ``demos`` folder structure. Use a name
   that captures the intent of your project.

   .. code-block:: shell

      mkdir <your-folder-name>

3. Add the following line at the end of the ``CMakeLists.txt`` file
   that lives at the same level of the folder that you created:
   
   .. code-block:: shell
      
      ADD_SUBDIRECTORY(your-folder-name)

4. Step into your demo folder and create a folder called
   ``validate``.

5. Copy the two output files (or copy all of them if you have more
   than two) generated at step 1 into the ``validate`` folder.

Configure SciCell++ to build and execute your demo
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once you have created your folder and copied the validation files
there you are ready to configure SciCell++ to build and execute your
demo.

1. Copy the source code for your project into your demo folder, in
   this case we suppose that the source code for your project is
   the file ``demo_sophy.cpp``.

2. Copy the ``CMakeLists.txt.demo_template`` from the ``/tools/``
   folder into your demo folder. Rename this file as
   ``CMakeLists.txt``.

3. Change the content of the ``CMakeLists.txt`` file as follow:
   
   * Change all the instances of the tag ``SRC_demo_john`` for your
     own tag to identify your source code. For example:
     ``SRC_demo_sophy``.

   * Change all the instances of ``demo_john.cpp`` for the name of
     your source code file. For example: ``demo_sophy.cpp``.

   * Change all the instances of ``demo_john``, this will be the name
     of your executable and the name you need to type at the terminal
     to compile your project. For example:``demo_sophy``.
     
   * Change all the instances of the tag ``LIB_demo_john`` for your
     own tag to identify libraries required for your code. For
     example: ``LIB_demo_sophy``.

   * Include the modules you need. In the template we only include the
     ``general_lib`` and the ``problem_lib`` modules. Check the
     :doc:`modules` document for the full list of module and their
     details.
    
4. In the same file perform the following changes in the ``Test
   section``.
   
   * Change all the instances of ``TEST_demo_john_run`` by the name of
     your demo. For example: ``TEST_demo_sophy_run``.

     .. important:: Make sure to keep the ``TEST`` and ``_run`` prefix
                    and postfix, respectively.
  
   * Change all the instances of ``demo_john`` with the name of your
     demo. For example: ``demo_sophy``.

   * Change all the instances of ``VALIDATE_FILENAME_demo_john`` with
     the name of your tag for the validation file. For example:
     ``VALIDATE_FILENAME_demo_sophy``.

   * Change the name of the validation file
     ``validate_double_demo_john.dat`` by yours. Recall that this file
     should store the output of your project executed using double
     precision. For example: ``validate_double_demo_sophy.dat``.

   * Change the name of the validation file ``validate_demo_john.dat``
     by yours. Recall that this file should store the output of your
     project executed using single double precision. For example:
     ``validate_demo_sophy.dat``.
  
   * Change all instances of ``TEST_demo_john_check_output`` with the
     name of your demo. For example: ``TEST_demo_sophy_check_output``.

   .. important:: Make sure to keep the ``TEST`` and ``_output``
                  prefix and postfix, respectively.

5. Make sure that the computations of your demo are stored in an
   output file. If the file that you generate is called differently
   than ``output_test.dat`` then modify any instance of that name in
   the ``CMakeLists.txt`` file.

6. Go to the root folder of SciCell++ and execute the ``./autogen.sh``
   script and enable the execution of the demos. If you find errors
   please make sure you correctly changed all the tags indicated in
   the previous steps. Your project should be automatically built,
   executed and validated.

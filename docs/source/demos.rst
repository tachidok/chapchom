Demos
=====

Examples and test cases
-----------------------

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

Current demos for specific functionalities
------------------------------------------

* Interpolation
* Linear solvers
* Matrices operations
* Newton's method
* Solution of ODE's
  * Lotka-Volterra solved with different time steppers
  * N-body problem (only 3-body and 4-body cases)
  * Explicit time steppers
  * Implicit time steppers (full implicit and *E(PC)^k E* implementations)
  * Adaptive time steppers

Here is some example text::

    make 'this'
    >> output

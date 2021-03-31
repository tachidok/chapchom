Differential Equations
======================

What are differential equations?
--------------------------------

* Move the solution of a differential equation ot other section
  * You may start by stating that a solution is a function and not a
    value

* In the section of why DE are important check the YouTube video
  https://youtu.be/p_di4Zn4wz4

A differential equation is any expression where a function :math:`y`
is related to its derivative [Strang2014]_, for example:

.. math::
   :label: eq_basic_differential_equation
   
   \begin{equation}
     \frac{d}{dt}y(t) = y(t)
   \end{equation}

This equation states that the change in the function :math:`y` with
respect to a change in the variable :math:`t` is equal to the function
itself evaluated at time :math:`t`. A solution for such equation
should be a function such that its derivative is the same function
:math:`y`.

A different way to think about a solution for that equation may be

  "what function has the property that its derivative is the very same
  function?", or "what function satisfy the relation given by
  :eq:`eq_basic_differential_equation`?"

A function with such properties is the exponential function
:math:`e^t`, therefore the solution for
:eq:`eq_basic_differential_equation` is:

.. math::
   
   \begin{equation}
     y(t) = e^t
   \end{equation}

If you do the maths, you will notice that the derivative of
:math:`e^t`, that is :math:`\frac{d}{dt} e^t= e^t`; and you are done.

Some more examples of differential equations are the following:

.. math::
   :label: eq_more_differential_equations
   
   \begin{align}
     \frac{d}{dt}y(t) &= 2ty(t)\\
     \frac{d}{dt}y(t) &= y(t)^2\\
     \frac{d}{dt}y(t) &= 3y(t)^2 \sin (t+y(t))\\
     \frac{d^2}{dt^2}y(t) &= \sin t + 3y(t) + \left( \frac{d}{dt}y(t) \right)^2\\
     \frac{d^3}{dt^3}y(t) &= e^{-y(t)} + t + \frac{d^2}{dt^2}y(t)
   \end{align}

Observe that differential equations may represent complex relations
between a function and its derivatives. Have a second look at the
previous equations, you will notice that there are relations regarding
the second and the third derivate of a function, expressed as
:math:`\frac{d^2}{dt^2}` and :math:`\frac{d^3}{dt^3}`,
respectively. You may find differential equations relating a function
with its :math:`n` derivate; which is expressed as
:math:`\frac{d^n}{dt^n}`.

Why are differential equations important?
-----------------------------------------

Differential equations are very useful to study a wide variety of
phenomena found in nature. Differential equations connect maths with
physics, biology and chemestry.

Differential equations describe changes

Differential equations are commonly used when it is easier to
describe changes on a phenomena rather than state why a phenome is at
a particular state.
           
.. important::

   It is a common practice to write the dependent function without its
   parameters, for example, :math:`y` is commonly used instead of
   :math:`y(t)`. Therefore the notation is simplified as
   :math:`\frac{dy}{dt}` instead of :math:`\frac{d}{dt}y(t)`. You
   should be careful that a similar notation may be used for dependant
   function with multiple parameters, for example, :math:`u(t, x)` may
   be wrote as :math:`u`. By now we will only deal with functions with
   one parameter.

Types of differential equations
-------------------------------

Differential equations can be classified according to its degree, its
number of variables, ...

**Ordinary Differential Equations vs Partial Differential Equations**
   
How to interpret a differential equation
----------------------------------------
           


References
----------

.. [Strang2014] Strang, G. (2014). Differential Equations and Linear
                Algebra. Wellesley, MA: Wellesley-Cambridge Press.

.. []
                

# Swig Python wrappers

This directory contains the [swig](http://swig.org) Python wrappers for the
Cartesian space objects. Swig builds the wrappers from the [space.i](space.i)
interface definition.


This has some differences from the manual and boost wrapped
versions. I have adapted the unit tests to have the same coverage
except where I needed to skip tests because of as yet unresolved
implementation differences.

The [Makefile](Makefile) is setup to wrap and build the _space.so
library. This can simply be imported directly when the interpreter is
run in this directory or setting the PYTHONPATH otherwise.

    $ python
    Python 2.7.5 (default, Mar  9 2014, 22:15:05) 
    [GCC 4.2.1 Compatible Apple LLVM 5.0 (clang-500.0.68)] on darwin
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import space
    >>> foo = space.space(1,2,3)
    >>> repr(foo)
    ‘(1, 2, 3)’
    >>>





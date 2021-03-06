# Manual Python wrappers

This directory contains the Python wrappers for the Cartesian space
objects.  It is built directly as described in the documentation
[Extending Python with C or
C++](https://docs.python.org/2/extending/extending.html). Here I
created setup.py and built it with Python using the command:

    python setup.py build

setup.py assumes libSpace.dylib is built and located in ../../libSpace.
This can be changed by setting the CARTESIAN_LIBRARY_PATH environment
variable. See [setenv.sh](setenv.sh) for details.

Once built you will need to add the module to your Python path to use.
setenv.sh show some examples of how I set this on my iMac during
development.

pylaunch.sh will start an interpreter to test with.

    $ ./pylaunch.sh
    Python 2.7.1 (r271:86832, Jul 31 2011, 19:30:53)
    [GCC 4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2335.15.00)] on darwin
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import space
    >>> a = space.space(1, 2, 3)
    >>> a
    (1, 2, 3)
    >>>


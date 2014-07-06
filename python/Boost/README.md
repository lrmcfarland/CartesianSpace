# Boost python wrappers

This directory contains the [boost](http://www.boost.org/) generated
python wrappers for the Cartesian space object. Boost builds the
python module from the Boost.Python wrapper, in this case
[boost_space_module.cpp](boost_space_module.cpp). This does not use
[bjam](https://wiki.python.org/moin/boost.python/BuildingExtensions)
as described in the
[tutorial](http://www.boost.org/doc/libs/1_55_0/libs/python/doc/tutorial/doc/html/index.html). Instead
I found it simpler to create setup.py directly and have it build like other
python modules:

   python setup.py build

setup.py assumes libSpace.dylib is built and located in ../../libSpace.
This can be changed by setting the CARTESIAN_LIBRARY_PATH environment
variable. See the [Makefile](Makefile) for details.

Once built you will need to add the module to your python path to use.
setenv.sh shows some examples of how I set this on my iMac during
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

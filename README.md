# Cartesian Space

## Superseded by [Coordinates](https://github.com/lrmcfarland/Coordinates)

## Features

This is my take on creating a Cartesian three space vector for use in
physics applications as a full featured C++ object. It has only three
doubles as the data members for x, y and z, but makes full use of
namespace,
[Cartesian](http://en.wikipedia.org/wiki/Cartesian_coordinate_system),
const correct accessors and a variety of constructors, including copy
and copy assign, that can build or modify the space object. All of the
appropriate math operators, their commuted and in place variants are
overloaded to support vector arithmetic. Additional functions
including the dot and cross products, rotation operations as well as
the output operator<<() are supported.

I have used this to investigate how far I can push C++ features
like operator overloading by [extending
Python](https://docs.python.org/2/extending/extending.html) directly
and using the [boost](http://www.boost.org) and
[swig](http://www.swig.org) tools. I created similar unit tests for
each using the skip decorator when there was a feature that was not
supported or one I haven't yet figured out how to implement with that
tool.


## Build

Each directory has its own Makefile with 'build', 'test', and 'clean'
targets, e.g.

```
$ pwd
/Users/.../libSpace
$ make clean
$ make test
```

libSpace must be built first. There is a build.sh script that runs
the Makefiles in all the directories in the necessary order and takes
these targets as command line arguments.

```
$ pwd
/Users/.../CartesianSpace
$ ./build.sh clean
$ ./build.sh test
```

Each directory also has a suite of unit tests. libAngles uses
[gtest](https://code.google.com/p/googletest/). The Python
modules use Python native unittest.

To build the Boost wrappers you will, of course, need to install
[Boost](http://www.boost.org).

### [googletest](https://code.google.com/p/googletest/)

The C++ library uses [googletest](https://code.google.com/p/googletest/) to
run the unit tests. I have downloaded and built it in /usr/local by
following the instructions in the README

```
[root gtest-1.7.0]# export GTEST_DIR=/usr/local/gtest-1.7.0
[root gtest-1.7.0]# g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc

[root@lrmz-iMac gtest-1.7.0]# ar -rv libgtest.a gtest-all.o
ar: creating archive libgtest.a
a - gtest-all.o
```

libSpace/Makefile sets its GTEST_DIR to /usr/local/gtest-1.7.0 and picks
up libgtest.a from there.

### [Boost](http://www.boost.org)

I have been wanting to use [homebrew](http://brew.sh) to install
boost, but some reason, I find it does not yet install
libboost_python.a by default or even with the --with-python or
--build-from-source options. So I built and installed it from source.

```
cd boost_1_56_0

./bootstrap.sh
./b2
sudo ./b2 install
```

The files are now in /usr/local/include and /usr/local/lib/libboost_*
and python/Boost/setup.py sets BOOST_ROOT to point there.
brew doctor will notice and complain about this.


### OSX

I built this on my iMac using the g++ compiler that comes with
[Xcode](https://developer.apple.com/xcode/), but there is nothing special
that should cause a problem for other compilers.

### Linux

TODO


## Use

### C++

See [libSpace/example1.cpp](libSpace/example1.cpp).

```
// ============================================================
// Filename:    example1.cpp
//
// Description: Example of using libSpace
//
// Authors:     L.R. McFarland
// Created:     2014oct25
// ============================================================

#include <iostream>
#include <math.h>

#include <space.h>

int main () {

  Cartesian::space s1(10);
  Cartesian::space s2(0, 10);
  Cartesian::space s3;

  std::cout << "s1 = " << s1 << std::endl;
  std::cout << "s2 = " << s2 << std::endl;

  s3 = Cartesian::cross(s1, s2);

  std::cout << "s1 x s2 = " << s3 << std::endl;

  return 0;
}

```

This has its own make target "example1"

```
$ make example1
g++ -g -W -Wall -fPIC -I.   -c -o example1.o example1.cpp
g++ example1.o -o example1 -L. -lspace
$ ./example1.sh
# CARTESIAN_SPACE_ROOT not set. Using ..
s1 = <space><x>10</x><y>0</y><z>0</z></space>
s2 = <space><x>0</x><y>10</y><z>0</z></space>
s1 x s2 = <space><x>0</x><y>0</y><z>100</z></space>

```


### Python

Use the pylaunch.sh script to set the environment varialbes.


```
$ pwd
/Users/.../CartesianSpace/python/Boost
$ ./pylaunch.sh

>>> import space
>>> s1 = space.space(1)
>>> s2 = space.space(0, 1)
>>> s3 = space.cross(s1, s2)
>>> print s1, " x ", s2, " = ", s3
<space><x>1</x><y>0</y><z>0</z></space>  x  <space><x>0</x><y>1</y><z>0</z></space>  =  <space><x>0</x><y>0</y><z>1</z></space>

```

In python/Manual, repr() is different from str() as an
alternative to the XML output.

```
$ pwd
/Users/.../CartesianSpace/python/Manual
$ ./pylaunch.sh

>>> import space
>>> s1 = space.space(1)
>>> s2 = space.space(0, 1)
>>> s3 = space.cross(s1, s2)
>>> print repr(s1), " x ", repr(s2), " = ", repr(s3)
(1, 0, 0)  x  (0, 1, 0)  =  (0, 0, 1)

```


## TODO

### Manual

- TBD

### Boost

- rich comparison operators

## About

This is a submodule of my space craft simulation program Orbits. The
C++ model can either display the simulation in 3D with OpenGL or
investigate derived properties like distance from another body, fuel,
speed or angular momentum over time, by using the Python wrappers to
extract the features of interest, with out having to re-code the
simulation.

Demos are available on my web-site [starbug.com](http://starbug.com)

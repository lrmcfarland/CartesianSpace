# Comparing python wrappers

This is my comparison of python wrapper generators for my C++ space
object.  Naturally, not all of the C++ features are supported by
python, for example overloading operator*(space, double). Unit tests
for this are present but skipped.

## Manual

[Extending Python with C or
C++](https://docs.python.org/2/extending/extending.html) is
official way to extend python with C++ and the most feature complete,
but a lot of work for even a small module like this.


## Boost

[Boost](http://www.boost.org/) provides a [python wrapper
generator](http://www.boost.org/doc/libs/1_55_0/libs/python/doc/tutorial/doc/html/index.html)
that takes a lot of the fight out of the wrapping, but I am still
looking into how to do features like operator==() and repr() distinct
from str().

## Swig

[swig](http://swig.org) python wrappers has an extensions feature that
I can use to re-implement operator==() and repr() distinct from str(),
but I have not found a way to directly access the static data members
Uo, Ux, Uy, and Uz. Adding methods should provide reasonable a work
around. Also I do not see a way to make x, y and z look like
properties the way I can with Boost or manually. They must be accessed
through the x(), y() and z() accessors.

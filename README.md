# Cartesian Space

This is my take on creating a Cartesian three space vector for use in
physics applications as a full featured C++ object. It has only three
doubles as the data members for x, y and z, but makes full use of
namespace (Cartesian), const correct accessors and a variety of
constructors, copy and copy assign, that can build or modify the space
(vector) object from doubles or strings.  All of the appropriate math
operators, their commuted and in place variants are overloaded to
support vector arithmetic. Additional functions including the dot and
cross products, rotation operations as well as the output operator<<()
are supported.

    Cartesian::space F;
    double m(0.25); // kg
    Cartesian::space a(0, 0, -9.81); // m/s2

    F = m * a;

    std::cout << "The force on the apple is " << F << " Newtons" << std::endl;

A full set of examples can be found in [space_unittest.cpp](libSpace/space_unittest.cpp).

I have also use this to investigate how to wrap this in python using
various tools to see what limitations in porting each tool has (mostly
due to things C++ supports but python doesn't, like constructor
overloading). First manually by creating a new python type in
[space.cpp](python/Manual/space.cpp), then using boost wrappers
generated in the [space module](python/Boost/boost_space_module.cpp)
and finally swig with [space.i](python/Swig/space.i)

These each has a full suite of unit tests to serve as examples.

This is used as a submodule of my space craft simulation program
Orbits. The C++ model can either display the simulation in 3D with
OpenGL or analyze properties on using the python wrappers to extract
the features of interest, like distance from another body, fuel, speed
or angular momentum over time, with out having to re-code the
simulation.

Demos are available on my web-site [starbug.com](http://starbug.com)


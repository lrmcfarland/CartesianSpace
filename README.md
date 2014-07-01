# CartesianSpace

This is my take on creating a Cartesian three space vector for use in
physics applications as a full featured C++ object. It has only three
doubles as the data members for x, y and z. There are a variety of
accessors and constructors that can build or modify the space (vector)
object from doubles or strings as well as from the copy and copy
assign constructors. All of the math operators, their commuted and in
place variants are overloaded to support vector arithmetic. Additional
functions including the dot and cross products, rotation opertions as
well as the output operator<<() are supported.

    Cartesian::space F;
    double m(0.25); // kg
    Cartesian::space a(0, 0, -9.81); // m/s2

    F = m * a;

    std::cout << "The force on the apple is " << F << " Newtons" << std::endl;

A full set of examples can be found in lib/Space/space_unittest.cpp.

I have also wrapped this in python both manually by creating a new
python type (see python/Manual/space.cpp), by using swig
(python/Swig/space.i) and boost (see python/Boost/boost_space_module.cpp).

These each has a full suite of unit tests to serve as examples.

This is used as a submodule of my space craft simulation program
Orbits. The C++ model can either display the simulation in OpenGL
with Qt or analyze the results using the python wrappers to extract
the features of interest, like speed or angular momentum over time.

Demos are available on my web-site http://starbug.com


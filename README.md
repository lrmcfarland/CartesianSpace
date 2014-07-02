# Cartesian Space

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

    Cartesian::space F;
    double m(0.25); // kg
    Cartesian::space a(0, 0, -9.81); // m/s2

    F = m * a;

    std::cout << "The force on the apple is " << F << " Newtons" << std::endl;

I have also use this to investigate how far I can push C++ features
like operator overloading by [extending
python](https://docs.python.org/2/extending/extending.html) directly
and using the [boost](http://www.boost.org) and
[swig](http://www.swig.org) tools. I created similar unit tests for
each using the skip decorator when there was a feature that was not
supported or one I haven't yet figured out how to implement with that
tool.

This is a submodule of my space craft simulation program Orbits. The
C++ model can either display the simulation in 3D with OpenGL or
investigate derived properties like distance from another body, fuel,
speed or angular momentum over time, by using the python wrappers to
extract the features of interest, with out having to re-code the
simulation.

Demos are available on my web-site [starbug.com](http://starbug.com)


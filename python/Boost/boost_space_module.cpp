// ==========================================================================
// Filename:    boost_space_module.cpp
// Description: Contains the python wrappers for the Cartesian::space objects
//              using boost and python.
//
// Author:      L.R. McFarland
// Created:     2013jun17
// ==========================================================================

#include <boost/python.hpp>

#include "space.h"

using namespace boost::python;

// overload wrappers.
void (Cartesian::space::*setx)(const double&) = &Cartesian::space::x;
void (Cartesian::space::*sety)(const double&) = &Cartesian::space::y;
void (Cartesian::space::*setz)(const double&) = &Cartesian::space::z;

BOOST_PYTHON_MODULE(space) {

  class_<Cartesian::space>("space")

    // static members
    .def_readonly("Uo", &Cartesian::space::Uo)
    .def_readonly("Ux", &Cartesian::space::Ux)
    .def_readonly("Uy", &Cartesian::space::Uy)
    .def_readonly("Uz", &Cartesian::space::Uz)

    // constructors
    .def(init<>()) // default
    .def(init<Cartesian::space>()) // copy

    .def(init<double>()) // x
    .def(init<double, double>()) // x, y
    .def(init<double, double, double>()) // x, y, z

    // accessors
    .def("getX", &Cartesian::space::getX)
    .def("setX", setx)
    .add_property("x", &Cartesian::space::getX, setx)

    .def("getY", &Cartesian::space::getY)
    .def("setY", sety)
    .add_property("y", &Cartesian::space::getY, sety)

    .def("getZ", &Cartesian::space::getZ)
    .def("setZ", setz)
    .add_property("z", &Cartesian::space::getZ, setz)

    // operator<<(), str not repr
    .def(self_ns::str(self_ns::self))

    // operators
    .def(self + Cartesian::space())
    .def(Cartesian::space() + self)

    .def(self - Cartesian::space())
    .def(Cartesian::space() - self)

    .def(self * Cartesian::space())
    .def(Cartesian::space() * self)

    .def(self / double()) // scale

    // other methods
    .def("magnitude", &Cartesian::space::magnitude)
    .def("normalized", &Cartesian::space::normalized)


    ; // end of class_

  // functions
  def("cross", Cartesian::cross);
  def("dot", Cartesian::dot);


};

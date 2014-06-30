// ================================================================
// Filename:    space.i
//
// Description: Defines the swig wrappers for a space class for use
//              with physics applications.  Implemented as classic
//              Cartesian three space coordinates.  This file is part
//              of lrm's Orbits software library.
//
//              ASSUMES angles are in radians
//
// Author:      L.R. McFarland, lrm@starbug.com
// Created:     2014 Jun 29
// Language:    swig
//
//  Orbits is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Orbits is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Orbits.  If not, see <http://www.gnu.org/licenses/>.
// ================================================================

// TODOs
// 1) wrappers for static consts Ux, Uy, Uz, Uo
// 2) make accessors look like properties, e.g. space a.x not a.x(), a.x = 4.0 not a.x(4.0)
// 3) mixed operators like space * double
//

%module space
%{
#include "space.h"
%}

namespace Cartesian {

  class space{
  public:

    // TODO consts
    %immutable;
    space Uo; // TODO compiles but not working
    %mutable;

    // constructors
    space();
    space(double x);
    space(double x, double y);
    space(double x, double y, double z);
    ~space();

    // accessors
    void x(double a);
    double x();

    void y(double a);
    double y();

    void z(double a);
    double z();

    %extend {
      // from http://www.swig.org/Doc1.3/SWIGPlus.html#SWIGPlus_class_extension

      char* __str__() {
	static char temp[1024]; // TODO std::string?
	sprintf(temp, "<space><x>%.12g</x><y>%.12g</y><z>%.12g</z></space>",
		$self->x(), $self->y(), $self->z()); // TODO precision
	return &temp[0];
      }

      char* __repr__() {
	static char temp[1024]; // TODO std::string?
	sprintf(temp, "(%.12g, %.12g, %.12g)", $self->x(), $self->y(), $self->z()); // TODO precision
	return &temp[0];
      }
    }

    // operators

    %rename(__eq__) operator==;
    %rename(__ne__) operator!=;

    %rename(__add__) operator+;
    %rename(__iadd__) operator+=;

    %rename(__sub__) operator-;
    %rename(__isub__) operator-=;

    // TODO multiply and divide by doubles

    // other methods
    double magnitude();
    double magnitude2();
    space normalized();


  };

  // functions
  space cross(const space& a, const space& b);
  double dot(const space& a, const space& b);

  // extensions

  %extend space {
    bool __eq__(const space& rhs) {
      Cartesian::space result;
      return *$self == rhs;
    }

    bool __ne__(const space& rhs) {
      Cartesian::space result;
      return *$self != rhs;
    }

    space __add__(const space& rhs) {
      Cartesian::space result;
      return *$self + rhs;
    }

    const space& __iadd__(const space& rhs) {
      *$self += rhs;
      return *$self;
    }

    space __sub__(const space& rhs) {
      Cartesian::space result;
      return *$self - rhs;
    }

    const space& __isub__(const space& rhs) {
      *$self -= rhs;
      return *$self;
    }


  } // end extend space



} // end namespace Cartesian

// ==================================================================
// Filename:    space.cpp
// Description: Implements the space class
//              Assumes angles are in radians
// Author:      L.R. McFarland, lrm@starbug.com
// Created:     4 Feb 1999
// Language:    C++
//
//  This file is part of lrm's Orbits software library.
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
// ==================================================================


#include <stdlib.h>  /* strtod */
#include <space.h>

// stand-ins until c++ 11
double Cartesian::stod(const std::string& a_string) {
  // TBD better conversion
  // doesn't catch syntax errors
  // TBD no worse than m_current_x = atof(m_current_characters.c_str());
  double a_double;

#if 0
  // this will error on bad strings
  // Value of: 0
  // Expected: d.x()
  // Which is: 2.1651736027593485e-314
  // space_unittest.cpp:71: Failure
  // Value of: 0
  // Expected: e.x()
  // Which is: 6.9289207366834453e-310
  // space_unittest.cpp:74: Failure
  // Value of: 0
  // Expected: f.x()
  // Which is: 2.1651736027593485e-314
  std::stringstream(a_string) >> a_double;
#else
 a_double = strtod(a_string.c_str(), NULL);
#endif

  return a_double;
}

// TODO needed?
int Cartesian::stoi(const std::string& a_string) {
  int an_int;
  std::stringstream(a_string) >> an_int;
  return an_int;
}


// -----------------------
// ----- class space -----
// -----------------------

// ----- static data members -----

const double Cartesian::space::epsilon(1e-16); // TODO from build

const Cartesian::space Cartesian::space::Uo(0,0,0);
const Cartesian::space Cartesian::space::Ux(1,0,0);
const Cartesian::space Cartesian::space::Uy(0,1,0);
const Cartesian::space Cartesian::space::Uz(0,0,1);

const std::string Cartesian::space::zeroString("0.0");

// ----- constructor from string for building from xml ----
Cartesian::space::space(const std::string& a,
			const std::string& b,
			const std::string& c)
  : m_x(0), m_y(0), m_z(0) {

  // TODO this will not throw exceptions on strings with out number, 
  // it will just set the value to 0. With C++ 11 use std::stod(a);
  // and catch std::invalid_argument

  m_x = Cartesian::stod(a);
  m_y = Cartesian::stod(b);
  m_z = Cartesian::stod(c);
}

// ----- methods -----

const Cartesian::space Cartesian::operator+(const Cartesian::space& lhs,
					    const Cartesian::space& rhs) {
  return Cartesian::space(lhs.x() + rhs.x(),
			  lhs.y() + rhs.y(),
			  lhs.z() + rhs.z());
}

const Cartesian::space Cartesian::operator-(const Cartesian::space& lhs,
					    const Cartesian::space& rhs) {
  return Cartesian::space(lhs.x() - rhs.x(),
			  lhs.y() - rhs.y(),
			  lhs.z() - rhs.z());
}

// scale
const Cartesian::space Cartesian::operator*(const Cartesian::space& lhs,
					    const double& rhs) {
  return Cartesian::space(lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs);
}

const Cartesian::space Cartesian::operator*(const double& lhs,
					    const Cartesian::space& rhs) {
  return Cartesian::operator*(rhs, lhs);
}

const Cartesian::space Cartesian::operator/(const Cartesian::space& lhs,
					    const double& rhs)
  throw (DivideZeroError) {
  if (rhs == 0)
    throw DivideZeroError("Cartesian::space::operator/() divide by zero.");
  return Cartesian::space(lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs);
}

const Cartesian::space Cartesian::operator/(const double& lhs,
					    const Cartesian::space& rhs)
  throw (DivideZeroError) {
  if (rhs.x() == 0 || rhs.y() == 0 || rhs.z() == 0)
    throw DivideZeroError("Cartesian::space::operator/() divide by zero.");
  return Cartesian::space(lhs / rhs.x(), lhs / rhs.y(), lhs / rhs.z());
}

// ----- vector products -----

double Cartesian::operator*(const Cartesian::space& lhs,
			    const Cartesian::space& rhs) {
  return lhs.x()*rhs.x() + lhs.y()*rhs.y() + lhs.z()*rhs.z();
}

double Cartesian::dot(const Cartesian::space& lhs,
		      const Cartesian::space& rhs) {
  return lhs * rhs;
}

Cartesian::space Cartesian::cross(const Cartesian::space& a,
				  const Cartesian::space& b) {
  Cartesian::space tmp;
  tmp.x(a.y()*b.z() - a.z()*b.y());
  tmp.y(a.z()*b.x() - a.x()*b.z());
  tmp.z(a.x()*b.y() - a.y()*b.x());
  return tmp;
}

// ----- set using polar coordinates -----

void Cartesian::space::setUsingPolarCoords(double radius,
					   double theta,
					   double phi) {
  /// ASSUMES: angles in radians
  // theta: angle in the x-y plane
  // phi: polar angle (from the z axis)
  x(radius * sin(phi) * cos(theta));
  y(radius * sin(phi) * sin(theta));
  z(radius * cos(phi));
}

// -------------------------
// ----- class rotator -----
// -------------------------

Cartesian::rotator::rotator(const Cartesian::space& a_axis) :
  m_axis(a_axis),
  m_rotation_matrix(3, std::vector<double>(3, 0)),
  m_is_new_axis(true),
  m_old_radians(0.0)
{}


Cartesian::rotator::rotator(const Cartesian::rotator& rhs) :
  m_axis(rhs.axis()),
  m_rotation_matrix(rhs.m_rotation_matrix),
  m_is_new_axis(rhs.m_is_new_axis)
{} // TBD test this

// TODO use swap http://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)
Cartesian::rotator&
Cartesian::rotator::operator=(const Cartesian::rotator& rhs) {
  if (this == &rhs) return *this;
  axis(rhs.axis());
  m_rotation_matrix = rhs.m_rotation_matrix;
  m_is_new_axis = rhs.m_is_new_axis;
  return *this;
} // TBD test this



void Cartesian::rotator::axis(const Cartesian::space& a_axis) {
  if (a_axis != m_axis) {
    m_axis = a_axis;
    m_is_new_axis = true;
  }
}

Cartesian::space Cartesian::rotator::rotate(const Cartesian::space& a_heading,
					    const double& a_radians) {

  if (m_is_new_axis || m_old_radians != a_radians) {

    double c(cos(a_radians));
    double s(sin(a_radians));

    Cartesian::space normal(axis().normalized());

    double t(1-c);

    m_rotation_matrix[0][0] = c + normal.x()*normal.x()*t;
    m_rotation_matrix[1][1] = c + normal.y()*normal.y()*t;
    m_rotation_matrix[2][2] = c + normal.z()*normal.z()*t;

    double t1(normal.x()*normal.y()*t);
    double t2(normal.z()*s);

    m_rotation_matrix[1][0] = t1 + t2;
    m_rotation_matrix[0][1] = t1 - t2;

    t1 = normal.x()*normal.z()*t;
    t2 = normal.y()*s;

    m_rotation_matrix[2][0] = t1 - t2;
    m_rotation_matrix[0][2] = t1 + t2;

    t1 = normal.y()*normal.z()*t;
    t2 = normal.x()*s;

    m_rotation_matrix[2][1] = t1 + t2;
    m_rotation_matrix[1][2] = t1 - t2;

    m_is_new_axis = false;
    m_old_radians = a_radians;

  }

  Cartesian::space tmp(m_rotation_matrix[0][0]*a_heading.x() +
	    m_rotation_matrix[0][1]*a_heading.y() +
	    m_rotation_matrix[0][2]*a_heading.z(),
	    m_rotation_matrix[1][0]*a_heading.x() +
	    m_rotation_matrix[1][1]*a_heading.y() +
	    m_rotation_matrix[1][2]*a_heading.z(),
	    m_rotation_matrix[2][0]*a_heading.x() +
	    m_rotation_matrix[2][1]*a_heading.y() +
	    m_rotation_matrix[2][2]*a_heading.z());

  return tmp;

}


// =========================
// ===== SpaceRecorder =====
// =========================

const unsigned int Cartesian::SpaceRecorder::default_size(1024);

Cartesian::SpaceRecorder::SpaceRecorder(const unsigned int& a_size_limit) :
  m_size_limit(a_size_limit),
  m_data(std::deque<Cartesian::space>(m_size_limit))
{}

Cartesian::SpaceRecorder::SpaceRecorder(const Cartesian::SpaceRecorder& a):
  m_size_limit(a.sizeLimit()),
  m_data(a.m_data)
{}

// TODO use swap http://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)
Cartesian::SpaceRecorder&
Cartesian::SpaceRecorder::operator=(const Cartesian::SpaceRecorder& rhs) {
  if (this == &rhs) return *this;
  sizeLimit(rhs.sizeLimit());
  m_data = rhs.m_data;
  return *this;
}

void Cartesian::SpaceRecorder::push(Cartesian::space a) {
  // even up the sizes to just under the limit.
  while (m_data.size() > sizeLimit() - 1)
    m_data.pop_front();
  m_data.push_back(a);
}

// output compatible for R frames <- read.table(flnm)
void Cartesian::SpaceRecorder::write2R(const std::string& flnm, bool skip_Uo) {

  std::ofstream ssfile(flnm.c_str());

  if (!ssfile.is_open()) {
    std::stringstream err;
    err << "Error: unable to open file \"" << flnm << "\"";
    throw Cartesian::SpaceRecorderIOError(err.str());
  }

  ssfile << "# Formated for R frames <- read.table(" << flnm << ")"
	 << std::endl;
  ssfile << "x y z" << std::endl;

  for (unsigned int k = 0; k < m_data.size(); ++k) {

    // skip zero points from partially filled buffer.
    if (skip_Uo and m_data[k] == Cartesian::space::Uo)
      continue;

    ssfile << k << " "
	   << m_data[k].x() << " "
	   << m_data[k].y() << " "
	   << m_data[k].z() << std::endl;
  }

  ssfile.close();

}



// EOF

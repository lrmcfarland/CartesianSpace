// ================================================================
// Filename:    space.h
// Description: Defines space class for Orbits applications.
//              Implemented as classic Cartesian three space coordinates.
//
//              ASSUMES angles are in radians
//
// Author:      L.R. McFarland, lrm@starbug.com
// Created:     12 May 2004
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
// ================================================================

#pragma once

#include <cmath>
#include <deque>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace Cartesian {

  class SpaceError : public std::runtime_error {
  public:
  SpaceError(const std::string& msg) : std::runtime_error(msg) {}
  };

  class DivideZeroError : public SpaceError {
  public:
  DivideZeroError(const std::string&  msg) : SpaceError(msg) {}
  };

  class SpaceRecorderIOError : public SpaceError {
  public:
  SpaceRecorderIOError(const std::string& msg) : SpaceError(msg) {}
  };

  // TODO stand-ins until c++ 11
  double stod(const std::string& a_string);
  int    stoi(const std::string& a_string);

  // -----------------------
  // ----- class space -----
  // -----------------------

  class space {
  public:

    // ----- unit vectors -----

    static const double epsilon; // machine epsilon for this build.

    static const space Uo; // zero
    static const space Ux;
    static const space Uy;
    static const space Uz;

    static const std::string zeroString;

    // ----- ctor and dtor -----

    explicit space(double a = 0.0, double b = 0.0, double c = 0.0)
      : m_x(a), m_y(b), m_z(c) {}; // ctors, including default.

    explicit space(const std::string& a, // The ambiguity is in the box.
		   const std::string& b=zeroString,
		   const std::string& c=zeroString);

    ~space() {};

    inline space(const space& a);
    inline space& operator=(const space& rhs);

    // ----- accessors -----

    void          x(const double& rhs) {m_x = rhs;}
    const double& x() const            {return m_x;}
    double        getX() const         {return m_x;} // for python wrappers, no const return

    void          y(const double& rhs) {m_y = rhs;}
    const double& y() const            {return m_y;}
    double        getY() const         {return m_y;} // for python wrappers, no const return

    void          z(const double& rhs) {m_z = rhs;}
    const double& z() const            {return m_z;}
    double        getZ() const         {return m_z;} // for python wrappers, no const return

    // ----- bool operators -----

    inline bool operator== (const space& rhs) const;
    inline bool operator!= (const space& rhs) const;

    // ----- assignment operators -----

    inline space& operator+=(const space& rhs);
    inline space& operator-=(const space& rhs);

    inline space& operator*=(const double& rhs); // scale
    inline space& operator/=(const double& rhs) throw (DivideZeroError);

    // ----- other methods -----

    void zero() {x(0.0); y(0.0); z(0.0);};

    inline double magnitude()  const;
    inline double magnitude2() const;

    inline space  normalized() const throw (DivideZeroError);

    // TODO more
    void setUsingPolarCoords(double radius, double theta, double phi = M_PI/2);

  private:

    // ----- data members -----

    double m_x, m_y, m_z;

  };

  // ---------------------------------------------------
  // ----- inline implementations of space methods -----
  // ---------------------------------------------------

  // copy constructor
  inline space::space(const space& a) {
    m_x = a.x();
    m_y = a.y();
    m_z = a.z();
  };

  // copy assignment
  inline space& space::operator=(const space& rhs) {
    if (this == &rhs) return *this;
    m_x = rhs.x();
    m_y = rhs.y();
    m_z = rhs.z();
    return *this;
  }

  // ----- bool operators -----

  inline bool space::operator== (const space& rhs) const {
    return x() == rhs.x() && y() == rhs.y() && z() == rhs.z();
  }

  inline bool space::operator!= (const space& rhs) const {
    return !operator==(rhs);
  }

  // ----- assignment operators -----

  inline space& space::operator+=(const space& rhs) {
    m_x += rhs.x();
    m_y += rhs.y();
    m_z += rhs.z();
    return *this;
  }

  inline space& space::operator-=(const space& rhs) {
    m_x -= rhs.x();
    m_y -= rhs.y();
    m_z -= rhs.z();
    return *this;
  }

  inline space& space::operator*=(const double& rhs) {
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
    return *this;
  }

  inline space& space::operator/=(const double& rhs) throw (DivideZeroError) {
    if (rhs == 0)
      throw DivideZeroError("space::operator/=(const double& rhs) "
			    "attempted divide by zero.");
    m_x /= rhs;
    m_y /= rhs;
    m_z /= rhs;
    return *this;
  }

  // ----- normalizing -----

  inline double space::magnitude() const {
    return sqrt(magnitude2());
  }

  inline double space::magnitude2() const {
    return m_x*m_x + m_y*m_y + m_z*m_z;
  }

  inline space space::normalized() const throw (DivideZeroError) {
    const double h(magnitude());
    return space(m_x/h, m_y/h, m_z/h);
  }

  // ---------------------
  // ----- functions -----
  // ---------------------

  const space operator+ (const space& lhs, const space& rhs);
  const space operator- (const space& lhs, const space& rhs);

  // explicit double cast to force scale and not dot product of default space ctor.
  const space operator* (const space& lhs, const double& rhs); // scale
  const space operator* (const double& lhs, const space& rhs); // scale

  const space operator/ (const space& lhs, const double& rhs) throw (DivideZeroError); // scale
  const space operator/ (const double& lhs, const space& rhs) throw (DivideZeroError); // scale

  // vector products
  double operator* (const space& lhs, const space& rhs); // dot product
  double dot(const space& a, const space& b);  // vector dot product
  space cross(const space& a, const space& b);  // vector cross product

  // operator<<
  inline std::ostream& operator<< (std::ostream& os, const space& a) {
    os << "<space><x>" << a.x()
       << "</x><y>" << a.y()
       << "</y><z>" << a.z()
       << "</z></space>";
    return os;
  }


  // -------------------------
  // ----- class rotator -----
  // -------------------------

  // supports rotating space vectors about space axies.

  class rotator {
  public:

    // angle conversions
    static double deg2rad(const double& deg) {return deg*M_PI/180.0;}
    static double rad2deg(const double& rad) {return rad*180.0/M_PI;}

    rotator(const space& a_axis); // ctor, no default
    ~rotator() {}; // dtor

    rotator(const rotator& a); // copy ctor
    rotator& operator=(const rotator& rhs); // assignment ctor

    const space& axis() const              {return m_axis;}
    void         axis(const space& a_axis);

    space rotate(const space& a_heading, const double& a_radians);

  private:

    space                              m_axis;
    std::vector< std::vector<double> > m_rotation_matrix;

    // for optimization
    bool                               m_is_new_axis;
    double                             m_old_radians;

  };


  // -------------------------------
  // ----- class SpaceRecorder -----
  // -------------------------------

  // implements a simple deque to store three space data.
  // It is intended for use to store and later plotting positions and
  // other three space data.

  class SpaceRecorder {

  public:

    static const unsigned int default_size; /// default size limit for deque

    SpaceRecorder(const unsigned int& a_size_limit=SpaceRecorder::default_size);
   ~SpaceRecorder() {}; // dtor

    SpaceRecorder(const SpaceRecorder& a);   // copy ctor
    SpaceRecorder& operator=(const SpaceRecorder& a); // copy assignment

    const unsigned int& sizeLimit() const       {return m_size_limit;}
    void                sizeLimit(const int& a) {m_size_limit = a;}

    unsigned long size() const            {return m_data.size();}
    const space& get(const unsigned int& idx) {return m_data[idx];}

    void push(space a);
    void clear() {m_data.clear();}

    void write2R(const std::string& flnm, bool skip_Uo=true);

  private:

    unsigned int       m_size_limit; /// size limit of position deque

    std::deque<space>  m_data;       /// data deque


  };

} // end namespace Cartesian

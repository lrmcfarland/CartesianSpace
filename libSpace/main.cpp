// ============================================================
// Filename:    main.cpp
// Description: An example of a test harness for space object
// Author:      L.R. McFarland lrm@starbug.com
// Created:     05 Apr 2005
//
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
// ============================================================

#include <getopt.h>
#include <iostream>
#include <sstream>
#include <space.h>

int main(int argc, char* argv[]) {

  // ------------------------------------------
  // ----- process command line arguments -----
  // ------------------------------------------

  int    opt;
  bool   hasError(false);

  std::stringstream usage;
  usage << "Usage: " << argv[0] << " ";

  while ((opt = getopt(argc, argv, "")) != -1) {

    switch(opt) {

    case ':':       /* -o without operand */
      std::cerr << "Option -" << (char) optopt << " requires an operand."
		<< std::endl;
      hasError = true;
      break;

    case '?':
      std::cerr << "Unrecognized option: -" << (char) optopt << std::endl;
      hasError = true;
      break;

    }

  }

  if (hasError) {
    std::cerr << usage.str() << std::endl;
    return -1;
  }

  // --------------------
  // ----- run test -----
  // --------------------

  const double a( 3.0);   // TBD use other numbers
  const double b(-4.0);   // TBD use other numbers
  const double c( 5.0);   // TBD use other numbers

  const double tol(1.0e-7); // ~machine epsilon. tolerance where appropiate.

  const Cartesian::space Origin(0, 0, 0);
  const Cartesian::space Unit(1, 1, 1);

  // ----- default consturctor -----

  Cartesian::space x0;

  if (x0 == Origin)
    std::cout << "Passed defalut constructor: " << std::endl
	      << "  Origin = " << x0 << std::endl;
  else
    std::cout << "FAILED defalut constructor: " << std::endl
	      << "  Origin = " << x0 << std::endl;


  // TBD tests for x(1), x(1,2)


  // ----- full constructor -----

  Cartesian::space x1(1, 0, 0);

  if (x1 == Cartesian::space::Ux)
    std::cout << "Passed 3 parameter constructor: " << std::endl
	      << "  x1" << x1 << " == Ux" << Cartesian::space::Ux << std::endl;
  else
    std::cout << "FAILED 3 parameter constructor: " << std::endl
	      << "  x1" << x1 << " == Ux" << Cartesian::space::Ux << std::endl;

  // ----- copy assign -----

  Cartesian::space copy_x1(x1);

  if (x1 == copy_x1)
    std::cout << "Passed copy constructor: " << std::endl
	      << " x1" << x1 << " == copy_x1(x1) == " << copy_x1 << std::endl;
  else
    std::cout << "FAILED reference copy constructor: " << std::endl
	      << " x1" << x1 << " != copy_x1(x1) == " << copy_x1 << std::endl;

  // ----- destructor -----
  // TBD destructor must not raise exceptions anyway.

  Cartesian::space* copy_x2 = new Cartesian::space();

  try {
    delete copy_x2;
  } catch (...) {
    std::cout << "Error on delete" << std::endl;
  }

  std::cout << "Passed delete()." << std::endl;

  // ----- assignment operator -----

  Cartesian::space assignment_x1 = x1;

  if (x1 == assignment_x1)
    std::cout << "Passed assignment operator=(): " << std::endl
	      << " x1" << x1
	      << " == assignment_x1(&x1)" << assignment_x1
	      << std::endl;
  else
    std::cout << "FAILED assignment operator=(): " << std::endl
	      << " x1" << x1
	      << " != assignment_x1(&x1)" << assignment_x1
	      << std::endl;

  // ----- access methods -----

  x1.x(a);
  x1.y(b);
  x1.z(c);

  if (x1.x() == a && x1.y() == b && x1.z() == c)
    std::cout << "Passed accessors: " << std::endl
	      << "  x1" << x1 << std::endl;
  else
    std::cout << "FAILED accessors: " << std::endl
	      << "  x1" << x1 << std::endl;


  // ----- zero method, operators == and != -----

  x1.zero();

  if (x1 == Origin)
    std::cout << "Passed zero method and operator==(): " << std::endl
	      << "  x1" << x1 << " == Origin" << Origin << std::endl;
  else
    std::cout << "FAILED zero method and operator==(): " << std::endl
	      << "  x1" << x1 << " == Origin" << Origin << std::endl;

  if (x1 != Cartesian::space::Ux &&
      x1 != Cartesian::space::Uy &&
      x1 != Cartesian::space::Uz)
    std::cout << "Passed operator!=(): " << std::endl
	      << "  x1" << x1 << " != Ux" << Cartesian::space::Ux << std::endl;
  else
    std::cout << "FAILED zero method and operator!=(): " << std::endl
	      << "  x1" << x1 << " != Ux" << Cartesian::space::Ux << std::endl;

  if (Cartesian::space::Ux != Cartesian::space::Uy)
    std::cout << "Passed operator!=(): " << std::endl
	      << "  Ux" << Cartesian::space::Ux
	      << " != Uy" << Cartesian::space::Uy
	      << std::endl;
  else
    std::cout << "FAILED operator!=(): " << std::endl
	      << "  Ux" << Cartesian::space::Ux
	      << " == Uy" << Cartesian::space::Uy
	      << std::endl;

  if (Cartesian::space::Ux != Cartesian::space::Ux)
    std::cout << "FAILED operator!=(): " << std::endl
	      << "  Ux" << Cartesian::space::Ux
	      << " != Ux" << Cartesian::space::Ux
	      << std::endl;
  else
    std::cout << "Passed operator!=(): " << std::endl
	      << "  Ux" << Cartesian::space::Ux
	      << " == Ux" << Cartesian::space::Ux
	      << std::endl;

  // ----- operator()+= -----

  x1.zero();
  x1 += Cartesian::space::Ux;
  x1 += Cartesian::space::Uy;
  x1 += Cartesian::space::Uz;

  if (x1 == Unit)
    std::cout << "Passed operator+=(): " << std::endl
	      << "  x1" << Origin << " + Unit"
	      << Cartesian::space::Ux + Cartesian::space::Uy + Cartesian::space::Uz
	      << " == Unit" << Unit << std::endl;
  else
    std::cout << "FAILED operator+=(): " << std::endl
	      << "  x1" << Origin << " + Unit"
	      << Cartesian::space::Ux + Cartesian::space::Uy + Cartesian::space::Uz
	      << " != Unit" << Unit << std::endl;


  // ----- operator()+ -----

  x1 = Cartesian::space::Ux + Cartesian::space::Uy + Cartesian::space::Uz;

  if (x1 == Unit)
    std::cout << "Passed operator+(): " << std::endl
	      << "  x1" << Origin << " + Unit"
	      << Cartesian::space::Ux + Cartesian::space::Uy + Cartesian::space::Uz
	      << " == Unit" << Unit << std::endl;
  else
    std::cout << "FAILED operator+(): " << std::endl
	      << "  x1" << Origin << " + Unit"
	      << Cartesian::space::Ux + Cartesian::space::Uy + Cartesian::space::Uz
	      << " != Unit" << Unit << std::endl;


  // ----- operator()-= -----

  x1 = Unit;
  x1 -= Cartesian::space::Ux;
  x1 -= Cartesian::space::Uy;
  x1 -= Cartesian::space::Uz;

  if (x1 == Origin)
    std::cout << "Passed operator-=(): " << std::endl
	      << "  x1" << Unit << " - Unit"  << Unit
	      << " == Origin" << x1 << std::endl;
  else
    std::cout << "FAILED operator-=(): " << std::endl
	      << "  x1" << Unit << " - Unit"  << Unit
	      << " != Origin" << x1 << std::endl;


  // ----- operator()- -----

  x1 = Unit;
  x1 = x1 - Unit;

  if (x1 == Origin)
    std::cout << "Passed operator-(): " << std::endl
	      << "  x1" << Unit << " - Unit"  << Unit
	      << " == Origin" << x1 << std::endl;
  else
    std::cout << "FAILED operator-(): " << std::endl
	      << "  x1" << Unit << " - Unit"  << Unit
	      << " != Origin" << x1 << std::endl;


  // ----- operator()*= -----
  x1 = Unit;
  x1 *= a;

  if (x1.x() == a && x1.y() == a && x1.z() == a)
    std::cout << "Passed operator*=(double):" << std::endl
	      << "  Unit" << Unit << " *= a(" << a << ")"
	      << " == " << x1 << std::endl;
  else
    std::cout << "FAILED operator*=(double):" << std::endl
	      << "  Unit" << Unit << " *= a(" << a << ")"
	      << " != " << x1 << std::endl;


  // ----- operator()* -----

  x1 = Unit * a;

  if (x1.x() == a && x1.y() == a && x1.z() == a)
    std::cout << "Passed operator*(Cartesian::space, double):" << std::endl
	      << "  Unit" << Unit << " * a(" << a << ")"
	      << " == " << x1 << std::endl;
  else
    std::cout << "FAILED operator*(Cartesian::space, double):" << std::endl
	      << "  Unit" << Unit << " * a(" << a << ")"
	      << " != " << x1 << std::endl;

  x1 = a * Unit; // test operator* overload for doubles

  if (x1.x() == a && x1.y() == a && x1.z() == a)
    std::cout << "Passed operator*(double, Cartesian::space):" << std::endl
	      << "  Unit" << Unit << " * a(" << a << ")"
	      << " == " << x1 << std::endl;
  else
    std::cout << "FAILED operator*(double, Cartesian::space):" << std::endl
	      << "  Unit" << Unit << " * a(" << a << ")"
	      << " != " << x1 << std::endl;


  // ----- operator()/= -----

  x1 = Unit;
  x1 /= a;

  if (x1.x() == 1/a && x1.y() == 1/a && x1.z() == 1/a)
    std::cout << "Passed operator/=(double):" << std::endl
	      << "  Unit" << Unit << " /= a(" << a << ")"
	      << " == " << x1 << std::endl;
  else
    std::cout << "FAILED operator/=(double):" << std::endl
	      << "  Unit" << Unit << " /= a(" << a << ")"
	      << " != " << x1 << std::endl;


  // ----- operator()/ -----

  x1 = a / Unit;

  if (x1.x() > a*(1.0-tol) && x1.x() < a*(1.0+tol) &&
      x1.y() > a*(1.0-tol) && x1.y() < a*(1.0+tol) &&
      x1.z() > a*(1.0-tol) && x1.z() < a*(1.0+tol))
    std::cout << "Passed operator/() for doubles:" << std::endl
	      << "  a(" << a << ") / Unit " << Unit << " == " << x1
	      << " to within +/- " << tol
	      << std::endl;
  else
    std::cout << "FAILED operator/() for doubles:" << std::endl
	      << "  a(" << a << ") / Unit "
	      << Unit << " != " << x1
	      << std::endl;


  x1 = Unit / a; // test operator* class method

  if (x1.x() > 1/a*(1.0-tol) && x1.x() < 1/a*(1.0+tol) &&
      x1.y() > 1/a*(1.0-tol) && x1.y() < 1/a*(1.0+tol) &&
      x1.z() > 1/a*(1.0-tol) && x1.z() < 1/a*(1.0+tol))
    std::cout << "Passed operator/() for doubles:" << std::endl
	      << "  Unit(" << Unit << ")/(" << a << ") == " << x1
	      << " to within +/- " << tol
	      << std::endl;

  else
    std::cout << "FAILED operator/=() and operator/() for doubles:" << std::endl
	      << "  Unit" << Unit << " / a(" << a << ") != " << x1 << std::endl;



  // ----- magnitude -----

  x1.x(a); x1.y(b); x1.z(c); // reset x1

  if (x1.magnitude() == sqrt(a*a + b*b + c*c))
    std::cout << "Passed magnigude(): " << std::endl
	      << "  x1" << x1 << " magnitude = " << x1.magnitude() << std::endl;
  else
    std::cout << "FAILED magnigude(): " << std::endl
	      << "  x1" << x1 << " magnitude = " << x1.magnitude() << std::endl;

  if (x1.magnitude2() == a*a + b*b + c*c)
    std::cout << "Passed magnigude2(): " << std::endl
	      << "  x1" << x1 << " magnitude2 = " << x1.magnitude2()
	      << std::endl;
  else
    std::cout << "FAILED magnigude2(): " << std::endl
	      << "  x1" << x1 << " magnitude2 = " << x1.magnitude2()
	      << std::endl;


  // ----- divide by zero checks -----

  try {

    x1 /= 0;

  } catch (Cartesian::DivideZeroError& rex) {
    std::cout << "Passed divide by zero check: " << std::endl
	      << "  " << rex.what() << std::endl;
  }

  try {

    Cartesian::space zero;
    Cartesian::space No(zero.normalized());

  } catch (Cartesian::DivideZeroError& rex) {
    std::cout << "Passed normalize zero check: " << std::endl
	      << "  " << rex.what() << std::endl;
  }

  try {

    Cartesian::space zero;
    Cartesian::space z1 = a/zero;

    std::cout << z1 << std::endl;

  } catch (Cartesian::DivideZeroError& rex) {
    std::cout << "Passed double divided by zero Cartesian::space check: "
	      << std::endl
	      << "  " << rex.what() << std::endl;
  }

  // ----- normalize -----

  x1.x(a); x1.y(b); x1.z(c); // reset x1

  Cartesian::space n1(x1.normalized());

  if (n1.magnitude() > 1.0 - tol && n1.magnitude() < 1.0 + tol)
    std::cout << "Passed normalize(): " << std::endl
	      << "  n1" << n1 << ".magnitude() == " << n1.magnitude()
	      << " to within +/-" << tol <<std::endl;
  else
    std::cout << "FAILED normalize(): " << std::endl
	      << "  n1" << n1 << ", magnitude != " << n1.magnitude()
	      << std::endl;


  // ----- dot product -----

  x1.x(a); x1.y(b); x1.z(c); // reset x1

  double projection = x1 * Cartesian::space::Ux;

  if (projection == a)
    std::cout << "Passed \"dot\" operator*(space, space): "
	      << std::endl
	      << "  x1 * " << x1 << "Ux " << Cartesian::space::Ux
	      << "= " << projection << std::endl;
  else
    std::cout << "FAILED \"dot\" opeator*(space, space): "
	      << std::endl
	      << "  x1 * " << x1 << "Ux " << Cartesian::space::Ux
	      << "!= " << projection << std::endl;


  projection = Cartesian::space::Uy * x1;

  if (projection == b)
    std::cout << "Passed \"dot\" operator*(space, space): "
	      << std::endl
	      << "  Uy * " << Cartesian::space::Uy << "x1 " << x1
	      << "= " << projection << std::endl;
  else
    std::cout << "FAILED \"dot\" operator(space, space): "
	      << std::endl
	      << "  x1 * " << x1 << "Uy " << Cartesian::space::Uy
	      << "!= " << projection << std::endl;


  // ----- cross product -----

  x1 = cross(Cartesian::space::Ux, Cartesian::space::Uy);

  if (x1 == Cartesian::space::Uz)
    std::cout << "Passed cross(): " << std::endl
	      << "  Ux " << Cartesian::space::Ux
	      << " x Uy " << Cartesian::space::Uy
	      << " == Uz " << Cartesian::space::Uz
	      << std::endl;
  else
    std::cout << "FAILED cross(): " << std::endl
	      << "  Ux " << Cartesian::space::Ux
	      << " x Uy " << Cartesian::space::Uy
	      << " != Uz " << Cartesian::space::Uz
	      << std::endl;

  x1 = cross(Cartesian::space::Uy, Cartesian::space::Uz);

  if (x1 == Cartesian::space::Ux)
    std::cout << "  Uy " << Cartesian::space::Uy
	      << " x Uz " << Cartesian::space::Uz
	      << " == Ux " << Cartesian::space::Ux
	      << std::endl;
  else
    std::cout << "FAILED cross(): " << std::endl
	      << "  Uy " << Cartesian::space::Uy
	      << " x Uz " << Cartesian::space::Uz
	      << " == Ux " << Cartesian::space::Ux
	      << std::endl;

  x1 = cross(Cartesian::space::Uz, Cartesian::space::Ux);

  if (x1 == Cartesian::space::Uy)
    std::cout << "  Uz " << Cartesian::space::Uz
	      << " x Ux " << Cartesian::space::Ux
	      << " == Uy " << Cartesian::space::Uy
	      << std::endl;
  else
    std::cout << "FAILED cross(): " << std::endl
	      << "  Uz " << Cartesian::space::Uz
	      << " x Ux " << Cartesian::space::Ux
	      << " == Uy " << Cartesian::space::Uy
	      << std::endl;


  // ----- Rotations -----

  double twoPi1(Cartesian::rotator::deg2rad(360));
  double twoPi2(Cartesian::rotator::deg2rad(Cartesian::rotator::rad2deg(2.0*M_PI)));

  if (twoPi1 == twoPi2)
    std::cout << "Passed: deg2rad test success" << std::endl;
  else
    std::cout << "FAILED: deg2rad test failed" << std::endl;


  // ----- rotator tests -----

  double angle(Cartesian::rotator::deg2rad(90));

  // rotate about z
  const Cartesian::space zRot(cos(angle), sin(angle), 0);
  Cartesian::rotator about_z(Cartesian::space::Uz);
  Cartesian::space r(Cartesian::space::Ux); // initial direction vector
  Cartesian::space s(about_z.rotate(r, angle));

  if (s == zRot)
    std::cout << "Passed rotate about z axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about z"
	      << Cartesian::space::Uz << " == " << s << std::endl;
  else
    std::cout << "FAILED rotate about z axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about z"
	      << Cartesian::space::Uz << " != " << s << std::endl;

  // twice at same angle and axis to test optimization
  // better test
  s = about_z.rotate(r, angle);
  std::cout << "Twice rotate about z axis:" << std::endl
	    << "  rotate r " << r << " "
	    << Cartesian::rotator::rad2deg(angle) << " degrees about z"
	    << Cartesian::space::Uz << " == " << s << std::endl;



  // rotate about x
  const Cartesian::space xRot(0, cos(angle), sin(angle));
  Cartesian::rotator about_x(Cartesian::space::Ux);

  r = Cartesian::space::Uy;
  s = about_x.rotate(r, angle);

  if (s == xRot)
    std::cout << "Passed rotate about x axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about x"
	      << Cartesian::space::Ux << " == " << s << std::endl;
  else
    std::cout << "FAILED rotate about x axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about x"
	      << Cartesian::space::Ux << " != " << s << std::endl;

  // rotate about y
  const Cartesian::space yRot(sin(angle), 0, cos(angle));
  Cartesian::rotator about_y(Cartesian::space::Uy);

  r = Cartesian::space::Uz;
  s = about_y.rotate(r, angle);

  if (s == yRot)
    std::cout << "Passed rotate about y axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about y"
	      << Cartesian::space::Uy << " == " << s << std::endl;
  else
    std::cout << "FAILED rotate about y axis:" << std::endl
	      << "  rotate r " << r << " "
	      << Cartesian::rotator::rad2deg(angle) << " degrees about y"
	      << Cartesian::space::Uy << " != " << s << std::endl;


  // TBD more arbitrary axis


}

// EOF

// ================================================================
// Filename:    space_unittest.cpp
// Description: This is the gtest unittest of the space library.
//
// Author:      L.R. McFarland, lrm@starbug.com
// Created:     2012 May 13
// Language:    C++
//
// See also: http://code.google.com/p/googletest/wiki/Primer
//
// To compile manually:
// g++ -I /usr/local/gtest-1.6.0/include -I . -c space_unittest.cpp
// g++ -L /usr/local/gtest-1.6.0 -lgtest space_unittest.o -o space_unittest
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

#include <space.h>

#include <chrono>
#include <random>
#include <sstream>

#include <gtest/gtest.h>


// TODO setUsingPolarCoords
// TODO Rotation: more arbitrary rotations, copy and assign operators
// TODO SpaceRecorder


namespace {

  // -----------------------
  // ----- Fixed Space -----
  // -----------------------

  TEST(FixedSpace, Accessors) {

    Cartesian::space a;

    a.x(1.1);
    EXPECT_EQ(1.1, a.x());
    EXPECT_EQ(1.1, a.getX());

    a.y(-2.2);
    EXPECT_EQ(-2.2, a.y());
    EXPECT_EQ(-2.2, a.getY());

    a.z(3.3);
    EXPECT_EQ(3.3, a.z());
    EXPECT_EQ(3.3, a.getZ());

  }

  TEST(FixedSpace, OutputOperator) {
    Cartesian::space a(1, 2, 3);
    std::stringstream out;
    out << a;
    EXPECT_STREQ("<space><x>1</x><y>2</y><z>3</z></space>", out.str().c_str());
  }

  TEST(FixedSpace, UnitVectors) {
    EXPECT_EQ(Cartesian::space::Uo, Cartesian::space());
    EXPECT_EQ(Cartesian::space::Ux, Cartesian::space(1));
    EXPECT_EQ(Cartesian::space::Uy, Cartesian::space(0, 1));
    EXPECT_EQ(Cartesian::space::Uz, Cartesian::space(0, 0, 1));
  }

  TEST(FixedSpace, Equivalence) {
    EXPECT_TRUE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.0, 3.0));

    EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.1, 2.0, 3.0));
    EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.1, 3.0));
    EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.0, 3.1));

    EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.1, 2.0, 3.0));
    EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.0, 2.1, 3.0));
    EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.0, 2.0, 3.1));
  }

  TEST(FixedSpace, DefaultConstructor) {
    Cartesian::space a;
    EXPECT_DOUBLE_EQ(0, a.x());
    EXPECT_DOUBLE_EQ(0, a.y());
    EXPECT_DOUBLE_EQ(0, a.z());
  }

  TEST(FixedSpace, ConstructFromString) {

    Cartesian::space a("1.23");
    EXPECT_DOUBLE_EQ(1.23, a.x());

    Cartesian::space b("-1.23", "1.23e-7");
    EXPECT_DOUBLE_EQ(-1.23, b.x());
    EXPECT_DOUBLE_EQ(1.23e-7, b.y());

    Cartesian::space c("1.23", "-1.23e-7", "10");
    EXPECT_DOUBLE_EQ(1.23, c.x());
    EXPECT_DOUBLE_EQ(-1.23e-7, c.y());
    EXPECT_DOUBLE_EQ(10.0, c.z());

  }

  TEST(FixedSpace, ConstructFromBadString) {

    // TODO in future, expect throw std::invalid_argument from std::stod.
    Cartesian::space d("asdf");
    EXPECT_DOUBLE_EQ(0, d.x());

    Cartesian::space e("");
    EXPECT_DOUBLE_EQ(0, e.x());

    Cartesian::space f("asdf 3.1415 blah");
    EXPECT_DOUBLE_EQ(0, f.x());

  }

  TEST(FixedSpace, Magnitude) {
    Cartesian::space a(1, 2, 3);
    EXPECT_DOUBLE_EQ(3.7416573867739413, a.magnitude());
  }

  TEST(FixedSpace, Normalized) {
    Cartesian::space a(1, 2, 3);
    Cartesian::space a_norm(a.normalized());
    EXPECT_DOUBLE_EQ(1.0, a_norm.magnitude());
    EXPECT_DOUBLE_EQ(0.2672612419124244, a_norm.x());
    EXPECT_DOUBLE_EQ(0.53452248382484879, a_norm.y());
    EXPECT_DOUBLE_EQ(0.80178372573727319, a_norm.z());
  }

  TEST(FixedSpace, DotProduct) {
    Cartesian::space dx2(-1, -2, -3);
    EXPECT_EQ(-1.0, Cartesian::dot(dx2, Cartesian::space::Ux));
    EXPECT_EQ(-2.0, Cartesian::dot(dx2, Cartesian::space::Uy));
    EXPECT_EQ(-3.0, Cartesian::dot(dx2, Cartesian::space::Uz));
  }

  TEST(FixedSpace, XYCrossProduct) {
    Cartesian::space z = Cartesian::cross(Cartesian::space::Ux,
					  Cartesian::space::Uy);
    EXPECT_EQ(Cartesian::space::Uz, z);
  }

  TEST(FixedSpace, YZCrossProduct) {
    Cartesian::space x = Cartesian::cross(Cartesian::space::Uy,
					  Cartesian::space::Uz);
    EXPECT_EQ(Cartesian::space::Ux, x);
  }

  TEST(FixedSpace, ZXCrossProduct) {
    Cartesian::space y = Cartesian::cross(Cartesian::space::Uz,
					  Cartesian::space::Ux);
    EXPECT_EQ(Cartesian::space::Uy, y);
  }

  TEST(FixedSpace, SpaceException) {
    try {
      throw Cartesian::SpaceError("custom error message");
    } catch (Cartesian::SpaceError& err) {
      EXPECT_STREQ(err.what(),"custom error message");
    }
  }

  TEST(FixedSpace, InplaceDivideByZeroException) {
    try {
      Cartesian::space a; a /= 0;
    } catch (Cartesian::SpaceError& err) {
      EXPECT_STREQ(err.what(), "division by zero is undefined");
    }
  }

  // ------------------------
  // ----- Random Space -----
  // ------------------------

  class RandomSpace : public ::testing::Test {
    // Creates new random x, y, z values each test.
  protected:

    virtual void SetUp() {

      seed = std::chrono::system_clock::now().time_since_epoch().count();
      lo = -1e3;
      hi = 1e3;

      std::default_random_engine generator(seed);
      std::uniform_real_distribution<double> distribution(lo, hi);

      p1.x(distribution(generator));
      p1.y(distribution(generator));
      p1.z(distribution(generator));

      p2.x(distribution(generator));
      p2.y(distribution(generator));
      p2.z(distribution(generator));

      c = distribution(generator);
    }

    virtual void TearDown() {}

    // members

    unsigned int seed;
    double lo;
    double hi;

    Cartesian::space p1;
    Cartesian::space p2;
    double c; // random double

  };

  TEST_F(RandomSpace, CopyConstructor) {
    Cartesian::space a(p1);
    EXPECT_EQ(p1, a);
  }

  TEST_F(RandomSpace, CopyAssign) {
    Cartesian::space a;
    a = p1;
    EXPECT_EQ(p1, a);
  }

  TEST_F(RandomSpace, Zero) {
    Cartesian::space a(p1);
    a.zero();
    EXPECT_EQ(Cartesian::space::Uo, a);
  }


  TEST_F(RandomSpace, AddInplace) {
    Cartesian::space result(p1.x() + p2.x(),
			    p1.y() + p2.y(),
			    p1.z() + p2.z());
    Cartesian::space a(p1);
    a += p2;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpacePlusSpace) {
    Cartesian::space result(p1.x() + p2.x(),
			    p1.y() + p2.y(),
			    p1.z() + p2.z());
    Cartesian::space a;
    a = p1 + p2;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SubtractInplace) {
    Cartesian::space result(p1.x() - p2.x(),
			    p1.y() - p2.y(),
			    p1.z() - p2.z());
    Cartesian::space a(p1);
    a -= p2;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, UnitaryMinus) {
    Cartesian::space result(-p1.x(),
			    -p1.y(),
			    -p1.z());
    Cartesian::space a(p1);
    a = -p1;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceMinusSpace) {
    Cartesian::space result(p1.x() - p2.x(),
			    p1.y() - p2.y(),
			    p1.z() - p2.z());
    Cartesian::space a;
    a = p1 - p2;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceTimesSpace) {
    // dot product
    double result(p1.x() * p2.x() +
		  p1.y() * p2.y() +
		  p1.z() * p2.z());
    double a;
    a = p1 * p2;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceTimesDouble) {
    // scale
    Cartesian::space result(p1.x() * c,
			    p1.y() * c,
			    p1.z() * c);
    Cartesian::space a;
    a = p1 * c;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, DoubleTimesSpace) {
    // scale commutes
    Cartesian::space result(p1.x() * c,
			    p1.y() * c,
			    p1.z() * c);

    Cartesian::space a;
    a = c * p1;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceTimesDoubleInplace) {
    Cartesian::space result(p1.x() * c,
			    p1.y() * c,
			    p1.z() * c);
    Cartesian::space a(p1);
    a *= c;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceDivideDouble) {
    // scale
    Cartesian::space result(p1.x() / c,
			    p1.y() / c,
			    p1.z() / c);
    Cartesian::space a;
    a = p1 / c;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, SpaceDivideDoubleInplace) {
    Cartesian::space result(p1.x() / c,
			    p1.y() / c,
			    p1.z() / c);
    Cartesian::space a(p1);
    a /= c;
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, DivideByZeroException) {
    Cartesian::space a(p1);
    EXPECT_THROW(a/0, Cartesian::DivideZeroError);
    EXPECT_THROW(a/=0, Cartesian::DivideZeroError);
    EXPECT_THROW(1.0/Cartesian::space::Uo, Cartesian::DivideZeroError);
  }

  TEST_F(RandomSpace, Magnitude) {
    double result(sqrt(p1.x()*p1.x() + p1.y()*p1.y() + p1.z()*p1.z()));
    Cartesian::space a(p1);
    EXPECT_EQ(result, a.magnitude());
  }

  TEST_F(RandomSpace, Magnitude2) {
    double result(p1.x()*p1.x() + p1.y()*p1.y() + p1.z()*p1.z());
    Cartesian::space a(p1);
    EXPECT_EQ(result, a.magnitude2());
  }

  TEST_F(RandomSpace, Normalized) {
    double mag(sqrt(p1.x()*p1.x() + p1.y()*p1.y() + p1.z()*p1.z()));
    Cartesian::space result(p1.x()/mag,
			    p1.y()/mag,
			    p1.z()/mag);
    EXPECT_EQ(result, p1.normalized());
  }

  TEST_F(RandomSpace, DotProduct) {
    double result(p1.x() * p2.x() +
		  p1.y() * p2.y() +
		  p1.z() * p2.z());
    double a(Cartesian::dot(p1, p2));
    EXPECT_EQ(result, a);
  }

  TEST_F(RandomSpace, CrossProduct) {
    Cartesian::space result(p1.y() * p2.z() - p1.z()*p2.y(),
			    p1.z() * p2.x() - p1.x()*p2.z(),
			    p1.x() * p2.y() - p1.y()*p2.x());
    Cartesian::space a(Cartesian::cross(p1, p2));
    EXPECT_EQ(result, a);
  }

  // ----------------------------
  // ----- X Rotation tests -----
  // ----------------------------


  TEST(XRotationTest, Positive90AboutZ) {

    double angle(Cartesian::rotator::deg2rad(90));
    Cartesian::rotator about_z(Cartesian::space::Uz);

    Cartesian::space s(about_z.rotate(Cartesian::space::Ux, angle));

    EXPECT_NEAR(Cartesian::space::Uy.x(), s.x(), Cartesian::space::epsilon);
    EXPECT_DOUBLE_EQ(Cartesian::space::Uy.y(), s.y());
    EXPECT_DOUBLE_EQ(Cartesian::space::Uy.z(), s.z());

  }

  TEST(XRotationTest, Negative90AboutY) {

    double angle(Cartesian::rotator::deg2rad(-90));
    Cartesian::rotator about_y(Cartesian::space::Uy);

    Cartesian::space s(about_y.rotate(Cartesian::space::Ux, angle));

    EXPECT_NEAR(Cartesian::space::Uz.x(), s.x(), Cartesian::space::epsilon);
    EXPECT_DOUBLE_EQ(Cartesian::space::Uz.y(), s.y());
    EXPECT_DOUBLE_EQ(Cartesian::space::Uz.z(), s.z());

  }

  // ----------------------------
  // ----- Y Rotation tests -----
  // ----------------------------

  TEST(YRotationTest, Positive90AboutX) {

    double angle(Cartesian::rotator::deg2rad(90));
    Cartesian::rotator about_x(Cartesian::space::Ux);

    Cartesian::space s(about_x.rotate(Cartesian::space::Uy, angle));

    EXPECT_DOUBLE_EQ(Cartesian::space::Uz.x(), s.x());
    EXPECT_NEAR(Cartesian::space::Uz.y(), s.y(), Cartesian::space::epsilon);
    EXPECT_DOUBLE_EQ(Cartesian::space::Uz.z(), s.z());

  }

  TEST(YRotationTest, Negative90AboutZ) {

    double angle(Cartesian::rotator::deg2rad(-90));
    Cartesian::rotator about_z(Cartesian::space::Uz);

    Cartesian::space s(about_z.rotate(Cartesian::space::Uy, angle));

    EXPECT_DOUBLE_EQ(Cartesian::space::Ux.x(), s.x());
    EXPECT_NEAR(Cartesian::space::Ux.y(), s.y(), Cartesian::space::epsilon);
    EXPECT_DOUBLE_EQ(Cartesian::space::Ux.z(), s.z());

  }

  // ----------------------------
  // ----- Z Rotation tests -----
  // ----------------------------

  TEST(ZRotationTest, Positive90AboutY) {

    double angle(Cartesian::rotator::deg2rad(90));
    Cartesian::rotator about_y(Cartesian::space::Uy);

    Cartesian::space s(about_y.rotate(Cartesian::space::Uz, angle));

    EXPECT_DOUBLE_EQ(Cartesian::space::Ux.x(), s.x());
    EXPECT_DOUBLE_EQ(Cartesian::space::Ux.y(), s.y());
    EXPECT_NEAR(Cartesian::space::Ux.z(), s.z(), Cartesian::space::epsilon);

  }

  TEST(ZRotationTest, Negative90AboutX) {

    double angle(Cartesian::rotator::deg2rad(-90));
    Cartesian::rotator about_x(Cartesian::space::Ux);

    Cartesian::space s(about_x.rotate(Cartesian::space::Uz, angle));

    EXPECT_DOUBLE_EQ(Cartesian::space::Uy.x(), s.x());
    EXPECT_DOUBLE_EQ(Cartesian::space::Uy.y(), s.y());
    EXPECT_NEAR(Cartesian::space::Uy.z(), s.z(), Cartesian::space::epsilon);

  }

} // end anonymous namespace


// ==================
// ===== main() =====
// ==================

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

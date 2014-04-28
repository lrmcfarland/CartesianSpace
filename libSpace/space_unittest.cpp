// ================================================================
// Filename:    space_unittest.cpp
// Description: This is the gtest unittest of the space library.
//
// Author:      L.R. McFarland, lrm@starbug.com
// Created:     2012 May 13
// Revised:     2012 May 13
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

#include <sstream>
#include <gtest/gtest.h>

// -----------------------
// ----- space tests -----
// -----------------------

// explicitly test default constructors,
// implicitly test Unit vectors and operator=()
TEST(SpaceTest, UnitVectors) {
  EXPECT_EQ(Cartesian::space::Uo, Cartesian::space());
  EXPECT_EQ(Cartesian::space::Ux, Cartesian::space(1));
  EXPECT_EQ(Cartesian::space::Uy, Cartesian::space(0, 1));
  EXPECT_EQ(Cartesian::space::Uz, Cartesian::space(0, 0, 1));
}

TEST(SpaceTest, ConstructFromString) {

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

TEST(SpaceTest, ConstructFromBadString) {

  // TODO in future, expect throw std::invalid_argument from std::stod.
  Cartesian::space d("asdf");
  EXPECT_DOUBLE_EQ(0, d.x());

  Cartesian::space e("");
  EXPECT_DOUBLE_EQ(0, e.x());

  Cartesian::space f("asdf 3.1415 blah");
  EXPECT_DOUBLE_EQ(0, f.x());

}

TEST(SpaceTest, Equivalence) {
  EXPECT_TRUE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.0, 3.0));

  EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.1, 2.0, 3.0));
  EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.1, 3.0));
  EXPECT_FALSE(Cartesian::space(1, 2, 3) == Cartesian::space(1.0, 2.0, 3.1));

  EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.1, 2.0, 3.0));
  EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.0, 2.1, 3.0));
  EXPECT_TRUE(Cartesian::space(1, 2, 3) != Cartesian::space(1.0, 2.0, 3.1));
}

TEST(SpaceTest, Copy) {

  // copy construct
  Cartesian::space x(1.1, -2.2, 3.3);
  Cartesian::space y(x);
  EXPECT_EQ(x, y);

  // copy assign
  Cartesian::space z;
  z = x;
  EXPECT_EQ(x, z);
}

TEST(SpaceTest, Accessors) {

  Cartesian::space x;

  x.x(1.1);
  EXPECT_EQ(1.1, x.x());
  EXPECT_EQ(1.1, x.getX());

  x.y(-2.2);
  EXPECT_EQ(-2.2, x.y());
  EXPECT_EQ(-2.2, x.getY());

  x.z(3.3);
  EXPECT_EQ(3.3, x.z());
  EXPECT_EQ(3.3, x.getZ());

}

TEST(SpaceTest, Printing) {

  Cartesian::space x(1, 2, 3);
  std::stringstream xout;
  xout << x;

  EXPECT_STREQ("<space><x>1</x><y>2</y><z>3</z></space>", xout.str().c_str());
}

TEST(SpaceTest, Magnitude) {

  Cartesian::space x(1, 2, 3);
  EXPECT_DOUBLE_EQ(3.7416573867739413, x.magnitude());

  Cartesian::space x_norm(x.normalized());
  EXPECT_DOUBLE_EQ(1.0, x_norm.magnitude());
  EXPECT_DOUBLE_EQ(0.2672612419124244, x_norm.x());
  EXPECT_DOUBLE_EQ(0.53452248382484879, x_norm.y());
  EXPECT_DOUBLE_EQ(0.80178372573727319, x_norm.z());
}

TEST(SpaceTest, Add) {

  Cartesian::space x;

  x = Cartesian::space::Ux + Cartesian::space::Uy;

  EXPECT_EQ(1.0, x.x());
  EXPECT_EQ(1.0, x.y());
  EXPECT_EQ(0.0, x.z());

  x += Cartesian::space::Uz;

  EXPECT_EQ(1.0, x.x());
  EXPECT_EQ(1.0, x.y());
  EXPECT_EQ(1.0, x.z());

}

TEST(SpaceTest, Subtract) {

  Cartesian::space x;

  x = -1*Cartesian::space::Ux - Cartesian::space::Uy;

  EXPECT_EQ(-1.0, x.x());
  EXPECT_EQ(-1.0, x.y());
  EXPECT_EQ(0.0, x.z());

  x -= Cartesian::space::Uz;

  EXPECT_EQ(-1.0, x.x());
  EXPECT_EQ(-1.0, x.y());
  EXPECT_EQ(-1.0, x.z());

}

TEST(SpaceTest, Multiply) {

  Cartesian::space v(1, 1, 1);

  // scale
  v *= -2;
  EXPECT_EQ(-2.0, v.x());
  EXPECT_EQ(-2.0, v.y());
  EXPECT_EQ(-2.0, v.z());

  // as product of double
  v = v * 0.5;
  EXPECT_EQ(-1.0, v.x());
  EXPECT_EQ(-1.0, v.y());
  EXPECT_EQ(-1.0, v.z());

  // commutes with int
  v = -1 * v;
  EXPECT_EQ(1.0, v.x());
  EXPECT_EQ(1.0, v.y());
  EXPECT_EQ(1.0, v.z());

}

TEST(SpaceTest, DotProduct) {

  // dot product
  Cartesian::space dx(1, 2, 3);
  EXPECT_EQ(1.0, dx * Cartesian::space::Ux);
  EXPECT_EQ(2.0, dx * Cartesian::space::Uy);
  EXPECT_EQ(3.0, dx * Cartesian::space::Uz);

  // dot product
  Cartesian::space dx2(-1, -2, -3);
  EXPECT_EQ(-1.0, Cartesian::dot(dx2, Cartesian::space::Ux));
  EXPECT_EQ(-2.0, Cartesian::dot(dx2, Cartesian::space::Uy));
  EXPECT_EQ(-3.0, Cartesian::dot(dx2, Cartesian::space::Uz));

}

TEST(SpaceTest, CrossProduct) {

  // cross product
  Cartesian::space z = Cartesian::cross(Cartesian::space::Ux,
					Cartesian::space::Uy);
  EXPECT_EQ(0.0, z.x());
  EXPECT_EQ(0.0, z.y());
  EXPECT_EQ(1.0, z.z());

  Cartesian::space x = Cartesian::cross(Cartesian::space::Uy,
					Cartesian::space::Uz);
  EXPECT_EQ(1.0, x.x());
  EXPECT_EQ(0.0, x.y());
  EXPECT_EQ(0.0, x.z());

  Cartesian::space y = Cartesian::cross(Cartesian::space::Uz,
					Cartesian::space::Ux);
  EXPECT_EQ(0.0, y.x());
  EXPECT_EQ(1.0, y.y());
  EXPECT_EQ(0.0, y.z());

}

TEST(SpaceTest, Divide) {

  Cartesian::space x(1, 1, 1);

  x /= 2;

  EXPECT_EQ(0.5, x.x());
  EXPECT_EQ(0.5, x.y());
  EXPECT_EQ(0.5, x.z());

  x = 1 / x;

  EXPECT_EQ(2.0, x.x());
  EXPECT_EQ(2.0, x.y());
  EXPECT_EQ(2.0, x.z());

  EXPECT_THROW(x /= 0, Cartesian::DivideZeroError);

}

// ----------------------------
// ----- X Rotation tests -----
// ----------------------------

class XRotationTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    r = Cartesian::space::Ux;
  }

  // virtual void TearDown() {}

  Cartesian::space r;

};

TEST_F(XRotationTest, Positive90AboutZ) {

  double angle(Cartesian::rotator::deg2rad(90));
  Cartesian::rotator about_z(Cartesian::space::Uz);

  Cartesian::space s(about_z.rotate(r, angle));

  EXPECT_NEAR(Cartesian::space::Uy.x(), s.x(), Cartesian::space::epsilon);
  EXPECT_DOUBLE_EQ(Cartesian::space::Uy.y(), s.y());
  EXPECT_DOUBLE_EQ(Cartesian::space::Uy.z(), s.z());

}

TEST_F(XRotationTest, Negative90AboutY) {

  double angle(Cartesian::rotator::deg2rad(-90));
  Cartesian::rotator about_y(Cartesian::space::Uy);

  Cartesian::space s(about_y.rotate(r, angle));

  EXPECT_NEAR(Cartesian::space::Uz.x(), s.x(), Cartesian::space::epsilon);
  EXPECT_DOUBLE_EQ(Cartesian::space::Uz.y(), s.y());
  EXPECT_DOUBLE_EQ(Cartesian::space::Uz.z(), s.z());

}

// ----------------------------
// ----- Y Rotation tests -----
// ----------------------------

class YRotationTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    r = Cartesian::space::Uy;
  }

  // virtual void TearDown() {}

  Cartesian::space r;

};

TEST_F(YRotationTest, Positive90AboutX) {

  double angle(Cartesian::rotator::deg2rad(90));
  Cartesian::rotator about_x(Cartesian::space::Ux);

  Cartesian::space s(about_x.rotate(r, angle));

  EXPECT_DOUBLE_EQ(Cartesian::space::Uz.x(), s.x());
  EXPECT_NEAR(Cartesian::space::Uz.y(), s.y(), Cartesian::space::epsilon);
  EXPECT_DOUBLE_EQ(Cartesian::space::Uz.z(), s.z());

}

TEST_F(YRotationTest, Negative90AboutZ) {

  double angle(Cartesian::rotator::deg2rad(-90));
  Cartesian::rotator about_z(Cartesian::space::Uz);

  Cartesian::space s(about_z.rotate(r, angle));

  EXPECT_DOUBLE_EQ(Cartesian::space::Ux.x(), s.x());
  EXPECT_NEAR(Cartesian::space::Ux.y(), s.y(), Cartesian::space::epsilon);
  EXPECT_DOUBLE_EQ(Cartesian::space::Ux.z(), s.z());

}

// ----------------------------
// ----- Z Rotation tests -----
// ----------------------------

class ZRotationTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    r = Cartesian::space::Uz;
  }

  // virtual void TearDown() {}

  Cartesian::space r;

};

TEST_F(ZRotationTest, Positive90AboutY) {

  double angle(Cartesian::rotator::deg2rad(90));
  Cartesian::rotator about_y(Cartesian::space::Uy);

  Cartesian::space s(about_y.rotate(r, angle));

  EXPECT_DOUBLE_EQ(Cartesian::space::Ux.x(), s.x());
  EXPECT_DOUBLE_EQ(Cartesian::space::Ux.y(), s.y());
  EXPECT_NEAR(Cartesian::space::Ux.z(), s.z(), Cartesian::space::epsilon);

}

TEST_F(ZRotationTest, Negative90AboutX) {

  double angle(Cartesian::rotator::deg2rad(-90));
  Cartesian::rotator about_x(Cartesian::space::Ux);

  Cartesian::space s(about_x.rotate(r, angle));

  EXPECT_DOUBLE_EQ(Cartesian::space::Uy.x(), s.x());
  EXPECT_DOUBLE_EQ(Cartesian::space::Uy.y(), s.y());
  EXPECT_NEAR(Cartesian::space::Uy.z(), s.z(), Cartesian::space::epsilon);

}


// TODO Rotation: more arbitrary rotations, copy and assign operators


// TODO SpaceRecorder


// ==================
// ===== main() =====
// ==================

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#!/usr/bin/env python

"""Unit tests for space objects."""

import math
import random
import time
import unittest

import space


class TestSpace(unittest.TestCase):

    def setUp(self):

        """Set up test parameters."""

        self.places = 7 # precision

        # random test points

        self.lower_range = -1.0e3
        self.upper_range =  1.0e3

        self.p1 = space.space(random.uniform(self.lower_range, self.upper_range),
                              random.uniform(self.lower_range, self.upper_range),
                              random.uniform(self.lower_range, self.upper_range))

        self.p2 = space.space(random.uniform(self.lower_range, self.upper_range),
                              random.uniform(self.lower_range, self.upper_range),
                              random.uniform(self.lower_range, self.upper_range))


    def assertSpacesAreEqual(self, lhs_space, rhs_space):
        """Space assert helper method."""
        # TODO wrap operator==()
        self.assertAlmostEqual(lhs_space.x, rhs_space.x, places=self.places)
        self.assertAlmostEqual(lhs_space.y, rhs_space.y, places=self.places)
        self.assertAlmostEqual(lhs_space.z, rhs_space.z, places=self.places)

    # -----------------------------
    # ----- test constructors -----
    # -----------------------------

    def test_default_constructor(self):
        """Test default constructor"""
        a = space.space()
        self.assertEqual(0, a.x)
        self.assertEqual(0, a.y)
        self.assertEqual(0, a.z)
        self.assertSpacesAreEqual(space.space.Uo, a)


    def test_x_constructor(self):
        """Test x constructor"""
        a = space.space(self.p1.x)
        self.assertEqual(self.p1.x, a.x)
        self.assertEqual(0, a.y)
        self.assertEqual(0, a.z)


    def test_xy_constructor(self):
        """Test xy constructor"""
        a = space.space(self.p1.x, self.p1.y)
        self.assertEqual(self.p1.x, a.x)
        self.assertEqual(self.p1.y, a.y)
        self.assertEqual(0, a.z)


    def test_xyz_constructor(self):
        """Test xyz constructor"""
        a = space.space(self.p1.x, self.p1.y, self.p1.z)
        self.assertSpacesAreEqual(self.p1, a)


    @unittest.skip('Not available in boost')
    def test_xyz_constructor2(self):
        """Test xyz constructor by named args"""
        a = space.space(z=self.p1.z, x=self.p1.x, y=self.p1.y)
        self.assertSpacesAreEqual(self.p1, a)


    def test_xyz_assignments(self):
        """Test space xyz assignment operators"""
        a = space.space()
        a.x = self.p1.x
        a.y = self.p1.y
        a.z = self.p1.z
        self.assertSpacesAreEqual(self.p1, a)


    def test_copy_assign1(self):
        """Test copy assignment operator"""
        a = self.p1
        self.assertSpacesAreEqual(self.p1, a)


    def test_copy_assign2(self):
        """Test copy assignment operator is shallow"""
        a = space.space(1,2,3)
        b = a
        b.x = 4.0
        self.assertSpacesAreEqual(a, b)
        self.assertEqual(4, b.x)

    @unittest.skip('Not available in boost')
    def test_copy_assign3(self):
        """Test copy assignment operator can use deep copy"""
        import copy
        a = space.space(1,2,3)
        b = copy.deepcopy(a)
        b.x = 4.0
        self.assertEqual(1, a.x)
        self.assertEqual(4, b.x)


    def test_string_constructor_exception(self):
        """Test string constructor exception"""

        self.assertRaises(TypeError, lambda a: space.space(a), 'some_string')
        self.assertRaises(TypeError, lambda a: space.space(1, a), 'some_string')
        self.assertRaises(TypeError, lambda a: space.space(1, -1, a), 'some_string')


    def test_string_assignment_exception(self):
        """Test string assignment exception"""

        self.assertRaises(TypeError, self.p1.x, 'some_string')
        self.assertRaises(TypeError, self.p1.y, 'some_string')
        self.assertRaises(TypeError, self.p1.z, 'some_string')

    # --------------------------------
    # ----- test unitary methods -----
    # --------------------------------


    def test_str(self):
        """Test str"""

        # precision is controlled by boost and not always passing the random number test

        a_point = space.space(1.23, -4.56, 7.89)

        a_str = '<space><x>%(x)s</x><y>%(y)s</y><z>%(z)s</z></space>' % {'x':a_point.x,
                                                                         'y':a_point.y,
                                                                         'z':a_point.z}
        self.assertEqual(a_str, str(a_point))


    @unittest.skip('Not available in boost')
    def test_repr(self):
        """Test repr"""

        # %s precision is controlled by space.cpp and designed to match this test
        a_repr = '(%(x)s, %(y)s, %(z)s)' % {'x':self.p1.x,
                                            'y':self.p1.y,
                                            'z':self.p1.z}
        self.assertEqual(a_repr, repr(self.p1))


    def test_magnitude(self):
        """Test space magnitude"""
        root_sum_square = math.sqrt(self.p1.x*self.p1.x + self.p1.y*self.p1.y + self.p1.z*self.p1.z)
        a = space.space.magnitude(self.p1)
        self.assertAlmostEqual(root_sum_square, a, self.places)


    def test_normalized(self):
        """Test space normalized"""
        root_sum_square = math.sqrt(self.p1.x*self.p1.x + self.p1.y*self.p1.y + self.p1.z*self.p1.z)
        normalized = space.space(self.p1.x/root_sum_square,
                                 self.p1.y/root_sum_square,
                                 self.p1.z/root_sum_square)

        a = space.space.normalized(self.p1)
        self.assertSpacesAreEqual(normalized, a)


    # -------------------------------
    # ----- test math operators -----
    # -------------------------------

    @unittest.skip('TODO wrap operator==()')
    def test_space_eq_space(self):
        """Test space == space"""
        a = space.space(1, 2, 3)
        b = space.space(1, 2, 3)
        self.assertTrue(result == a)


    @unittest.skip('TODO wrap operator!=()')
    def test_space_ne_space(self):
        """Test space != space"""
        a = space.space(1, 2, 3)
        b = space.space(1, 2, 3)
        self.assertTrue(a != b) # false positive comparing addresses


    def test_space_plus_space(self):
        """Test space + space"""
        result = space.space(self.p1.x + self.p2.x,
                             self.p1.y + self.p2.y,
                             self.p1.z + self.p2.z)
        a = self.p1 + self.p2
        self.assertSpacesAreEqual(result, a)


    def test_inplace_add(self):
        """Test space +="""
        result = space.space(self.p1.x + self.p2.x,
                             self.p1.y + self.p2.y,
                             self.p1.z + self.p2.z)
        a = self.p1
        a += self.p2
        self.assertSpacesAreEqual(result, a)


    def test_space_minus_space(self):
        """Test space - space"""
        result = space.space(self.p1.x - self.p2.x,
                             self.p1.y - self.p2.y,
                             self.p1.z - self.p2.z)
        a = self.p1 - self.p2
        self.assertSpacesAreEqual(result, a)


    def test_inplace_subtract(self):
        """Test space -="""
        result = space.space(self.p1.x - self.p2.x,
                             self.p1.y - self.p2.y,
                             self.p1.z - self.p2.z)
        a = self.p1
        a -= self.p2
        self.assertSpacesAreEqual(result, a)


    @unittest.skip('TODO overload * double or no explicit constructor?')
    def test_space_times_double(self):
        """Test space * double (scale)"""
        scale = 0.5
        result = self.p1.x * scale + self.p1.y * scale + self.p1.z * scale
        a = self.p1 * scale
        self.assertAlmostEqual(result, a, self.places)


    def test_space_times_space(self):
        """Test space * space dot product"""
        result = self.p1.x * self.p2.x + self.p1.y * self.p2.y + self.p1.z * self.p2.z
        a = self.p1 * self.p2
        self.assertAlmostEqual(result, a, self.places)


    def test_inplace_multiply(self):
        """Test space *= dot product"""
        result = self.p1.x * self.p2.x + self.p1.y * self.p2.y + self.p1.z * self.p2.z
        a = self.p1
        a *= self.p2
        self.assertAlmostEqual(result, a, self.places)


    def test_dot_product(self):
        """Test space dot product function"""
        result = self.p1.x * self.p2.x + self.p1.y * self.p2.y + self.p1.z * self.p2.z
        a = space.dot(self.p1, self.p2)
        self.assertEqual(result, a)


    def test_x_cross_y(self):
        """Test x cross y is z"""
        a = space.cross(space.space.Ux, space.space.Uy)
        self.assertSpacesAreEqual(space.space.Uz, a)


    def test_y_cross_z(self):
        """Test x cross y is z"""
        a = space.cross(space.space.Uy, space.space.Uz)
        self.assertSpacesAreEqual(space.space.Ux, a)


    def test_z_cross_x(self):
        """Test x cross y is z"""
        a = space.cross(space.space.Uz, space.space.Ux)
        self.assertSpacesAreEqual(space.space.Uy, a)


    def test_cross_1(self):
        """Test more arbitrary cross product"""
        a = space.space(1, 1, 1)
        b = space.space(0, 0, 0.5)
        c = space.cross(a, b)
        self.assertSpacesAreEqual(space.space(0.5, -0.5, 0), c)


    def test_divide(self):
        """Test divide (scale)"""
        result = space.space(self.p1.x / 2.0,
                             self.p1.y / 2.0,
                             self.p1.z / 2.0)
        a = self.p1 / 2.0
        self.assertSpacesAreEqual(result, a)


    def test_inplace_divide(self):
        """Test inplace divide (scale)"""
        result = space.space(self.p1.x / 2.0,
                             self.p1.y / 2.0,
                             self.p1.z / 2.0)
        a = self.p1
        a /= 2.0
        self.assertSpacesAreEqual(result, a)


if __name__ == '__main__':
    random.seed(time.time())
    unittest.main()

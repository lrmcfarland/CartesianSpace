#!/usr/bin/env python

"""Unit test test harness for space objects."""

import math
import unittest

import space

class TestSpace(unittest.TestCase):

    def setUp(self):

        """Set up test parameters."""

        self.places = 7 # almost equal places

        # various types to check math operators
        self.most_exception_types = (
            'foo', 0, 1, -2, 3.1415, -2.7, complex(1.2, -3.4))

        self.divisor_exception_types = ('foo', complex(1.2, -3.4))

        # one point
        self.x1 = 1
        self.y1 = 2
        self.z1 = 3

        self.space1 = space.space(self.x1, self.y1, self.z1)

        self.space1_mag = math.sqrt(self.x1*self.x1 + self.y1*self.y1 + self.z1*self.z1)
        self.normal1 = space.space(self.x1/self.space1_mag,
                                   self.y1/self.space1_mag,
                                   self.z1/self.space1_mag)


        # hardcoded strings keep this from being too circular.
        self.one_as_str = '<space><x>1</x><y>2</y><z>3</z></space>'
        self.one_as_repr = '(1, 2, 3)'

        # another point
        self.x2 = 0.123456789
        self.y2 = -2.71828
        self.z2 = 3.14159

        self.space2 = space.space(self.x2, self.y2, self.z2)

        # Note: space print precision (default) is less than in Body.
        self.two_as_str = '<space><x>0.123457</x><y>-2.71828</y><z>3.14159</z></space>'
        self.two_as_repr = '(0.123457, -2.71828, 3.14159)'

        # sum
        self.sum_space1_space2 = space.space(self.x1 + self.x2,
                                             self.y1 + self.y2,
                                             self.z1 + self.z2)

        # difference
        self.diff_space1_space2 = space.space(self.x1 - self.x2,
                                              self.y1 - self.y2,
                                              self.z1 - self.z2)

        # dot product
        self.dot_prod_space1_space2 = \
            self.x1 * self.x2 + \
            self.y1 * self.y2 + \
            self.z1 * self.z2

        self.quotient_space1_over_2 = space.space(self.x1 / 2.0,
                                                  self.y1 / 2.0,
                                                  self.z1 / 2.0)


    def assertSpaceAreEqual(self, lhs_space, rhs_space):
        """Helper function."""
        self.assertAlmostEqual(lhs_space.x, rhs_space.x, places=self.places)
        self.assertAlmostEqual(lhs_space.y, rhs_space.y, places=self.places)
        self.assertAlmostEqual(lhs_space.z, rhs_space.z, places=self.places)

    def test_constructors(self):

        """Test space constructors"""

        a = space.space()
        self.assertEqual(a.x, 0)
        self.assertEqual(a.y, 0)
        self.assertEqual(a.z, 0)
        self.assertSpaceAreEqual(a, space.Uo)

        a = space.space(self.x1)
        self.assertEqual(a.x, self.x1)
        self.assertEqual(a.y, 0)
        self.assertEqual(a.z, 0)

        a = space.space(self.x1, self.y1)
        self.assertEqual(a.x, self.x1)
        self.assertEqual(a.y, self.y1)
        self.assertEqual(a.z, 0)

        a = space.space(self.x1, self.y1, self.z1)
        self.assertSpaceAreEqual(self.space1, a)

        a = space.space(z=self.z2, x=self.x2, y=self.y2)
        self.assertSpaceAreEqual(self.space2, a)


    def test_assignments(self):
        """Test space assignment operators"""

        a = space.space()

        a.x = self.x1
        a.y = self.y1
        a.z = self.z1

        self.assertSpaceAreEqual(self.space1, a)

        # TODO assign to space


    def test_exceptions(self):
        """Test space exceptions"""

        a_space = space.space()

        self.assertRaises(TypeError, a_space.x, 'foo')
        self.assertRaises(TypeError, a_space.y, 'foo')
        self.assertRaises(TypeError, a_space.z, 'foo')

        # assert exceptions on operators of different types.

        if False:
            # FN
            self.assertRaises(TypeError, lambda a, b: a + b,
                              self.space1, self.space2)

        for type_ in self.most_exception_types:
            self.assertRaises(TypeError, lambda a, b: a + b, a_space, type_)
            self.assertRaises(TypeError, lambda a, b: b + a, a_space, type_)
        # TODO +=

        for type_ in self.most_exception_types:
            self.assertRaises(TypeError, lambda a, b: a - b, a_space, type_)
            self.assertRaises(TypeError, lambda a, b: b - a, a_space, type_)
        # TODO -=

        for type_ in self.most_exception_types:
            self.assertRaises(TypeError, lambda a, b: a * b, a_space, type_)
            self.assertRaises(TypeError, lambda a, b: b * a, a_space, type_)
       # TODO *=

        for type_ in self.divisor_exception_types:
            self.assertRaises(TypeError, lambda a, b: a / b, a_space, type_)
            self.assertRaises(TypeError, lambda a, b: b / a, a_space, type_)
        # TODO /=

        # divide by 0
        self.assertRaises(space.space_error, lambda a, b: a / b, a_space, 0)


        # TODO other exceptions


    def test_prints(self):
        """Test space print and repr"""

        a = space.space(self.x2, self.y2, self.z2)

        self.assertEqual(self.two_as_str, str(a))
        self.assertEqual(self.two_as_repr, repr(a))

        # TODO ints?


    def test_add(self):
        """Test space add"""

        # operator+
        a = self.space1 + self.space2
        self.assertSpaceAreEqual(a, self.sum_space1_space2)

        # operator+=
        a = self.space1
        a += self.space2
        self.assertSpaceAreEqual(a, self.sum_space1_space2)

        # was causing a Segmentation fault when += implementation
        # was not making a copy of m_space (refence count problem?)


    def test_subtract(self):
        """Test space subtract"""

        # operator-
        a = self.space1 - self.space2
        self.assertSpaceAreEqual(a, self.diff_space1_space2)

        # operator -=
        a = self.space1
        a -= self.space2
        self.assertSpaceAreEqual(a, self.diff_space1_space2)

        a # reference test


    def test_multiply(self):
        """Test space multiply (dot product)"""

        # operator*
        a = self.space1 * self.space2
        self.assertEqual(a, self.dot_prod_space1_space2)

        # operator*=
        a = self.space1
        a *= self.space2
        self.assertEqual(a, self.dot_prod_space1_space2)

        a # reference test


    def test_divide(self):
        """Test space divide (scale)"""

        # operator/
        a = self.space1 / 2.0
        self.assertSpaceAreEqual(a, self.quotient_space1_over_2)

        # operator*=
        a = self.space1
        a /= 2.0
        self.assertSpaceAreEqual(a, self.quotient_space1_over_2)

        a # reference test


    def test_cross_product(self):
        """Test space cross product"""

        # simple axis rotation.
        a = space.cross(space.Ux, space.Uy)
        self.assertSpaceAreEqual(a, space.Uz)

        a = space.cross(space.Uy, space.Uz)
        self.assertSpaceAreEqual(a, space.Ux)

        a = space.cross(space.Uz, space.Ux)
        self.assertSpaceAreEqual(a, space.Uy)

        # more complex
        a = space.space(1, 1, 1)
        b = space.space(0, 0, 0.5)

        c = space.cross(a, b)

        self.assertSpaceAreEqual(space.space(0.5, -0.5, 0), c)


    def test_dot_product(self):
        """Test space dot product function"""

        a = space.dot(self.space1, self.space2)
        self.assertEqual(a, self.dot_prod_space1_space2)


    def test_normalized(self):
        """Test space normalized"""

        a = space.normalized(self.space1)
        self.assertSpaceAreEqual(a, self.normal1)


    def test_magnitude(self):
        """Test space magnitude"""

        a = space.magnitude(self.space1)

        self.assertAlmostEqual(a, self.space1_mag, self.places)



if __name__ == '__main__':
    unittest.main()

"""Tests boost space module."""

import math
import unittest

import space

class TestSpace(unittest.TestCase):

    def setUp(self):

        self.places = 7 # almost equal places

        self.zero = space.space()
        self.A = 1.1
        self.B = 2.2
        self.C = 3.3

        self.product = self.A*self.A + self.B*self.B + self.C*self.C
        self.magnitude = math.sqrt(self.product)

        self.a_str = '<space><x>1.1</x><y>2.2</y><z>3.3</z></space>'


    def test_default_constructors(self):
        """Test space default constructors"""

        a = space.space()
        self.assertEqual(0, a.x)
        self.assertEqual(0, a.y)
        self.assertEqual(0, a.z)

        a = space.space(self.A)
        self.assertEqual(self.A, a.x)
        self.assertEqual(0, a.y)
        self.assertEqual(0, a.z)

        a = space.space(self.A, self.B)
        self.assertEqual(self.A, a.x)
        self.assertEqual(self.B, a.y)
        self.assertEqual(0, a.z)

        a = space.space(self.A, self.B, self.C)
        self.assertEqual(self.A, a.x)
        self.assertEqual(self.B, a.y)
        self.assertEqual(self.C, a.z)


    def test_copy_constructor(self):
        """Test space copy constructor"""

        a = space.space(self.A, self.B, self.C)
        b = space.space(a)
        self.assertEqual(self.A, b.x)
        self.assertEqual(self.B, b.y)
        self.assertEqual(self.C, b.z)


    def test_copy_assign(self):
        """Test space copy assign"""

        a = space.space(self.A, self.B, self.C)
        b = a
        self.assertEqual(self.A, b.x)
        self.assertEqual(self.B, b.y)
        self.assertEqual(self.C, b.z)


    def test_accessors(self):
        """Test space accessors"""

        a = space.space()
        a.setX(self.A)
        a.setY(-self.B)
        a.setZ(self.C)

        self.assertEqual(self.A, a.getX())
        self.assertEqual(-self.B, a.getY())
        self.assertEqual(self.C, a.getZ())


    def test_properties(self):
        """Test properties"""

        a = space.space()
        a.x = self.A
        a.y = -self.B
        a.z = self.C

        self.assertEqual(self.A, a.x)
        self.assertEqual(-self.B, a.y)
        self.assertEqual(self.C, a.z)


    def test_str(self):
        """Test string representation."""
        a = space.space(self.A, self.B, self.C)
        self.assertEqual(self.a_str, str(a))


    def test_add(self):
        """Test add"""
        a = space.space(self.A, self.B, self.C)
        b = space.space(-self.A, -self.B, -self.C)
        c = a + b
        self.assertEqual(0, c.x)
        self.assertEqual(0, c.y)
        self.assertEqual(0, c.z)


    def test_inplace_add(self):
        """Test inplace add"""
        a = space.space(self.A, self.B, self.C)
        a += a

        self.assertEqual(2*self.A, a.x)
        self.assertEqual(2*self.B, a.y)
        self.assertEqual(2*self.C, a.z)


    def test_subtract(self):
        """Test subtract"""
        a = space.space(self.A, self.B, self.C)
        b = space.space(self.A, self.B, self.C)
        c = a - b
        self.assertEqual(c.x, 0)
        self.assertEqual(c.y, 0)
        self.assertEqual(c.z, 0)


    def test_inplace_subtract(self):
        """Test inplace subtract"""
        a = space.space(self.A, self.B, self.C)
        a -= a

        self.assertEqual(0, a.x)
        self.assertEqual(0, a.y)
        self.assertEqual(0, a.z)


    def test_multiply(self):
        """Test multiply, a.k.a. dot product"""
        a = space.space(self.A, self.B, self.C)
        b = space.space(self.A, self.B, self.C)
        c = a * b
        self.assertAlmostEqual(self.product, c, self.places)


    def test_inplace_multiply(self):
        """Test inplace multiply

        This is weird because a becomes a float since this is a dot product.
        """
        a = space.space(self.A, self.B, self.C)
        a *= a
        self.assertAlmostEqual(self.product, a, self.places)


    def test_divide(self):
        """Test divide, a.k.a. scale"""
        a = space.space(self.A, self.B, self.C)
        b = a / 10

        self.assertEqual(self.A/10, b.x)
        self.assertEqual(self.B/10, b.y)
        self.assertEqual(self.C/10, b.z)


    def test_inplace_divide(self):
        """Test inplace divide, a.k.a. scale"""
        a = space.space(self.A, self.B, self.C)
        a /= 10

        self.assertEqual(self.A/10, a.x)
        self.assertEqual(self.B/10, a.y)
        self.assertEqual(self.C/10, a.z)


    def DISABLED_test_divide_zero(self):
        """Test divide by zero to raise exception"""
        a = space.space(self.A, self.B, self.C)
        self.assertRaises(RuntimeError, a / 0)


    def test_magnitude(self):
        """Test magnitude"""
        a = space.space(self.A, self.B, self.C)

        self.assertAlmostEqual(self.magnitude, a.magnitude(), self.places)


    def test_normalized(self):
        """Test normalized"""
        a = space.space(self.A, self.B, self.C)
        b = a.normalized()
        self.assertAlmostEqual(1.0, b.magnitude())


    def test_cross(self):
        """Test cross product and static members"""
        z = space.cross(space.space.Ux, space.space.Uy)

        self.assertEqual(space.space.Uz.x, z.x)
        self.assertEqual(space.space.Uz.y, z.y)
        self.assertEqual(space.space.Uz.z, z.z)


if __name__ == '__main__':
    unittest.main()

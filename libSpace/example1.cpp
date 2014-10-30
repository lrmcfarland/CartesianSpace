// ============================================================
// Filename:    example1.cpp
//
// Description: Example of using libSpace
//
// Authors:     L.R. McFarland
// Created:     2014oct25
// ============================================================

#include <iostream>
#include <math.h>

#include <space.h>

int main () {

  Cartesian::space s1(10);
  Cartesian::space s2(0, 10);
  Cartesian::space s3;

  std::cout << "s1 = " << s1 << std::endl;
  std::cout << "s2 = " << s2 << std::endl;

  s3 = Cartesian::cross(s1, s2);

  std::cout << "s1 x s2 = " << s3 << std::endl;

  return 0;
}

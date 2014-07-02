# Cartesian Space C++ library

This is my C++ implementation of a Cartesian space object for use in
physics applications as a full featured C++ object. It is built around
three doubles for x, y and z. The math operators are overloaded to
support vector arithmetic.

To debug with gdb (or lldb on OS X) using the gtest filter, use the
full method name (in this example Cartesian::rotator::rotate) to set
the break point and --gtest_filter with the GTEST name
(XRotationTest.Positive90AboutZ) to only run that test.

    $ lldb space_unittest
    Current executable set to 'space_unittest' (x86_64).

    (lldb) **b Cartesian::rotator::rotate**
    Breakpoint 1: where = libSpace.1.dylib`Cartesian::rotator::rotate(Cartesian::space const&, double const&) + 42 at space.cpp:202, address = 0x000000000000313a

    (lldb) **run --gtest_filter=XRotationTest.Positive90AboutZ**
    Process 27285 launched: '/Users/lrm/src/GitHub/CartesianSpace/libSpace/space_unittest' (x86_64)
    1 location added to breakpoint 1
    Note: Google Test filter = XRotationTest.Positive90AboutZ
    [==========] Running 1 test from 1 test case.
    [----------] Global test environment set-up.
    [----------] 1 test from XRotationTest
    [ RUN      ] XRotationTest.Positive90AboutZ
    Process 27285 stopped
    * thread #1: tid = 0x1a21ba, 0x00000001000fe13a libSpace.1.0.0.dylib`Cartesian::rotator::rotate(this=0x00007fff5fbff388, a_heading=0x0000000100117b30, a_radians=0x00007fff5fbff3d0) + 42 at space.cpp:202, queue = 'com.apple.main-thread', stop reason = breakpoint 1.2
	frame #0: 0x00000001000fe13a libSpace.1.0.0.dylib`Cartesian::rotator::rotate(this=0x00007fff5fbff388, a_heading=0x0000000100117b30, a_radians=0x00007fff5fbff3d0) + 42 at space.cpp:202
       199	Cartesian::space Cartesian::rotator::rotate(const Cartesian::space& a_heading,
       200						    const double& a_radians) {
       201
    -> 202	  if (m_is_new_axis || m_old_radians != a_radians) {
       203
       204	    double c(cos(a_radians));
       205	    double s(sin(a_radians));

    (lldb) p a_heading
    (const Cartesian::space) $0 = (m_x = 1, m_y = 0, m_z = 0)

    (lldb) p a_radians
    (const double) $0 = 1.5707963267948966

    (lldb) c
    Process 27285 resuming
    [       OK ] XRotationTest.Positive90AboutZ (14058 ms)
    [----------] 1 test from XRotationTest (14058 ms total)

    [----------] Global test environment tear-down
    [==========] 1 test from 1 test case ran. (14058 ms total)
    [  PASSED  ] 1 test.
    Process 27285 exited with status = 0 (0x00000000)
    (lldb) ^D

# ===============================================================
# Filename:    Makefile
# Description: makes libSpace.so and test scripts
# Author:      L.R. McFarland, lrm@starbug.com
# Created:     2011 Oct 02
#
#              optional debugging (-g) and optimize for speed (-O)
#              linux support (the following is OS X/Darwin specific):
#                  -dynamiclib
#                  -fpic (position independent code) vs. -fPIC
#
# ===============================================================

# where to find google's gtest code
GTEST_DIR = /usr/local/gtest-1.7.0

# programs and flags
CXX      = g++
CXXFLAGS = -g -W -Wall -fPIC -I.

LINK     = g++
DYLFLAGS  = -headerpad_max_install_names -single_module -dynamiclib -compatibility_version 1.0 -current_version 1.0.0 -install_name libSpace.1.dylib

RM       = rm -f
LN       = ln -s
AR       = ar cq
RANLIB   = ranlib -s

# targets

INCLUDES = space.h
SOURCES = space.cpp
OBJECTS = space.o

TARGET_A = libSpace.a

# Detect operating system flavor.
UNAME   := $(shell uname)

# .dylib is only for Darwin
ifeq ($(UNAME), Darwin)
TARGET_D = libSpace.1.0.0.dylib
TARGET_D0 = libSpace.dylib
TARGET_D1 = libSpace.1.dylib
TARGET_D2 = libSpace.1.0.dylib
endif

# builds

all: staticlib $(TARGET_D)

staticlib: $(TARGET_A)

$(TARGET_A): $(OBJECTS) $(INCLUDES)
	-$(RM) $(TARGET_A)
	$(AR) $(TARGET_A) $(OBJECTS)
	$(RANLIB) $(TARGET_A)

$(TARGET_D): $(OBJECTS) $(INCLUDES)
	-$(RM) $(TARGET_D) $(TARGET_D0) $(TARGET_D1) $(TARGET_D2)
	$(LINK) $(DYLFLAGS) -o $(TARGET_D) $(OBJECTS)
	-$(LN) $(TARGET_D) $(TARGET_D0)
	-$(LN) $(TARGET_D) $(TARGET_D1)
	-$(LN) $(TARGET_D) $(TARGET_D2)


main: main.o $(TARGET_A)
	g++ main.o -o main -L. -lSpace

mepsilon: mepsilon.c
	g++ mepsilon.c -o mepsilon

test: space_unittest
	./space_unittest

space_unittest: space_unittest.o $(TARGET_D)
	g++ -L$(GTEST_DIR) -lgtest -L. -lSpace space_unittest.o -o space_unittest

space_unittest.o: space_unittest.cpp
	g++ -I$(GTEST_DIR)/include -I . -g -c space_unittest.cpp

example1: example1.o $(TARGET_D)
	g++ example1.o -o example1 -L. -lspace

clean:
	-$(RM) main
	-$(RM) main.o
	-$(RM) space_unittest
	-$(RM) space_unittest.o
	-$(RM) mepsilon
	-$(RM) mepsilon.o
	-$(RM) example1
	-$(RM) example1.o
	-$(RM) $(OBJECTS)
	-$(RM) $(TARGET_D0) $(TARGET_D1) $(TARGET_D2)
	-$(RM) $(TARGET_D)
	-$(RM) $(TARGET_A)

clobber: clean
	-$(RM) *~

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
LFLAGS  = -headerpad_max_install_names -single_module -dynamiclib -compatibility_version 1.0 -current_version 1.0.0 -install_name libSpace.1.dylib

RM       = rm -f
LN       = ln -s
AR       = ar cq
RANLIB   = ranlib -s

# targets

INCLUDES = space.h
SOURCES = space.cpp
OBJECTS = space.o

TARGET  = libSpace.1.0.0.dylib
TARGETA = libSpace.a
TARGET0 = libSpace.dylib
TARGET1 = libSpace.1.dylib
TARGET2 = libSpace.1.0.dylib

# Detect operating system flavor.
UNAME   := $(shell uname)

# .dylib is only for Darwin, so remove the target.
ifneq ($(UNAME), Darwin)
TARGET = 
TARGET0 = 
TARGET1 = 
TARGET2 = 
endif

# builds

$(TARGET): $(OBJECTS) $(INCLUDES)
	-$(RM) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS)
	-$(LN) $(TARGET) $(TARGET0)
	-$(LN) $(TARGET) $(TARGET1)
	-$(LN) $(TARGET) $(TARGET2)

staticlib: $(TARGETA)

$(TARGETA): $(OBJECTS) $(INCLUDES)
	-$(RM) $(TARGETA)
	$(AR) $(TARGETA) $(OBJECTS)
	$(RANLIB) $(TARGETA)

all: staticlib main

main: main.o $(TARGET)
	g++ main.o -o main -L. -lSpace

mepsilon: mepsilon.c
	g++ mepsilon.c -o mepsilon

test: space_unittest
	./space_unittest

space_unittest: space_unittest.o $(TARGET)
	g++ -L$(GTEST_DIR) -lgtest -L. -lSpace space_unittest.o -o space_unittest

space_unittest.o: space_unittest.cpp
	g++ -I$(GTEST_DIR)/include -I . -g -c space_unittest.cpp

clean:
	-$(RM) mepsilon
	-$(RM) mepsilon.o
	-$(RM) main
	-$(RM) main.o
	-$(RM) space_unittest
	-$(RM) space_unittest.o
	-$(RM) $(OBJECTS)
	-$(RM) $(TARGET0) $(TARGET1) $(TARGET2)
	-$(RM) $(TARGET)
	-$(RM) $(TARGETA)

clobber: clean
	-$(RM) *~

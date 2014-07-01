# ===============================================================
# Filename:    Makefile
# Description: makefile to run build, test commands
# Author:      L.R. McFarland
# Created:     2014 Jun 29
# ===============================================================

# Detect operating system flavor.
UNAME   := $(shell uname)

# TODO improve
ifeq ($(UNAME), Darwin)
PYINCS = /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
endif

all:

space_module: space_swig
	g++ -fPIC -I. -c space.cpp
	g++ -fPIC -I$(PYINCS) -c space_wrap.cxx
	g++ -lpython -dynamiclib space.o space_wrap.o -o _space.so

space_swig: space.i space.h space.cpp
	swig -c++ -python space.i


test: space_module
	python test_space.py -v

clean:
	-$(RM) space_wrap.cxx space_wrap.o
	-$(RM) space.py space.pyc
	-$(RM) space.o
	-$(RM) _space.so


clobber: clean
	-$(RM) *~

# ===============================================================
# Filename:    Makefile
# Description: Makefile to run build, test commands
# Author:      L.R. McFarland
# Created:     2013jun17
# ===============================================================

OSXFLAGS = env ARCHFLAGS="-arch x86_64 -Wno-error=unused-command-line-argument-hard-error-in-future"

all: build

build: setup.py boost_space_module.cpp
	${OSXFLAGS} python setup.py build

test: build test_space.py
	./test_space.sh -v

clean:
	rm -rf build

clobber:
	rm -rf build
	rm *~

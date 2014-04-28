# ===============================================================
# Filename:    Makefile
# Description: makefile to run build, test commands
# Author:      L.R. McFarland
# Created:     27 Mar 2009
# ===============================================================

OSXFLAGS = env ARCHFLAGS="-arch x86_64 -Wno-error=unused-command-line-argument-hard-error-in-future"
SOURES = space.cpp test_space.py

all: build

build: space.cpp setup.py
	${OSXFLAGS} python setup.py build

test: build
	./test_space.sh -v

clean:
	rm -rf build

clobber:
	rm -rf build
	rm *~

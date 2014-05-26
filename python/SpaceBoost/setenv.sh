#!/usr/bin/env bash
#
# Shell wrapper to set up OS X python environment
#
# TODO: add linux support
#

# python path

if [ -z "$ORBITS_ROOT" ]; then
    ORBITS_ROOT=../..
    echo "# ORBITS_ROOT not set. Using" $ORBITS_ROOT
else
    echo "# ORBITS_ROOT is" $ORBITS_ROOT
fi

SPACE_SO=`find . -name space.so`

if [ -z "$SPACE_SO" ]; then
    echo "space.so not found"
    exit 1
else
    echo "# space.so:" $SPACE_SO # TODO
    export PYTHONPATH=${PYTHONPATH}:$(dirname ${SPACE_SO})
fi

# env

ORBITS_LIBRARY_PATH=${ORBITS_ROOT}/libSpace
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${ORBITS_LIBRARY_PATH}

echo '# DYLD_LIBRARY_PATH' ${DYLD_LIBRARY_PATH}
echo '# PYTHONPATH' ${PYTHONPATH}
echo # linefeed

# EoF

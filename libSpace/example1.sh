#!/usr/bin/env bash
#
# Shell wrapper to set up library path for sim
#
# TODO: add linux support
#

if [ -z "$CARTESIAN_SPACE_ROOT" ]; then
    CARTESIAN_SPACE_ROOT=..
    echo "# CARTESIAN_SPACE_ROOT not set. Using" $CARTESIAN_SPACE_ROOT
else
    echo "# CARTESIAN_SPACE_ROOT is" $CARTESIAN_SPACE_ROOT
fi

CARTESIAN_SPACE_LIBRARY_PATH=${CARTESIAN_SPACE_ROOT}/libSpace

# if OSX
DYLD_LIBRARY_PATH=${CARTESIAN_SPACE_LIBRARY_PATH} ${CARTESIAN_SPACE_ROOT}/libSpace/example1 "$@"

# EoF

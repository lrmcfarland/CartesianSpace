#!/usr/bin/env bash
#
# Shell wrapper to set up OS X python environment
#
# TODO: add linux support
#

# --------------------------------
# ----- Cartesian space root -----
# --------------------------------

if [ -n "$CARTESIAN_SPACE_ROOT" ]; then
    echo "# CARTESIAN_SPACE_ROOT is" $CARTESIAN_SPACE_ROOT
else
    CARTESIAN_SPACE_ROOT=../..
    echo "# CARTESIAN_SPACE_ROOT not set. Using" $CARTESIAN_SPACE_ROOT
fi

# ----------------------------
# ----- set library path -----
# ----------------------------

CARTESIAN_LIBRARY_PATH=${CARTESIAN_SPACE_ROOT}/libSpace
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${CARTESIAN_LIBRARY_PATH}

# ---------------------------
# ----- set python path -----
# ---------------------------

SPACE_SO=`find ${CARTESIAN_SPACE_ROOT}/python/Boost -name space.so`

if [ -n "$SPACE_SO" ]; then
    echo "# space.so:" $SPACE_SO
    export PYTHONPATH=${PYTHONPATH}:$(dirname ${SPACE_SO})
else
    echo "space.so not found"
    exit 1
fi

# -----------------------
# ----- echo result -----
# -----------------------

echo '# DYLD_LIBRARY_PATH' ${DYLD_LIBRARY_PATH}
echo '# PYTHONPATH' ${PYTHONPATH}
echo  # linefeed

# EoF

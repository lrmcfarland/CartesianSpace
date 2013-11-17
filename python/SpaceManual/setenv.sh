#!/usr/bin/env bash
#
# Shell wrapper to set up python environment
#
# TODO: add linux support
#

if [ -z "$ORBITS_ROOT" ]; then
    ORBITS_ROOT=../../
    echo "ORBITS_ROOT not set. Using" $ORBITS_ROOT
else
    echo "ORBITS_ROOT is" $ORBITS_ROOT
fi

ORBITS_LIBRARY_PATH=${ORBITS_ROOT}/libSpace
export DYLD_LIBRARY_PATH=${DYLD_LIBRARY_PATH}:${ORBITS_LIBRARY_PATH}

# set OSX version

OSX_Version=`sw_vers -productVersion`

echo "OS X:" $OSX_Version

if [[ "$OSX_Version" =~ 10.6.* ]] ; then

    export PYTHONPATH=${PYTHONPATH}:${ORBITS_ROOT}/python/SpaceManual/build/lib.macosx-10.6-x86_64-2.7

elif [[ "$OSX_Version" =~ 10.7.* ]] ; then

    export PYTHONPATH=${PYTHONPATH}:${ORBITS_ROOT}python/SpaceManual/build/lib.macosx-10.7-intel-2.7/

elif [[ "$OSX_Version" =~ 10.8.* ]] ; then

    export PYTHONPATH=${PYTHONPATH}:${ORBITS_ROOT}/python/SpaceManual/build/lib.macosx-10.8-x86_64-2.7/

elif [[ "$OSX_Version" =~ 10.9.* ]] ; then

    export PYTHONPATH=${PYTHONPATH}:${ORBITS_ROOT}/python/SpaceManual/build/lib.macosx-10.9-intel-2.7/

else

    echo "OSX Version yet not supported:" $OSX_Version
    exit 1

fi

# EoF

#!/usr/bin/env bash
#
# Run space unit tests

. ./setenv.sh

python ./test_space.py "$@"

# EoF

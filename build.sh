#!/bin/sh
#
# build.sh
# Script to build checkpass
# By J. Stuart McMurray
# Created 20160526
# Last Modified 20160526

set -e
set -x

cc -O2 -Wall --pedantic -o checkpass checkpass.c -static

#!/bin/bash

# liburt: Highly portable drop-in replacement for libgcc or compiler-rt.
# by Mibi88
#
# This software is licensed under the BSD-3-Clause license:
#
# Copyright 2025 Mibi88
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
# contributors may be used to endorse or promote products derived from this
# software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

help="USAGE: $0 [-d]\n"\
"A small tool to compile liburt.\n\n"\
"Options:\n"\
"  -d   Debug build (-O0 and no LTO)\n"\
"  -n   Support non ANSI C features\n"\
"  -c   Libc avilable\n"\
"  -s   Compile as a shared library\n"\
"  -h   Show this help message"

cc=clang
ld=clang
ar=llvm-ar

cflags=(-Wall -Wextra -Wpedantic -Isrc -Iinclude)
ldflags=()

builddir=build

name=liburt
srcdir=src
testdir=tests

debug=false
nonansi=false
shared=false
has_libc=false

errorcheck() {
    rc=$?
    if [ $rc -ne 0 ]; then
        echo "-- Build failed with exit code $rc!"
        echo "-- Exiting $rootdir..."
        cd $orgdir
        exit $rc
    fi
}

while getopts "dncsh" flag; do
    case "${flag}" in
        d) debug=true ;;
        n) nonansi=true ;;
        c) libc_available=true ;;
        s) shared=true ;;
        h) echo -e $help
           exit 0 ;;
    esac
done

if [ $debug = true ]; then
    echo "-- Debug build..."
    cflags+=(-O0 -g)
    ldflags+=(-g)
else
    echo "-- Release build..."
    cflags+=(-Os)
    ldflags+=(-flto=auto)
fi

if [ $nonansi = true ]; then
    echo "-- Supporting non ANSI C features!"
    cflags+=(-DURT_NONANSI)
else
    cflags+=(-ansi)
fi

if [ $has_libc = true ]; then
    echo "-- Libc available"
    cflags+=(-DURT_HAS_LIBC)
fi

libcflags=${cflags[@]}

if [ $shared = true ]; then
    echo "-- Shared library build..."
    libcflags+=(-fpic)
fi

rootdir=$(dirname $0)
orgdir=$(pwd)
echo "-- Entering $rootdir..."
cd $rootdir

mkdir -p $builddir

objfiles=()

for i in $(find $srcdir -mindepth 1 -type f \( -name "*.c" -o -name "*.s" \
           -o -name "*.S" \)); do
    obj=$builddir/${i#$srcdir*}.o
    echo "-- Compiling ${i} to ${obj}..."
    mkdir -p $(dirname $obj)
    $cc -c $i -o $obj ${libcflags[@]}
    errorcheck
    objfiles+=($obj)
done

echo "-- Generating $name.a..."
rm -f $name.a
$ar rsv $name.a ${objfiles[@]}

if [ $shared = true ]; then
    echo "-- Generating $name.so..."
    $ld -shared ${ldflags[@]} ${objfiles[@]} -o $name.so
fi

# Compile the tests
objfiles=()

for i in $(find $testdir -mindepth 1 -type f \( -name "*.c" -o -name "*.s" \
           -o -name "*.S" \)); do
    obj=$builddir/${i#$srcdir*}.o
    echo "-- Compiling ${i} to ${obj}..."
    mkdir -p $(dirname $obj)
    $cc -c $i -o $obj ${cflags[@]}
    errorcheck
    objfiles+=($obj)
done

# Linking
echo "-- Linking $name..."
$ld ${objfiles[@]} -nodefaultlibs -lc -lm $name.a -o $name ${ldflags[@]}

errorcheck

echo "-- Exiting $rootdir..."
cd $orgdir
echo "-- Build succeeded!"

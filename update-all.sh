#!/bin/bash
#
# @file update-all.sh
#   update all shttpd binary files for end users.
# 
# @author: 350137278@qq.com
#
# @create: 2020-07-05
# @update: 2020-07-05
########################################################################
_file=$(readlink -f $0)

_cdir=$(dirname $_file)
_name=$(basename $_file)
_ver=1.0.0


# Treat unset variables as an error (set -u / +u)
set -o nounset

# Treat any error as exit (set -e / +e)
set -o errexit

################################################################
bindir=$_cdir/libshttpd

rm -rf $bindir

mkdir -p $bindir/bin/{x64,Win32}

mkdir -p $bindir/include/shttpd

mkdir -p $bindir/lib/{x64,Win32}

libtarget=$_cdir/msvc/libshttpd/target
binexample=$_cdir/msvc/example/target
binshttpd=$_cdir/msvc/shttpd/target

echo "[1] update libshttpd lib: $libtarget => $bindir/lib"
cp -r $libtarget/x64/Debug $bindir/lib/x64/
cp -r $libtarget/x64/Release/ $bindir/lib/x64/

cp -r $libtarget/Win32/Debug $bindir/lib/Win32/
cp -r $libtarget/Win32/Release/ $bindir/lib/Win32/

echo "[2] update example bin: $binexample => $bindir/bin"
cp $binexample/x64/Release/example.exe $bindir/bin/x64/
cp $binexample/Win32/Release/example.exe $bindir/bin/Win32/

echo "[3] update shttpd bin: $binshttpd => $bindir"
cp $binshttpd/x64/Release/shttpd.exe $bindir/bin/x64/
cp $binshttpd/Win32/Release/shttpd.exe $bindir/bin/Win32/

echo "[4] update libshttpd include: $_cdir/src => $bindir/include"
cp $_cdir/src/shttpd.h $bindir/include/shttpd/

echo "Update all files success: $bindir"


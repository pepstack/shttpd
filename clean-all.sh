#!/bin/bash
#
# @file clean-all.sh
#   clean all intermediate files.
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

rm -rf "$bindir"

rm -rf "$_cdir/msvc/shttpd.VC.db"

find "$_cdir/msvc/example/" -maxdepth 1 \
    -not -name 'example' -and \
    -not -name 'example.vcxproj' \
    -and -not -name 'example.vcxproj.filters' | xargs rm -rf


find "$_cdir/msvc/libshttpd/" -maxdepth 1 -not -name 'libshttpd' -and -not -name 'libshttpd.vcxproj*' | xargs rm -rf

find "$_cdir/msvc/shttpd/" -maxdepth 1 -not -name 'shttpd' -and -not -name 'shttpd.vcxproj*' | xargs rm -rf

echo "success clean all files."

#!/bin/sh

# This script is used to setup your build after you clone it from git or if configure.ac or Makefile.am are modified. You should not need it in any other circumstance.
# It is based on guidance and the linked example from this stackoverflow article:
# https://stackoverflow.com/questions/3290908/which-files-generated-by-autotools-should-i-keep-in-version-control-repository 

## Autotools generation
echo "Generating Autotools files"
autoreconf --install || exit 1
echo "Finished generating Autotools files"
echo ""

echo "Now run './configure' and 'make'"
echo "Additionally run 'make install' if you wish to install this program"
echo ""

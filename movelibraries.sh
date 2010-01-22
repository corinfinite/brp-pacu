#!/bin/sh
# Copyright (C) 2010 Andreas Schwab andreas.schwab@mcgill.ca
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Library General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
######################################################
# Find dynamic shared libraries to be incorporated
# into an OS-X application bundle 
# and change installnames to be relative to
# the executable in the application
#
# usage: 
#   movelibraries.sh APPLICATION SOURCE_LIB
#   where APPLICATION is the path to the application 
#   and SOURCE_LIB is the absolute path of the directory
#   that contains the dynamic shared libraries
#   to be copied to the application.
#
######################################################
###########################
APPL_CONTENTS=`cd "$1"/Contents; pwd`
SOURCE_LIB="$2"
#### Define temporary files ####
TMP1=`mktemp /tmp/BRPXXXXXX`
TMP2=`mktemp /tmp/BRPXXXXXX`
cd "$APPL_CONTENTS"/Frameworks
#### Make a list of dylibs liked by the executable or any dylibs already in the application ####
otool -L $APPL_CONTENTS/MacOS/* `ls` \
    | sed -n 's:'"$SOURCE_LIB"'.*/\(.*\) (.*:\1:p' \
    | sort -u -o $TMP1
#### Test if any more dylibs have been added to the list
cd "$SOURCE_LIB"
until cmp -s $TMP1 $TMP2
  #### save old list
  do cp $TMP1 $TMP2
  #### Add any dylibs linked by existing dylibs to the list ####
  otool -L `cat $TMP1` | \
    sed -n 's:'"$SOURCE_LIB"'.*/\(.*\) (.*:\1:p' \
    | sort -u \
    | sort -mu - $TMP1 -o $TMP1
done
#### Copy the dylibs to the destination directory
cp -p `cat $TMP1` $APPL_CONTENTS/Frameworks
#### Change install names to be relative to the executable in the application
for i in "$APPL_CONTENTS"/Frameworks/* "$APPL_CONTENTS"/MacOS/*
  do install_name_tool `otool -L $i \
       | sed -n  '\:'"$SOURCE_LIB"': s/\(.*\/\)\(.*\) (.*/-change \1\2 @executable_path\/..\/Frameworks\/\2 /p'` \
  $i
done
#### clean up ####
rm $TMP1 $TMP2


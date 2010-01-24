# Copyright (C) 2007-2008 Brian Phelps(lm317t@gmail.com)
# Macintosh implementation Copyright (C) 2009 Andreas Schwab
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

bin_PROGRAMS = BRP_PACU
pkgconfigdir = $(libdir)/pkgconfig
BRP_PACU_SOURCES = testfft.c gui.c BRP_PACU.c 
include_HEADERS = testfft.h gui.h main.h
EXTRA_DIST = BRP_PACU.ui sinc.png info.plist \
 sinc.icns sinc.xcf brpData.icns README-Mac.txt INSTALL-Mac.txt movelibraries.sh
AM_CFLAGS =  -O2 -Wall -g `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gdk-2.0` `pkg-config --cflags glib-2.0`  `pkg-config --cflags  gtkdatabox` -DDATADIR=\"$(datadir)\" -lgthread-2.0
LIBS =   -lm  -lfftw  `pkg-config --libs  gtk+-2.0` `pkg-config --libs  gdk-2.0` `pkg-config --libs glib-2.0` `pkg-config --libs gthread-2.0` `pkg-config --libs gtkdatabox`  `pkg-config --libs jack` 
pkgdata_DATA = BRP_PACU.ui sinc.png
#########  Macintosh implementation #########
if APPLE
PKG_CONFIG_PATH+=@PKG_CONFIG_PATH@
export PKG_CONFIG_PATH
MACAPPLICATION=macdistdir/BRP-PACU.app
MACCONTENTS=$(MACAPPLICATION)/Contents
MACRESOURCES=$(MACCONTENTS)/Resources
MACFRAMEWORKS=$(MACCONTENTS)/Frameworks
MACEXECUTABLE=$(MACCONTENTS)/MacOS/BRP_PACU
MACDISK=BRP-PACU-mac-$(VERSION)
AM_LDFLAGS=-framework Carbon
AM_CFLAGS += `pkg-config --cflags  gdk-quartz-2.0` `pkg-config --cflags ige-mac-integration`
LIBS += `pkg-config --libs gdk-quartz-2.0` `pkg-config --libs ige-mac-integration`
$(MACCONTENTS): BRP_PACU.ui AUTHORS COPYING COPYING.LESSER NEWS ChangeLog README-Mac.txt sinc.icns brpData.icns info.plist
	mkdir -p $(MACRESOURCES)/en.lproj $(MACCONTENTS)/MacOS $(MACFRAMEWORKS)
	cp -fp BRP_PACU.ui sinc.icns brpData.icns sinc.png $(MACRESOURCES)
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS ChangeLog README-Mac.txt $(MACRESOURCES)/en.lproj
	sed -e 's/VERSION/$(VERSION)/' < info.plist > $(MACCONTENTS)/info.plist
	echo APPLBRPP > $(MACCONTENTS)/PkgInfo
	cp -fRP `pkg-config --variable=libdir gtkdatabox`/libgtkdatabox*.dylib $(MACFRAMEWORKS)
macapplication: $(MACAPPLICATION)
$(MACAPPLICATION): $(bin_PROGRAMS) $(MACCONTENTS) 
	cp $(bin_PROGRAMS) $(MACEXECUTABLE)
# Change install names to be relative to the executable in the application
	movelibraries.sh $(MACAPPLICATION) `pkg-config --variable=libdir gtk+-2.0`
	install_name_tool \
          `otool -L $(MACEXECUTABLE) | sed -n  '\:/libgtkdatabox: s/\(.*\/\)\(.*\) (.*/-change \1\2 @executable_path\/..\/Frameworks\/\2 /p'` \
	  $(MACEXECUTABLE)
	touch $(MACAPPLICATION)
# create distribution disk image
macdist: $(MACDISK).dmg
$(MACDISK).dmg: $(MACAPPLICATION) AUTHORS COPYING COPYING.LESSER NEWS ChangeLog macdistdir README-Mac.txt
	test -z $(MACDISK).dmg || rm -f $(MACDISK).dmg
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS ChangeLog macdistdir
	cp -fp README-Mac.txt macdistdir/README
	hdiutil create -srcfolder macdistdir -fs HFS+J -volname $(MACDISK) $(MACDISK).dmg
clean-local:
	-rm -rf macdistdir
#############################################
endif

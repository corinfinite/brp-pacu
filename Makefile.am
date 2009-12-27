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
include_HEADERS = testfft.h gui.h main.h ige-mac-menu.h ige-mac-private.h ige-mac-dock.h ige-mac-image-utils.h
EXTRA_DIST = ige-mac-menu.c ige-mac-dock.c gui.glade sinc.png info.plist \
 sinc.icns sinc.xcf brpData.icns README-Mac.txt INSTALL-Mac.txt
AM_CFLAGS =  -O2 -Wall -g  `pkg-config --cflags libglade-2.0`  `pkg-config --cflags gtk+-2.0` `pkg-config --cflags gdk-2.0` `pkg-config --cflags glib-2.0`  `pkg-config --cflags  gtkdatabox` -DDATADIR=\"$(datadir)\"
LIBS =   -lm  -lfftw  `pkg-config --libs  libglade-2.0`  `pkg-config --libs  gtk+-2.0` `pkg-config --libs  gdk-2.0`  `pkg-config --libs gtkdatabox` `pkg-config --libs jack` 
pkgdata_DATA = gui.glade sinc.png ige-mac-menu.c
#########  Macintosh implementation #########
if APPLE
BRP_PACU_SOURCES += ige-mac-menu.c ige-mac-dock.c
PKG_CONFIG_PATH+=@PKG_CONFIG_PATH@
export PKG_CONFIG_PATH
MACAPPLICATION=macdistdir/BRP-PACU.app
MACDISTRESOURCES=$(MACAPPLICATION)/Contents/Resources
MACEXECUTABLE=$(MACAPPLICATION)/Contents/MacOS/BRP_PACU
INFOPLIST=$(MACAPPLICATION)/Contents/info.plist
MACDISK=BRP-PACU-mac-$(VERSION)
AM_CFLAGS+=-xobjective-c 
AM_LDFLAGS=-framework Carbon -lobjc
LINK = $(CCLD) $(AM_LDFLAGS) $(LDFLAGS) -o $@
$(INFOPLIST): gui.glade AUTHORS COPYING COPYING.LESSER NEWS ChangeLog README-Mac.txt sinc.icns brpData.icns info.plist
	mkdir -p $(MACDISTRESOURCES)/en.lproj $(MACAPPLICATION)/Contents/MacOS
	cp -fp gui.glade sinc.icns brpData.icns sinc.png $(MACDISTRESOURCES)
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS ChangeLog README-Mac.txt $(MACDISTRESOURCES)/en.lproj
	sed -e 's/VERSION/$(VERSION)/' < info.plist > $(INFOPLIST)
	echo APPLBRPP > $(MACAPPLICATION)/Contents/PkgInfo
macapplication: $(MACEXECUTABLE)
$(MACEXECUTABLE): $(BRP_PACU_SOURCES:.c=.o) $(INFOPLIST) 
# Use static libraries for libglade and gtkdatabox in application
	$(CCLD) -o $(MACEXECUTABLE) $(BRP_PACU_SOURCES:.c=.o) -lm -lpthread -lfftw `pkg-config --variable=libdir gtkdatabox`/libgtkdatabox.a `pkg-config --variable=libdir libglade-2.0`/libglade-2.0.a `pkg-config --libs jack` -framework Gtk -framework GLib -framework Cairo -framework CoreAudio -framework CoreServices -framework AudioUnit -framework Carbon -lxml2 -lpthread -lz -lm -lobjc
	touch $(MACAPPLICATION)
# create distribution disk image
macdist: $(MACDISK).dmg
$(MACDISK).dmg: $(MACEXECUTABLE)
	test -z $(MACDISK).dmg || rm -f $(MACDISK).dmg
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS ChangeLog macdistdir
	cp -fp README-Mac.txt macdistdir/README
	hdiutil create -srcfolder macdistdir -fs HFS+J -volname $(MACDISK) $(MACDISK).dmg
CLEANFILES=$(MACAPPLICATION) $(INFOPLIST) $(MACDISK).dmg
clean-local:
	-rm -rf macdistdir
else
AM_CFLAGS+=-lgthread-2.0
endif
#############################################

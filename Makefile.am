# Copyright (C) 2007-2008 Brian Phelps(lm317t@gmail.com)
# Macintosh implementation Copyright (C) 2009-2013 Andreas Schwab
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
 sinc.icns sinc.xcf brpData.icns README-Mac.txt INSTALL-Mac.txt movelibraries.sh BRP_PACU_sh
AM_CFLAGS =  -O2 -Wall -g `pkg-config --cflags gtk+-3.0` `pkg-config --cflags gdk-3.0` `pkg-config --cflags glib-2.0`  `pkg-config --cflags  gtkdatabox` -DDATADIR=\"$(pkgdatadir)\" -lgthread-2.0 -DGTK_DISABLE_SINGLE_INCLUDES -DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGSEAL_ENABLE
LIBS =   -lm  -lfftw3  `pkg-config --libs  gtk+-3.0` `pkg-config --libs  gdk-3.0` `pkg-config --libs glib-2.0` `pkg-config --libs gthread-2.0` `pkg-config --libs gtkdatabox`  `pkg-config --libs jack`
pkgdata_DATA = BRP_PACU.ui sinc.png
AUTOMAKE_OPTIONS = foreign
#########  Macintosh implementation #########
if APPLE
PKG_CONFIG_PATH+=@PKG_CONFIG_PATH@
export PKG_CONFIG_PATH
MACAPPLICATION=macdistdir/BRP-PACU.app
MACCONTENTS=$(MACAPPLICATION)/Contents
MACRESOURCES=$(MACCONTENTS)/Resources
MACFRAMEWORKS=$(MACCONTENTS)/Frameworks
MACEXECUTABLE=$(MACCONTENTS)/MacOS/BRP_PACU
MACDISK=BRP-PACU-mac-$(VERSION).dmg
AM_LDFLAGS=-framework Carbon
AM_CFLAGS += `pkg-config --cflags gtk-mac-integration`
LIBS += `pkg-config --libs gdk-quartz-2.0` `pkg-config --libs gtk-mac-integration`
$(MACCONTENTS): BRP_PACU.ui AUTHORS COPYING COPYING.LESSER NEWS README-Mac.txt sinc.icns brpData.icns info.plist BRP_PACU_sh
	mkdir -p $(MACRESOURCES)/en.lproj $(MACRESOURCES)/pango $(MACRESOURCES)/pango/modules $(MACCONTENTS)/MacOS $(MACFRAMEWORKS)
	cp -fp BRP_PACU.ui sinc.icns brpData.icns $(MACRESOURCES)
	sed -e 's/GDK_CONTROL_MASK/GDK_META_MASK/' BRP_PACU.ui > $(MACRESOURCES)/BRP_PACU.ui
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS README-Mac.txt $(MACRESOURCES)/en.lproj
	sed -e 's/VERSION/$(VERSION)/' < info.plist > $(MACCONTENTS)/info.plist
	echo APPLBRPP > $(MACCONTENTS)/PkgInfo
	cp -fRP `pkg-config --variable=libdir gtkdatabox`/libgtkdatabox*.dylib $(MACFRAMEWORKS)
	touch $(MACCONTENTS)
macapplication: $(MACAPPLICATION)
$(MACAPPLICATION): $(bin_PROGRAMS) $(MACCONTENTS)
	cp $(bin_PROGRAMS) $(MACEXECUTABLE)
	cp BRP_PACU_sh $(MACCONTENTS)/MacOS
	cp `pkg-config --variable=libdir gtk+-2.0`/pango/1.8.0/modules/pango-basic-coretext.so $(MACRESOURCES)/pango/modules
# Change install names to be relative to the executable in the application
	./movelibraries.sh $(MACAPPLICATION) `pkg-config --variable=libdir gtk+-2.0`
	install_name_tool \
          `otool -L $(MACEXECUTABLE) | sed -n  '\:/libgtkdatabox: s/\(.*\/\)\(.*\) (.*/-change \1\2 @executable_path\/..\/Frameworks\/\2 /p'` \
	  $(MACEXECUTABLE)
	touch $(MACAPPLICATION)
# create distribution disk image
macdist: $(MACDISK)
$(MACDISK): $(MACAPPLICATION) AUTHORS COPYING COPYING.LESSER NEWS macdistdir README-Mac.txt
	test -z $(MACDISK) || rm -f $(MACDISK)
	cp -fp AUTHORS COPYING COPYING.LESSER NEWS macdistdir
	cp -fp README-Mac.txt macdistdir/README
	hdiutil create -srcfolder macdistdir -fs HFS+J -volname BRP-PACU-mac-$(VERSION) $(MACDISK)
clean-local:
	-rm -rf macdistdir
#############################################
endif

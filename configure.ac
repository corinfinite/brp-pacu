AC_INIT
########## Macintosh implementation #########
if [[ `uname` = 'Darwin' ]]
 then if [[ -n "PKG_CONFIG_PATH" ]]
   then PKG_CONFIG_PATH='/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig/:/Library/Frameworks/Gtk.framework/Resources/dev/lib/pkgconfig:/Library/Frameworks/GLib.framework/Resources/dev/lib/pkgconfig:/Library/Frameworks/Cairo.framework/Resources/dev/lib/pkgconfig/'
   export PKG_CONFIG_PATH
  fi
fi
AM_CONDITIONAL([APPLE], [ test `uname` = 'Darwin'])
AC_SUBST(PKG_CONFIG_PATH)
#############################################
AC_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(BRP_PACU,2.0.7)
AC_PROG_CC
AC_PROG_INSTALL
AC_OUTPUT(Makefile)
AC_CHECK_LIB(m,cos,,AC_MSG_ERROR([could not link to mathlib.]))
AC_CHECK_LIB(fftw,fftw_create_plan,,AC_MSG_ERROR([could not link to fftw please install the fftw package.]))
PKG_CHECK_MODULES(GTK, gtk+-2.0,,exit)
PKG_CHECK_MODULES(PANGO, pango,,exit)
PKG_CHECK_MODULES(CAIRO, cairo,,exit)
PKG_CHECK_MODULES(LIBGLADE, libglade-2.0,,exit)
PKG_CHECK_MODULES(GDK, gdk,,exit)
PKG_CHECK_MODULES(GTKDATABOX, gtkdatabox,,AC_MSG_ERROR([please install gtkdatabox development version.]))
PKG_CHECK_MODULES(JACK, jack,,AC_MSG_ERROR([please install the jack development version.]))


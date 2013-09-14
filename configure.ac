AC_INIT(BRP-PACU,2.1.2,lm317t@gmail.com)
########## Macintosh implementation #########
if [[ `uname` = 'Darwin' ]]
 then if [[ -n "PKG_CONFIG_PATH" ]]
   # Assume that PGK is installed with jhbuild in the home directory
   then PKG_CONFIG_PATH='/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig/:'$HOME'/gtk/inst/lib/pkgconfig'
   export PKG_CONFIG_PATH
  fi
fi
AM_CONDITIONAL([APPLE], [ test `uname` = 'Darwin'])
AC_SUBST(PKG_CONFIG_PATH)
#############################################
AC_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_INSTALL
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
AC_CHECK_LIB(m,cos,,AC_MSG_ERROR([could not link to mathlib.]))
AC_CHECK_LIB(fftw,fftw_create_plan,,AC_MSG_ERROR([could not link to fftw please install the fftw package.]))
PKG_CHECK_MODULES(GTK, gtk+-2.0,,exit)
PKG_CHECK_MODULES(PANGO, pango,,exit)
PKG_CHECK_MODULES(CAIRO, cairo,,exit)
#PKG_CHECK_MODULES(GDK-2.0, gdk-2.0,,exit)
PKG_CHECK_MODULES(GTKDATABOX, gtkdatabox,,AC_MSG_ERROR([please install gtkdatabox development version.]))
PKG_CHECK_MODULES(JACK, jack,,AC_MSG_ERROR([please install the jack development version.]))


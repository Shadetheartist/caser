AC_INIT([caser], [1.0.1], [b.derehemi@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_PROG_CC

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 tests/Makefile
])

AM_PATH_CHECK

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])

AC_OUTPUT

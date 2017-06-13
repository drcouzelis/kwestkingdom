AC_INIT([kwestkingdom], [0.2], [drcouzelis@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_PROG_CXX

AC_CHECK_HEADER([allegro.h], [], [AC_MSG_ERROR([header not found.])])
AC_SEARCH_LIBS([install_allegro], [alleg], [], [AC_MSG_ERROR([library not found.])])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT

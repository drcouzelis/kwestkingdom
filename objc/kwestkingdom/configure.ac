AC_INIT([kwestkingdom], [0.1], [drcouzelis@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_SRCDIR([src/KwestKingdom.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_OBJC

# Checks for libraries.
AC_CHECK_LIB([alleg], [install_allegro], [],
             [AC_MSG_ERROR([liballeg not found.])])

AC_CHECK_LIB([gnustep-base], [__objc_class_name_NSObject], [],
             [AC_MSG_ERROR([libgnustep-base not found.])])

AC_CHECK_LIB([objc], [__objc_exec_class], [],
             [AC_MSG_ERROR([libobjc not found.])])

#AC_DEFINE_UNQUOTED([PKGDATADIR], [$pkgdatadir],
#    [Define to the read-only architecture-independent package data directory.])
#AM_CPPFLAGS = -DPKGDATADIR='"$(pkgdatadir)"'

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/images/Makefile
                 data/sounds/Makefile
                 src/Makefile])

AC_OUTPUT

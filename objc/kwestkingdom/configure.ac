#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

#AC_PREREQ([2.69])
AC_INIT([kwestkingdom], [0.1], [drcouzelis@gmail.com])
AC_CONFIG_SRCDIR([src/KwestKingdom.h])
AM_INIT_AUTOMAKE([-Wall -Werror])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
#AC_PROG_CC
AC_PROG_OBJC

# Checks for libraries.
AC_CHECK_LIB([alleg], [allegro_init])
AC_CHECK_LIB([gnustep-base])
AC_CHECK_LIB([objc])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT

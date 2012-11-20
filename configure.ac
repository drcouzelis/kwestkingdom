# Run "autoreconf" to create the "configure" script.

# Initialize autoconf with the name of the program,
# the version number, and the contact information.
AC_INIT([kwestkingdom], [0.1], [drcouzelis@gmail.com])

# Initialize automake with all warnings.
AM_INIT_AUTOMAKE([-Wall -Werror])

# Mark the source code directory.
AC_CONFIG_SRCDIR([src/KwestKingdom.h])

# Rebuild these header files.
AC_CONFIG_HEADERS([config.h])

# Check for the Objective-C compiler.
AC_PROG_OBJC

# Check for libraries.
AC_CHECK_LIB([objc], [__objc_exec_class], [],
             [AC_MSG_ERROR([libobjc not found.])])

AC_CHECK_LIB([gnustep-base], [__objc_class_name_NSObject], [],
             [AC_MSG_ERROR([libgnustep-base not found.])])

AC_CHECK_LIB([alleg], [install_allegro], [],
             [AC_MSG_ERROR([liballeg not found.])])

# A list of the Makefiles that need to be created.
AC_CONFIG_FILES([Makefile
                 data/Makefile
                 data/images/Makefile
                 data/sounds/Makefile
                 src/Makefile])

# Finish up by writing the new configuration files.
AC_OUTPUT

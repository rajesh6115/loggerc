# Autoconf Minimum Version Required Check
AC_PREREQ([2.68])
# Initilise Autoconf with project Name and Version Details
AC_INIT([clogger], [1.0.0], [sahoorajesh.d@gmail.com], [clogger], [https://github.com/rajesh6115/loggerc])
# Put autotools auxiliary files in a subdir, so they don't clutter top dir:
AC_CONFIG_AUX_DIR([build-aux])
# Initialise Automake with Default version Number and Default CPP flags
AM_INIT_AUTOMAKE([1.11 -Wall -Werror ])
# Check for some Unique file in the Project
AC_CONFIG_SRCDIR([src/clogger.c])
# Check for C Compiler
AC_PROG_CC
# config.h will be created and default header
AC_CONFIG_HEADERS([config.h])
# all Macro in this folder
AC_CONFIG_MACRO_DIR([m4])
# AR required to create static library
AM_PROG_AR
# libtool Required  
LT_PREREQ([2.2])
LT_INIT([dlopen])
AC_ENABLE_SHARED
AC_PROG_LIBTOOL(libtool)

# Generate These Files for Sucessfully Build
AC_CONFIG_FILES([
		Makefile
		src/Makefile
])
AC_OUTPUT

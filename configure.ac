#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([librpigrafx], [2.0], [ysugi@idein.jp])
AM_INIT_AUTOMAKE([foreign -W -Wall])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# pkgconfig
AC_ARG_WITH(pkgconfigdir,
            AC_HELP_STRING([--with-pkgconfigdir=DIR],
                           [pkgconfig dir [default=LIBDIR/pkgconfig]]),
            [pkgconfigdir=${withval}],
            [pkgconfigdir=${libdir}/pkgconfig])
AC_MSG_NOTICE([pkgconfig directory is ${pkgconfigdir}])
AC_SUBST([pkgconfigdir])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR

# Checks for libraries.
PKG_CHECK_MODULES([BCM_HOST], [bcm_host],
                  [AC_SUBST([BCM_HOST_CFLAGS])
                   AC_SUBST([BCM_HOST_LIBS])],
                  [librpigrafx_cv_have_bcm_host="no"])
if test "$librpigrafx_cv_have_bcm_host" = "no"; then
  AC_CHECK_LIB([vcos], [vcos_vsnprintf],
               [],
               [AC_MSG_ERROR("missing -lvcos")])
  AC_CHECK_LIB([vchiq_arm], [vchiu_queue_init],
               [],
               [AC_MSG_ERROR("missing -lvchiq_arm")])
  AC_CHECK_LIB([bcm_host], [bcm_host_init],
               [],
               [AC_MSG_ERROR("missing -lbcm_host")])
fi
PKG_CHECK_MODULES([MMAL], [mmal],
                  [AC_SUBST([MMAL_CFLAGS])
                   AC_SUBST([MMAL_LIBS])],
                  [librpigrafx_cv_have_mmal="no"])
if test "$librpigrafx_cv_have_mmal" = "no"; then
  AC_CHECK_LIB([vcsm], [vcsm_init],
               [],
               [AC_MSG_ERROR("missing -lvcsm")])
  AC_CHECK_LIB([mmal_util], [mmal_util_rgb_order_fixed],
               [],
               [AC_MSG_ERROR("missing -lmmal_util")],
               [-lmmal_core])
  AC_CHECK_LIB([mmal_core], [mmal_ports_alloc],
               [],
               [AC_MSG_ERROR("missing -lmmal_core")])
  AC_CHECK_LIB([containers], [vc_uri_path],
               [],
               [AC_MSG_ERROR("missing -lcontainers")])
  AC_CHECK_LIB([mmal_components], [mmal_register_component_null_sink],
               [],
               [AC_MSG_ERROR("missing -lmmal_components")])
  AC_CHECK_LIB([mmal], [mmal_status_to_string],
               [],
               [AC_MSG_ERROR("missing -lmmal")])
  AC_CHECK_LIB([mmal_vc_client], [mmal_vc_use],
               [],
               [AC_MSG_ERROR("missing -lmmal_vc_client")])
fi
AC_CHECK_LIB([qmkl], [mailbox_qpu_enable],
             [QMKL_LIBS=-lqmkl
              AC_SUBST(QMKL_LIBS)],
             [AC_MSG_ERROR("missing -lqmkl")])
PKG_CHECK_MODULES([RPICAM], [librpicam],
                 [AC_SUBST([RPICAM_CFLAGS])
                  AC_SUBST([RPICAM_LIBS])],
                 [AC_MSG_ERROR("missing -lrpicam")])
PKG_CHECK_MODULES([RPIRAW], [librpiraw],
                  [AC_SUBST([RPIRAW_CFLAGS])
                  AC_SUBST([RPIRAW_LIBS])],
                 [AC_MSG_ERROR("missing -lrpiraw")])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdint.h stdlib.h])
AC_CHECK_HEADER([bcm_host.h], [], [AC_MSG_ERROR("missing bcm_host.h")])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_REALLOC

LT_INIT
AC_CONFIG_FILES([Makefile include/Makefile src/Makefile test/Makefile librpigrafx.pc])
AC_OUTPUT

AM_CFLAGS = -pipe -O2 -g -W -Wall -Wextra -I$(top_srcdir)/include $(BCM_HOST_CFLAGS) $(MMAL_CFLAGS)

lib_LTLIBRARIES = librpigrafx.la

librpigrafx_la_SOURCES = main.c mmal.c dispmanx.c local.c
librpigrafx_la_LIBADD = $(BCM_HOST_LIBS) $(MMAL_LIBS)

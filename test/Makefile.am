AM_CFLAGS = -pipe -O2 -g -W -Wall -Wextra -I$(top_srcdir)/include $(BCM_HOST_CFLAGS) $(MMAL_CFLAGS)

check_PROGRAMS = test_dispmanx

nodist_test_dispmanx_SOURCES = test_dispmanx.c
test_dispmanx_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS)

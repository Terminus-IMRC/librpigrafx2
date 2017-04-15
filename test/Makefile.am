AM_CFLAGS = -pipe -O2 -g -W -Wall -Wextra -I$(top_srcdir)/include $(BCM_HOST_CFLAGS) $(MMAL_CFLAGS)

check_PROGRAMS = test_dispmanx test_capture_and_render_once

nodist_test_dispmanx_SOURCES = test_dispmanx.c
test_dispmanx_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS)

nodist_test_capture_and_render_once_SOURCES = test_capture_and_render_once.c
test_capture_and_render_once_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS)

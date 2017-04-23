AM_CFLAGS = -pipe -O2 -g -W -Wall -Wextra -I$(top_srcdir)/include $(BCM_HOST_CFLAGS) $(MMAL_CFLAGS)

check_PROGRAMS = test_dispmanx test_capture_render_seq test_capture_edit_render_seq

nodist_test_dispmanx_SOURCES = test_dispmanx.c
test_dispmanx_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS)

nodist_test_capture_render_seq_SOURCES = test_capture_render_seq.c
test_capture_render_seq_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS) $(QMKL_LIBS)

nodist_test_capture_edit_render_seq_SOURCES = test_capture_edit_render_seq.c
test_capture_edit_render_seq_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS)

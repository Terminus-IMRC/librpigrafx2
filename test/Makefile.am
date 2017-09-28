AM_CFLAGS = -pipe -O2 -g -W -Wall -Wextra -I$(top_srcdir)/include $(BCM_HOST_CFLAGS) $(MMAL_CFLAGS) $(RPICAM_CFLAGS) $(RPIRAW_CFLAGS)

check_PROGRAMS = test_dispmanx test_capture_render_seq test_rawcam_imx219

nodist_test_dispmanx_SOURCES = test_dispmanx.c
test_dispmanx_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS) $(RPICAM_LIBS) $(RPIRAW_LIBS)

nodist_test_capture_render_seq_SOURCES = test_capture_render_seq.c
test_capture_render_seq_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS) $(QMKL_LIBS) $(RPICAM_LIBS) $(RPIRAW_LIBS)

nodist_test_rawcam_imx219_SOURCES = test_rawcam_imx219.c
test_rawcam_imx219_LDADD = $(top_builddir)/src/.libs/librpigrafx.a $(BCM_HOST_LIBS) $(MMAL_LIBS) $(RPICAM_LIBS) $(RPIRAW_LIBS)

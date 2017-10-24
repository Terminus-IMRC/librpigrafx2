#include <rpigrafx.h>
#include <stdio.h>
#include <sys/time.h>
#include <rpiraw.h>

#define _check(x) \
    do { \
        const int ret = ((x)); \
        if (ret) { \
            fprintf(stderr, "%s:%d: error: %d\n", __FILE__, __LINE__, ret); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

static double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double) tv.tv_sec + tv.tv_usec * 1e-6;
}

static void *frame = NULL;
static const int frame_width  = 2048,
                 frame_height = 2048;

static void sighandler_save_image(int signum)
{
    static unsigned cnt = 0;
    char file[100];
    int ret;

    (void) signum;

    if (frame == NULL)
        return;

    snprintf(file, sizeof(file) / sizeof(*file), "raw%04d.png", cnt);
    cnt ++;
    printf("Writing to %s\n", file);
    ret = rpiraw_write_png_rgb888(file, frame, frame_width,
            frame_width, frame_height);
    if (ret) {
        fprintf(stderr, "rpiraw_write_png_rgb888: %d\n", ret);
        exit(EXIT_FAILURE);
    }
}

int main()
{
    int i;
    const int nframes = 100;
    int screen_width, screen_height;
    rpigrafx_frame_config_t fc;
    double start, end, time;

    if (signal(SIGINT, sighandler_save_image) == SIG_ERR) {
        fprintf(stderr, "signal: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    rpigrafx_set_verbose(0);
    _check(rpigrafx_get_screen_size(&screen_width, &screen_height));
    _check(rpigrafx_config_camera_frame(0, frame_width, frame_height,
                                        MMAL_ENCODING_RGB24, 0, &fc));
    _check(rpigrafx_config_rawcam(RPIGRAFX_RAWCAM_CAMERA_MODEL_IMX219,
                                  MMAL_CAMERA_RX_CONFIG_DECODE_NONE,
                                  MMAL_CAMERA_RX_CONFIG_ENCODE_NONE,
                                  MMAL_CAMERA_RX_CONFIG_UNPACK_NONE,
                                  MMAL_CAMERA_RX_CONFIG_PACK_NONE,
                                  2, 10, RPIGRAFX_BAYER_PATTERN_BGGR, &fc));
    _check(rpigrafx_config_rawcam_imx219(24.0, 0, 0, 1, 1,
                                       RPIGRAFX_RAWCAM_IMX219_BINNING_MODE_NONE,
                                         &fc));
    _check(rpigrafx_config_camera_frame_render(0, 0, 0, screen_width, screen_height, 0, &fc));
    _check(rpigrafx_finish_config());

    start = get_time();
    for (i = 0; i < nframes; i ++) {
        fprintf(stderr, "#%d\n", i);
        _check(rpigrafx_capture_next_frame(&fc));
        frame = rpigrafx_get_frame(&fc);
        _check(rpigrafx_render_frame(&fc));
    }
    end = get_time();

    time = end - start;
    fprintf(stderr, "%f [s], %f [frame/s]\n", time, nframes / time);

    return 0;
}

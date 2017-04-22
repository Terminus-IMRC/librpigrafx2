#include <rpigrafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define _check(x) \
    do { \
        if ((x)) { \
            fprintf(stderr, "Error at %s:%d:%s\n", __FILE__, __LINE__, __func__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

static char *progname = NULL;

static double get_time()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double) t.tv_sec + t.tv_usec * 1e-6;
}

static void usage()
{
    fprintf(stderr, "Usage: %s CAMERA_NUM CAMERA_PORT NUM_FRAMES [WIDTH] [HEIGHT]\n", progname);
    fprintf(stderr, "CAMERA_PORT: 'p' for preview and 'c' for capture\n");
}

int main(int argc, char *argv[])
{
    int i, n, camera_num;
    int width = 1024, height = 768;
    rpigrafx_camera_port_t port = RPIGRAFX_CAMERA_PORT_PREVIEW;
    rpigrafx_frame_config_t fc;
    double start, time;

    progname = argv[0];

    if (argc < 1 + 3) {
        fprintf(stderr, "Invalid the number of the arguments.\n");
        usage();
        exit(EXIT_FAILURE);
    }
    camera_num = atoi(argv[1]);
    switch (argv[2][0]) {
        case 'p':
        case 'P':
            port = RPIGRAFX_CAMERA_PORT_PREVIEW;
            break;
        case 'c':
        case 'C':
            port = RPIGRAFX_CAMERA_PORT_CAPTURE;
            break;
        default:
            fprintf(stderr, "Invalid CAMERA_PORT parameter: %s\n", argv[2]);
            usage();
            exit(EXIT_FAILURE);
            break;
    }
    n = atoi(argv[3]);
    if (argc >= 1 + 4)
        width  = atoi(argv[4]);
    if (argc >= 1 + 5)
        height = atoi(argv[5]);

    rpigrafx_set_verbose(1);
    _check(rpigrafx_config_camera_frame(camera_num, width, height, MMAL_ENCODING_RGB24, 1, &fc));
    _check(rpigrafx_config_camera_port(camera_num, port));
    _check(rpigrafx_config_camera_frame_render(1, 0, 0, 0, 0, 5, &fc));
    _check(rpigrafx_finish_config());

    start = get_time();
    for (i = 0; i < n; i ++) {
        fprintf(stderr, "Frame #%d\n", i);
        _check(rpigrafx_capture_next_frame(&fc));
        _check(rpigrafx_render_frame(&fc));
    }
    time = get_time() - start;
    fprintf(stderr, "%f [s], %f [frame/s]\n", time, n / time);

    return 0;
}

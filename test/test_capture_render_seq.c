#include <rpigrafx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <qmkl.h>

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
    fprintf(stderr, "Usage: %s [OPTION]...\n", progname);
    fprintf(stderr,
            "\n"
            " Camera options:\n"
            "\n"
            "  -c CAMERA_NUM      Use camera CAMERA_NUM (default: 0)\n"
            "  -P                 Use preview port (default)\n"
            "  -C                 Use capture port\n"
            "  -w WIDTH\n"
            "  -h HEIGHT          Size of the capture frame\n"
            "                     Default is the size of the screen\n"
            "  -n NFRAMES         Capture and render NFRAMES frames (default: 20)\n"
            "\n"
            " Rendering options:\n"
            "\n"
            "  -f [FULLSCREEN]    Render frame in fullscreen or not (default: 1)\n"
            "  -x X\n"
            "  -y Y               Coordinations of render frame; default: (0,0)\n"
            "  -W WIDTH\n"
            "  -H HEIGHT          Size of render frame.\n"
            "                     Default is the size of the screen\n"
            "  -l LAYER           Layer of render frame (default: 5)\n"
            "\n"
            " Misc options:\n"
            "\n"
            "  -q                 Turn off/on QPU before/after each capture\n"
            "  -v [VERBOSE]       Be verbose or not (default: 1)\n"
            "  -?                 What you are doing\n"
           );
}

int main(int argc, char *argv[])
{
    int opt;
    int i, camera_num = 0, nframes = 20, width, height;
    int render_fullscreen = 1, render_layer = 5;
    int render_x = 0, render_y = 0, render_width, render_height;
    int mb = 0;
    _Bool on_off_qpu = 0;
    int verbose = 1;
    rpigrafx_camera_port_t camera_port = RPIGRAFX_CAMERA_PORT_PREVIEW;
    rpigrafx_frame_config_t fc;
    double start, time;

    progname = argv[0];

    rpigrafx_set_verbose(verbose);
    _check(rpigrafx_get_screen_size(&width, &height));
    render_width  = width;
    render_height = height;

    while ((opt = getopt(argc, argv, "c:PCw:h:n:f::x:y:W:H:l:qv::?")) != -1) {
        switch (opt) {
            case 'c':
                camera_num = atoi(optarg);
                break;
            case 'P':
                camera_port = RPIGRAFX_CAMERA_PORT_PREVIEW;
                break;
            case 'C':
                camera_port = RPIGRAFX_CAMERA_PORT_CAPTURE;
                break;
            case 'w':
                width  = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'n':
                nframes = atoi(optarg);
                break;
            case 'f':
                render_fullscreen = (optarg == 0) ? 1 : !!atoi(optarg);
                break;
            case 'x':
                render_x = atoi(optarg);
                break;
            case 'y':
                render_y = atoi(optarg);
                break;
            case 'W':
                render_width  = atoi(optarg);
                break;
            case 'H':
                render_height = atoi(optarg);
                break;
            case 'l':
                render_layer = atoi(optarg);
                break;
            case 'q':
                on_off_qpu = 1;
                break;
            case 'v':
                verbose = (optarg == 0) ? 1 : !!atoi(optarg);
                break;
            default:
                if (opt != '?')
                    fprintf(stderr, "error: Unknown option: %c\n", opt);
                usage();
                exit(EXIT_FAILURE);
        }
    }

    if (optind != argc) {
        fprintf(stderr, "error: Extra argument(s) after options.\n");
        exit(EXIT_FAILURE);
    }

    if (on_off_qpu)
        mb = mailbox_open();
    else
        mailbox_qpu_enable(mb, 0);

    rpigrafx_set_verbose(verbose);
    _check(rpigrafx_config_camera_frame(camera_num, width, height,
                                        MMAL_ENCODING_RGB24, 1, &fc));
    _check(rpigrafx_config_camera_port(camera_num, camera_port));
    _check(rpigrafx_config_camera_frame_render(render_fullscreen,
                                               render_x, render_y,
                                               render_width, render_height,
                                               render_layer, &fc));
    _check(rpigrafx_finish_config());

    start = get_time();
    for (i = 0; i < nframes; i ++) {
        fprintf(stderr, "Frame #%d\n", i);
        if (on_off_qpu)
            mailbox_qpu_enable(mb, 0);
        _check(rpigrafx_capture_next_frame(&fc));
        if (on_off_qpu)
            mailbox_qpu_enable(mb, 1);
        _check(rpigrafx_render_frame(&fc));
    }
    time = get_time() - start;
    fprintf(stderr, "%f [s], %f [frame/s]\n", time, nframes / time);

    if (on_off_qpu)
        mailbox_close(mb);
    else
        mailbox_qpu_enable(mb, 1);
    return 0;
}

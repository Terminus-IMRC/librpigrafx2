#include <rpigrafx.h>
#include <stdio.h>
#include <stdlib.h>

#define _check(x) \
    do { \
        int status = ((x)); \
        if (status) { \
            fprintf(stderr, "%s:%d: error: 0x%08x\n", __FILE__, __LINE__, status); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main(int argc, char *argv[])
{
    rpigrafx_frame_config_t fc;
    int camera_num;

    if (argc != 1 + 1) {
        fprintf(stderr, "Invalid the number of the arguments.\n");
        fprintf(stderr, "Usage: %s CAMERA_NUM\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    camera_num = atoi(argv[1]);

    _check(rpigrafx_config_camera_frame(camera_num, 512, 512, MMAL_ENCODING_OPAQUE, 1, &fc));
    _check(rpigrafx_config_camera_frame_render(1, 0, 0, 0, 0, 5, &fc));
    _check(rpigrafx_finish_config());
    _check(rpigrafx_capture_next_frame(&fc));
    _check(rpigrafx_render_frame(&fc));

    return 0;
}

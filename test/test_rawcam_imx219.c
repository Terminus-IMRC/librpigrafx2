#include <rpigrafx.h>
#include <stdio.h>

#define _check(x) \
    do { \
        const int ret = ((x)); \
        if (ret) { \
            fprintf(stderr, "%s:%d: error: %d\n", __FILE__, __LINE__, ret); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main()
{
    int i;
    int screen_width, screen_height;
    rpigrafx_frame_config_t fc;

    rpigrafx_set_verbose(1);
    _check(rpigrafx_get_screen_size(&screen_width, &screen_height));
    _check(rpigrafx_config_camera_frame(0, 2048, 2048,
                                        MMAL_ENCODING_RGB24, 0, &fc));
    _check(rpigrafx_config_rawcam(RPIGRAFX_RAWCAM_CAMERA_MODEL_IMX219,
                                  MMAL_CAMERA_RX_CONFIG_DECODE_NONE,
                                  MMAL_CAMERA_RX_CONFIG_ENCODE_NONE,
                                  MMAL_CAMERA_RX_CONFIG_UNPACK_NONE,
                                  MMAL_CAMERA_RX_CONFIG_PACK_NONE,
                                  2, 10, &fc));
    _check(rpigrafx_config_rawcam_imx219(24.0, 0, 0, 1, 1,
                                       RPIGRAFX_RAWCAM_IMX219_BINNING_MODE_NONE,
                                         &fc));
    _check(rpigrafx_config_camera_frame_render(0, 0, 0, screen_width, screen_height, 0, &fc));
    _check(rpigrafx_finish_config());

    for (i = 0; i < 100; i ++) {
        void *p = NULL;
        fprintf(stderr, "#%d\n", i);
        _check(rpigrafx_capture_next_frame(&fc));
        p = rpigrafx_get_frame(&fc);
        _check(rpigrafx_render_frame(&fc));
    }

    return 0;
}

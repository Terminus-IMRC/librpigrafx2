/*
 * Copyright (c) 2017 Sugizaki Yukimasa (ysugi@idein.jp)
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#ifndef RPIGRAFX2_H
#define RPIGRAFX2_H

#include <stdint.h>
#include <bcm_host.h>
#include <interface/mmal/mmal.h>

    struct callback_context {
        MMAL_STATUS_T status;
        MMAL_BUFFER_HEADER_T *header;
        _Bool is_header_passed_to_render;
    };

    typedef struct {
        int32_t camera_number;
        unsigned splitter_output_port_index;
        _Bool is_zero_copy_rendering;
        struct callback_context *ctx;
    } rpigrafx_frame_config_t;

    typedef enum {
        RPIGRAFX_CAMERA_PORT_PREVIEW,
        RPIGRAFX_CAMERA_PORT_CAPTURE
    } rpigrafx_camera_port_t;

    typedef enum {
        RPIGRAFX_RAWCAM_CAMERA_MODEL_IMX219
    } rpigrafx_rawcam_camera_model_t;

    typedef enum {
        RPIGRAFX_BAYER_PATTERN_BGGR,
        RPIGRAFX_BAYER_PATTERN_GRBG,
        RPIGRAFX_BAYER_PATTERN_GBRG,
        RPIGRAFX_BAYER_PATTERN_RGGB
    } rpigrafx_bayer_pattern_t;

    typedef enum {
        RPIGRAFX_RAWCAM_IMX219_BINNING_MODE_NONE
    } rpigrafx_rawcam_imx219_binning_mode_t;

    int rpigrafx_init()     __attribute__((constructor));
    int rpigrafx_finalize() __attribute__((destructor));

    int rpigrafx_config_camera_frame(const int32_t camera_number,
                                     const int32_t width, const int32_t height,
                                     const MMAL_FOURCC_T encoding,
                                     const _Bool is_zero_copy_rendering,
                                     rpigrafx_frame_config_t *fcp);
    int rpigrafx_config_rawcam(const rpigrafx_rawcam_camera_model_t
                                                                   camera_model,
                               const MMAL_CAMERA_RX_CONFIG_DECODE decode,
                               const MMAL_CAMERA_RX_CONFIG_ENCODE encode,
                               const MMAL_CAMERA_RX_CONFIG_UNPACK unpack,
                               const MMAL_CAMERA_RX_CONFIG_PACK   pack,
                               const uint32_t data_lanes,
                               const uint32_t nbits_of_raw_from_camera,
                               const rpigrafx_bayer_pattern_t bayer_pattern,
                               rpigrafx_frame_config_t *fcp);
    int rpigrafx_config_rawcam_imx219(const float exck_freq,
                                      uint_least16_t x, uint_least16_t y,
                                      _Bool orient_hori, _Bool orient_vert,
                                      rpigrafx_rawcam_imx219_binning_mode_t
                                                                   binning_mode,
                                      rpigrafx_frame_config_t *fcp);
    int rpigrafx_config_camera_port(const int32_t camera_number,
                                    const rpigrafx_camera_port_t camera_port);
    int rpigrafx_config_camera_frame_render(const _Bool is_fullscreen,
                                            const int32_t x, const int32_t y,
                                            const int32_t width, const int32_t height,
                                            const int32_t layer,
                                            rpigrafx_frame_config_t *fcp);
    int rpigrafx_finish_config();

    void rpigrafx_set_verbose(const int verbose);

    int rpigrafx_capture_next_frame(rpigrafx_frame_config_t *fcp);
    void* rpigrafx_get_frame(rpigrafx_frame_config_t *fcp);
    int rpigrafx_free_frame(rpigrafx_frame_config_t *fcp);
    /*void* rpigrafx_get_output_buffer(rpigrafx_frame_config_t *fcp);*/
    /*void* rpigrafx_get_input_buffer(rpigrafx_frame_config_t *fcp);*/
    int rpigrafx_register_frame_pool_to_qmkl(rpigrafx_frame_config_t *fcp);

    int rpigrafx_render_frame(rpigrafx_frame_config_t *fcp);

    int rpigrafx_get_screen_size(int *widthp, int *heightp);

#endif /* RPIGRAFX2_H */

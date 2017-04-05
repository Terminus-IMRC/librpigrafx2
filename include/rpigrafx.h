#ifndef RPIGRAFX2_H
#define RPIGRAFX2_H

#include <stdint.h>
#include <bcm_host.h>
#include <interface/mmal/mmal.h>

    struct callback_context {
        MMAL_STATUS_T status;
        MMAL_BUFFER_HEADER_T *header;
        VCOS_SEMAPHORE_T sem_capture_next_frame, sem_header_set;
    };

    typedef struct {
        int32_t camera_number;
        unsigned splitter_output_port_index;
        _Bool is_zero_copy_rendering;
        struct callback_context *ctx;
        MMAL_COMPONENT_T *render;
    } rpigrafx_frame_config_t;

    int rpigrafx_init()     __attribute__((constructor));
    int rpigrafx_finalize() __attribute__((destructor));

    int rpigrafx_config_camera_frame(const int32_t camera_number,
                                     const int32_t width, const int32_t height,
                                     const MMAL_FOURCC_T encoding,
                                     const _Bool is_zero_copy_rendering,
                                     rpigrafx_frame_config_t *fcp);
    int rpigrafx_config_camera_frame_render(const _Bool is_fullscreen,
                                            const int32_t x, const int32_t y,
                                            const int32_t width, const int32_t height,
                                            const int32_t layer,
                                            rpigrafx_frame_config_t *fcp);
    int rpigrafx_finish_config();

    int rpigrafx_capture_next_frame(rpigrafx_frame_config_t *fcp);
    void* rpigrafx_get_frame(rpigrafx_frame_config_t *fcp);
    /*void* rpigrafx_get_output_buffer(rpigrafx_frame_config_t *fcp);*/
    /*void* rpigrafx_get_input_buffer(rpigrafx_frame_config_t *fcp);*/
    int rpigrafx_register_frame_pool_to_qmkl(rpigrafx_frame_config_t *fcp);

    int rpigrafx_render_frame(rpigrafx_frame_config_t *fcp);

#endif /* RPIGRAFX2_H */

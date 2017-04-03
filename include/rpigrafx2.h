#ifndef RPIGRAFX2_H
#define RPIGRAFX2_H

#include <stdint.h>
#include <interface/mmal/mmal.h>

    typedef struct {
        int32_t camera_number;
        unsigned splitter_output_port_index;
        _Bool is_zero_copy_rendering;
    } rpigrafx_frame_config_t;

    typedef struct {
        MMAL_COMPONENT_T *render;
    } rpigrafx_render_config_t;

    void rpigrafx_init()     __attribute__((constructor));
    void rpigrafx_finalize() __attribute__((destructor));

    int rpigrafx_config_camera_frame(const int32_t camera_number,
                                     const int32_t width, const int32_t height,
                                     const MMAL_FOURCC_T encoding,
                                     const _Bool is_zero_copy_rendering
                                     rpigrafx_frame_config_t *fcp);
    int rpigrafx_finish_config();

    void* rpigrafx_get_frame(rpigrafx_frame_config_t fc);
    /*void* rpigrafx_get_output_buffer(rpigrafx_frame_config_t fc);*/
    /*void* rpigrafx_get_input_buffer(rpigrafx_frame_config_t fc);*/
    int rpigrafx_register_frame_pool_to_qmkl(rpigrafx_frame_config_t fc);

    int rpigrafx_config_render(const _Bool is_fullscreen,
                               const int32_t x, const int32_t y,
                               const int32_t width, const int32_t height,
                               const int32_t layer,
                               rpigrafx_render_config_t *rcp);
    int rpigrafx_render_frane(rpigrafx_frame_cofig_t fc,
                              rpigrafx_render_config_t rc);

#endif /* RPIGRAFX2_H */

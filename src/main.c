/*
 * Copyright (c) 2017 Sugizaki Yukimasa (ysugi@idein.jp)
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#include "rpigrafx.h"
#include "local.h"

struct priv_rpigrafx_called priv_rpigrafx_called = {
    .main     = 0,
    .mmal     = 0,
    .dispmanx = 0
};

int rpigrafx_init()
{
    int ret = 0;

    if (priv_rpigrafx_called.main != 0)
        goto end;

    ret = priv_rpigrafx_mmal_init();
    if (ret) {
        print_error("Initializing mmal failed: 0x%08x", ret);
        goto end;
    }
    ret = priv_rpigrafx_dispmanx_init();
    if (ret) {
        print_error("Initializing mmal failed: 0x%08x", ret);
        goto end;
    }

end:
    priv_rpigrafx_called.main ++;
    return ret;
}

int rpigrafx_finalize()
{
    int ret = 0;

    if (priv_rpigrafx_called.main != 1)
        goto end;

    ret = priv_rpigrafx_dispmanx_finalize();
    if (ret) {
        print_error("Finalizing mmal failed: 0x%08x", ret);
        goto end;
    }
    ret = priv_rpigrafx_mmal_finalize();
    if (ret) {
        print_error("Finalizing mmal failed: 0x%08x", ret);
        goto end;
    }

end:
    priv_rpigrafx_called.main --;
    return ret;
}

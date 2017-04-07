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

struct called called = {
    .main = 0,
    .mmal = 0
};

int rpigrafx_init()
{
    int ret = 0;

    if (called.main != 0)
        goto end;

    ret = priv_rpigrafx_mmal_init();
    if (ret) {
        print_error("Initializing mmal failed: 0x%08x", ret);
        goto end;
    }

end:
    called.main ++;
    return ret;
}

int rpigrafx_finalize()
{
    int ret = 0;

    if (called.main != 1)
        goto end;

    ret = priv_rpigrafx_mmal_finalize();
    if (ret) {
        print_error("Finalizing mmal failed: 0x%08x", ret);
        goto end;
    }

end:
    called.main --;
    return ret;
}

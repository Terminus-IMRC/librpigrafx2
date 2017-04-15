/*
 * Copyright (c) 2017 Sugizaki Yukimasa (ysugi@idein.jp)
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#include <bcm_host.h>
#include "rpigrafx.h"
#include "local.h"

static DISPMANX_DISPLAY_HANDLE_T display = 0;
static DISPMANX_MODEINFO_T info;

int priv_rpigrafx_dispmanx_init()
{
    int status = 0;
    int ret = 0;

    if (priv_rpigrafx_called.dispmanx != 0)
        goto end;

    bcm_host_init();

    display = vc_dispmanx_display_open(0);
    if (!display) {
        print_error("Failed to open dispmanx display: 0x%08x", display);
        ret = 1;
        goto end;
    }

    status = vc_dispmanx_display_get_info(display, &info);
    if (status) {
        print_error("Failed to get display info: 0x%08x", status);
        ret = 1;
        goto end;
    }

end:
    priv_rpigrafx_called.dispmanx ++;
    return ret;
}

int priv_rpigrafx_dispmanx_finalize()
{
    int status = 0;
    int ret = 0;

    if (priv_rpigrafx_called.dispmanx != 1)
        goto end;

    status = vc_dispmanx_display_close(display);
    if (status) {
        print_error("Failed to close dispmanx display: 0x%08x", status);
        ret = 1;
        goto end;
    }
    display = 0;

    bcm_host_deinit();

end:
    priv_rpigrafx_called.dispmanx --;
    return ret;
}

int rpigrafx_get_screen_size(int *widthp, int *heightp)
{
    int ret = 0;

    *widthp  = info.width;
    *heightp = info.height;

    return ret;
}

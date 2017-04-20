/*
 * Copyright (c) 2017 Sugizaki Yukimasa (ysugi@idein.jp)
 * All rights reserved.
 *
 * This software is licensed under a Modified (3-Clause) BSD License.
 * You should have received a copy of this license along with this
 * software. If not, contact the copyright holder above.
 */

#ifndef LOCAL_H
#define LOCAL_H

    struct priv_rpigrafx_called {
        int main, mmal, dispmanx;
    } priv_rpigrafx_called;

    extern int priv_rpigrafx_verbose;

#define print_error(fmt, ...) print_error_core(__FILE__, __LINE__, __func__, \
                                               fmt, ##__VA_ARGS__)
    void print_error_core(const char *file, const int line, const char *func,
                          const char *fmt, ...);

    /* mmal.c */
    int priv_rpigrafx_mmal_init();
    int priv_rpigrafx_mmal_finalize();

    /* dispmanx.c */
    int priv_rpigrafx_dispmanx_init();
    int priv_rpigrafx_dispmanx_finalize();

#endif /* LOCAL_H */

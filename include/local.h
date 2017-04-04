#ifndef LOCAL_H
#define LOCAL_H

    struct called {
        int main, mmal;
    } called;

#define print_error(fmt, ...) print_error_core(__FILE__, __LINE__, __func__, \
                                               fmt, ##__VA_ARGS__)
    void print_error_core(const char *file, const int line, const char *func,
                          const char *fmt, ...);

    /* mmal.c */
    int priv_rpigrafx_mmal_init();
    int priv_rpigrafx_mmal_finalize();

#endif /* LOCAL_H */

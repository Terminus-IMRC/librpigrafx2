#include <rpigrafx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define _check(x) \
	do { \
		if ((x)) { \
			fprintf(stderr, "Error at %s:%d:%s\n", __FILE__, __LINE__, __func__); \
			exit(EXIT_FAILURE); \
		} \
	} while (0)

static double get_time()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double) t.tv_sec + t.tv_usec * 1e-6;
}

int main(int argc, char *argv[])
{
	rpigrafx_frame_config_t fc;
	double start, time;
    int i, n, camera_num;
    int width = 1024, height = 768;

    if (argc < 1 + 2) {
        fprintf(stderr, "Invalid the number of the arguments.\n");
        fprintf(stderr, "Usage: %s CAMERA_NUM NUM_FRAMES [WIDTH] [HEIGHT]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    camera_num = atoi(argv[1]);
    n = atoi(argv[2]);
    if (argc >= 1 + 3)
        width  = atoi(argv[3]);
    if (argc >= 1 + 4)
        height = atoi(argv[4]);

    rpigrafx_set_verbose(1);
	_check(rpigrafx_config_camera_frame(camera_num, width, height, MMAL_ENCODING_RGB24, 1, &fc));
	_check(rpigrafx_config_camera_port(camera_num, RPIGRAFX_CAMERA_PORT_PREVIEW));
	_check(rpigrafx_config_camera_frame_render(1, 0, 0, 0, 0, 5, &fc));
	_check(rpigrafx_finish_config());

	start = get_time();
	for (i = 0; i < n; i ++) {
		_check(rpigrafx_capture_next_frame(&fc));
		_check(rpigrafx_render_frame(&fc));
	}
    time = get_time() - start;
    fprintf(stderr, "%f [s], %f [frame/s]\n", time, n / time);

	return 0;
}

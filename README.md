# `librpigrafx`

`librpigrafx` is a graphic library for Raspberry Pi.


## What does it do?

* Get image from camera in any size.
    * Resizing is done in GPU.
* Draw boxes and images on console.


## Installation

You need to install [librpicam](https://github.com/Idein/librpicam) and
[librpiraw](https://github.com/Idein/librpiraw) to use rawcam (described below).

```
$ autoreconf -i -m
$ PKG_CONFIG_PATH=/opt/vc/lib/pkgconfig ./configure
$ make
$ make check
$ sudo make install
```


# How to run

```
$ sudo ./test/test_capture_render_seq
```

`sudo` is needed here because it uses
[qmkl](https://github.com/Terminus-IMRC/qmkl), which uses `/dev/mem` to
communicate with GPU, for testing of resource confliction.


## Using rawcam

The official IMX219 camera module is protected by a cryptographic chip
[ATSHA204A](http://www.microchip.com/wwwproducts/en/ATSHA204A) not to let users
to use their ISP (image signal processor) and algorithms *fully* for processing
raw image from camera.

This library supports rawcam, which is a framework provided by the Raspberry Pi
firmware. rawcam enables to receive raw image from MIPI/CSI-2 image sensor
directly. With it, **you can use non-official cameras i.e. without cryptographic
chips**. In addition, this library implements raw image processing, AWB, etc. so
you can use it without much configurations.

Currently, our rawcam support is limited to IMX219. How to run:

```
$ echo 'dtparam=i2c_vc=on' | sudo tee -a /boot/config.txt
$ sudo reboot
$ wget https://raw.githubusercontent.com/6by9/userland/rawcam/camera_i2c
$ chmod u+x camera_i2c
$ ./camera_i2c
$ ./test/test_rawcam_imx219
```

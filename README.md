# `librpigrafx`

`librpigrafx` is a graphic library for Raspberry Pi.


## What does it do?

* Get image from camera in any size.
    * Resizing is done in GPU.
* Draw boxes and images on console.


## Installation

```
$ autoreconf -i -m
$ PKG_CONFIG_PATH=/opt/vc/lib/pkgconfig ./configure
$ make
$ sudo make install
```

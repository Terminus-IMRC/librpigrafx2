#!/usr/bin/env bash

set -e

# /dev/i2c-0 is needed to communicate with camera.
echo '* Checking if /dev/i2c-0 is enabled...'
IS_I2C0_DISABLED=
fgrep --quiet 'dtparam=i2c_vc=on' /boot/config.txt || IS_I2C0_DISABLED=1
if test -n "$IS_I2C0_DISABLED"; then
    echo 'dtparam=i2c_vc=on' | sudo tee -a /boot/config.txt
    echo '/boot/config.txt has been changed. Reboot is needed.'
    echo '* Exiting.'
    exit 0
fi

# Install i2c-tools for i2cdetect command which is used in camera_i2c script.
echo '* Installing i2c-tools...'
sudo apt-get --quiet install --quiet --yes i2c-tools

# Install rpi3-gpiovirtbuf which is ued in camera_i2c script.
echo '* Installing rpi3-gpiovirtbuf...'
rm -rf rpi3-gpiovirtbuf/
mkdir rpi3-gpiovirtbuf/
wget --quiet --directory-prefix=rpi3-gpiovirtbuf/ https://github.com/6by9/userland/raw/rawcam/rpi3-gpiovirtbuf
chmod u+x rpi3-gpiovirtbuf/rpi3-gpiovirtbuf

# Run camera_i2c script to enable power for camera.
echo '* Running camera_i2c script...'
curl --silent https://raw.githubusercontent.com/6by9/userland/rawcam/camera_i2c | bash

echo '* Done.'

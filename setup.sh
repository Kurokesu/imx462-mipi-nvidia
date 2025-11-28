#!/bin/bash

# Install from prebuilt files
DRV_FILES_DIR=./prebuilt

# Exit on errors
set -e

echo "Copying prebuilt device tree entry to /boot"
cp $DRV_FILES_DIR/tegra234-p3767-camera-p3768-imx462-A.dtbo /boot

echo "Copying camera calibration to /var/nvidia/nvcam/settings"
cp ./tuning/camera_overrides.isp /var/nvidia/nvcam/settings

echo "Sucess! Don't forget to run \"sudo /opt/nvidia/jetson-io/jetson-io.py\""
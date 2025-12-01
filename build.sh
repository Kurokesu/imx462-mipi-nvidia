#!/bin/bash

# Exit on errors
set -e

# Set kernel source directory
KERNEL_SRC_DIR=$HOME/Linux_for_Tegra/source

# Export build variables
export CROSS_COMPILE=$HOME/l4t-gcc/aarch64--glibc--stable-2022.08-1/bin/aarch64-buildroot-linux-gnu-
export KERNEL_HEADERS=$KERNEL_SRC_DIR/kernel/kernel-jammy-src

echo "Copying driver files to $KERNEL_SRC_DIR/nvidia-oot/drivers/media/i2c"
cp ./makefiles/Makefile-drivers $KERNEL_SRC_DIR/nvidia-oot/drivers/media/i2c/Makefile
cp ./nv_imx462.c $KERNEL_SRC_DIR/nvidia-oot/drivers/media/i2c
cp ./imx462_mode_tbls.h $KERNEL_SRC_DIR/nvidia-oot/drivers/media/i2c

echo "Copying device-tree files to $KERNEL_SRC_DIR/hardware/nvidia/t23x/nv-public/overlay"
cp ./makefiles/Makefile-overlays $KERNEL_SRC_DIR/hardware/nvidia/t23x/nv-public/overlay/Makefile
cp ./tegra234-p3767-camera-p3768-imx462-A.dts $KERNEL_SRC_DIR/hardware/nvidia/t23x/nv-public/overlay

echo "Building loadable imx462 kernel module"
make -C $KERNEL_SRC_DIR modules

echo "Building dtbs"
make -C $KERNEL_SRC_DIR dtbs

mkdir -p build

echo "Retrieving nv_imx462.ko to build dir"
cp $KERNEL_SRC_DIR/nvidia-oot/drivers/media/i2c/nv_imx462.ko ./build

echo "Success"
echo "Retrieving tegra234-p3767-camera-p3768-imx462-A.dtbo to build dir"
cp $KERNEL_SRC_DIR/kernel-devicetree/generic-dts/dtbs/tegra234-p3767-camera-p3768-imx462-A.dtbo ./build

echo "Success"

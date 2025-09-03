# imx462 MIPI NVIDIA driver

Compatible with NVIDIA Jetson Linux 36.4.4

## Quick test

Pre-built driver files are provided in [./build](./build) directory.

Connect camera to cam0 port.

Copy device tree entry to `/boot` directory:
```bash
cp ./build/tegra234-p3767-camera-p3768-imx462-A.dtbo /boot
```

Use Jetsion-IO tool to configure 24pin CSI Connector:
```bash
sudo /opt/nvidia/jetson-io/jetson-io.py
```
Navigate through menu:
1. Configure Jetson 24pin CSI Connector
1. Configure for compatible hardware
1. Select Camera IMX462-A

![jetson-io-tool](./img/jetson-io-tool.png "jetson-io-tool")

```bash
sudo reboot
```

Load imx462 driver module:
```bash
sudo insmod ./build/nv_imx462.ko
```

Verify sensor detected over i2c:
```bash
sudo dmesg | grep imx462
```
![dmesg-imx462](./img/dmesg.png "dmesg-imx462")

Stream raw data to file:
```bash
v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat=RG10 --stream-mmap --stream-to imx462_1080p.raw --stream-count=1 --stream-skip=10 --verbose
```

## Build

Currently the driver is built directly in the kernel sources as acquiring NVIDIA Linux headers hasn't been implemented yet. Best to use host PC, because whole kernel has to be built initially. Full NVIDIA kernel customization guide: https://docs.nvidia.com/jetson/archives/r36.4.4/DeveloperGuide/SD/Kernel/KernelCustomization.html

### Prerequisites

git:
```bash
sudo apt install git
```

Linux kernel build utilities:
```bash
sudo apt install build-essential bc flex bison libssl-dev zstd
```

Download the Bootlin toolchain binaries:
```bash
cd ~/Downloads
wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v3.0/toolchain/aarch64--glibc--stable-2022.08-1.tar.bz2
```

Extract the toolchain:
```bash
mkdir $HOME/l4t-gcc
cd $HOME/l4t-gcc
tar xf ~/Downloads/aarch64--glibc--stable-2022.08-1.tar.bz2
```

Download Linux for Tegra kernel source:
```bash
cd ~/Downloads
wget https://developer.download.nvidia.com/embedded/L4T/r36_Release_v4.4/release/Jetson_Linux_R36.4.4_aarch64.tbz2
```

Extract:
```bash
cd $HOME
tar xf ~/Downloads/Jetson_Linux_R36.4.4_aarch64.tbz2 
```

Sync the Kernel Sources with Git:
```bash
cd Linux_for_Tegra/source/
./source_sync.sh -k -t jetson_36.4.4
```

Export build variables:
```bash
export CROSS_COMPILE=$HOME/l4t-gcc/aarch64--glibc--stable-2022.08-1/bin/aarch64-buildroot-linux-gnu-
export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
```

Build the kernel:
```bash
make -C kernel
```

Build the NVIDIA Out-of-Tree modules:
```bash
make modules
```

Build the DTBs:
```bash
make dtbs
```

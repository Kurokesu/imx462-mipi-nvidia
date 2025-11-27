# imx462 MIPI NVIDIA driver

Compatible with NVIDIA Jetson Linux 36.4.4

## Quickstart

Prebuilt driver files are provided in [./prebuilt](./prebuilt) directory.

Connect camera to cam0 port.

Copy device tree entry to `/boot` directory:
```bash
cp ./prebuilt/tegra234-p3767-camera-p3768-imx462-A.dtbo /boot
```

Copy camera calibration ISP settings file to `/var/nvidia/nvcam/settings`:
```bash
cp ./tuning/camera_overrides.isp /var/nvidia/nvcam/settings
```

Use Jetson-IO tool to configure 24pin CSI connector:
```bash
sudo /opt/nvidia/jetson-io/jetson-io.py
```
Navigate through the menu:
1. Configure Jetson 24pin CSI Connector
1. Configure for compatible hardware
1. Select Camera IMX462-A

![jetson-io-tool](./img/jetson-io-tool.png "jetson-io-tool")

Reboot:
```bash
sudo reboot
```

Load imx462 driver module:
```bash
sudo insmod ./prebuilt/nv_imx462.ko
```

Verify that the sensor is detected over I2C:
```bash
sudo dmesg | grep imx462
```
![dmesg-imx462](./img/dmesg.png "dmesg-imx462")

### GStreamer
```bash
gst-launch-1.0 -e nvarguscamerasrc sensor-id=0 ! \
   'video/x-raw(memory:NVMM),width=1920,height=1080,framerate=30/1' ! \
   queue ! nvvidconv ! queue ! nveglglessink
```

### NVIDIA sample camera capture application
```bash
nvgstcapture-1.0 --sensor-id 0
```

### Raw v4l2
Stream raw data to file:
```bash
v4l2-ctl -d /dev/video0 --set-fmt-video=width=1920,height=1080,pixelformat=RG10 --stream-mmap --stream-to imx462_1080p.raw --stream-count=1 --stream-skip=10 --verbose
```

View raw bayer file:
```bash
python3 view_raw.py ./imx462_1080p.raw
```

## Test mode

Sensor has built-in test pattern generator which can be enabled for verifying data validity.

In order to enable it, simply add `test_mode=<test pattern>` to `insmod` command.

Horizontal color-bar chart example:
```bash
sudo insmod ./prebuilt/nv_imx462.ko test_mode=2
```

| Test pattern code | Description |
| ------------ | ----------- |
| 1 | Sequence Pattern 1 |
| 2 | Horizontal Color-bar Chart |
| 3 | Vertical Color-bar Chart |
| 4 | Sequence Pattern 2 |
| 5 | Gradation Pattern 1 |
| 6 | Gradation Pattern 2 |
| 7 | 000h/555h Toggle Pattern |

## Build

Currently the driver is built directly in the kernel sources as acquiring NVIDIA Linux headers hasn't been implemented yet. Best to use host PC, because whole kernel has to be built initially. Full NVIDIA kernel customization guide can be found [here](https://docs.nvidia.com/jetson/archives/r36.4.4/DeveloperGuide/SD/Kernel/KernelCustomization.html).

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
export KERNEL_HEADERS=$HOME/Linux_for_Tegra/source/kernel/kernel-jammy-src
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

Now that the default kernel build is ready, we can add imx462 driver sources and build them using `build.sh` script.
Make script executable:
```bash
cd <imx462-mipi-nvidia repo dir>
chmod +x ./build.sh 
```

Build:
```bash
./build.sh
```

Upon successful build the kernel files will be retrieved to `./build` directory. They can then be loaded onto target and used just as described in [Quickstart](#quickstart).

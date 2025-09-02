# imx462 MIPI NVIDIA driver

Compatible with NVIDIA Jetson Linux 36.4.4

## Quick test

Pre-built driver files are provided in [./build](./build) directory.

Connect camera to cam0 port.

Copy device tree entry to /boot directory:
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

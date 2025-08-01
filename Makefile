KERNEL_SRC ?= /usr/src/linux-headers-$(shell uname -r)

# Module name
MODULE_NAME = krks_imx462

# Source files
obj-m := $(MODULE_NAME).o

# Driver source files
$(MODULE_NAME)-objs := krks_imx462.o

# Compiler flags
ccflags-y := -I$(KERNEL_SRC)/drivers/media/platform/tegra
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/camera_gpio
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/camera_common
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/tegracam
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/tegracam/include
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/tegracam/core
ccflags-y += -I$(KERNEL_SRC)/drivers/media/platform/tegra/camera/tegracam/utils

# Default target
all: $(MODULE_NAME).ko

# Build the kernel module
$(MODULE_NAME).ko: krks_imx462.c imx462.h imx462_mode_tbls.h
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) modules

# Clean target
clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
	rm -f $(MODULE_NAME).ko

# Install target
install: $(MODULE_NAME).ko
	sudo insmod $(MODULE_NAME).ko

# Uninstall target
uninstall:
	sudo rmmod $(MODULE_NAME) || true

# Help target
help:
	@echo "Available targets:"
	@echo "  all       - Build the kernel module (default)"
	@echo "  clean     - Clean build files"
	@echo "  install   - Install the module"
	@echo "  uninstall - Remove the module"
	@echo "  help      - Show this help message"

.PHONY: all clean install uninstall help 
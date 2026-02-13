#!/bin/bash
# SPDX-License-Identifier: GPL-2.0-only
# Copyright (c) 2026, UAB Kurokesu. All rights reserved.
#
# Install IMX462 camera driver (device tree overlay + kernel module via DKMS)
# Supports JetPack 6.2.1

# Exit on errors
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Read version from dkms.conf
VERSION=$(grep '^PACKAGE_VERSION=' "$SCRIPT_DIR/dkms.conf" | cut -d'"' -f2)
PACKAGE_NAME=$(grep '^PACKAGE_NAME=' "$SCRIPT_DIR/dkms.conf" | cut -d'"' -f2)
DKMS_SRC="/usr/src/${PACKAGE_NAME}-${VERSION}"

# --- Check prerequisites ---

if ! command -v dkms &>/dev/null; then
    echo "Error: dkms is not installed. Install it with: sudo apt install dkms"
    exit 1
fi

# --- Remove old DKMS registration if present ---

if dkms status "${PACKAGE_NAME}/${VERSION}" 2>/dev/null | grep -q .; then
    echo "Removing previous DKMS registration for ${PACKAGE_NAME}/${VERSION}..."
    dkms remove "${PACKAGE_NAME}/${VERSION}" --all 2>/dev/null || true
fi

# --- Copy source to DKMS tree ---

echo "Copying driver source to ${DKMS_SRC}"
rm -rf "$DKMS_SRC"
mkdir -p "$DKMS_SRC"
cp "$SCRIPT_DIR/dkms.conf" "$DKMS_SRC/"
cp "$SCRIPT_DIR/dkms.postinst" "$DKMS_SRC/"
cp "$SCRIPT_DIR/nv_imx462.c" "$DKMS_SRC/"
cp "$SCRIPT_DIR/imx462_mode_tbls.h" "$DKMS_SRC/"
cp "$SCRIPT_DIR/tegra234-p3767-camera-p3768-imx462-A.dts" "$DKMS_SRC/"
cp -r "$SCRIPT_DIR/scripts" "$DKMS_SRC/"

# --- Fetch NVIDIA device tree header (requires internet) ---

echo "Fetching NVIDIA device tree headers..."
"$DKMS_SRC/scripts/fetch-nvidia-headers.sh" "$DKMS_SRC/include"

# --- Install camera calibration / ISP overrides ---

echo "Copying camera calibration to /var/nvidia/nvcam/settings"
cp "$SCRIPT_DIR/tuning/camera_overrides.isp" /var/nvidia/nvcam/settings/

# --- DKMS add + build + install ---
# POST_INSTALL in dkms.conf triggers dkms.postinst which builds the DTBO
# and installs it to /boot.

echo "DKMS: adding ${PACKAGE_NAME}/${VERSION}"
dkms add -m "$PACKAGE_NAME" -v "$VERSION"

echo "DKMS: building ${PACKAGE_NAME}/${VERSION}"
dkms build -m "$PACKAGE_NAME" -v "$VERSION"

echo "DKMS: installing ${PACKAGE_NAME}/${VERSION}"
dkms install -m "$PACKAGE_NAME" -v "$VERSION"

echo ""
echo "Success! Run \"sudo /opt/nvidia/jetson-io/jetson-io.py\" to configure."

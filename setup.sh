#!/bin/sh
# SPDX-License-Identifier: GPL-2.0-only
# Copyright (c) 2026, UAB Kurokesu. All rights reserved.
#
# Install camera driver (device tree overlay + kernel module via DKMS)

# Exit on errors
set -e

# Status line formatter (matches Makefile's PRINT)
print() { printf '  %-7s %s\n' "$1" "$2"; }

# Derive package identity and paths from dkms.conf
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
DKMS_CONF="$SCRIPT_DIR/dkms.conf"
VERSION=$(grep '^PACKAGE_VERSION=' "$DKMS_CONF" | cut -d'"' -f2)
PACKAGE_NAME=$(grep '^PACKAGE_NAME=' "$DKMS_CONF" | cut -d'"' -f2)
SENSOR=$(grep '^BUILT_MODULE_NAME=' "$DKMS_CONF" | cut -d'"' -f2 | sed 's/^nv_//')
DKMS_SRC="/usr/src/${PACKAGE_NAME}-${VERSION}"

if [ -z "$VERSION" ] || [ -z "$PACKAGE_NAME" ] || [ -z "$SENSOR" ]; then
	echo "Error: failed to parse $DKMS_CONF"
	exit 1
fi

# Check prerequisites
if ! command -v dkms >/dev/null 2>&1; then
	echo "Error: dkms not installed. Run:"
	echo "sudo apt install --no-install-recommends dkms"
	exit 1
fi

# Check for headers, dkms's own error would suggest non-existent linux-headers-*
if [ ! -e "/lib/modules/$(uname -r)/build/Makefile" ]; then
	echo "Error: kernel headers not found. Run:"
	echo "sudo apt install --reinstall nvidia-l4t-kernel-headers"
	exit 1
fi

# Remove DKMS registrations matching sensor name
dkms status 2>/dev/null | sed 's/[,:].*//' | sort -u | while read -r ENTRY; do
	case "${ENTRY%%/*}" in
	*"$SENSOR"*)
		print DKMS "remove $ENTRY"
		dkms remove "$ENTRY" --all || true
		;;
	esac
done

# Copy source to DKMS tree
print COPY "driver source -> $DKMS_SRC"
rm -rf "$DKMS_SRC"
mkdir -p "$DKMS_SRC"
cp "$DKMS_CONF" "$DKMS_SRC/"
cp "$SCRIPT_DIR/dkms.postinst" "$DKMS_SRC/"
cp "$SCRIPT_DIR/Makefile" "$DKMS_SRC/"
cp "$SCRIPT_DIR"/*.c "$DKMS_SRC/"
cp "$SCRIPT_DIR"/*.h "$DKMS_SRC/"
cp "$SCRIPT_DIR"/*.dts "$DKMS_SRC/"
cp -r "$SCRIPT_DIR/scripts" "$DKMS_SRC/"

# Fetch NVIDIA device tree headers (requires internet)
"$DKMS_SRC/scripts/fetch-nvidia-headers.sh" "$DKMS_SRC/include"

# DKMS add + build + install
print DKMS "add ${PACKAGE_NAME}/${VERSION}"
dkms add -m "$PACKAGE_NAME" -v "$VERSION"

print DKMS "build ${PACKAGE_NAME}/${VERSION}"
dkms build -m "$PACKAGE_NAME" -v "$VERSION"

print DKMS "install ${PACKAGE_NAME}/${VERSION}"
dkms install -m "$PACKAGE_NAME" -v "$VERSION"

echo ""
echo "Done. To configure CSI connector, run:"
echo "sudo /opt/nvidia/jetson-io/jetson-io.py"

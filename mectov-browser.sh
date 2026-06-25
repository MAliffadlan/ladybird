#!/bin/bash
# Mectov Browser - Install & Run Script
# Tinggal jalanin: bash mectov-browser.sh

set -e

echo "=========================================="
echo "  Mectov Browser - Quick Install"
echo "=========================================="
echo ""

# Cek OS
if [ ! -f /etc/os-release ]; then
    echo "[ERROR] Cuma support Linux buat sekarang"
    exit 1
fi

# Install dependencies
echo "[1/3] Menginstall dependensi..."
if command -v apt &> /dev/null; then
    sudo apt update -qq
    sudo apt install -y -qq qt6-base-dev qt6-wayland libpulse-dev 2>/dev/null
elif command -v pacman &> /dev/null; then
    sudo pacman -S --needed qt6-base qt6-wayland libpulse
elif command -v dnf &> /dev/null; then
    sudo dnf install qt6-qtbase-devel qt6-qtwayland-devel pulseaudio-libs-devel
else
    echo "[WARN] Gak detect package manager. Install Qt6 manual ya."
fi

# Cari binary
echo "[2/3] Mencari binary..."
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

LADYBIRD=""
if [ -f "Ladybird" ]; then
    LADYBIRD="./Ladybird"
elif [ -f "Build/release/bin/Ladybird" ]; then
    LADYBIRD="./Build/release/bin/Ladybird"
else
    echo "[ERROR] Ladybird binary gak ditemukan."
    echo "        Coba build dulu:"
    echo "        cd Build/release && cmake ../.. -G Ninja && ninja ladybird"
    exit 1
fi

chmod +x "$LADYBIRD"

# Jalankan
echo "[3/3] Menjalankan Mectov Browser..."
echo ""
echo "=========================================="
echo "  Mectov Browser jalan! 🚀"
echo "=========================================="
echo ""

"$LADYBIRD" "$@"

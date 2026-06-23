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

# Ekstrak browser
echo "[2/3] Ekstrak Mectov Browser..."
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

if [ ! -f "Ladybird" ]; then
    echo "[ERROR] File Ladybird gak ditemukan di folder ini."
    echo "        Pastikan file Ladybird ada di folder yang sama."
    exit 1
fi

chmod +x Ladybird

# Jalankan
echo "[3/3] Menjalankan Mectov Browser..."
echo ""
echo "=========================================="
echo "  Mectov Browser jalan! 🚀"
echo "=========================================="
echo ""

./Ladybird

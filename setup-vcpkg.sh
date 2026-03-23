#!/bin/bash

set -e  # Exit on error

echo "================================"
echo "vcpkg Setup for Linux"
echo "================================"
echo ""

# Step 1: Clone vcpkg
echo "Step 1: Cloning vcpkg repository..."
if [ -d "$HOME/vcpkg" ]; then
    echo "vcpkg already exists at ~/vcpkg, skipping clone."
else
    git clone https://github.com/Microsoft/vcpkg.git ~/vcpkg
    echo "✓ vcpkg cloned to ~/vcpkg"
fi
echo ""

# Step 2: Bootstrap vcpkg
echo "Step 2: Bootstrapping vcpkg..."
cd ~/vcpkg
./bootstrap-vcpkg.sh
echo "✓ vcpkg bootstrapped successfully"
echo ""

# Step 3: Set VCPKG_ROOT environment variable
echo "Step 3: Setting VCPKG_ROOT environment variable..."
export VCPKG_ROOT=~/vcpkg
echo "✓ VCPKG_ROOT set to ~/vcpkg in current session"
echo ""

# Step 4: Make it persistent
echo "Step 4: Making VCPKG_ROOT persistent in ~/.bashrc..."
if grep -q "export VCPKG_ROOT" ~/.bashrc; then
    echo "VCPKG_ROOT already in ~/.bashrc, skipping."
else
    echo 'export VCPKG_ROOT=~/vcpkg' >> ~/.bashrc
    echo "✓ Added 'export VCPKG_ROOT=~/vcpkg' to ~/.bashrc"
fi
echo ""

# Step 5: Initialize vcpkg for the project
echo "Step 5: Initializing vcpkg for the project..."
cd "$(dirname "$0")"  # Return to the project root
~/vcpkg/vcpkg new --application
echo "✓ vcpkg initialized for the project"
echo ""

echo "================================"
echo "Setup Complete!"
echo "================================"
echo ""
echo "To apply environment changes to your current terminal, run:"
echo "  source ~/.bashrc"
echo ""
echo "Then you can run the build script with:"
echo "  ./cnb.sh"
echo ""

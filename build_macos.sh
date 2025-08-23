#!/bin/bash

# Swoop Device VST3 Build Script for macOS
# Requires JUCE framework and Xcode

echo "======================================"
echo "Building Swoop Device VST3 Plugin"
echo "======================================"

# Set paths
PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
JUCE_PATH="/Users/edengrill/JUCE"
PROJUCER_PATH="/Applications/Projucer.app/Contents/MacOS/Projucer"

# Check if Projucer exists
if [ ! -f "$PROJUCER_PATH" ]; then
    echo "Error: Projucer not found at $PROJUCER_PATH"
    echo "Please install JUCE and Projucer first"
    exit 1
fi

# Check if JUCE modules exist
if [ ! -d "$JUCE_PATH/modules" ]; then
    echo "Error: JUCE modules not found at $JUCE_PATH/modules"
    echo "Please install JUCE framework"
    exit 1
fi

cd "$PROJECT_DIR"

# Generate Xcode project
echo "Generating Xcode project..."
"$PROJUCER_PATH" --resave SwoopDevice.jucer

if [ $? -ne 0 ]; then
    echo "Error: Failed to generate Xcode project"
    exit 1
fi

# Build with xcodebuild
echo "Building VST3 plugin..."
cd Builds/MacOSX

xcodebuild -project SwoopDevice.xcodeproj \
           -scheme "SwoopDevice - VST3" \
           -configuration Release \
           clean build \
           SYMROOT=build \
           BUILD_DIR=build

if [ $? -ne 0 ]; then
    echo "Error: Build failed"
    exit 1
fi

# Build standalone app
echo "Building Standalone app..."
xcodebuild -project SwoopDevice.xcodeproj \
           -scheme "SwoopDevice - Standalone Plugin" \
           -configuration Release \
           build \
           SYMROOT=build \
           BUILD_DIR=build

# Check if build succeeded
VST3_PATH="build/Release/SwoopDevice.vst3"
APP_PATH="build/Release/SwoopDevice.app"

if [ -d "$VST3_PATH" ]; then
    echo ""
    echo "✅ VST3 plugin built successfully!"
    echo "Location: $PROJECT_DIR/Builds/MacOSX/$VST3_PATH"
    
    # Option to install to system
    echo ""
    read -p "Install VST3 to ~/Library/Audio/Plug-Ins/VST3? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        cp -R "$VST3_PATH" ~/Library/Audio/Plug-Ins/VST3/
        echo "✅ VST3 installed to ~/Library/Audio/Plug-Ins/VST3/"
    fi
else
    echo "❌ VST3 build failed"
fi

if [ -d "$APP_PATH" ]; then
    echo ""
    echo "✅ Standalone app built successfully!"
    echo "Location: $PROJECT_DIR/Builds/MacOSX/$APP_PATH"
    
    # Option to open standalone
    echo ""
    read -p "Open standalone app now? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        open "$APP_PATH"
    fi
else
    echo "❌ Standalone build failed"
fi

echo ""
echo "======================================"
echo "Build complete!"
echo "======================================" 
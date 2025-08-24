#!/bin/bash

# Red Belly Sea Sweeper - Release Package Creator
# Version 1.4.5

echo "Creating Red Belly Sea Sweeper Release Package v1.4.5..."

# Set version
VERSION="1.4.5"
RELEASE_NAME="RedBellySeaSweeper_v${VERSION}_macOS"
RELEASE_DIR="Release/${RELEASE_NAME}"

# Clean and create release directory
rm -rf Release
mkdir -p "${RELEASE_DIR}"

# Copy plugins from build directory
echo "Copying AU plugin..."
cp -R "Builds/MacOSX/build/Release/Red Belly Sea Sweeper.component" "${RELEASE_DIR}/"

echo "Copying VST3 plugin..."
cp -R "Builds/MacOSX/build/Release/Red Belly Sea Sweeper.vst3" "${RELEASE_DIR}/"

# Copy documentation
echo "Copying documentation..."
cp INSTALLATION.md "${RELEASE_DIR}/INSTALLATION.txt"
cp USER_MANUAL.html "${RELEASE_DIR}/USER_MANUAL.html"
cp README.md "${RELEASE_DIR}/README.txt"
cp CHANGELOG.md "${RELEASE_DIR}/CHANGELOG.txt"

# Create a quick start guide
cat > "${RELEASE_DIR}/QUICK_START.txt" << 'EOF'
RED BELLY SEA SWEEPER v1.4.5
=============================

QUICK INSTALLATION:
1. Copy "Red Belly Sea Sweeper.component" to ~/Library/Audio/Plug-Ins/Components/
2. Copy "Red Belly Sea Sweeper.vst3" to ~/Library/Audio/Plug-Ins/VST3/
3. Restart your DAW
4. Find the plugin under "Garden of Ed"

QUICK START:
1. Load plugin on an audio track
2. Press X or click power button to start sweep
3. Adjust Start/End frequencies and Time as needed

For detailed instructions, see INSTALLATION.txt and USER_MANUAL.html

Enjoy!
- Garden of Ed
EOF

# Create version info
cat > "${RELEASE_DIR}/VERSION.txt" << EOF
Red Belly Sea Sweeper
Version: ${VERSION}
Build Date: $(date +"%Y-%m-%d")
Formats: AU, VST3
Platform: macOS (Intel & Apple Silicon)
Developer: Garden of Ed
Website: https://gardenofed.com
GitHub: https://github.com/edengrill/RedBellySeaSweeper
EOF

# Create the zip file
echo "Creating zip archive..."
cd Release
zip -r "${RELEASE_NAME}.zip" "${RELEASE_NAME}"
cd ..

# Calculate file sizes
AU_SIZE=$(du -h "${RELEASE_DIR}/Red Belly Sea Sweeper.component" | cut -f1)
VST3_SIZE=$(du -h "${RELEASE_DIR}/Red Belly Sea Sweeper.vst3" | cut -f1)
ZIP_SIZE=$(du -h "Release/${RELEASE_NAME}.zip" | cut -f1)

echo ""
echo "✅ Release package created successfully!"
echo ""
echo "📦 Package Contents:"
echo "  - Red Belly Sea Sweeper.component (${AU_SIZE})"
echo "  - Red Belly Sea Sweeper.vst3 (${VST3_SIZE})"
echo "  - Documentation files"
echo ""
echo "📁 Output:"
echo "  - Directory: Release/${RELEASE_NAME}/"
echo "  - Zip file: Release/${RELEASE_NAME}.zip (${ZIP_SIZE})"
echo ""
echo "Next steps:"
echo "1. Test the plugins from the Release folder"
echo "2. Upload ${RELEASE_NAME}.zip to GitHub Releases"
echo "3. Tag the release as v${VERSION}"
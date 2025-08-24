# Version Guide - Red Belly Sea Sweeper (Swoop Device)

## Current Active Version: v1.1.1
✅ **WORKING AUDIO** - Dropdown menus with sound

## Version History

### v1.0.5 
- Original working version with dropdowns
- Name: "Swoop Device"
- Files: `PluginEditor_v1.0.5_backup.cpp/h`
- Status: ✅ AUDIO WORKS

### v1.1.0
- Rebranded to "Red Belly Sea Sweeper by Garden of Ed"
- Reduced height from 644px to 480px
- Files: `PluginEditor_v1.1.0.cpp/h`
- Status: ✅ AUDIO WORKS (probably)

### v1.1.1 (CURRENTLY ACTIVE)
- Fixed positioning of branding and dropdowns
- Moved text left to x=50
- Files: `PluginEditor_v1.1.1.cpp`
- Status: ✅ AUDIO WORKS

### v1.1.2
- Attempted to move dropdowns to bottom (y=430)
- Files: `PluginEditor_v1.1.2.cpp`
- Status: Dropdowns still overlapped

### v1.2.0 
- **ARROW SELECTORS** - No dropdown menus
- Uses up/down arrows to cycle options
- Files: `PluginEditor_v1.2.0.cpp/h`
- Status: ❌ NO AUDIO (needs fixing)

## How to Switch Versions

To switch to any version:
```bash
# Copy the version files
cp PluginEditor_vX.X.X.cpp PluginEditor.cpp
cp PluginEditor_vX.X.X.h PluginEditor.h  # if header exists

# Rebuild
cd Builds/MacOSX
xcodebuild -configuration Release -target "SwoopDevice - AU"
```

## Known Issues

### v1.2.0 Arrow Selector - No Audio
The arrow selector version doesn't produce audio. The issue is likely that the ArrowSelector doesn't properly notify the audio processor of parameter changes. Need to:
1. Check onChange callback implementation
2. Ensure proper parameter notification
3. Verify audio processor connection

### Dropdown Positioning
Versions 1.1.1 and 1.1.2 have dropdown menus that open in middle of plugin rather than staying within white bezel area.

## Recommended Action
Stay on v1.1.1 for now (audio works) and fix the arrow selector audio issue in a new v1.2.1
# Red Belly Sea Sweeper - Installation Guide

## Quick Install

### macOS
1. Download the latest release
2. Unzip the downloaded file
3. Copy the plugins to their respective folders:
   - **AU**: Copy `Red Belly Sea Sweeper.component` to `~/Library/Audio/Plug-Ins/Components/`
   - **VST3**: Copy `Red Belly Sea Sweeper.vst3` to `~/Library/Audio/Plug-Ins/VST3/`
4. Restart your DAW
5. Look for "Red Belly Sea Sweeper" under "Garden of Ed" manufacturer

## Detailed Installation

### Audio Unit (AU) Installation
1. Open Finder
2. Press `Cmd+Shift+G` and enter: `~/Library/Audio/Plug-Ins/Components/`
3. Drag `Red Belly Sea Sweeper.component` into this folder
4. If prompted, enter your password to authorize the installation
5. Restart your DAW (Logic Pro, Ableton Live, etc.)

### VST3 Installation
1. Open Finder
2. Press `Cmd+Shift+G` and enter: `~/Library/Audio/Plug-Ins/VST3/`
3. Drag `Red Belly Sea Sweeper.vst3` into this folder
4. If prompted, enter your password to authorize the installation
5. Restart your DAW (Cubase, Studio One, Reaper, etc.)

## First Run

### macOS Security (Gatekeeper)
If macOS prevents the plugin from loading:
1. Open System Preferences → Security & Privacy
2. Click the "General" tab
3. Look for a message about the blocked plugin
4. Click "Open Anyway"
5. Restart your DAW

### Alternative method:
Open Terminal and run:
```bash
# For AU
xattr -cr ~/Library/Audio/Plug-Ins/Components/Red\ Belly\ Sea\ Sweeper.component

# For VST3
xattr -cr ~/Library/Audio/Plug-Ins/VST3/Red\ Belly\ Sea\ Sweeper.vst3
```

## Verify Installation

### In Logic Pro
1. Open Logic Pro
2. Create a new Audio track
3. Click on Audio FX slot
4. Navigate to: Garden of Ed → Red Belly Sea Sweeper

### In Ableton Live
1. Open Ableton Live
2. Go to Plug-ins section in browser
3. Look under "Garden of Ed" or search for "Red Belly"
4. Drag onto an audio track

### In Other DAWs
1. Rescan plugins if needed (check DAW preferences)
2. Look for "Red Belly Sea Sweeper" or "Garden of Ed"
3. The plugin may appear under Instruments or Effects

## Troubleshooting

### Plugin doesn't appear
- Make sure you copied to the correct folder
- Restart your DAW
- Rescan plugins in DAW preferences
- Check both AU and VST3 sections

### "Damaged" or "Can't be opened" error
Run this in Terminal:
```bash
sudo spctl --master-disable
# Install plugin
sudo spctl --master-enable
```

### DAW crashes when loading
- Make sure you're using macOS 10.13 or later
- Try the other format (AU vs VST3)
- Contact support with crash report

## System Requirements
- **macOS**: 10.13 High Sierra or later
- **Architecture**: Intel or Apple Silicon (Universal Binary)
- **DAW**: Any AU or VST3 compatible host

## Uninstallation
To remove the plugin, delete:
- `~/Library/Audio/Plug-Ins/Components/Red Belly Sea Sweeper.component`
- `~/Library/Audio/Plug-Ins/VST3/Red Belly Sea Sweeper.vst3`

## Support
For help, visit: https://github.com/edengrill/RedBellySeaSweeper/issues

---
*Version 1.4.5 - August 2024*
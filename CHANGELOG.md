# Changelog

All notable changes to the Swoop Device audio plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.5] - 2024-08-24

### Added
- Entire combo box area is now clickable (not just the arrow)
- Improved user experience with larger clickable area

### Changed
- Created `DropUpComboBox_v1.0.5.h` with expanded hit area
- Override `hitTest` to make full rectangle interactive
- Better mouse event handling for entire combo box area

### Improved
- Users can now click anywhere on the Wave or Mode box to open dropdown
- More intuitive interaction - no need to click specifically on arrow
- Maintains all fixes from v1.0.4 (reopening, positioning)

## [1.0.4] - 2024-08-24

### Fixed
- Dropdown menus now work multiple times per session (was only opening once)
- Dropdown menu position now appears directly above combo box (was opening too high)
- Fixed mouse event handling to prevent popup glitches

### Changed
- Created `DropUpComboBox_v1.0.4.h` with improved event handling
- Used `withTargetComponent` for better menu positioning
- Simplified mouse event handling to prevent conflicts
- Adjusted menu gap to 4px for closer positioning

### Technical Improvements
- Override both `mouseDown` and `mouseUp` to control popup behavior
- Use `sendNotificationSync` for proper state updates
- More accurate positioning calculation relative to combo box

## [1.0.3] - 2024-08-24

### Fixed
- Mode dropdown now properly opens upward (was still opening downward in v1.0.2)
- Improved DropUpComboBox implementation for more reliable upward menu positioning

### Changed
- Created `DropUpComboBox_v1.0.3.h` with enhanced menu positioning logic
- More accurate menu height calculation (25px per item)
- Explicit 2px gap between combo box and menu

## [1.0.2] - 2024-08-24

### Added
- Custom `DropUpComboBox` class for upward-opening dropdown menus
- PopupMenu direction control using JUCE's PopupDirection::upwards

### Changed
- Wave and Mode combo boxes now use DropUpComboBox class
- Dropdown arrows now point upward to indicate menu direction

### Fixed
- Attempted to make dropdowns open upward (partially successful)

## [1.0.1] - 2024-08-24

### Fixed
- Duplicate text overlay in dropdown boxes
- Text was being rendered twice (once by JUCE, once manually)

### Changed
- Moved dropdown boxes closer to bottom of plugin window (y=460 to y=580)
- Removed manual text drawing in `drawComboBox`
- Added `drawComboBoxTextWhenNothingSelected` for proper text handling
- Modified dropdown arrow to point upward (visual only)

## [1.0.0] - 2024-08-24

### Initial Release
- Frequency sweep generator plugin (20Hz - 20kHz)
- Real-time waveform visualization
- Power on/off toggle switch
- Start/End frequency controls
- Sweep time control (0.1s - 60s)
- Wave type selection (Sine, Sawtooth, Square, Triangle)
- Sweep mode selection (Single, Loop, Sweep/Bidirectional)
- Custom UI with red/black color scheme
- Pixel-perfect recreation from original design screenshots

### Technical Features
- JUCE 7.0.9 framework
- AU (Audio Unit) format for macOS
- VST3 support (build configuration included)
- Standalone application build
- Thread-safe audio processing
- 60 FPS waveform animation
- Logarithmic frequency sweeping
- Custom Look & Feel implementation

### Development Journey
- **Phase 1**: Screenshot analysis and design extraction
- **Phase 2**: HTML/CSS/JavaScript prototype with Web Audio API
- **Phase 3**: JUCE plugin development
- **Phase 4**: Build, validation, and deployment

---

## Version Numbering

This project uses Semantic Versioning:
- **Major version (1.x.x)**: Incompatible API changes or major feature additions
- **Minor version (x.1.x)**: Backwards-compatible functionality additions
- **Patch version (x.x.1)**: Backwards-compatible bug fixes

## Build Information

All versions are built using:
- macOS Xcode
- JUCE Framework 7.0.9
- C++17 standard
- Target: macOS 10.13+

## Installation

Copy the `.component` file to:
```
~/Library/Audio/Plug-Ins/Components/
```

Then restart your DAW or rescan plugins.

## Repository

Source code and releases available at:
https://github.com/edengrill/SwoopDevice

---

*This plugin was developed using AI-assisted development with Claude (Anthropic)*
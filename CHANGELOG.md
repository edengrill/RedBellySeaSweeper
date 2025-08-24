# Changelog

All notable changes to the Swoop Device audio plugin will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.3.0] - 2024-08-24

### Revolutionary UI Update - Integrated Controls
- **Wave and Mode selectors integrated into visualizer window**
- Positioned on left side, similar to frequency/percentage display
- Click to cycle through options (no dropdown menus)
- Hover effect shows clickable areas
- Clean, minimal design with no popups

### Features
- WAVE: Click to cycle through SINE → SAWTOOTH → SQUARE → TRIANGLE
- MODE: Click to cycle through SINGLE → LOOP → SWEEP
- Visual feedback on hover (highlight effect)
- Hand cursor on hover to indicate clickable

### Improved
- No more dropdown positioning issues
- All controls within the main visualizer
- Cleaner interface with better use of space
- Maintains full audio functionality from v1.1.1

### Removed
- External combo boxes/dropdowns
- Separate Wave and Mode controls below plugin

## [1.1.3] - 2024-08-24

### Fixed - Dropdown Positioning Solution
- **Moved dropdowns to top area** between waveform and control panel
- Wave and Mode dropdowns now at y=205 (just below waveform)
- Using regular dropdowns (drop DOWN) instead of drop-up menus
- Dropdowns have clear space to open without overlapping

### Changed
- Switched from DropUpComboBox to regular ComboBox
- Dropdowns positioned horizontally centered below waveform
- Branding text moved slightly lower (y=400, y=425)

### Improved
- Clean separation between all UI elements
- No more overlapping menus
- All options visible when dropdown clicked
- Maintains full audio functionality

## [1.2.0] - 2024-08-24

### Changed - Major UI Update
- **Replaced dropdown menus with arrow selectors**
- Wave and Mode selection now uses up/down arrow buttons
- No more overlapping popup menus
- Cleaner, more compact interface

### Features
- Arrow buttons (▲▼) to cycle through Wave types (Sine/Sawtooth/Square/Triangle)
- Arrow buttons to cycle through Modes (Single/Loop/Sweep)
- Current selection always visible in display area
- No popup menus - everything stays within the plugin bounds

### Improved
- Better user experience with no overlapping elements
- More reliable interaction model
- Suitable for both mouse and touch interfaces
- Maintains all existing functionality

## [1.1.2] - 2024-08-24

### Fixed  
- Moved Wave and Mode controls to bottom of white bezel area (y=430)
- Adjusted drop-up menu positioning to fit within white area
- Menus now appear between control panel and combo boxes

### Changed
- Wave/Mode controls repositioned from y=405 to y=430 (closer to bottom edge)
- Reduced combo box heights from 30px to 25px for better fit
- Drop-up menus constrained to area between y=380 and y=430

### Added
- Alternative ArrowSelector implementation for cycling through options
- Option to use up/down arrow buttons instead of dropdown menus

## [1.1.1] - 2024-08-24

### Fixed
- Repositioned branding text and dropdowns to align better on left side
- Adjusted dropdown positions to prevent right-side overflow
- Fixed drop-up menu positioning to avoid overlapping with control panel
- Ensured drop-up menus stay below control panel area (y=385 minimum)

### Changed
- Moved "Red Belly Sea Sweeper" text from x=90 to x=50
- Adjusted Wave dropdown position from x=435 to x=375
- Adjusted Mode dropdown position from x=615 to x=555
- Improved overall UI balance and spacing

## [1.1.0] - 2024-08-24

### Major Update - Rebranding and Redesign

### Changed
- **New Name**: Plugin renamed to "Red Belly Sea Sweeper by Garden of Ed"
- **Reduced Height**: Plugin window reduced from 644px to 480px
- **Control Panel**: Now same height as waveform display (160px)
- **Layout**: More compact design with less dead space

### Added
- Plugin branding text "Red Belly Sea Sweeper"
- Author credit "by Garden of Ed"
- Both in red color (#d83427) matching the theme

### Repositioned
- Wave and Mode dropdowns moved to bottom area
- Dropdowns aligned with branding text on same line
- Labels positioned inline with dropdowns
- Controls vertically centered in panel

### Visual Improvements
- Consistent red accent color throughout
- Better use of space
- Professional branding presentation
- Maintained all v1.0.5 functionality

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
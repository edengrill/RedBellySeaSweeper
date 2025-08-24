# UI Options for Wave/Mode Selection

Version 1.1.2 includes two different UI approaches for Wave and Mode selection:

## Option 1: Drop-up Menus (Currently Active)
- Uses dropdown menus that open upward
- Wave and Mode buttons positioned at bottom of white bezel (y=430)
- Menus appear in the space between control panel and buttons

## Option 2: Arrow Selectors
- Uses up/down arrow buttons to cycle through options
- No overlapping popup menus
- Cleaner look, always visible current selection
- Better for small spaces

## How to Switch Between Options

### To use Drop-up Menus (default):
The plugin currently uses this option. No changes needed.

### To use Arrow Selectors:
1. Edit `Source/PluginEditor.h`:
   - Replace `#include "DropUpComboBox_v1.1.2.h"` with `#include "ArrowSelector.h"`
   - Replace `DropUpComboBox waveTypeCombo;` with `ArrowSelector waveTypeSelector;`
   - Replace `DropUpComboBox sweepModeCombo;` with `ArrowSelector sweepModeSelector;`

2. Update the implementation in `Source/PluginEditor.cpp` to use the ArrowSelector API

3. Rebuild the plugin

## Benefits of Each Approach

### Drop-up Menus:
- Familiar interface pattern
- Shows all options at once
- Takes less permanent space

### Arrow Selectors:
- No overlapping issues
- Always visible
- Simpler interaction
- Better for touch interfaces

Both options maintain the same functionality and parameter control.
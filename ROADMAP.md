# Red Belly Sea Sweeper - Development Roadmap

## Version History
- **v1.4.5** (Current) - VST3 keyboard focus fix
- **v1.4.4** - Default settings update (Sweep mode, 6.7kHz→699Hz, 13.5s)
- **v1.4.0** - Added X key activation
- **v1.3.0** - Wave/Mode integrated in visualizer

## Future Features & Enhancements

### 🎯 Priority Features (v1.5.0)
- [ ] **Standalone Application**
  - Build standalone version for non-DAW users
  - Useful for audio testing and demos
  - Cross-platform compatibility

- [ ] **Preset System**
  - Save/load sweep configurations
  - Built-in factory presets:
    - THX Deep Sweep
    - Quick Test Sweep
    - Sub Bass Check
    - High Frequency Test
    - Room Resonance Finder
  - User preset management
  - Preset browser with categories

### 🎨 Visual Enhancements (v1.6.0)
- [ ] **Real-time Frequency Display**
  - Large frequency readout during sweep
  - Frequency spectrum analyzer
  - Peak frequency indicator

- [ ] **Progress Indicators**
  - Sweep progress bar
  - Time remaining display
  - Visual markers for start/end frequencies on waveform

- [ ] **Enhanced Waveform Visualization**
  - 3D waveform option
  - Color gradients based on frequency
  - Animated wave patterns
  - Oscilloscope mode

### 🎹 MIDI & Control Features (v1.7.0)
- [ ] **MIDI Control**
  - Map start/stop to MIDI notes
  - CC control for all parameters
  - MIDI learn functionality
  - Program change for presets

- [ ] **Enhanced Automation**
  - Smooth parameter interpolation
  - Automation recording mode
  - Parameter lock/unlock
  - Automation curves visualization

### 🔊 Audio Features (v2.0.0)
- [ ] **Advanced Sweep Modes**
  - Exponential sweep curve
  - Logarithmic sweep curve
  - Custom curve editor
  - Chirp signal generator
  - White/Pink noise sweep

- [ ] **Audio Export**
  - Export sweep as WAV/AIFF file
  - Batch export presets
  - Export with markers
  - Loop export for DAW import

- [ ] **Additional Controls**
  - Dry/Wet mix knob
  - Output gain control
  - Pan control for stereo sweeps
  - Phase adjustment
  - Harmonic content control

### 🛠 Technical Improvements
- [ ] **Performance Optimization**
  - CPU usage optimization
  - Memory footprint reduction
  - Multi-threading support
  - GPU acceleration for visuals

- [ ] **Compatibility**
  - AAX format support (Pro Tools)
  - AUv3 support (iOS/iPadOS)
  - Linux VST3 support
  - CLAP format support

### 📱 Mobile & Touch Support
- [ ] **Touch Interface**
  - iPad/tablet optimized UI
  - Multi-touch gesture support
  - Pinch to zoom waveform
  - Swipe to change presets

### 🔬 Analysis Tools
- [ ] **Measurement Features**
  - Room response analysis
  - Speaker frequency response
  - THD measurement
  - Phase response display
  - Waterfall plot

### 🎮 Creative Features
- [ ] **Modulation System**
  - LFO for parameter modulation
  - Envelope follower
  - Step sequencer for sweep triggers
  - Random sweep generator

- [ ] **Multi-band Mode**
  - Split frequency sweeps
  - Parallel sweep bands
  - Crossover controls
  - Per-band wave selection

### 🌐 Connectivity
- [ ] **Network Features**
  - Remote control via web interface
  - OSC support
  - Wireless MIDI
  - Cloud preset sharing

### 📚 Documentation & Learning
- [ ] **Interactive Tutorials**
  - In-app help system
  - Video tutorials integration
  - Tooltips with examples
  - Contextual help

### 🎨 Themes & Customization
- [ ] **UI Themes**
  - Dark mode
  - Light mode
  - Custom color schemes
  - Scalable UI (50%-200%)
  - Font size options

## Release Strategy

### Short Term (1-2 months)
1. v1.5.0 - Standalone + Preset System
2. v1.5.5 - Visual Enhancements

### Medium Term (3-6 months)
3. v1.6.0 - MIDI Control
4. v1.7.0 - Advanced Sweep Modes

### Long Term (6-12 months)
5. v2.0.0 - Major feature release with audio export and analysis tools

## Community Requested Features
_Space for user-requested features from feedback_
- [ ] _Add community requests here_

## Technical Debt
- [ ] Refactor waveform generation for efficiency
- [ ] Improve preset file format
- [ ] Add comprehensive unit tests
- [ ] Documentation improvements
- [ ] Code optimization for real-time performance

## Notes
- Maintain backward compatibility with presets
- Keep UI simple and intuitive despite new features
- Prioritize audio quality and real-time performance
- Consider modular architecture for feature plugins

---
*Last Updated: August 2024*
*Version: 1.4.5*
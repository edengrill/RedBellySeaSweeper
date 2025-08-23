//------------------------------------------------------------------------
// Project     : VST SDK
// Module      : vstfxstore.h
// Compatibility header for JUCE VST3 builds
//------------------------------------------------------------------------

#pragma once

#include "../vst/vsttypes.h"

namespace Steinberg {
namespace Vst {

// Basic VST2 compatibility types for JUCE
typedef int32 VstInt32;
typedef int64 VstInt64;

struct FXBank
{
    VstInt32 chunkMagic;
    VstInt32 byteSize;
    VstInt32 fxMagic;
    VstInt32 version;
    VstInt32 fxID;
    VstInt32 fxVersion;
    VstInt32 numPrograms;
    char future[128];
};

struct FXProgram  
{
    VstInt32 chunkMagic;
    VstInt32 byteSize;
    VstInt32 fxMagic;
    VstInt32 version;
    VstInt32 fxID;
    VstInt32 fxVersion;
    VstInt32 numParams;
    char prgName[28];
};

} // namespace Vst
} // namespace Steinberg
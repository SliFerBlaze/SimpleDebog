#pragma once

#include <string>

enum class DebugEventType {
    Fake, // For testing purposes
    BreakpointHit,
    LeakDetected,
    ExceptionThrown,
};

struct DebugEvent {
    DebugEventType type;
    std::string description;
};

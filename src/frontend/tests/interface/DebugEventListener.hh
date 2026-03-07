#pragma once
#include <cstdint>
#include <vector>
#include "../shared/models/StackFrame.hh"

enum class DebugEventType {
    BreakpointHit,
    StackUpdated
};

struct DebugEvent {
    DebugEventType type;
    std::uintptr_t address;
    std::vector<StackFrame> stackFrames;
};

class DebugEventListener {
public:
    virtual ~DebugEventListener() = default;
    virtual void onEvent(const DebugEvent& event) = 0;
};

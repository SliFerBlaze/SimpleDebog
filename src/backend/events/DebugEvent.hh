#pragma once

#include <string>

enum class DebugEventType {
    Fake,
};

struct DebugEvent {
    DebugEventType type;
    std::string description;
};

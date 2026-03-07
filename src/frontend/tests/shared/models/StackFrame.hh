#pragma once
#include <string>
#include <cstdint>

struct StackFrame {
    std::string functionName;
    std::uintptr_t address;
};

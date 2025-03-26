#pragma once
#include <string>
#include <variant>
#include <memory>
#include "../syscall.h"

using DecodedValue = std::variant<int, unsigned int, std::string, uintptr_t>;

class Decoder
{
public:
    virtual ~Decoder() = default;
    virtual DecodedValue decode(pid_t pid, uintptr_t value) const = 0;
};

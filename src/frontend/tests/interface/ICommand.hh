#pragma once
#include <memory>
#include <cstdint>

struct ICommand {
    virtual ~ICommand() = default;
};

struct StepCommand : public ICommand {};
struct AddBreakpointCommand : public ICommand {
    std::uintptr_t address;
    explicit AddBreakpointCommand(std::uintptr_t addr) : address(addr) {}
};

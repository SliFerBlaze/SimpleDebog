#pragma once
#include <memory>
#include <vector>
#include "DebugEventListener.hh"

class ICommand; // Forward declaration for future compatibility

class IDebugger {
public:
    virtual ~IDebugger() = default;

    virtual void addListener(DebugEventListener* listener) = 0;
    virtual void removeListener(DebugEventListener* listener) = 0;

    virtual void executeCommand(std::unique_ptr<ICommand> cmd) = 0;
};

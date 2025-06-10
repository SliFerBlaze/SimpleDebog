#pragma once

#include "backend/commands/ICommand.hh"
#include "interface/DebugEventListener.hh"
#include <memory>

class IDebugger
{
  public:
    virtual void executeCommand(std::unique_ptr<ICommand> cmd) = 0;
    virtual void addListener(DebugEventListener *event_listener) = 0;
    virtual ~IDebugger() = default;
};

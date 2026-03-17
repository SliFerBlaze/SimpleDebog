#pragma once

#include "interface/DebugEventListener.hh"
#include "interface/ICommand.hh"
#include <memory>

class IDebugger
{
  public:
    virtual void executeCommand(std::unique_ptr<ICommand> cmd) = 0;
    virtual void addListener(DebugEventListener *event_listener) = 0;
    virtual ~IDebugger() = default;
};

#pragma once

#include "backend/commands/ICommand.hh"
#include "backend/events/DebugEvent.hh"
#include "interface/DebugEventListener.hh"
#include "interface/IDebugger.hh"
#include <memory>
#include <queue>
#include <vector>

class DebuggerEngine : IDebugger
{
  private:
    std::vector<DebugEventListener *> _listeners;
    std::queue<std::unique_ptr<ICommand>> _commands;

  public:
    void executeCommand(std::unique_ptr<ICommand> cmd) override;
    void addListener(DebugEventListener *event_listener) override;
    void emitEvent(std::unique_ptr<DebugEvent> event);
    std::unique_ptr<ICommand> popCommand(void);
    DebuggerEngine();
    ~DebuggerEngine();
};

#include "DebuggerEngine.hh"
#include <iostream>

DebuggerEngine::DebuggerEngine() {}

DebuggerEngine::~DebuggerEngine()
{
}

void DebuggerEngine::executeCommand(std::unique_ptr<ICommand> cmd)
{
    if (cmd) {
        _commands.push(std::move(cmd));
    }
    else {
        throw std::invalid_argument("Command cannot be null");
    }
}

void DebuggerEngine::addListener(DebugEventListener *event_listener)
{
    if (event_listener) {
        _listeners.push_back(event_listener);
    }
    else {
        throw std::invalid_argument("Event listener cannot be null");
    }
}

void DebuggerEngine::emitEvent(std::unique_ptr<DebugEvent> event)
{
    if (event) {
        for (auto &listener : _listeners) {
            listener->onEvent(*event);
        }
    }
    else {
        throw std::invalid_argument("Debug event cannot be null");
    }
}

std::unique_ptr<ICommand> DebuggerEngine::popCommand(void)
{
    if (_commands.empty()) {
        return nullptr;
    }
    auto cmd = std::move(_commands.front());
    _commands.pop();
    return cmd;
}

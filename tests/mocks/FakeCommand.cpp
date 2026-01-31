#include "FakeCommand.hh"
#include <iostream>

FakeCommand::FakeCommand(DebuggerEngine *engine)
{
    if (engine) {
        _engine = engine;
    }
    else {
        throw std::invalid_argument("DebuggerEngine cannot be null");
    }
}

FakeCommand::~FakeCommand()
{
    // not responsable for deleting _engine
}

void FakeCommand::execute()
{
    std::cout << "FakeCommand executed" << std::endl;
    _engine->emitEvent(std::make_unique<DebugEvent>(DebugEventType::Fake, "Fake command executed"));
}
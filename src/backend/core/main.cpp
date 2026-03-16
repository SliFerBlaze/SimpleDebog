#include "./main.hh"

void main_backend_core(DebuggerEngine &engine, ILowLevelDebugger &debugger, bool &running)
{
    while (running) {
        auto command = engine.popCommand();
        if (command) {
            command->addArgument(std::reference_wrapper<ILowLevelDebugger>(debugger));
            command->execute();
            command->callback({});
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

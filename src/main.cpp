#include "backend/core/main.hh"
#include "backend/core/DebuggerEngine.hh"
#include "backend/platform/linux/PtraceWrapper.hh"
#include <Logger.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

int main(int ac, char **av)
{
    Logger::parse_args(ac, av);

    // string vector from av
    std::vector<std::string> args(av + 1, av + ac);

    debug("Launching the program with " + std::to_string(args.size()) + " arguments.");
    for (size_t i = 0; i < args.size(); ++i) {
        debug("Argument " + std::to_string(i) + ": " + args[i]);
    }
    PtraceWrapper ptraceWrapper;

    ptraceWrapper.attach(args[0], args);
    debug("Program attached");

    DebuggerEngine debugger;
    bool running = true;

    std::thread backendThread(
        main_backend_core,
        std::ref(debugger),
        std::ref(ptraceWrapper),
        std::ref(running));

    //    MainWindow mainWindow;
    //    mainWindow.loop(std::move(command), std::move(debugger));

    running = false;
    backendThread.join();
    debug("Detaching from program");
    ptraceWrapper.detach();
    debug("Program detached");
    return 0;
}

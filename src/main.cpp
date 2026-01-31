#include <Logger.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "backend/platform/linux/PtraceWrapper.hh"
#include <unistd.h>

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
    debug("Resuming program");
    ptraceWrapper.resume();

    debug("Detaching from program");

    ptraceWrapper.detach();

    debug("Program detached");
    return 0;
}

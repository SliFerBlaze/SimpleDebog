#include <Logger.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "backend/platform/linux/PtraceWrapper.hh"
#include <unistd.h>

int main(int ac, char **av)
{
    Logger::parse_args(ac, av);
    debug("Launching the program with " + std::to_string(ac) + " arguments.");
    for (int i = 0; i < ac; ++i) {
        debug("Argument " + std::to_string(i) + ": " + av[i]);
    }
    PtraceWrapper ptraceWrapper;

    ptraceWrapper.attach(av[1], av + 2);

    debug("Program attached");
    debug("Resuming program");
    ptraceWrapper.resume();

    debug("Detaching from program");

    ptraceWrapper.detach();

    debug("Program detached");
    return 0;
}

#include "Decoder/DecoderFactory.hpp"
#include "Decoder/Include.hpp"
#include "PlatformDefines.hpp"
#include "Trace.hh"
#include <iostream>

int main([[maybe_unused]] int argc, char **argv, char **env)
{

    const char *newMessage = "ALED \n";

    Trace a(&argv[1], env);
    a.run();
    a.next();
    while (a.get_lastsyscall().name != "write") {
        a.next();
    }

    std::cout << "\n\n"
              << a.get_lastsyscall().raw_args[2] << std::endl;
    if (!a.dumpMemory(a.get_lastsyscall().raw_args[1], a.get_lastsyscall().raw_args[2], "memory_dump.bin"))
        std::cerr << "Failed to dump memory\n";

    if (!a.modifyMemory(a.get_lastsyscall().raw_args[1], newMessage, a.get_lastsyscall().raw_args[2])) {
        std::cerr << "Failed to modify memory\n";
        return 1;
    }

    while (a.next())
        ;

    return 0;
}

#include <Logger.hpp>
#include <iostream>

int main(int ac, char **av)
{
    Logger::parse_args(ac, av);
    debug("Launching the program with " + std::to_string(ac) + " arguments.");
    for (int i = 0; i < ac; ++i) {
        debug("Argument " + std::to_string(i) + ": " + av[i]);
    }
    return 0;
}

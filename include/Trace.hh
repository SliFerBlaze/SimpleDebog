#pragma once

#include <sys/ptrace.h>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <optional>
#include "syscall.h"
#include "Decoder/DecoderFactory.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

struct SyscallData
{
    size_t id; // Store syscall ID
    std::string name;
    std::vector<DecodedValue> args;
    std::vector<long long unsigned int> raw_args;
    std::optional<DecodedValue> retval;
};

class Trace
{
private:
    pid_t _pid;
    char **_argv;
    char **_env;
    std::vector<SyscallData> _syscallLog;
    uintptr_t _baseAddress = 0;
    std::unordered_map<std::string, uintptr_t> _sharedLibBase;

    void peekdata(struct user_regs_struct &regs);
    uintptr_t getSharedLibBase(const std::string &libName) const;
    uintptr_t resolveAddress(uintptr_t addr, const std::string &lib);

public:
    explicit Trace(char **argv, char **env);
    void run(void);
    bool next(void);
    void show(void);
    SyscallData get_lastsyscall(void) const;
    uintptr_t getBaseAddress(void);

    bool dumpMemory(uintptr_t address, size_t size, const std::string &filename);
    bool modifyMemory(uintptr_t addr, const void *data, size_t size);

    ~Trace(void);
};

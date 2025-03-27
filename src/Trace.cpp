#include "Trace.hh"
#include "Decoder/DecoderFactory.hpp"
#include "syscall.h"
#include <cstring>
#include <filesystem>
#include <iostream>

Trace::Trace(char **argv, char **env) : _argv(argv), _env(env)
{
    if (argv == nullptr || env == nullptr || *argv == nullptr)
        throw std::runtime_error("Invalid arguments");

    if (access(*argv, X_OK | R_OK))
        throw std::runtime_error("Err: Trace: Bin is not Executable or Readable");
}

void Trace::peekdata(struct user_regs_struct &regs)
{
    auto &factory = DecoderFactory::getInstance();

    size_t syscall_num = regs.orig_rax;
    if (syscall_num >= 329) {
        std::cout << "Unsupported syscall: " << syscall_num << "\n";
        return;
    }

    const syscall_t &info = table[syscall_num];

    SyscallData syscallData;
    syscallData.id = syscall_num;
    syscallData.name = info.name;

    uintptr_t args[] = {
        regs.rdi, regs.rsi, regs.rdx, regs.r10, regs.r8, regs.r9};

    int types[] = {
        info.param1, info.param2, info.param3,
        info.param4, info.param5, info.param6};

    // Decode arguments
    for (int i = 0; i < info.nb_param; ++i) {
        auto decoder = factory.createDecoder(types[i]);
        if (decoder) {
            DecodedValue value = decoder->decode(_pid, args[i]);
            syscallData.args.push_back(std::move(value));
            syscallData.raw_args.push_back(args[i]);
        }
        else {
            syscallData.args.push_back(std::string("<unknown>"));
            syscallData.raw_args.push_back(args[i]);
        }
    }

    _syscallLog.push_back(std::move(syscallData));
}

uintptr_t Trace::getBaseAddress()
{
    std::ifstream mapsFile("/proc/" + std::to_string(_pid) + "/maps");
    if (!mapsFile.is_open()) {
        throw std::runtime_error("Failed to open /proc/" + std::to_string(_pid) + "/maps");
    }

    std::string line;
    uintptr_t executableBase = 0;
    std::unordered_map<std::string, uintptr_t> sharedLibs;

    while (std::getline(mapsFile, line)) {
        std::istringstream iss(line);

        uintptr_t start;
        uintptr_t end;
        char dash;
        std::string perms;
        std::string offset;
        std::string dev;
        std::string inode;
        std::string pathname;

        if (!(iss >> std::hex >> start >> dash >> end >> perms >> offset >> dev >> inode)) {
            continue;
        }

        if (iss >> pathname) {
            // Detect main executable
            if (perms.find('x') != std::string::npos) {
                if (std::filesystem::path(pathname).filename() == std::filesystem::path(*_argv).filename()) {
                    executableBase = start;
                    std::cout << "[+] Found executable base address: 0x"
                              << std::hex << executableBase << "\n"
                              << std::dec;
                }
                // Detect shared libraries
                else if (pathname.find(".so") != std::string::npos) {
                    sharedLibs[pathname] = start;
                    std::cout << "[+] Found shared library: " << pathname
                              << " at 0x" << std::hex << start << "\n"
                              << std::dec;
                }
            }
        }
    }

    mapsFile.close();

    if (executableBase == 0) {
        throw std::runtime_error("Base address not found");
    }

    // Store the executable base address (main target)
    _baseAddress = executableBase;

    // Optionally store shared libraries for later resolving
    _sharedLibBase = std::move(sharedLibs);

    return executableBase;
}

uintptr_t Trace::getSharedLibBase(const std::string &libName) const
{
    auto it = _sharedLibBase.find(libName);
    if (it != _sharedLibBase.end())
        return it->second;

    throw std::runtime_error("Shared library not found: " + libName);
}

uintptr_t Trace::resolveAddress(uintptr_t addr, const std::string &lib = "")
{
    if (!lib.empty())
        return getSharedLibBase(lib) + addr;

    if (_baseAddress == 0)
        throw std::runtime_error("Base address not set");

    return _baseAddress + addr;
}

bool Trace::next()
{
    int status;
    struct user_regs_struct regs;

    // Wait for syscall entry
    ptrace(PTRACE_SYSCALL, _pid, 0, 0);
    waitpid(_pid, &status, 0);

    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        return false;
    }

    // Get syscall state on entry
    ptrace(PTRACE_GETREGS, _pid, NULL, &regs);

    // Process syscall entry
    size_t syscall_num = regs.orig_rax;
    if (syscall_num < 329) {
        peekdata(regs);
    }
    else {
        std::cout << "Unsupported syscall: " << syscall_num << "\n";
    }

    // Wait for syscall exit
    ptrace(PTRACE_SYSCALL, _pid, 0, 0);
    waitpid(_pid, &status, 0);

    if (WIFEXITED(status) || WIFSIGNALED(status)) {
        return false;
    }

    // Get syscall state on exit
    ptrace(PTRACE_GETREGS, _pid, NULL, &regs);

    auto retval = static_cast<long long>(regs.rax);

    if (!_syscallLog.empty()) {
        auto &lastSyscall = _syscallLog.back();

        // Decode the return value based on syscall ID
        const syscall_t &info = table[lastSyscall.id];
        auto decoder = DecoderFactory::getInstance().createDecoder(info.return_value);

        if (decoder) {
            lastSyscall.retval = decoder->decode(_pid, regs.rax);
        }
        else {
            lastSyscall.retval = std::string("<unknown>");
        }

        // Handle syscall errors
        if (retval < 0) {
            lastSyscall.retval = static_cast<int>(-retval);
        }
    }

    return true;
}

void Trace::show()
{

    std::cout << "[+] Base Address: 0x" << std::hex << _baseAddress << "\n"
              << std::dec;
    for (const auto &[lib, addr] : _sharedLibBase) {
        std::cout << "    [+] " << lib << " at 0x" << std::hex << addr << "\n"
                  << std::dec;
    }

    for (const auto &syscall : _syscallLog) {
        std::cout << "Syscall [" << syscall.id << "]: " << syscall.name << "\n";

        for (size_t i = 0; i < syscall.args.size(); ++i) {
            std::cout << "  Arg" << i + 1 << ": " << std::visit([](auto &&val) -> std::string {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, std::string>)
                    return val;
                else if constexpr (std::is_same_v<T, int>)
                    return std::to_string(val);
                else if constexpr (std::is_same_v<T, uintptr_t>)
                    return "0x" + std::to_string(val);
                else
                    return "<unknown>"; }, syscall.args[i])
                      << "\n";
        }

        if (syscall.retval) {
            std::cout << "  Return: " << std::visit([](auto &&val) -> std::string {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, std::string>)
                    return val;
                else if constexpr (std::is_same_v<T, int>)
                    return std::to_string(val);
                else if constexpr (std::is_same_v<T, uintptr_t>)
                    return "0x" + std::to_string(val);
                else
                    return "<unknown>"; }, *syscall.retval)
                      << "\n";
        }

        std::cout << "---------------------------------\n";
    }
}

bool Trace::dumpMemory(uintptr_t address, size_t size, const std::string &filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }

    size_t bytesRead = 0;
    while (bytesRead < size) {

        errno = 0;
        long data = ptrace(PTRACE_PEEKDATA, _pid, address + bytesRead, nullptr);
        if (errno != 0) {
            std::cerr << "Failed to read memory at 0x"
                      << std::hex << (address + bytesRead)
                      << " (errno: " << std::dec << errno << ")\n";
            break;
        }

        outFile.write(reinterpret_cast<char *>(&data), sizeof(data));

        bytesRead += sizeof(data);
    }

    outFile.close();

    if (bytesRead > 0) {
        std::cout << "[+] Dumped " << bytesRead << " bytes from 0x"
                  << std::hex << address << " to " << filename << "\n";
        return true;
    }
    else {
        std::cerr << "[-] Failed to dump memory\n";
        return false;
    }
}

bool Trace::modifyMemory(uintptr_t addr, const void *data, size_t size)
{
    if (_baseAddress == 0)
        throw std::runtime_error("Base address not set");

    const uint8_t *bytes = static_cast<const uint8_t *>(data);

    // Write in aligned word-sized chunks (usually 8 bytes on x86_64)
    size_t offset = 0;
    while (offset < size) {
        // Create a full word to write
        uintptr_t word = 0;
        std::memcpy(&word, bytes + offset, std::min(sizeof(word), size - offset));

        // Inject it using ptrace
        if (ptrace(PTRACE_POKEDATA, _pid, addr + offset, word) == -1) {
            perror("ptrace(POKEDATA) failed");
            return false;
        }

        offset += sizeof(word);
    }

    return true;
}

SyscallData Trace::get_lastsyscall(void) const
{
    return _syscallLog.back();
}

void Trace::run()
{
    _pid = fork();

    if (_pid < 0)
        throw std::runtime_error("Fork failed");

    if (_pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execve(*_argv, _argv, _env);
        perror("Execve failed");
        exit(1);
    }

    // Wait for the child to stop
    waitpid(_pid, nullptr, 0);

    _baseAddress = getBaseAddress();
}

Trace::~Trace()
{
    if (_pid != 0)
        waitpid(_pid, nullptr, 0);
}

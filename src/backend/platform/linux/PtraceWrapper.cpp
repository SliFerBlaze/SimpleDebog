#include "PtraceWrapper.hh"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>

PtraceWrapper::PtraceWrapper()
{
}

PtraceWrapper::~PtraceWrapper()
{
}

ILowLevelDebugger::StepResult PtraceWrapper::step(unsigned int stepSize) noexcept
{
    if (_process_info.pid == 0) {
        StepFailure ret;
        ret.success = false;
        ret.processInfo = _process_info.clone();
        ret.context = ILowLevelDebugger::Context::empty();
        ret.errorMessage = "No process attached";
        return ret;
    }
    int i = 0;
    while (stepSize) {
        int status = ptrace(PTRACE_SINGLESTEP, _process_info.pid, nullptr, nullptr);
        if (status != 0) {
            StepFailure ret;
            ret.success = false;
            ret.processInfo = _process_info.clone();
            ret.context = ILowLevelDebugger::Context::empty();
            ret.errorCode = errno;
            ret.errorMessage = "Failed to step process";
            ret.instructionCount = i;
            return ret;
        }
        status = waitpid(_process_info.pid, nullptr, 0);
        if (status == -1) {
            StepFailure ret;
            ret.success = false;
            ret.processInfo = _process_info.clone();
            ret.context = ILowLevelDebugger::Context::empty();
            ret.errorCode = errno;
            ret.errorMessage = "Failed to wait for process";
            ret.instructionCount = i;
            return ret;
        }
        if (WIFEXITED(status)) {
            StepFailure ret;
            ret.success = false;
            ret.processInfo = _process_info.clone();
            ret.context = ILowLevelDebugger::Context::empty();
            ret.errorMessage = "Process exited";
            ret.instructionCount = i;
            ret.errorCode = WEXITSTATUS(status);
            return ret;
        }
        if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            if (sig == SIGTRAP) {
                // SIGTRAP means SINGLESTEP
                stepSize--;
            }
            else {
                StepFailure ret;
                ret.success = false;
                ret.processInfo = _process_info.clone();
                ret.context = ILowLevelDebugger::Context::empty();
                ret.errorMessage = "Process stopped by signal";
                ret.instructionCount = i;
                ret.errorCode = sig;
                ret.signal = sig;
                return ret;
            }
        }
    }
    StepSuccess ret;
    ret.success = true;
    ret.processInfo = _process_info.clone();
    ret.context = ILowLevelDebugger::Context::empty();
    ret.instructionCount = i;
    return ret;
}

void PtraceWrapper::attach(pid_t pid)
{
    ILowLevelDebugger::attach(pid);
    if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) == -1) {
        ILowLevelDebugger::detach();
        throw std::runtime_error("Failed to attach to process");
    }
    _process_info.pid = pid;
}

void PtraceWrapper::detach()
{
    ILowLevelDebugger::detach();
    ptrace(PTRACE_DETACH, _process_info.pid, nullptr, nullptr);
}

std::vector<std::uint8_t> PtraceWrapper::readMemory(std::uintptr_t addr, size_t size) const
{
    std::vector<std::uint8_t> data(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = ptrace(PTRACE_PEEKDATA, _process_info.pid, addr + i, nullptr);
        if (errno) {
            throw std::runtime_error("Failed to read memory at address " + std::to_string(addr + i));
        }
    }
    return data;
}

bool PtraceWrapper::writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data)
{
    for (size_t i = 0; i < data.size(); ++i) {
        if (ptrace(PTRACE_POKEDATA, _process_info.pid, addr + i, data[i]) != 0) {
            return false;
        }
    }
    return true;
}

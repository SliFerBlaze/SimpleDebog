#include "PtraceWrapper.hh"
#include <signal.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <wait.h>

PtraceWrapper::PtraceWrapper() {}
PtraceWrapper::~PtraceWrapper() {}

ILowLevelDebugger::StepResult PtraceWrapper::step(unsigned int stepSize)
{
    StepResult result{};
    result.success = true;

    ProcessInfo info{};
    info.pid = _pid;
    info.isRunning = true;

    unsigned int instructionCount = 0;
    for (; instructionCount < stepSize; instructionCount++) {
        if (ptrace(PTRACE_SINGLESTEP, _pid, nullptr, nullptr) == -1) {
            StepFailure fail{};
            fail.success = false;
            fail.errorCode = static_cast<unsigned int>(errno);
            fail.errorMessage = "PTRACE_SINGLESTEP failed";
            fail.instructionCount = instructionCount;
            fail.processInfo = info;
            return fail;
        }

        int status = 0;

        if (waitpid(_pid, &status, 0) == -1) {
            StepFailure fail{};
            fail.success = false;
            fail.errorCode = static_cast<unsigned int>(errno);
            fail.errorMessage = "waitpid failed";
            fail.instructionCount = instructionCount;
            fail.processInfo = info;
            return fail;
        }

        if (WIFEXITED(status)) {
            StepSuccess done{};
            done.success = true;

            info.isRunning = false;
            info.exitCode = WEXITSTATUS(status);

            done.processInfo = info;

            done.instructionCount = instructionCount + 1;

            return done;
        }

        if (WIFSIGNALED(status)) {
            StepFailure fail{};
            fail.success = false;
            fail.signal = WTERMSIG(status);
            fail.errorCode = 0;
            fail.errorMessage = "Process terminated by signal";
            info.isRunning = false;
            fail.processInfo = info;
            fail.instructionCount = instructionCount;
            return fail;
        }

        if (!WIFSTOPPED(status)) {
            StepFailure fail{};
            fail.success = false;
            fail.errorCode = 0;
            fail.errorMessage = "Unexpected wait status";
            fail.processInfo = info;
            fail.instructionCount = instructionCount;
            return fail;
        }

        int sig = WSTOPSIG(status);

        if (sig != SIGTRAP) {
            StepFailure fail{};
            fail.success = false;
            fail.signal = sig;
            fail.errorCode = 0;
            fail.errorMessage = "Stopped by non-SIGTRAP signal";
            fail.processInfo = info;
            fail.instructionCount = instructionCount;
            return fail;
        }

        ++info.instructionCount;
    }

    result.instructionCount = instructionCount;
    result.processInfo = info;
    return result;
}

void PtraceWrapper::attach(pid_t pid)
{
    ILowLevelDebugger::attach(pid);
}

void PtraceWrapper::attach(std::string path, std::vector<std::string> argv)
{
    pid_t processPid = fork();

    if (processPid == -1)
        throw std::runtime_error("fork failed");

    if (processPid == 0) {
        // Create argument array
        std::vector<char *> args;
        args.push_back(const_cast<char *>(path.c_str()));
        for (const auto &arg : argv) {
            args.push_back(const_cast<char *>(arg.c_str()));
        }
        args.push_back(nullptr);

        // Child process
        if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) == -1) {
            perror("ptrace(PTRACE_TRACEME) failed");
            exit(1);
            // function that will simulate the attached process void()
        }

        // Exec the target program
        if (execve(path.c_str(), args.data(), environ) == -1) {
            perror("execve failed");
            exit(1);
        }
    }

    int status;

    if (waitpid(processPid, &status, 0) == -1) {
        throw std::runtime_error("waitpid failed");
    }

    if (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP) {
        throw std::runtime_error("Child did not stop as expected");
    }

    ILowLevelDebugger::attach(processPid);
}

void PtraceWrapper::detach()
{
    if (_pid <= 0) {
        return;
    }

    kill(_pid, SIGSTOP);
    waitpid(_pid, nullptr, 0);

    ptrace(PTRACE_DETACH, _pid, nullptr, nullptr);

    ILowLevelDebugger::detach();
    _pid = 0;
}

int PtraceWrapper::resume()
{
    errno = 0;
    long result = ptrace(PTRACE_CONT, _pid, nullptr, nullptr);
    return result == -1 ? -errno : 0;
}

std::vector<std::uint8_t> PtraceWrapper::readMemory(std::uintptr_t addr, size_t size) const
{
    (void)addr;
    (void)size;
    throw std::runtime_error("PtraceWrapper::readMemory not implemented");
}

bool PtraceWrapper::writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data)
{

    (void)addr;
    (void)data;
    throw std::runtime_error("PtraceWrapper::writeMemory not implemented");
}
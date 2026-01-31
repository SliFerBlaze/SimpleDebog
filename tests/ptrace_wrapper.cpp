#include "backend/platform/linux/PtraceWrapper.hh"
#include <cstdlib>
#include <fcntl.h>
#include <functional>
#include <gtest/gtest.h>
#include <signal.h>
#include <stdexcept>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

class PtraceWrapperMock : public PtraceWrapper
{
  public:
    PtraceWrapperMock() : PtraceWrapper() {};
    ~PtraceWrapperMock() = default;

    void attachWithSimulatedProcess(std::function<void(void *)> simulateProcess, void *arg)
    {
        pid_t processPid = fork();
        if (processPid == -1)
            throw std::runtime_error("fork failed");
        if (processPid == 0) {
            // tace me to attach
            if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) == -1) {
                perror("ptrace(PTRACE_TRACEME)");
                exit(1);
            }
            // Simulate execve-stop
            raise(SIGTRAP);

            simulateProcess(arg);
            _exit(1);
        }
        int status;

        if (waitpid(processPid, &status, WUNTRACED) == -1)
            throw std::runtime_error("waitpid failed");

        if (!WIFSTOPPED(status))
            throw std::runtime_error("Child did not stop as expected");

        ILowLevelDebugger::attach(processPid);
    }
};

TEST(PtraceWrapperTest, AttachDetachProcess)
{
    PtraceWrapperMock dbg = PtraceWrapperMock();
    EXPECT_NO_THROW(dbg.attachWithSimulatedProcess([](void *arg) {
        (void)arg;
    },
                                                   nullptr));

    EXPECT_NO_THROW(dbg.detach());
}

TEST(PtraceWrapperTest, ContinueProcess)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
        throw std::runtime_error("pipe failed");

    PtraceWrapperMock dbg = PtraceWrapperMock();
    dbg.attachWithSimulatedProcess([](void *arg) {
        int *pipefdlocal = reinterpret_cast<int *>(arg);

        close(pipefdlocal[0]);
        ssize_t written = write(pipefdlocal[1], "1234", 5);
        EXPECT_EQ(written, 5);
        close(pipefdlocal[1]);
    },
                                   reinterpret_cast<void *>(pipefd));

    int fdOut = pipefd[0];

    // Make the pipe non-blocking
    int flags = fcntl(fdOut, F_GETFL, 0);
    if (flags == -1 || fcntl(fdOut, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("fcntl failed");
    }

    char buffer[10];

    usleep(100000);
    ssize_t readed = read(fdOut, buffer, 10);
    EXPECT_EQ(readed, -1);
    EXPECT_EQ(errno, EAGAIN); // Explicitly check non-blocking behavior

    // Resume and let child proceed
    EXPECT_NO_THROW(dbg.resume());

    // Make the pipe blocking again for the actual read
    flags = fcntl(fdOut, F_GETFL, 0);
    if (flags != -1) {
        fcntl(fdOut, F_SETFL, flags & ~O_NONBLOCK);
    }

    readed = read(fdOut, buffer, 10);
    EXPECT_EQ(readed, 5);
    EXPECT_STREQ(buffer, "1234");

    EXPECT_NO_THROW(dbg.detach());
    close(fdOut);
}

TEST(PtraceWrapperTest, StepExecutesExactlyOneInstruction)
{
    PtraceWrapperMock dbg;

    dbg.attachWithSimulatedProcess([](void *) {
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        _exit(0);
    },
                                   nullptr);

    ILowLevelDebugger::StepResult r1 = dbg.step(1);
    EXPECT_TRUE(r1.success);
    EXPECT_TRUE(r1.processInfo.isRunning);

    ILowLevelDebugger::StepResult r2 = dbg.step(1);
    EXPECT_TRUE(r2.success);
    EXPECT_TRUE(r2.processInfo.isRunning);

    ILowLevelDebugger::StepResult r3 = dbg.step(1);
    EXPECT_TRUE(r3.success);
    EXPECT_TRUE(r3.processInfo.isRunning);

    dbg.detach();
}

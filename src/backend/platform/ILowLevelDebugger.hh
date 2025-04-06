#pragma once

#include <sys/types.h> // For pid_t

#ifdef _WIN32
typedef int pid_t;
#endif

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/*
This interface is designed to be implemented by a low-level debugger class.
It provides methods for attaching to a process, detaching from it, and stepping through its execution.
The interface is implementing the RAII pattern, which means that it will automatically manage the call to detach() when the last copy of the object is destroyed.
This includes detaching from the process when the object is destroyed.
*/
class ILowLevelDebugger {
  public:
    // Context information about the process being debugged.
    // This could include registers, memory state, or other relevant information.

    // TODO: Define the structure of the context object.
    // This could include registers, memory state, or other relevant information.
    struct Context {
        // This function creates an empty context object.
        static Context empty();
    };

    struct ProcessInfo {
      public:
        // Process ID of the target process
        pid_t pid;

      private:
        // Counter for the number of instructions executed
        // It is initialized to `0` and increments with each instruction executed.
        struct Counter {
            unsigned int _value;
            Counter() : _value(0) {}
            Counter &operator++();
            Counter operator++(int);
            void increment();
            unsigned int value() const;
        };

      public:
        // Number of instructions executed since attachment
        // Starts at `0`
        Counter instructionCount = Counter();

        // Indicates if the process is currently running
        // Defaults to `true` assuming the process is running when attached
        bool isRunning = true;

        // Exit code of the process if it has terminated
        // Defaults to `0` indicating no exit code available or clean exit. Check the `isRunning` flag first.
        int exitCode = 0;
    };

    struct StepResult {
        // Information about the process after stepping
        ProcessInfo processInfo;

        // Number of instructions successfully executed during the step before failure
        // This could be less than the requested step size if an error occurred
        // Defaults to `0` if the step operation was not attempted or failed immediately
        unsigned int instructionCount = 0;

        // Indicates if the step operation was successful
        // If `true` this should be casted to `StepSuccess` to access additional information
        // If `false`, this should be casted to `StepFailure` to access additional information
        bool success;

        // Context information about the step operation (if applicable)
        // This could include details about the state of the process or the environment at the time of stepping
        // Defaults to `""`
        ILowLevelDebugger::Context context = ILowLevelDebugger::Context::empty();
    };

    // StepResult subclasses to represent success case
    struct StepSuccess : StepResult {};

    // StepResult subclasses to represent failure case
    struct StepFailure : StepResult {
        // Signal that caused the failure (if applicable)
        // Defaults to `0`
        unsigned int signal = 0;

        // Error code indicating the reason for failure
        // `0` indicates the process exited correctly before reaching the wanted step count
        unsigned int errorCode;

        // Error message providing more details about the failure (if applicable)
        // Defaults to `""`
        std::string errorMessage = "";
    };

    /*
    Method to step through the execution of the process being debugged.
    This method should be implemented to perform the actual stepping operation.
    The implementation should handle the low-level details (e.g. system calls).
    @param stepSize The number of steps to take. Default is 1, meaning a single step.
    This allows for flexibility in stepping through the process, such as stepping over multiple instructions or functions if needed.
    @return A StepResult object containing information about the step operation.
    */
    virtual StepResult step(unsigned int stepSize = 1) = 0;

    /*
    Method to attach to a process for debugging.
    This method should be implemented to perform the actual attachment operation.
    This should call ILowLevelDebugger::attach(pid) at the start of the method.
    @param pid The process ID of the target process that is to be attached.
    */
    virtual void attach(pid_t pid);

    /*
    Method to detach from the process being debugged.
    This should call ILowLevelDebugger::detach() at the start of the method.
    This method should be implemented to perform the actual detachment operation.
    */
    virtual void detach();

    /*
    Method to read memory from the target process.
    WARNING: This method might not be safe and should be used with caution.
    @param addr The address in the target process's memory to read from.
    @param size The number of bytes to read.
    @return A vector of bytes read from the target process's memory.
    */
    virtual std::vector<std::uint8_t> readMemory(std::uintptr_t addr, size_t size) const = 0;

    /*
    Method to read memory from the target process and cast it to a specific type.
    WARNING: This method is not safe and should be used with caution.
    @param addr The address in the target process's memory to read from.
    @return An object read from the target process's memory.
    */
    template <typename T>
    T readMemoryWithCast(std::uintptr_t addr) const;

    /*
    Method to write memory to the target process.
    WARNING: This method might not be safe and should be used with caution.
    @param addr The address in the target process's memory to write to.
    @param data A vector of bytes to write to the target process's memory.
    @return A boolean indicating success or failure of the write operation.
    */
    virtual bool writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data) = 0;

    /*
    Method to write memory to the target process from a cast of a specific type.
    WARNING: This method is not safe and should be used with caution.
    @param addr The address in the target process's memory to write to.
    @param data An object to write to the target process's memory.
    @return A boolean indicating success or failure of the write operation.
    */
    template <typename T>
    bool writeMemory(std::uintptr_t addr, const T &data);

    ILowLevelDebugger() = default;
    ILowLevelDebugger(ILowLevelDebugger const &other);
    ILowLevelDebugger(ILowLevelDebugger &other);
    virtual ~ILowLevelDebugger();

  private:
    // Process ID of the target process
    pid_t _pid = 0;

    // Map of process IDs to number of debugger instances using them
    static std::map<pid_t, unsigned int> _processes;
};

#include "ILowLevelDebugger.inl"

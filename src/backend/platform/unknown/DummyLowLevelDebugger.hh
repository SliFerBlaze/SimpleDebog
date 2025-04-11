#pragma once

#include "../ILowLevelDebugger.hh"

class DummyLowLevelDebugger : public ILowLevelDebugger
{
    public:
        DummyLowLevelDebugger() = default;
        DummyLowLevelDebugger(DummyLowLevelDebugger const &other) = default;
        DummyLowLevelDebugger(DummyLowLevelDebugger &other) = default;
        ~DummyLowLevelDebugger() override = default;

        StepResult step(unsigned int stepSize = 1) override;
        void attach(pid_t pid) override;
        void detach() override;
        std::vector<std::uint8_t> readMemory(std::uintptr_t addr, size_t size) const override;
        bool writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data) override;

        /// @brief Set the maximum number of instructions to simulate.
        /// @param amount The maximum number of instructions.
        void setMaxInstructions(uint8_t amount);

        /// @brief Simulate the process of stopping the execution.
        /// This method sets the processInfo.isRunning flag to false, simulating a stop in the process.
        /// @param signal The signal that caused the stop (default is 0).
        void simulateSignal(int signal = 0);

        /// @brief Simulate the process of exiting with a specific exit code.
        /// This method sets the processInfo.isRunning flag to false and sets the exit code.
        /// @param exitCode The exit code to simulate (default is 0).
        /// @note This simulates a clean exit of the process.
        void simulateExit(int exitCode = 0);

    protected:
        ProcessInfo processInfo;

    private:
        uint8_t AMOUNT_OF_INSTRUCTIONS = 1000;
        static std::map<std::uintptr_t, std::uint8_t> _address;
};

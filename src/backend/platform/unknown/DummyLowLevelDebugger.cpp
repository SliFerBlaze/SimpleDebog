#include "DummyLowLevelDebugger.hh"

std::map<std::uintptr_t, std::uint8_t> DummyLowLevelDebugger::_address = std::map<std::uintptr_t, std::uint8_t>();

ILowLevelDebugger::StepResult DummyLowLevelDebugger::step(unsigned int stepSize)
{
    for (unsigned int i = 0; i < stepSize && this->processInfo.isRunning; ++i) {
        this->processInfo.instructionCount.increment();
        if (this->processInfo.instructionCount.value() >= this->AMOUNT_OF_INSTRUCTIONS) {
            this->processInfo.isRunning = false;
            this->processInfo.exitCode = 0;
            StepFailure result;
            result.instructionCount = i + 1;
            result.processInfo = this->processInfo;
            result.errorCode = 0;
            result.errorMessage = "Reached maximum instruction limit.";
            return result;
        }
    }
    if (!this->processInfo.isRunning) {
        StepFailure result;
        result.instructionCount = stepSize;
        result.processInfo = this->processInfo;
        result.errorCode = this->processInfo.exitCode;
        result.signal = this->processInfo.exitCode > 128 ? this->processInfo.exitCode - 128 : 0;
        result.errorMessage = "Process exited before reaching the wanted step count.";
        return result;
    }
    StepSuccess result;
    result.instructionCount = stepSize;
    result.processInfo = this->processInfo;
    return result;
}

void DummyLowLevelDebugger::attach(pid_t pid)
{
    if (pid <= 0) {
        throw std::invalid_argument("Invalid process ID.");
    }
    this->processInfo.pid = pid;
    this->processInfo.isRunning = true;
}

void DummyLowLevelDebugger::detach()
{
    if (this->processInfo.pid <= 0) {
        throw std::runtime_error("No process attached.");
    }
    this->processInfo.isRunning = false;
    this->processInfo.pid = 0;
}

std::vector<std::uint8_t> DummyLowLevelDebugger::readMemory(std::uintptr_t addr, size_t size) const
{
    if (addr == 0 || size == 0) {
        throw std::invalid_argument("Invalid address or size.");
    }
    std::vector<std::uint8_t> data(size, 0);
    for (size_t i = 0; i < size; ++i) {
        try {
            // Simulate reading memory by accessing the static map
            data[i] = DummyLowLevelDebugger::_address.at(addr + i);
        } catch (const std::out_of_range &) {
            // Simulate reading memory by filling with address value when not found
            data[i] = static_cast<std::uint8_t>(addr + i);
        }
    }
    return data;
}

bool DummyLowLevelDebugger::writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data)
{
    if (addr == 0 || data.empty()) {
        throw std::invalid_argument("Invalid address or data.");
    }
    for (size_t i = 0; i < data.size(); ++i) {
        // Simulate writing memory by storing the data in the static map
        DummyLowLevelDebugger::_address[addr + i] = data[i];
    }
    return true;
}

void DummyLowLevelDebugger::setMaxInstructions(uint8_t amount)
{
    if (amount < 0) {
        throw std::invalid_argument("Invalid instruction limit.");
    }
    this->AMOUNT_OF_INSTRUCTIONS = amount;
}

void DummyLowLevelDebugger::simulateSignal(int signal)
{
    simulateExit(signal + 128);
}

void DummyLowLevelDebugger::simulateExit(int exitCode)
{
    this->processInfo.isRunning = false;
    this->processInfo.exitCode = exitCode;
}

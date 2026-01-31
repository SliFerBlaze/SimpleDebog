#pragma once

#include "../ILowLevelDebugger.hh"
#include <string>

class PtraceWrapper : public ILowLevelDebugger
{
  public:
    PtraceWrapper();
    ~PtraceWrapper();

    StepResult step(unsigned int stepSize = 1) noexcept override;
    void attach(pid_t pid) override;
    void attach(std::string path, std::vector<std::string> argv);

    void detach() override;
    int resume() override;

    std::vector<std::uint8_t> readMemory(std::uintptr_t addr, size_t size) const override;
    bool writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data) override;
    bool isAddressValid(std::uintptr_t addr) const noexcept override;
};

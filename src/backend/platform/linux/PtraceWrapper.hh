#pragma once

#include "../ILowLevelDebugger.hh"

class PtraceWrapper : public ILowLevelDebugger
{
  private:
    ProcessInfo _process_info;

  public:
    PtraceWrapper();
    ~PtraceWrapper();
    StepResult step(unsigned int stepSize = 1) noexcept override;
    void attach(pid_t pid) override;
    void detach() override;
    std::vector<std::uint8_t> readMemory(std::uintptr_t addr, size_t size) const override;
    bool writeMemory(std::uintptr_t addr, const std::vector<std::uint8_t> &data) override;
};

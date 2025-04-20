#include <cstring>
#include "ILowLevelDebugger.hh"

template<typename T>
T ILowLevelDebugger::readMemoryWithCast(std::uintptr_t addr) const
{
    std::vector<std::uint8_t> data = readMemory(addr, sizeof(T));
    T castedData;
    std::memcpy(&castedData, data.data(), sizeof(T));
    return castedData;
};

template <typename T>
bool ILowLevelDebugger::writeMemory(std::uintptr_t addr, const T &data)
{
    std::vector<std::uint8_t> byteData(sizeof(T));
    std::memcpy(byteData.data(), &data, sizeof(T));
    return writeMemory(addr, byteData);
};

#pragma once
#include "Decoder.hpp"
#include "DecoderFactory.hpp"

class PointerDecoder : public Decoder
{
  public:
    DecodedValue decode(pid_t, uintptr_t value) const override
    {
        return value;
    }

  private:
    static inline const bool registered = [] {
        DecoderFactory::getInstance().registerDecoder(VOID_P, [] { return std::make_unique<PointerDecoder>(); });
        return true;
    }();
};

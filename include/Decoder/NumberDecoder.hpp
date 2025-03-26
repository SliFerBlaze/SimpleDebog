#pragma once
#include "Decoder.hpp"
#include "DecoderFactory.hpp"

class NumberDecoder : public Decoder
{
public:
    DecodedValue decode(pid_t, uintptr_t value) const override
    {
        return static_cast<int>(value);
    }

private:
    static inline const bool registered = []
    {
        DecoderFactory::getInstance().registerDecoder(NUM, []
                                                      { return std::make_unique<NumberDecoder>(); });
        return true;
    }();
};

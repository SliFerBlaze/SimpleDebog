#pragma once
#include "Decoder.hpp"
#include "DecoderFactory.hpp"
#include <sys/ptrace.h>
#include <cstring>
#include <errno.h>

class StringDecoder : public Decoder
{
public:
    DecodedValue decode(pid_t pid, uintptr_t value) const override
    {
        if (value == 0)
            return std::string("NULL");

        char buffer[256] = {};
        size_t i = 0;
        long word;

        while (i < sizeof(buffer) - sizeof(long))
        {
            errno = 0;
            word = ptrace(PTRACE_PEEKDATA, pid, value + i, nullptr);
            if (errno != 0)
                break;

            std::memcpy(buffer + i, &word, sizeof(word));
            if (std::strchr(buffer, '\0'))
                break;
            i += sizeof(long);
        }

        return std::string(buffer);
    }

private:
    static inline const bool registered = []
    {
        DecoderFactory::getInstance().registerDecoder(STRING, []
                                                      { return std::make_unique<StringDecoder>(); });
        return true;
    }();
};

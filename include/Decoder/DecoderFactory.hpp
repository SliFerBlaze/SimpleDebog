#pragma once
#include "../PlatformDefines.hpp"
#include <map>
#include <memory>
#include <functional>
#include "Decoder.hpp"
#include <iostream>

#ifndef SYS_futex
#define SYS_futex 202
#endif

class DecoderFactory
{
public:
    using Creator = std::function<std::unique_ptr<Decoder>()>;

    static DecoderFactory &getInstance()
    {
        static DecoderFactory instance;
        return instance;
    }

    void registerDecoder(int type, Creator creator)
    {
        std::cout << "[DecoderFactory] Registering type " << type << "\n";
        decoders[type] = std::move(creator);
    }

    std::unique_ptr<Decoder> createDecoder(int type) const
    {
        auto it = decoders.find(type);
        if (it != decoders.end())
        {
            return it->second();
        }
        return nullptr;
    }

private:
    std::map<int, Creator> decoders;

    DecoderFactory() = default;
    ~DecoderFactory() = default;
};

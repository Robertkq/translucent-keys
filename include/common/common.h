#pragma once

#include <cstdint>

enum class messageType : uint8_t
{
    targetConnected,
    targetDisconnected,
    clientConnected,
    clientDisconnected,
    targetTyped
};

inline uint64_t validation_function(uint64_t input)
{
    auto out = input ^ 0x5A9B6C2F0F011;
    out = (out & 0xF0F0F0F0F0F0F0) >> 4;
    return out;
}
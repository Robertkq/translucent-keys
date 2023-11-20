#pragma once

#include <iostream>
#include "kqnet.h"
#include "common.h"

class Client : public kq::client_interface<messageType>
{
public:
    Client(uint64_t(*scrambleFunc)(uint64_t));
private:

};
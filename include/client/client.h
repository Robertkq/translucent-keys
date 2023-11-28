#pragma once

#include <iostream>
#include <thread>
#include "kqnet.h"
#include "kqlog.h"
#include "common.h"

class Client : public kq::client_interface<messageType>
{
public:
    Client(uint64_t(*scrambleFunc)(uint64_t));
    ~Client();

    void networkInitAndLoop();
private:
    kq::logger<kq::default_symbols> logger;
    std::thread networkingThread;
    bool networkLoop;

};
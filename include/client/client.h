#pragma once

#include <iostream>
#include <thread>
#include "kqnet.h"
#include "kqlog.h"
#include "clientUI.h"
#include "common.h"

class client : public kq::client_interface<messageType>
{
public:
    client(uint64_t(*scrambleFunc)(uint64_t));
    ~client();

    bool isUIRunning() const { return ui->isRunning(); }
    void run()
    {
        ui->run();
    }

    void networkInitAndLoop();
private:
    kq::logger<kq::default_symbols> logger;
    std::thread networkingThread;
    bool networkLoop;

    clientUI* ui;

};
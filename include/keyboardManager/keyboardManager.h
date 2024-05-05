#pragma once

#include "common.h"
#include <Windows.h>
#include <array>


enum class toggleKeys : uint8_t {
    caps,
    scrollLock,
    numLock,

    toggleKeysCount // keep last in this enum
};

class keyboardManager {
  public:
    keyboardManager();
    ~keyboardManager();

    void handleKeyPress(DWORD virtualKeyCode, keyStatus status);
    void handleKeyToggle(DWORD virtualKeyCode, keyStatus status);

    keyStatus getKey(DWORD virtualKeyCode);

  private:
    toggleKeys toggleConvert(DWORD virtualKeyCode);

  private:
    std::array<keyStatus, 256> keys;
    std::array<keyStatus, static_cast<uint8_t>(toggleKeys::toggleKeysCount)>
        toggles;
};
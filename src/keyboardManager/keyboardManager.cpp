#include "keyboardManager.h"

keyboardManager::keyboardManager() : keys(), toggles() {}

keyboardManager::~keyboardManager() {}

void keyboardManager::handleKeyPress(DWORD virtualKeyCode, keyStatus status) {
    keys[virtualKeyCode] = status;
}

void keyboardManager::handleKeyToggle(DWORD virtualKeyCode, keyStatus status) {
    toggleKeys key = toggleConvert(virtualKeyCode);
    toggles[static_cast<uint8_t>(key)] = status;
}

keyStatus keyboardManager::getKey(DWORD virtualKeyCode) {
    return keys[virtualKeyCode];
}

toggleKeys keyboardManager::toggleConvert(DWORD virtualKeyCode) {
    switch (virtualKeyCode) {
    case VK_CAPITAL:
        return toggleKeys::caps;
    case VK_NUMLOCK:
        return toggleKeys::numLock;
    case VK_SCROLL:
        return toggleKeys::scrollLock;
    default:
        return toggleKeys::toggleKeysCount;
    }
}
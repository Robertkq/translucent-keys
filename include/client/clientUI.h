#pragma once

#include <vector>
#include <thread>
#include "imgui_init.h"
#include "keyboardUI.h"

class clientUI
{
public:
	clientUI();
	~clientUI();
	
	void run();

    inline bool isInitialized() const { return initialized == true; }

private:
    void loopUI();

private:
    bool initialized;
    std::thread threadUI;
	std::vector<keyboardUI*> keyUIs;
private: // bloat stuff
    WNDCLASSEXW wc;
    HWND hwnd;

};
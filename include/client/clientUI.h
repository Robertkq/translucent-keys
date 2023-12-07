#pragma once

#include <vector>
#include <thread>
#include "imgui_init.h"
#include "keyboardUI.h"

constexpr uint32_t windowWidth = 1920;
constexpr uint32_t windowHeight = 1080;

class clientUI
{
public:
	clientUI();
	~clientUI();
	
	void run();

    bool isInitialized() const { return initialized == true; }
    bool isRunning() const { return done == true; }

private:
    void initUI();
    void loopUI();
    void cleanUI();
    void initLoopClean();

private:
    bool initialized;
    bool done;
	std::vector<keyboardUI*> keyUIs;
private: // bloat stuff
    WNDCLASSEXW wc;
    HWND hwnd;

};
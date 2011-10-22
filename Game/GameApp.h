#pragma once

#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "FontSystem.h"
#include "InputSystem.h"
#include "InputComponent.h"
#include "Window.h"

using std::string;

class GameApp
{
public:
	GameApp(string title, int windowWidth, int windowHeight);
    virtual ~GameApp();

    void init(HINSTANCE hInstance, int nCmdShow);
    virtual void init(GameEngine &gameEngine) = 0;
    virtual void update(time_t time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;

    void start();
    string getTitle();

    static long WindowDestroyHandler(Window &window, HWND hwnd, long wparam, long lparam);

private:
    void initWindow(HINSTANCE hInstance, int nCmdShow);
    void initInputSystem();

    string title; // this should be the title of the window, but isn't right now.
    int windowHeight;
    int windowWidth;

    Window window;
    InputSystem inputSystem;
    GraphicsEngine graphicsEngine;
    GameEngine gameEngine;
};
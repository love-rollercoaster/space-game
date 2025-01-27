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
#include "KeyboardInputHandler.h"

using std::string;

class GameApp
    : public KeyboardInputHandler
{
public:
    static long WindowDestroyHandler(Window &window, HWND hwnd, long wparam, long lparam);

	GameApp(string title, int windowWidth, int windowHeight);
    virtual ~GameApp();

    void init(HINSTANCE hInstance, int nCmdShow);
    
    virtual void init(GameEngine &gameEngine) = 0;
    virtual void update(float time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;
    virtual void quitGame();

    void start();
    string getTitle();

    virtual void handleEscapeKey(unsigned char key);
    virtual void registerKeyboardInputCallbacks();

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
#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#include "Win32Console.h"
#include "FontSystem.h"
#include "InputSystem.h"
#include "InputComponent.h"
#include "GameEngine.h"
#include "FlightSimulatorGameApp.h"
#include "Window.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

void SeedRandom();

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

long WindowDestroyHandler(Window &window, HWND hwnd, long wparam, long lparam) 
{
    ::PostQuitMessage(0);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Win32Console console;
    console.setScrollbackBufferSize(10000);
    console.show();

    SeedRandom();

    FlightSimulatorGameApp testGameApp;

    Window window;
    window.init(hInstance, testGameApp.getTitle(), WINDOW_WIDTH, WINDOW_HEIGHT);
    Window::RegisterMessageHandler(WM_DESTROY, WindowDestroyHandler);
    Window::ShowWindow(nCmdShow);

    InputSystem::StaticInit();
    InputSystem inputSystem;
    inputSystem.init();

    GraphicsEngine graphicsEngine;
    graphicsEngine.initializeD3D(window, false);

	FontSystem::Init(graphicsEngine);

    GameEngine gameEngine(testGameApp, graphicsEngine);

    testGameApp.init(gameEngine);

    gameEngine.startGameLoop();

	FontSystem::Cleanup();
}


void SeedRandom() 
{
    srand((unsigned)time(static_cast<time_t>(NULL)));
}

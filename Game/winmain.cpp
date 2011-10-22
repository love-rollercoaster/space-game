#include <windows.h>

#include "Win32Console.h"
#include "FlightSimulatorGameApp.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

void seedRandom();
void enableConsole();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    seedRandom();
    enableConsole();

    GameApp *gameApp = new FlightSimulatorGameApp();
    gameApp->init(hInstance, nCmdShow);
    gameApp->start();

    delete gameApp;
}


void enableConsole()
{
    Win32Console console;
    console.setScrollbackBufferSize(10000);
    console.show();
}


void seedRandom() 
{
    srand((unsigned)time(static_cast<time_t>(NULL)));
}

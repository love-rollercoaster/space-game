#if 1
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#include "GameEngine.h"
#include "TestGameApp.h"
#include "Window.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

void RedirectIOToConsole();
void seedRandom();

#define WINDOW_WIDTH 800   // these will change
#define WINDOW_HEIGHT 600

long WindowDestroyHandler(Window &window, HWND hwnd, long wparam, long lparam) 
{
    ::PostQuitMessage(0);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    #ifdef _DEBUG
        RedirectIOToConsole();
    #endif
    seedRandom();

    TestGameApp testGameApp;

    Window window;
    window.Initialize(hInstance, testGameApp.getTitle(), WINDOW_WIDTH, WINDOW_HEIGHT);
    window.RegisterMessageHandler(WM_DESTROY, WindowDestroyHandler);
    window.ShowWindow(nCmdShow);

    GraphicsEngine graphicsEngine;
    graphicsEngine.initializeD3D(window, false);
    GameEngine gameEngine(testGameApp, graphicsEngine);

    testGameApp.init(gameEngine);

    gameEngine.startGameLoop();
}



void RedirectIOToConsole(){
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;
    int hConHandle;
    long lStdHandle;

    // allocate a console for this app
    AllocConsole();

    // Disable its X button
    HWND console = GetConsoleWindow();
    EnableMenuItem ( GetSystemMenu ( console, FALSE),
        SC_CLOSE,
        MF_BYCOMMAND | MF_GRAYED );

    // And the close x in the right click menu as well
    EnableMenuItem ( GetSystemMenu ( console, FALSE),
        SC_CLOSE,
        MF_BYCOMMAND | MF_GRAYED );
    RemoveMenu     ( GetSystemMenu ( console, FALSE),
        SC_CLOSE,
        MF_BYCOMMAND );


    // Set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
        &coninfo);
    coninfo.dwSize.Y = 1000;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), 
        coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
    // point to console as well
    std::ios::sync_with_stdio();
}

BOOL WINAPI MyConsoleHandler(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_C_EVENT:
        PostQuitMessage(0);
        return TRUE;    //this just disables Ctrl-C
    case CTRL_CLOSE_EVENT:
        PostQuitMessage(0);
        return TRUE;    
    default:
        return FALSE;
    }
}

void seedRandom() {
    srand((unsigned)time(static_cast<time_t>(NULL)));
}
#endif
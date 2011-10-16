#include "Win32Console.h"
#include <io.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <stdio.h>


Win32Console::Win32Console(void)
{
}

Win32Console::~Win32Console(void)
{
}

void Win32Console::show()
{
    AllocConsole();
    disableXButton();
    disableXButtonInMenu();
    redirectStreams();
}

void Win32Console::redirectStreams()
{
    int hConHandle;
    long lStdHandle;
    FILE *fp;

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

    std::ios::sync_with_stdio();
}

void Win32Console::setScrollbackBufferSize( int size )
{
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = size;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
}

void Win32Console::disableXButton()
{
    HWND console = GetConsoleWindow();
    EnableMenuItem ( GetSystemMenu ( console, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED );
}

void Win32Console::disableXButtonInMenu()
{
    HWND console = GetConsoleWindow();
    EnableMenuItem ( GetSystemMenu ( console, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED );
    RemoveMenu     ( GetSystemMenu ( console, FALSE), SC_CLOSE, MF_BYCOMMAND );
}



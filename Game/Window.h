// This class is based on
// http://www.gamedev.net/page/resources/_/reference/programming/creating-a-win32-window-wrapper-class-r1810

#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>
#include <map>

using std::map;
using std::string;

class Window
{
public:
    
    typedef long (* MessageHandler)(Window&, HWND, long, long);

    Window(void);
    ~Window(void);

    static LRESULT CALLBACK MessageRouter(HWND, UINT, WPARAM, LPARAM);
    static HWND GetHWND();
    static void ShowWindow(int nCmdShow);
    static MessageHandler RegisterMessageHandler(long message, MessageHandler handler);

    void Initialize(HINSTANCE hInstance, string title, int width, int height);
    int getWidth();
    int getHeight();

private:
    typedef map<long, MessageHandler> MessageMap;
    typedef MessageMap::iterator MessageIterator;

    int width;
    int height;

    static HWND hwnd;
    static MessageMap MessageHandlers;

    static void SetHWND(HWND);

    static Window* RetrieveWindowInstanceFromWindowCreationData(HWND hwnd, LPARAM lparam);
    static void AssociateWindowInstanceFromWindowCreationData(HWND hwnd, Window *wnd);

};


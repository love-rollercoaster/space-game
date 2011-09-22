
#include <fcntl.h>
#include <fstream>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#include "Window.h"

// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void RedirectIOToConsole();
void seedRandom();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	#ifdef _DEBUG
		RedirectIOToConsole();
	#endif

	seedRandom();

	Window window("SpaceGame", hInstance, CS_HREDRAW | CS_VREDRAW, 500, 100);
	window.show();
	window.runMessageLoop();
}


#if 0
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_crtBreakAlloc = 17505; //for tracking down memory leaks

	// create a console window for us while in debug mode to show us all stderr messages 
	// (it will also have stdin and stdout)

	DWORD style;
	int x, y, width, height;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!FULLSCREEN)
		wc.hbrBackground = (HBRUSH) COLOR_WINDOW;    // only needed in windowed mode
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	// Window settins based on whether it's fullscreen or not
	if (FULLSCREEN == true){
		style = WS_EX_TOPMOST | WS_POPUP;
		x = 0;
		y = 0;
		width = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);
	} else {
		style = WS_CAPTION | WS_SYSMENU;

		//the position of the window. Try to make it so the window isn't going off the screen
		if (SCREEN_WIDTH + X_POS > GetSystemMetrics(SM_CXSCREEN))
			x = 0;
		else
			x = X_POS;

		if (SCREEN_HEIGHT + Y_POS > GetSystemMetrics(SM_CYSCREEN))
			y = 0;
		else
			y = Y_POS;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;
	}

	hWnd = CreateWindowEx(NULL,
		"WindowClass",
		"Sketchy Level Editor",
		style, // different values for a window or fullscreen, as seen above
		x, y,    // the starting x and y positions should be 0
		width, height,    // set the window to the desired width/height
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	// initialize the game engine
	try{
		engine = new GameEngine(hWnd, hInstance, FRAMERATE, FULLSCREEN, 4.0f/3.0f, SCREEN_WIDTH/10);

		//if the engine could not be initialized. throw was used just so it would reuse the code in the catch block
		//there are more throws in the code called from GameEngine's constructor
		if (engine == NULL){
			throw "Engine could not be created.";
		}
	} catch (char* error){
		//print any errors to standard error and show a dialog if there is a problem creating the engine
		std::string s(error);
		s += "\nPress OK to end the program.";

		MessageBox(hWnd, s.c_str() , "D3D Error", MB_OK | MB_ICONERROR);
		ERR(error);

		if (engine != NULL)
			delete engine;
		return 1;
	}

	game = new SketchyLE();
	if (game == NULL)
		return 3;

	game->playGame();

	//free the game
	if (game != NULL)
		delete game;

	//free the engine
	if (engine != NULL)
		delete engine;

#ifdef _DEBUG
	FreeConsole();
#endif

	//might want to change this at some point
	return 0;
}


// This is the main message handler for the program
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	case WM_ACTIVATEAPP:
		{
			// If we alt-tabbed out of full screen and came back, this gets called
			if (wParam && game)
				game->freeVolatileResources();
			if (wParam && engine != NULL)
				engine->resetDevice();
			if (wParam && game)
				game->initVolatileResources();
		} break;
	case WM_MOUSEMOVE:
		if (game != NULL)
		{
			//the mouse is moved with or without a button down
			D3DXVECTOR2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));



			if (wParam & MK_LBUTTON){
				//the left button is held down
				game->handleMouseDrag(MK_LBUTTON, pos);
			} else if (wParam & MK_RBUTTON){
				//the right button is held down
				game->handleMouseDrag(MK_RBUTTON, pos);
			} else {
				//neither right nor left is held
				game->handleMouseMoved(pos);
			}

		} break;
	case WM_LBUTTONDOWN:
		if (game != NULL)
		{
			//the left button is clicked
			D3DXVECTOR2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));

			game->handleMouseClick(MK_LBUTTON, pos);
		} break;
	case WM_LBUTTONUP:
		if (game != NULL)
		{
			//the left button is clicked
			D3DXVECTOR2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
			game->handleMouseReleased(MK_LBUTTON, pos);
		} break;
	case WM_RBUTTONDOWN:
		if (game != NULL)
		{
			//the right button is clicked
			D3DXVECTOR2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
			game->handleMouseClick(MK_RBUTTON, pos);
		} break;
	case WM_RBUTTONUP:
		if (game != NULL)
		{
			//the right button is clicked
			D3DXVECTOR2 pos((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
			game->handleMouseReleased(MK_RBUTTON, pos);
		}break;
	case WM_KEYDOWN:
		game->handleKeyPress(wParam); 
		break;

	}


	return DefWindowProc (hWnd, message, wParam, lParam);
}
#endif

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
#pragma once

#include <string>
#include <windows.h>
#include "graphicsengine.h"
// #include "inputhandler.h"

using std::string;

class GameApp
{
public:
	GameApp(string title);
	virtual ~GameApp(void) = 0;

private:
	// DisplaySystem displaySystem;
	GraphicsEngine *graphicsEngine;
	// InputHandler inputHandler;
};
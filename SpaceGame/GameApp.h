#pragma once

#include <string>
#include <Windows.h>

#include "GraphicsEngine.h"

using std::string;

class GameApp
{
public:
	GameApp(string title);

    virtual void update(time_t time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;
    // virtual void handleInput() = 0;

private:
    // MSG getMessage();
    string title;

};
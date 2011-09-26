#pragma once

#include <string>
#include <Windows.h>

using std::string;

class GameEngine;
class GraphicsEngine;

class GameApp
{
public:
	GameApp(string title)
        : title(title)
    {
    }

    virtual void init(GameEngine &gameEngine) = 0; // Passing in the game engine object is not so great.
                                                   // The problem is that I need the graphics engine in 
                                                   // order to initialize the graphic objects that have vertices.
                                                   // I need to redesign the window + game engine + gameapp 
                                                   // structure.
    virtual void update(time_t time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;

private:
    string title; // this should be the title of the window, but isn't right now.

};
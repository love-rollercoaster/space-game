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

    virtual void init(GameEngine &gameEngine) = 0;
    virtual void update(time_t time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;

    virtual string getTitle() {
        return title;
    }

private:
    string title; // this should be the title of the window, but isn't right now.

};
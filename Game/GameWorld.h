#pragma once

#include <list>
#include <time.h>
#include "GameEngine.h"
#include "GraphicsEngine.h"

class GameEngine;
class GraphicsEngine;

using std::list;

class GameWorld
{
public:
    virtual void init(GameEngine &gameEngine) = 0;
    virtual void update(time_t time) = 0;
    virtual void draw(GraphicsEngine &graphicsEngine) = 0;
};

#pragma once

#include "GameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "TestGraphicsComponent.h"
#include "GameObject.h"

class GameEngine;
class GraphicsEngine;

class TestGameWorld :
    public GameWorld
{
public:
    TestGameWorld(void);
    ~TestGameWorld(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    TestGraphicsComponent testGraphicsComponent; // Not good, these should be global almost.
    GameObject triangle;  // Not good, we probably would want to keep game objects between worlds.
};


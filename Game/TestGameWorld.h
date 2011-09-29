#pragma once

#include "GameWorld.h"
#include "GameEngine.h"
#include "GraphicsEngine.h"
#include "GameObject.h"


class TestGameWorld :
    public GameWorld
{
public:
    TestGameWorld(void);
    ~TestGameWorld(void);

    void init(GameEngine &gameEngine);
    // void init(GameEngine &gameEngine, list<GameObject*> gameObjects );
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);


};

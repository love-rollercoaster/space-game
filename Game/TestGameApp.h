#pragma once
#include "GameApp.h"
#include "TestGameWorld.h"

class TestGameApp : public GameApp
{
public:
    TestGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    TestGameWorld testGameWorld;
};


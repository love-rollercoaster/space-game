#pragma once

#include "GameApp.h"

class TestGameApp : public GameApp
{
public:
    TestGameApp(void);
    ~TestGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    void initComponents(GameEngine &gameEngine);
    void initGraphicsComponents(GraphicsEngine &graphicsEngine);
};


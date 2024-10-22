#pragma once

#include "GameApp.h"
#include "TestGameWorld.h"
#include "TestGraphicsComponent.h"

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

    TestGameWorld gameWorld;
    GameObject gameObject;

    TestGraphicsComponent graphicsComponent;
};
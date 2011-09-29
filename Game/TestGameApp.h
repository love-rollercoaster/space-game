#pragma once

#include "GameApp.h"
#include "GameObject.h"
#include "TestGameWorld.h"
#include "BlockGraphicsComponent.h"
#include "TestInputComponent.h"
#include "BlockGroup.h"

class TestGameApp : public GameApp
{
public:
    TestGameApp(void);
    ~TestGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    TestGameWorld testGameWorld;
    BlockGraphicsComponent testGraphicsComponent; // TODO: replace when graphics component system is done.
    TestInputComponent testInputComponent;

    void initComponents(GameEngine &gameEngine);
    void initGraphicsComponents(GraphicsEngine &graphicsEngine);
};


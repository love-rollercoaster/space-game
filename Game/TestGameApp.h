#pragma once

#include "GameApp.h"
#include "GameObject.h"
#include "TestGameWorld.h"
#include "TestGraphicsComponent.h"
#include "TestInputComponent.h"

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
    TestGraphicsComponent testGraphicsComponent; // TODO: replace when graphics component system is done.
    TestInputComponent testInputComponent;

    void initComponents(GameEngine &gameEngine);
    void initGraphicsComponents(GraphicsEngine &graphicsEngine);
};


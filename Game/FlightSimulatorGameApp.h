#pragma once

#include "GameApp.h"
#include "TestGameWorld.h"
#include "MeshSurfaceGraphicsComponent.h"

class FlightSimulatorGameApp : public GameApp
{
public:
    FlightSimulatorGameApp(void);
    ~FlightSimulatorGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    void initComponents(GameEngine &gameEngine);
    void initGraphicsComponents(GraphicsEngine &graphicsEngine);

    TestGameWorld gameWorld;
    GameObject gameObject;

    MeshSurfaceGraphicsComponent graphicsComponent;
};
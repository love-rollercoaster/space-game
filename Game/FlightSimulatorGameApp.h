#pragma once

#include "GameApp.h"
#include "TestGameWorld.h"

class FlightSimulatorGameApp : public GameApp
{
public:
    FlightSimulatorGameApp(void);
    ~FlightSimulatorGameApp(void);

    void init(GameEngine &gameEngine);
    void update(time_t time);
    void draw(GraphicsEngine &graphicsEngine);

private:
    TestGameWorld gameWorld;
};
#pragma once

#include "GameApp.h"
#include "AsteroidsGameWorld.h"

class FlightSimulatorGameApp : public GameApp
{
public:
    FlightSimulatorGameApp(void);
    ~FlightSimulatorGameApp(void);

    void init(GameEngine &gameEngine);
    void update(float time);
    void draw(GraphicsEngine &graphicsEngine);
    virtual void registerKeyboardInputCallbacks();
    virtual void handleSpacePress(unsigned char key);
    virtual void handleCommaPress(unsigned char key);
    virtual void handlePeriodPress(unsigned char key);
    virtual void handleSlashPress(unsigned char key);
    virtual void handle1KeyPress(unsigned char key);
    virtual void handle3KeyPress(unsigned char key);

private:
    AsteroidsGameWorld gameWorld;
    GameObject gameObject;
};
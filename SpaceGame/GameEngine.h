#pragma once

#include "GraphicsEngine.h"
#include "GameApp.h"

#define TARGET_FRAMERATE 60 // Maybe extract this to a parameter
class GameEngine
{
public:
    // Does not take ownership of sub-components
    GameEngine(GameApp &gameApp, GraphicsEngine &graphicsEngine);
    ~GameEngine(void);

    WPARAM startGameLoop();

private:
    const time_t TIME_PER_FRAME;

    MSG getMessage();
    void updateGameState(time_t time);

    GraphicsEngine &graphicsEngine;
    GameApp &gameApp;
};
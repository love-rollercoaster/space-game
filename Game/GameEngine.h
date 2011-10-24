#pragma once

#include "GraphicsEngine.h"

class GameApp;

#define TARGET_FRAMERATE 60 // Extract into some kind of 'display' class.

class GameEngine
{
public:
    GameEngine(GameApp &gameApp, GraphicsEngine &graphicsEngine);
    ~GameEngine(void);

    WPARAM startGameLoop();

    GraphicsEngine& getGraphicsEngine();

private:
    const float TIME_PER_FRAME;

    MSG getMessage();
    void updateGameState(float time);

    GraphicsEngine &graphicsEngine;
    GameApp &gameApp;
};
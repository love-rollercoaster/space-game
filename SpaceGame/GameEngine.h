#pragma once

#include "graphicsengine.h"
// #include "inputservice.h"

class GameEngine
{
public:
    GameEngine(void);
    ~GameEngine(void);

private:
    // DisplaySystem displaySystem;
    GraphicsEngine graphicsEngine;
    // InputHandler inputHandler;
};
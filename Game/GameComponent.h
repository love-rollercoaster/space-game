#pragma once

class GameEngine;

class GameComponent
{
public:
    virtual ~GameComponent() {}
    virtual void init(GameEngine &gameEngine) = 0;
};


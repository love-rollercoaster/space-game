#pragma once

#include "GameComponent.h"
#include "GameEngine.h"

class GraphicsEngine;
class GameObject;

class GraphicsComponent
    : public GameComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void init(GameEngine &gameEngine) {
        return init(gameEngine.getGraphicsEngine());
    }

    virtual void init(GraphicsEngine &graphicsEngine) = 0;
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine) = 0;
};

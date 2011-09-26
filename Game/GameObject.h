#pragma once

#include <time.h>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class GraphicsEngine;

// This class should not take ownership of its components.
class GameObject
{
public:
    GameObject(InputComponent* inputComponent,
               PhysicsComponent* physicsComponent,
               GraphicsComponent* graphicsComponent)
        : inputComponent(inputComponent)
        , physicsComponent(physicsComponent)
        , graphicsComponent(graphicsComponent)
    {
    }

    virtual void update(time_t time)
    {
        if (inputComponent != NULL)
            inputComponent->update(*this, time);

        if (physicsComponent != NULL)
            physicsComponent->update(*this, time);
    };

    virtual void draw(GraphicsEngine &graphicsEngine)
    {
        if (graphicsComponent != NULL)
            graphicsComponent->draw(*this, graphicsEngine);
    };

private:
    InputComponent* inputComponent;
    PhysicsComponent* physicsComponent;
    GraphicsComponent* graphicsComponent;
};

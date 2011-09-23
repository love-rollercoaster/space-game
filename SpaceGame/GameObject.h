#pragma once

#include <time.h>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class GraphicsEngine;

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
        inputComponent->update(*this, time);
        physicsComponent->update(*this, time);
    };

    virtual void draw(GraphicsEngine &graphicsEngine)
    {
        graphicsComponent->draw(*this, graphicsEngine);
    };

private:
    InputComponent* inputComponent;
    PhysicsComponent* physicsComponent;
    GraphicsComponent* graphicsComponent;
};

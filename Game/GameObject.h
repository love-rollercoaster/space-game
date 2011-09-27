#pragma once

#include <time.h>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class GraphicsEngine;

// Does not take ownership of components.
class GameObject
{
public:
    GameObject(void)
        : inputComponent(NULL)
        , physicsComponent(NULL)
        , graphicsComponent(NULL)
    {
    }

    virtual void init(InputComponent* inputComponent,
                      PhysicsComponent* physicsComponent,
                      GraphicsComponent* graphicsComponent)
    {
        this->inputComponent = inputComponent;
        this->graphicsComponent = graphicsComponent;
        this->physicsComponent = physicsComponent;
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

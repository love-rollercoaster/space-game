#pragma once

#include <list>
#include <memory>
#include <time.h>
#include <d3dx9.h>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class GraphicsEngine;

using std::tr1::shared_ptr;

// Does not take ownership of components.
class GameObject
{
public:
    GameObject(void)
        : inputComponent(NULL)
        , physicsComponent(NULL)
        , graphicsComponent(NULL)
        , drawn(true)
    {
    }

    virtual ~GameObject(void) {}

    virtual void init(shared_ptr<InputComponent> inputComponent,
                      shared_ptr<PhysicsComponent> physicsComponent,
                      shared_ptr<GraphicsComponent> graphicsComponent)
    {
        this->inputComponent = inputComponent;
        this->graphicsComponent = graphicsComponent;
        this->physicsComponent  = physicsComponent;
    }

    virtual void update(float time)
    {
        // if (inputComponent)
        //     inputComponent->update(*this, time);

        if (physicsComponent) {
            physicsComponent->update(*this, time);
        }
    }

    virtual void draw(GraphicsEngine &graphicsEngine)
    {
        if (drawn && graphicsComponent) {
            graphicsComponent->draw(*this, graphicsEngine);
        }
    }

    virtual void setDrawn(bool toBeDrawn) {
        drawn = toBeDrawn;
    }

    shared_ptr<GraphicsComponent> getGraphicsComponent() {
        return graphicsComponent;
    }

protected:
    bool drawn;
    shared_ptr<InputComponent>    inputComponent;
    shared_ptr<PhysicsComponent>  physicsComponent;
    shared_ptr<GraphicsComponent> graphicsComponent;
};

#pragma once

#include <string>
#include <list>
#include <time.h>
#include <d3dx9.h>
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
// #include "Property.h"

class GraphicsEngine;

using std::string;

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

    virtual ~GameObject(void) {}

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
        // if (inputComponent != NULL)
        //     inputComponent->update(*this, time);

        if (physicsComponent != NULL) {
            physicsComponent->update(*this, time);
        }
    }

    virtual void draw(GraphicsEngine &graphicsEngine)
    {
        if (graphicsComponent != NULL) {
            graphicsComponent->draw(*this, graphicsEngine);
        }
    }

/*
    Property getProperty(string propertyName)
    {
        PropertyMap::iterator propertyMapIterator = propertyMap.find(propertyName);

        if (propertyMapIterator != propertyMap.end()) {
            return propertyMapIterator->second;
        } else {
            // FIXME: Throw a better exception here.
            throw "Can't find property!";
        }
    }
*/

private:
    // typedef std::map<string, Property> PropertyMap;
    // typedef std::pair<string, Property> PropertyPair;
    // PropertyMap propertyMap;

    InputComponent* inputComponent;
    PhysicsComponent* physicsComponent;
    GraphicsComponent* graphicsComponent;
};

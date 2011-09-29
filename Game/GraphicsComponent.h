#pragma once

#include <string>

class GraphicsEngine;
class GameObject;

using std::string;

class GraphicsComponent
{
public:
    GraphicsComponent(string type)
        : TYPE(type)
    {
    }

    virtual void init(GraphicsEngine &graphicsEngine) = 0;
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine) = 0;

    virtual string getType() {
        return this->TYPE;
    }

private:
    const string TYPE;
};

#pragma once

class GameObject;
class GraphicsEngine;

class GraphicsComponent
{
public:
    virtual void init(GraphicsEngine &graphicsEngine) = 0;
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine) = 0;
};

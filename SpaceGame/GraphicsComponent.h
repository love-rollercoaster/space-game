#pragma once

class GameObject;
class GraphicsEngine;

class GraphicsComponent
{
public:
    GraphicsComponent(void);
    ~GraphicsComponent(void);

    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine) = 0;
};


#pragma once

#include "GraphicsComponent.h"

class TeapotGraphicsComponent
    : public GraphicsComponent
{
public:
    TeapotGraphicsComponent(void);
    ~TeapotGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH teapot;
};


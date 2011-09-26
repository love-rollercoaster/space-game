#pragma once

#include "GraphicsComponent.h"
#include "GraphicsEngine.h"

class TestGraphicsComponent :
    public GraphicsComponent
{
public:
    TestGraphicsComponent(void);
    ~TestGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
};

#pragma once

#include <string>
#include "GraphicsComponent.h"
#include "GraphicsEngine.h"

using std::string;

class TestGraphicsComponent :
    public GraphicsComponent
{
public:
    TestGraphicsComponent(void);

    void init(GraphicsEngine &graphicsEngine);
    void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    static const string TYPE;
};
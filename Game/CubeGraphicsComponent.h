#pragma once

#include <d3dx9.h>
#include <vector>
#include "GraphicsComponent.h"
#include "Cube.h"

using std::vector;

class CubeGraphicsComponent
    : public GraphicsComponent
{
public:
    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    virtual void initVertexBuffer(GraphicsEngine &graphicsEngine);
    virtual void initIndexBuffer(GraphicsEngine &graphicsEngine);

    virtual void performWorldTransformations(GameObject &gameObject, GraphicsEngine &graphicsEngine);

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};
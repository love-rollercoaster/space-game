// Reference
// http://www.gameengineer.net/samples-graphics.html

#pragma once

#include "Camera.h"

class GraphicsEngine;

class Skybox
{
public:
    Skybox(void);
    ~Skybox(void);

    struct TexturedVertex
    {
        D3DXVECTOR3 position;
        D3DXVECTOR2 texture;
    };

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(Camera &camera, GraphicsEngine &graphicsEngine);

protected:
    virtual void initVertexBuffer(GraphicsEngine &graphicsEngine);
    virtual void initTexture(GraphicsEngine &graphicsEngine);

    virtual void performWorldTransformations(Camera &camera, GraphicsEngine &graphicsEngine);

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9 texture[6];
    LPDIRECT3DINDEXBUFFER9 indexBuffer;
};


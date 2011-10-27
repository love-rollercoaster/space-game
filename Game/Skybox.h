// Reference
// http://www.gameengineer.net/samples-graphics.html

#pragma once

#include <d3dx9.h>
#include "SceneryElement.h"

class Camera;
class GraphicsEngine;

class Skybox
    : public SceneryElement
{
public:
    Skybox(void);
    ~Skybox(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(Camera &camera, GraphicsEngine &graphicsEngine);

protected:
    virtual void initVertexBuffer(GraphicsEngine &graphicsEngine);
    virtual void initTexture(GraphicsEngine &graphicsEngine);

    virtual void performWorldTransformations(Camera &camera, GraphicsEngine &graphicsEngine);

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9      texture[6];
    LPDIRECT3DINDEXBUFFER9  indexBuffer;
};


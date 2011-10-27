#pragma once

#include <d3dx9.h>
#include "SceneryElement.h"

class EarthSceneryElement
    : public SceneryElement
{
public:
    EarthSceneryElement(void);
    ~EarthSceneryElement(void);

    void init(GraphicsEngine &graphicsEngine);
    void draw(Camera &camera, GraphicsEngine &graphicsEngine);

private:
    void initVertexBuffer(GraphicsEngine &graphicsEngine);
    void initTexture(GraphicsEngine &graphicsEngine);
    void performWorldTransformations(Camera &camera, GraphicsEngine &graphicsEngine);

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9 texture;
};


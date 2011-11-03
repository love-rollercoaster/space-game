#pragma once

#include <d3dx9.h>
#include "SceneryElement.h"

#define EARTH_POS D3DXVECTOR3(0.0f, 0.0f, -15000.0f)
#define EARTH_RADIUS 10000.0f

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

    static float Z_CAMERA_POSITION_MULTIPLIER;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9 texture;
};


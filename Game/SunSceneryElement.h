#pragma once

#include <d3dx9.h>
#include "SceneryElement.h"
#define SUN_POS D3DXVECTOR3(0.0f, 10.0f, 0.0f)
#define SUN_RADIUS 10.0f

class SunSceneryElement
    : public SceneryElement
{
public:
    SunSceneryElement(void);
    ~SunSceneryElement(void);

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


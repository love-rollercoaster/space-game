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

    static D3DXVECTOR3 GetPosition();

private:
    static float EARTH_RADIUS;
    static D3DXVECTOR3 EARTH_POSITION;

    void initVertexBuffer(GraphicsEngine &graphicsEngine);
    void initTexture(GraphicsEngine &graphicsEngine);
    void performWorldTransformations(Camera &camera, GraphicsEngine &graphicsEngine);

    static float Z_CAMERA_POSITION_MULTIPLIER;

    LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
    LPDIRECT3DTEXTURE9 texture;
};
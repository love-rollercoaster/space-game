#pragma once

#include <d3dx9.h>
#include "GraphicsComponent.h"

class GameObject;
class GameEngine;
class GraphicsEngine;

class VolumetricLines
    : public GraphicsComponent
{
public:
    VolumetricLines(void);
    ~VolumetricLines(void);

    // The vertex structure we'll be using for line drawing. Each line is defined as two vertices,
    // and the vertex shader will create a quad from these two vertices. However, since the vertex
    // shader can only process one vertex at a time, we need to store information in each vertex
    // about the other vertex (the other end of the line).
    struct Vertex
    {
        D3DXVECTOR3 pos;
        D3DXVECTOR3 otherPos;
        D3DXVECTOR4 texOffset;
        D3DXVECTOR3 thickness;
        static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL |
            D3DFVF_TEX2 |               // D3DFVF_TEX2 specifies we have two sets of texture coordinates.
            D3DFVF_TEXCOORDSIZE4(0) |   // This specifies that the first (0th) tex coord set has size 4 floats.
            D3DFVF_TEXCOORDSIZE3(1);    // Specifies that second tex coord set has size 2 floats.
    };
   
    void init( GraphicsEngine &graphicsEngine );
    void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

private:
    LPDIRECT3DTEXTURE9 texture;
    LPD3DXEFFECT effect;

    void initVertices();
    void initTexture(GraphicsEngine &graphicsEngine);
    void initEffect(GraphicsEngine &graphicsEngine);
    void initTextures(GraphicsEngine &graphicsEngine);

    void drawLine(GraphicsEngine &graphicsEngine, D3DXVECTOR3 u, D3DXVECTOR3 v);

    LPD3DXMESH laserMesh;
    D3DMATERIAL9 material;
};


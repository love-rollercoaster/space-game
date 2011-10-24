#pragma once
#include "graphicscomponent.h"
#include "Obstacle.h"
#include "Log.h"

class SpaceshipGraphicsComponent :
    public GraphicsComponent
{
public:
    SpaceshipGraphicsComponent(void);
    ~SpaceshipGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH spaceshipMesh;
    D3DMATERIAL9* material;
    LPDIRECT3DTEXTURE9 texture;
    DWORD numMaterials;
};
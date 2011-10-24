#pragma once
#include "graphicscomponent.h"
#include "Obstacle.h"
#include "Log.h"

class AsteroidGraphicsComponent :
    public GraphicsComponent
{
public:
    AsteroidGraphicsComponent(void);
    ~AsteroidGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH asteroidMesh;
    D3DMATERIAL9* materials;
    LPDIRECT3DTEXTURE9 *texture;
    DWORD numMaterials;
};


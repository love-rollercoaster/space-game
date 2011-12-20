#pragma once
#include "graphicscomponent.h"
#include "Log.h"
#include "Laser.h"

class LaserGraphicsComponent :
    public GraphicsComponent
{
public:
    LaserGraphicsComponent(void);
    ~LaserGraphicsComponent(void);

    virtual void init(GraphicsEngine &graphicsEngine);
    virtual void draw(GameObject &gameObject, GraphicsEngine &graphicsEngine);

protected:
    LPD3DXMESH outerLaserMesh;
    LPD3DXMESH innerLaserMesh;
    D3DMATERIAL9 outerLaserMaterial;
    D3DMATERIAL9 innerLaserMaterial;
    static const float LASER_RADIUS;
    static const float LASER_LENGTH;

private:


};

